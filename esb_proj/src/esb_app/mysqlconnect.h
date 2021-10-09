// #pragma once
// #ifndef HEADER_FILE
// #define HEADER_FILE
// #include <stdio.h>
// #include <stdlib.h>
#include <mysql/mysql.h>
#include "esb.h"
// #include <string.h>

// unsigned int port = 3306; // active port in which mysql is running.
// static char *unix_socket = NULL;
// unsigned int flag = 0; //it behaves like ODBC connection.
// typedef struct
// {
//     char *MessageID;
//     char *Sender;
//     char *Destination;
//     char *MessageType;
//     char *Payload;
//     char *ReferenceID;
// } message_data; //It is used to return the entire data that we have mentioned in the struct after parsing.

void insert(MYSQL *con, bmd *msg, char *filename);
void validation(MYSQL *con, bmd *msg, char *file);
MYSQL *connect_mysql();
// #endif
