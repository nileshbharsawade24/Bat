#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>
static char *host = "localhost";
static char *user = "root";
static char *pass = "Nilesh@024";
static char *dbname = "pavan";

typedef struct {
    char *MessageID;
    char *Sender;
    char *Destination;
    char *MessageType;
    char *Payload;
    char *ReferenceID;
}message_data;

void insert(MYSQL* con, message_data *msg);

MYSQL* connect_mysql();
