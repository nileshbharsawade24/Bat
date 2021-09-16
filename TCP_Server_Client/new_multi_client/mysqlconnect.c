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
int main(){
 
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *temp,*temp2,*temp3;
	char *sender="756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA";
	char *destination="6393F82F-4687-433D-AA23-1966330381FE";
	char *message_type="CreditReport";

	con= mysql_init(NULL);// this fun initalizes the headerfiles i.e mysql.h
	
	if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))//this is the real fun which connects to the mysql-server.
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	
	printf("Connected to mysql-server\n");
	printf("\n");
		
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
	}
	
	if((strcmp(sender,temp)==0)&&(strcmp(destination,temp2)==0)&&(strcmp(message_type,temp3)==0))
	{
		printf("[+] VALIDATION IS OK\n");
	}
	else
	{
		printf("[-] Error Something went wrong in validation\n");
	}
	
	mysql_free_result(res);
	mysql_close(con);
	return 0;
}


	






