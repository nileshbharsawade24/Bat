#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>
static char *host = "localhost";
static char *user = "root";
static char *pass = "Prideoflion@01";
static char *dbname = "pavan";

unsigned int port =3306;// active port in which mysql is running.
static char *unix_socket= NULL;
unsigned int flag=0;  //it behaves like ODBC connection.

//struct for input message body and metadata
typedef struct {
    char *MessageID;
    char *Sender;
    char *Destination;
    char *MessageType;
    char *Payload;
    char *ReferenceID;
}message_data;

 /* fuction to insert the data to mysql*/

void insert(MYSQL* con, message_data *msg,char *filename){
			 
	char* q = (char *) malloc (500);
	q[0]='\0';
	strcat(q,"insert into esb_request(sender_id,dest_id, message_id, message_type,data_location,status,status_details,reference_id,received_on) values ('");
	strcat(q, msg->Sender);
	strcat(q, "', '");
	strcat(q,msg->Destination);
	strcat(q, "', '");
	strcat(q,msg->MessageID);
	strcat(q, "', '");
	strcat(q, msg->MessageType);
	strcat(q, "', '");
	strcat(q, "/home/pavankolur/Bat/TCP_Server_Client/new_multi_client/");
	strcat(q, "', '");
	strcat(q, "Received");
	strcat(q, "', '");
	strcat(q, "Available");
	strcat(q, "', '");
	strcat(q, msg->ReferenceID);
	strcat(q, "', ");
	strcat(q, "now()");
	strcat(q, " )");
	if(mysql_query(con,q)){
	fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
	 exit(1);
	 }
	q=NULL;
			
        }

 /* mysql server connection and validation of BMD file*/

MYSQL* connect_mysql(){
	MYSQL *con;
	
	char *temp,*temp2,*temp3;

	con= mysql_init(NULL);// this fun initalizes the headerfiles i.e mysql.h
	
	if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))//this is the real fun which connects to mysql-server.
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	
	printf("Connected to mysql-server\n");
	printf("\n");
	return con;
}
	
 /*validation of BMD*/
	
void validation(MYSQL* con,message_data *msg,char *file){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *temp,*temp2,*temp3;
	if((mysql_query(con,"select *from routes"))){
			fprintf(stderr,"ERROR: %s [%d]\n",mysql_error(con),mysql_errno(con));
			exit(1);
	}

	res = mysql_store_result(con);
	
	while(row=mysql_fetch_row(res))
	{
		//printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
	
		temp=row[1];
		temp2=row[2];
		temp3=row[3];
		if((strcmp(msg->Sender,temp)==0)&&(strcmp(msg->Destination,temp2)==0)&&(strcmp(msg->MessageType,temp3)==0))
        	{
                	printf("[+] VALIDATION IS OK\n");
			flag=1;
			
			insert(con,msg,file);
			
			printf("Data inserted to esb_request table.\n");
        		break;
   	
 		}
 	}
	
	if(flag==0){
		printf("[-] Error Something went wrong in validation\n");
		exit(1);
		}
	
}






