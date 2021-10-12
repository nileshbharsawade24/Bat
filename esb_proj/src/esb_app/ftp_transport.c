#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include "netinet/in.h"
#include "netdb.h"
#include <unistd.h>
#include <netinet/in.h>
#include <stdbool.h>
// #include "ftp_transport.h"

#define PORT 4445
#define BUF_SIZE 2000
#define SIZE 1024

bool ftp(char *hostname_or_ip, char* username, char* password, char *filename, char* token){
    if(!hostname_or_ip || !username || !password || !filename || !token)return false;
    char * dump_fname=malloc(200*sizeof(char));
    if(sprintf(dump_fname,"./.transport_dump/SFTP_%s_%s_%s_%s.csv",hostname_or_ip,username,password,token)>199){
      return false;
    }
    // Open another file for read and one for write
    FILE * f_r=fopen(filename,"r");
    FILE * f_w=fopen(dump_fname,"w");

    if (f_r == NULL || f_w==NULL)return false;

    // Read contents from file
    char c = fgetc(f_r);
    while (c != EOF)
    {
        fputc(c,f_w);
        c = fgetc(f_r);
    }
    fclose(f_w);
    fclose(f_r);
    return true;
}
 /*int main(int argc, char **argv)
 {
     ftp("BMD.xml","127.0.0.1");
 }*/
