#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>
#include<pthread.h>
static char *host = "localhost";
static char *user = "root";
static char *pass = "Prideoflion@01";
static char *dbname = "pavan";
unsigned int port =3306;// active port in which mysql is running.
static char *unix_socket= NULL;
unsigned int flag=0; 
MYSQL *con;
MYSQL_RES *res;
MYSQL_ROW row;
char *status;
char *id;
int attempts;
 void* child_thread(char *id){
	printf("Child thread started to process the received BMD request\n");
	
	  char p[20000];
	  snprintf(p,sizeof(p),"update esb_request set status='Taken',processing_attempts=processing_attempts+1 where id=%s",id);
	  
	  	//printf("%s\n",p);
	  if(mysql_query(con,p)){fprintf(stderr,"ERROR: %s [%d]\n",mysql_error(con),mysql_errno(con));
			exit(1);}
	  
	  printf("\n************** Status Updated Sucessfully at id=%s ****************\n\n",id);
	  
	  p[20000]='\0';
	  //return 0;
	  }

void start_esb_request_poller_thread(){
pthread_t childthread;
//mysql_data *data;

	while(true){
		if((mysql_query(con,"select *from esb_request where (status = 'Available' && processing_attempts <5) limit 1"))){
			fprintf(stderr,"ERROR: %s [%d]\n",mysql_error(con),mysql_errno(con));
			exit(1);}
		
		res = mysql_store_result(con);
	
		
	 	while(row=mysql_fetch_row(res))
	  	{
	 	for(int i=0;i<=10;i++){
	 	
			//printf("%s | ",row[i]);
			if(i==10){
				id=row[0];
				status=row[8];
				attempts=row[10];}
				
			}
		}
		
		//printf("\n%s\n%s\n%s\n",temp1,temp2,temp3);
			
			if(status!='\0')
			{
				printf("\nReceived New BMD request, Ready to process the BMD.\n");
				if(pthread_create(&childthread,NULL,&child_thread,id)){
				printf("unable to create the Childthread\n");}
				//child_thread(id);
				status='\0';
				
				//pthread_join(&childthread,NULL);	
 	  		}
 	  	 		else{printf("\n****************** No Request Available in esb_request.*******************\n");}
 	  	
 		printf("\n");
 		sleep(5);
 	 
 	 }
 		
 }
int main(int argc,char *argv[]){
	
	pthread_t t1;
	
	con= mysql_init(NULL);// this fun initalizes the headerfiles i.e mysql.h
	
	if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))//this is the real fun which connects to mysql-server.
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	
	printf("Connected to mysql-server\n");
	if(pthread_create(&t1,NULL,&start_esb_request_poller_thread,NULL)){
	 	printf("unable to create the thread\n");}
	 	pthread_join(&t1,NULL);
	
 		mysql_close(con);
 		return 0;
 	}

	
