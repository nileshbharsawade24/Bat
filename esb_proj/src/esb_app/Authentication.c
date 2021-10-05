/*command to run 
gcc -o aut Authentication.c $(mysql_config --cflags --libs)
run ./aut
*/
#include"Authentication.h"

void Authentication(char *sign)
{
	MYSQL *con;
	MYSQL_RES *res;
    MYSQL_ROW row;
    char *temp;
	//char *temp,*temp2,*temp3;

	con= mysql_init(NULL);// this fun initalizes the headerfiles i.e mysql.h
	
	if(!(mysql_real_connect(con,host,user,pass,dbname,port1,unix_socket1,flag1)))//this is the real fun which connects to mysql-server.
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	
	printf("Connected to mysql-server\n");
	printf("\n");
	char z[1001];
   
    
    snprintf(z,sizeof(z),"select count(id) from auth where signature='%s'",sign);
    if((mysql_query(con,z))){
			fprintf(stderr,"ERROR: %s [%d]\n",mysql_error(con),mysql_errno(con));
			exit(1);
	}
	res = mysql_store_result(con);
    while(row=mysql_fetch_row(res))
    { 
    	temp=row[0];
    }
    
    //printf("row=%s\n",temp);
    if(strcmp(temp,"0")==0)
    { 
    	printf("Authentication Failed\n");
    }
    else
    {
    	printf("Authentication Successfull.\n");
    }
}
/*void main (){
 Authentication("63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
 }*/
