#include"threads.h"
#include"status.h"

void status_done(char *id)
{
 
 char done[20001];
 snprintf(done,sizeof(done),"update esb_request set status='Done',status_details='Sucessfully reached the dest' where id=%s",id);
 if (mysql_query(con, done))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	printf("********|\"Status Updated to Done\"|*****\n");
}

