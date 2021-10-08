#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>
#include <unistd.h>
#include "mysqlconnect.h"

#define MAX_RETRY_FOR_GETTING_MYSQL_CONNECTION 5
#define host "localhost"
#define user "test_user"
#define pass "test_password"
#define dbname "BAT_DB"

// //struct for input message body and metadata
// typedef struct
// {
// 	char *MessageID;
// 	char *Sender;
// 	char *Destination;
// 	char *MessageType;
// 	char *Payload;
// 	char *ReferenceID;
// } message_data;

/* fuction to insert the data to mysql*/

void insert(MYSQL *con, message_data *msg, char *filename)
{

	char *q = (char *)malloc(500); // memory allocation to string query which nis going to be concated tor insert query
	q[0] = '\0';
	strcat(q, "insert into esb_request(sender_id,dest_id, message_id, message_type,data_location,status,status_details,reference_id,received_on) values ('");
	strcat(q, msg->Sender);
	strcat(q, "', '");
	strcat(q, msg->Destination);
	strcat(q, "', '");
	strcat(q, msg->MessageID);
	strcat(q, "', '");
	strcat(q, msg->MessageType);
	strcat(q, "', './");
	//strcat(q, "./");
	strcat(q, filename);
	strcat(q, "', '");
	strcat(q, "Available");
	strcat(q, "', '");
	strcat(q, "Yet to process");
	strcat(q, "', '");
	strcat(q, msg->ReferenceID);
	strcat(q, "', ");
	strcat(q, "now()");
	strcat(q, " )");
	if (mysql_query(con, q))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	q = NULL; // Free the allocated memory
}

/* mysql server connection and validation of BMD file*/

// establish connection with returning MYSQL Type(Struct)
MYSQL *connect_mysql()
{
  MYSQL *connection = mysql_init(NULL);
  if (connection == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(connection));
      exit(1);
  }
  for(int i=0;i<MAX_RETRY_FOR_GETTING_MYSQL_CONNECTION;i++){
    if(mysql_real_connect(connection, host, user, pass,
            dbname, 0, NULL, 0)!=NULL){
      break;
    }
    else if(i+1==MAX_RETRY_FOR_GETTING_MYSQL_CONNECTION){
      fprintf(stderr, "ERROR : You are not getting MySQL connection even after trying for %d times.\n",
              MAX_RETRY_FOR_GETTING_MYSQL_CONNECTION);
      break;
    }
    else{
      sleep(1);
    }
  }
  return connection;
}

/*validation of BMD*/

void validation(MYSQL *con, message_data *msg, char *file)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *temp, *temp2, *temp3;
	if ((mysql_query(con, "select *from routes")))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	//printf("yes=:%s\n",file);
	res = mysql_store_result(con);
	int flag=0;
	while (row = mysql_fetch_row(res)) // this is used to fetch each column.
	{

		if ((strcmp(msg->Sender, row[1]) == 0) && (strcmp(msg->Destination, row[2]) == 0) && (strcmp(msg->MessageType, row[3]) == 0))
		{
			printf("[+] VALIDATION IS OK\n");
			flag = 1;

			insert(con, msg, file);

			printf("Data inserted to esb_request table.\n");
			printf("**************************************\n\n");
			break;
		}
	}

	if (flag == 0)
	{
		printf("[-] Error Something went wrong in validation\n");
		exit(1);
	}
}
