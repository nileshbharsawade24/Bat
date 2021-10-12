/*command to run
gcc -o aut Authentication.c $(mysql_config --cflags --libs)
run ./aut
*/
#include "mysqlconnect.h"
#include "Authentication.h"

bool Authentication(char *sign)
{
	MYSQL *con=connect_mysql();
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *temp;
	//char *temp,*temp2,*temp3;

	// printf("Connected to mysql-server\n");
	// printf("\n");
	char z[1001];

	snprintf(z, sizeof(z), "select count(id) from auth where signature='%s'", sign);
	if ((mysql_query(con, z)))
	{
		return false;
	}
	res = mysql_store_result(con);
	while (row = mysql_fetch_row(res))
	{
		temp = row[0];
	}

	//printf("row=%s\n",temp);
	if (strcmp(temp, "0") == 0)
	{
		// printf("[-] Authentication Failed\n");
		return false;
	}
	else
	{
		// p/rintf("[+] Authentication Successfull.\n");
		return true;
	}
}
/*void main (){
 Authentication("63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
 }*/
