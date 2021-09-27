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
/*typedef struct {
 	char *status;
 	char *id;
 	char *pro_atmpts;
}mysql_data;*/
char *temp2;
char *temp1;
int temp3;
 int child_thread(char *temp1, char *temp2, int temp3){
	printf("Child thread started to process the received BMD request\n");
	  //mysql_data->status="Taken";
	  //data->pro_atmpts++;
	//temp3++;
	  
	  //printf("%d",temp3);
	  char* p = (char *) malloc (500);
	p[0]='\0';
	  strcat(p,"update esb_request set status='Taken',processing_attempts=2");
	  
	  strcat(p," where id=18;");
	  
	  	
	  if(mysql_query(con,p)){fprintf(stderr,"ERROR: %s [%d]\n",mysql_error(con),mysql_errno(con));
			exit(1);}
	  
	  printf("updated to Taken at id = %s\n",temp1);
	  p=NULL;
	  return 0;
	  }

void start_esb_request_poller_thread(){
//pthread_t childthread;
//mysql_data *data;

	while(true){
		if((mysql_query(con,"select *from esb_request where (status = 'Available' && processing_attempts <5) limit 1"))){
			fprintf(stderr,"ERROR: %s [%d]\n",mysql_error(con),mysql_errno(con));
			exit(1);}
		
		res = mysql_store_result(con);
	
		
	 	while(row=mysql_fetch_row(res))
	  	{
	 	for(int i=0;i<=10;i++){
	 	
			printf("%s | ",row[i]);
			if(i==10){
				temp1=row[0];
				temp2=row[8];
				temp3=row[10];}
				
			}
		}
		
		//printf("\n%s\n%s\n%s\n",temp1,temp2,temp3);
			
			if(temp2!='\0')
			{
				printf("\nReceived New BMD request, Ready to process the BMD.\n");
				//pthread_create(&childthread,NULL,&child_thread,&data);
				child_thread(temp1,temp2,temp3);
				temp2='\0';
				
				//pthread_join(&childthread,NULL);	
 	  		}
 	  	 		else{printf("No Request Available.");}
 	  	
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

	
