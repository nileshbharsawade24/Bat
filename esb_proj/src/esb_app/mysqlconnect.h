// #pragma once
// #ifndef HEADER_FILE
// #define HEADER_FILE
// #include <stdio.h>
// #include <stdlib.h>
#include <mysql/mysql.h>
#include "esb.h"
// #include <string.h>


char* insert(MYSQL *con, bmd *msg, char *filename);
bool validation(MYSQL *con, bmd *msg, char *file);
MYSQL *connect_mysql();
// #endif
