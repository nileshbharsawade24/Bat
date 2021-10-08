#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include<unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 4444
#define BUF_SIZE 2000
#define SIZE 1024

void send_file(FILE *fp,int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }

}

int main(int argc, char**argv) {
 struct sockaddr_in addr, cl_addr;
 int sockfd, ret;
 char buffer[BUF_SIZE];
 struct hostent * server;
 char * serverAddr;
 FILE *fp;

 if (argc < 2) {
  printf("Enter the Filename :\n");
  exit(1);
 }

 serverAddr = "127.0.0.1";

 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Error creating socket!\n");
  exit(1);
 }
 printf("Socket created on PORT NUMBER %d ...\n",PORT);

 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = inet_addr(serverAddr);
 addr.sin_port = PORT;

 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) {
  printf("Error connecting to the server!\n");
  exit(1);
 }
 printf("Connected to the server...\n");

 memset(buffer, 0, BUF_SIZE);

//file as a i/p
  // printf("Enter Your file with absolute/relative path:");

  // char *string;
  // scanf("%s",&string);

  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }

  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");

  printf("[+]Closing the connection.\n");


  //here, for demo purpose it is alive until client closes it, otherwise no meaning
  // int x=0;
  // scanf("%d",x);
  //to here

  close(sockfd);

 return 0;
}
