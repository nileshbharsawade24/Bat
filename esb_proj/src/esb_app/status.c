#include "threads.h"
#include "status.h"
#include "mysqlconnect.h"

bool update_status(char *id, char* status,char * status_details)
{
	MYSQL *con = connect_mysql();
	char buff[20001];
	snprintf(buff, sizeof(buff), "update esb_request set status='%s',status_details='%s' where id=%s",status,status_details,id);
	if (mysql_query(con, buff))
	{
		mysql_close(con);
		return false;
	}
	mysql_close(con);
	return true;
	// printf("********|\"Status Updated to Done\"|*****\n");
}
