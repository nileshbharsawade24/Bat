#include<stdio.h>
#include<stdlib.h>
#include <mysql/mysql.h>
#include<string.h>


static char *host = "localhost";		// MySQL required variables
static char *user = "root";
static char *pass = "Prideoflion@01";
static char *dbname = "pavan";

unsigned int port1 =3306;// active port in which mysql is running.
static char *unix_socket1= NULL;
unsigned int flag1=0;
void Authentication(char *sign);
