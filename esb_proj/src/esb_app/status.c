#include "threads.h"
#include "status.h"
#include "mysqlconnect.h"

void update_status(char *id, char* status,char * status_details)
{
	MYSQL *con = connect_mysql();
	char buff[20001];
	snprintf(buff, sizeof(buff), "update esb_request set status='%s',status_details='%s' where id=%s",status,status_details,id);
	if (mysql_query(con, buff))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	// printf("********|\"Status Updated to Done\"|*****\n");
}
