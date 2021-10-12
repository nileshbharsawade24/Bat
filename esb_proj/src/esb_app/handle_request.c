#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include "netinet/in.h"
#include <pthread.h>
#include "mysqlconnect.h"
#include "xml_parsing.h"
#include <mysql/mysql.h>
#include <unistd.h>
#include "handle_request.h"
#include "Authentication.h"

#define PORT 8887
#define BUF_SIZE 2000
#define CLADDR_LEN 100
#define SIZE 1024
#define NUM_THREADS 5
// to write the file in temporary file in directory with return as that filename
char* write_file(int sockfd)
{
  int n;
  FILE *fp;
  char buffer[SIZE];
  //Create unique filename
  unsigned long tm=(unsigned long)time(NULL);
	char *filename = malloc(50 * sizeof(char));
	sprintf(filename, "./.tmp/BMD_%d_%lu.xml", sockfd, tm);
  fp = fopen(filename, "w"); //open that file

  struct timeval tv;
  tv.tv_sec=1; //2 second timer
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
  //usefull link : https://stackoverflow.com/questions/40493016/cant-receive-data-from-socket
  while(read(sockfd,buffer,SIZE)>=0){
    fprintf(fp, "%s", buffer);
  }
  fclose(fp);
  return filename;
}

void* serve(void * fd){
  int sockfd=*(int*)fd;
  char * filename = write_file(sockfd); //send to write the input file into directory and return that filename
  MYSQL *con = connect_mysql(); // establish connection between the MySql and server
  bmd *request_message = do_parse(filename); // parse that file into valid BMD format and return the BMD
  char * reply=malloc(500*sizeof(char));
  if(Authentication(request_message->envelop.Signature)){//function defination is in Authentication.c file
    //checking spcial case
    if(strcmp(request_message->envelop.Destination,"ESB")==0 && strcmp(request_message->envelop.MessageType,"CheckStatus")==0){
      char * query=malloc(100*sizeof(char));
      sprintf(query,"select status from esb_request where id=%s",request_message->envelop.ReferenceID);
      if (mysql_query(con, query)){
        printf("ERROR : unable to query `%s` database.\n",query);
      }
      MYSQL_RES *result_rows = mysql_store_result(con);
      MYSQL_ROW result_row=mysql_fetch_row(result_rows);
      mysql_close(con);
      char * temp;
      if(!result_row){
        temp="null";
      }
      else{
        temp=result_row[0]; //returning first row and first column value
      }
      sprintf(reply,"-----------------------------------------------------------------------\n"
                    "STATUS regarding ID %s -> %s.\n"
                    "-----------------------------------------------------------------------\n",request_message->envelop.ReferenceID,temp);
    }
    else{
      if(validation(con, request_message, filename)){ // Validation by using Validation Function Call
        char * correlation_id=insert(con, request_message, filename);
        // printf("-->%s\n",correlation_id);
        sprintf(reply,"-----------------------------------------------------------------------\n"
                      "REQUEST ACCEPTED.\n"
                      "\"%s\" is your Correlation Id to check the status later.\n"
                      "-----------------------------------------------------------------------\n",correlation_id);
      }
      else{
        sprintf(reply,"-----------------------------------------------------------------------\n"
                      "VALIDATION FAILED.\n"
                      "-----------------------------------------------------------------------\n");
      }
    }
  }
  else{
    sprintf(reply,"-----------------------------------------------------------------------\n"
                  "AUTHENTICATION FAILED.\n"
                  "-----------------------------------------------------------------------\n");

  }
  if(write(sockfd, reply, strlen(reply))<0){
    printf("ERROR : NOT sended\n");
  }
  free(reply);
  // mysql_close(con); // Closing Resources
  close(sockfd);
  printf("Closing Client Socket FD %d.\n",sockfd);
  printf("**************************************\n\n");
  pthread_exit(NULL);
}

void request_handler()
{
  //workflow starts here
  struct sockaddr_in addr, cl_addr; // Socket Variable declaration
  int sockfd, len, ret;  // Socket Variable declaration
  char buffer[BUF_SIZE];            // buffer size of declared BUF_SIZE
  pid_t childpid;                   // socket childpid
  char clientAddr[CLADDR_LEN];      // socket client address

  sockfd = socket(AF_INET, SOCK_STREAM, 0); // creating socket
  if (sockfd < 0)
  {
    printf("Error creating socket!\n");
    exit(1);
  }
  printf("Socket created...\n");

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0){
    fprintf(stderr,"ERROR : setsockopt(SO_REUSEADDR) failed\n");
  }

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
  printf("Binding done on PORT NUMBER %d ...\n",PORT);

  printf("Waiting for a connection...\n");
  listen(sockfd, NUM_THREADS); // Listening socket file discripter

  //defining thread
	pthread_t threads[NUM_THREADS];
  unsigned int count=0;
  len = sizeof(cl_addr);
  for (;;)
  { //infinite loop to listen continous connection made by client

    int * clientsockfd=malloc(sizeof(int));
    *clientsockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &len); // making connection
    if (*clientsockfd < 0)
    {
      printf("Error accepting connection!\n");  //when client closes, throws error accepting connection
      exit(1);
    }
    printf("Connection accepted for Client Socket FD %d.\n",*clientsockfd);

    // child thread will handle client
    if(pthread_create(&threads[count%NUM_THREADS],NULL,serve,clientsockfd)!=0){
			 printf ("ERROR: child thread not created\n");
			 exit(-1);
		}
    count++;
  }
  close(sockfd);
}
