#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>
#include <pthread.h>
#include "xml_parsing.h"
#include "transform.h"
#include <curl/curl.h>
#include "smtp.h"
// #define DETAILS "select sender_id,dest_id,message_type from esb_request where id=%s"
#define ROUTE_ID "select route_id from routes where sender='%s' && destination='%s' && message_type='%s'"

typedef struct
{
	char *key;
	char *value;
} _data; //struct for storing the data from transport_config table.

typedef struct _transport_data
{
	_data data;
	struct _transport_data * next;
} transport_data; //struct for storing the data from transport_config table.


typedef struct {
    char * id;
    char* fpath;
}task;//created this in order to pass two argument to child thread

void start_esb_request_poller_thread();
char *check_transform(bmd *msg);
transport_data* check_transport(bmd *msg);
