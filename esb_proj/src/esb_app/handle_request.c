#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include "netinet/in.h"
// #include "mysqlconnect.h"
#include "xml_parsing.h"
#include <mysql/mysql.h>
#include <unistd.h>
#include "handle_request.h"

#define PORT 4444
#define BUF_SIZE 2000
#define CLADDR_LEN 100
#define SIZE 1024

// to write the file in temporary file in directory with return as that filename
char *write_file(int sockfd)
{
  int n;
  FILE *fp;
  char buffer[SIZE];

  //Create unique filename
  char filename[] = "fileXXXXXX";
  mkstemp(filename);
  char *file = filename;
  fp = fopen(filename, "w"); //open that file
  while (1)
  {
    n = recv(sockfd, buffer, SIZE, 0); //n is number of bytes received or -1 if error occurs
    if (n <= 0)
    {
      break;
      // return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);

  return file;
}

void request_handler()
{                                   //workflow starts here
  struct sockaddr_in addr, cl_addr; // Socket Variable declaration
  int sockfd, len, ret, newsockfd;  // Socket Variable declaration
  char buffer[BUF_SIZE];            // buffer size of declared BUF_SIZE
  pid_t childpid;                   // socket childpid
  char clientAddr[CLADDR_LEN];      // socket client address
  char *filename;                   // filename to send in string

  sockfd = socket(AF_INET, SOCK_STREAM, 0); // creating socket
  if (sockfd < 0)
  {
    printf("Error creating socket!\n");
    exit(1);
  }
  printf("Socket created...\n");

  memset(&addr, 0, sizeof(addr)); // filling memory with a constant byte

  // assigning structure values
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = PORT;

  ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)); // binding socket
  if (ret < 0)
  {
    printf("Error binding!\n");
    exit(1);
  }
  printf("Binding done...\n");

  printf("Waiting for a connection...\n");
  listen(sockfd, 5); // Listening socket file discripter

  for (;;)
  { //infinite loop to listen continous connection made by client
    len = sizeof(cl_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &len); // making connection
    if (newsockfd < 0)
    {
      //    printf("Error accepting connection!\n");  //when client closes, throws error accepting connection
      exit(1);
    }
    printf("Connection accepted...\n");

    // inet_ntops(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN); //convert from an internet address in binary format
    if ((childpid = fork()) == 0)
    { //using fork, creates its another copy i.e. creating a child process
      printf("Child created\n");
      close(sockfd);
      printf("Main Terminated\n");

      //stop listening for new connections by the main process. the child will continue to listen.
      //the main process now handles the connected client.

      filename = write_file(newsockfd); //send to write the input file into directory and return that filename
                                        // char *file=filename;
      printf("Reading done..\n");
      message_data *request_message; // struct pointer of message_data type

      printf("Parsing the BMD file: %s\n\n", filename);
      request_message = do_parse(filename); // parse that file into valid BMD format and return the BMD

      MYSQL *con = connect_mysql(); // establish connection between the MySql and server
      printf("Validating BMD...\n");

      validation(con, request_message, filename); // Validation by using Validation Function Call

      mysql_close(con); // Closing Resources
    }
    close(newsockfd); // Closing Resources
  }
}
