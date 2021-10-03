#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>
static char *host = "localhost";
static char *user = "root";
static char *pass = "Prideoflion@01";
static char *dbname = "pavan";

typedef struct {
    char *MessageID;
    char *Sender;
    char *Destination;
    char *MessageType;
    char *Payload;
    char *ReferenceID;
}message_data;  //It is used to return the entire data that we have mentioned in the struct after parsing.


void insert(MYSQL* con, message_data *msg);

MYSQL* connect_mysql();
