#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>
#include <pthread.h>
#include"mysqlconnect.h"
#include"xml_parsing.h"
#include"transform.h"
#include <curl/curl.h>
#include "smtp.h"
#define DETAILS "select sender_id,dest_id,message_type from esb_request where id=%s"
#define ROUTE_ID "select route_id from routes where sender='%s' && destination='%s' && message_type='%s'"


MYSQL *con;
MYSQL_RES *res, *res2;
MYSQL_ROW row, row1;
char *status, *sender, *dest, *msg_type;
char *id, *route_id;
int attempts;


typedef struct
{
	char *transport_key;
	char *transport_value;
} transport; //struct for storing the data from transport_config table.
