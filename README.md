# Bat
ESB APP

# Installation required
    sudo apt update
    sudo apt install mysql-server
    sudo apt install libmysqlclient-dev
    sudo apt install libxml2-dev
    sudo apt install libcurl4-openssl-dev

Also make sure in your mysql server, there is a user with  name *test_user*, password *test_password* and have all access grant on *BAT_DB* database. One can do this with following steps:<br />
1. Open mysql promt with sudo privilege
    ```
    sudo mysql
    ```
2. Create a user *test_user* with password *test_password*
    ```
    CREATE USER 'test_user' IDENTIFIED BY 'test_password';
    ```
3. Create a database *BAT_DB*
    ```
    create database BAT_DB;
    ```
4. Grant all access on *BAT_DB* database to user *test_user*
    ```
    GRANT ALL ON BAT_DB.* TO 'test_user';
    ```

## HTTP api to test http_transport() external api (Reference)
    * https://reqbin.com/echo/post/json

### Setup database:
* you can find the SQL dump file "mysq_dump.sql" in main directory. Dump that using below command :<br/>
    ```
    mysql -u test_user -p BAT_DB < mysql_dump.sql
    ```
* OR use setup.c file. Go inside this path "esb_proj/src/esb_app/" and use below commands :<br/>
    ```
      make clean
      make setup
      ./setup
     ```


## Running ESB_APPLICATION
* Server
    * Go inside this path mentioned "esb_proj/src/esb_app/" and run server using below commands :<br/>
        ```
          make clean
          make server  
          ./server
        ```



* Client
    * Go inside this path mentioned "esb_proj/Test/Client/" and run client using below commands :<br/>
        ```
          chmod 777 run_client.sh
          ./run_client.sh
        ```

## UNIT TESTING
* Go inside this path mentioned "esb_proj/Test/Unit_test/" and run server using below commands :<br/>
    ```
      make clean
      make test
      ./test
     ```
* Report
  ```
  Running test suite with seed 0x77459755...
  /test_for_update_status_function     [ OK    ] [ 0.33539153 / 0.00659327 CPU ]
  /test_for_transform_to_json_function [ OK    ] [ 0.00081235 / 0.00081228 CPU ]
  /test_for_transform_to_csv_function  [ OK    ] [ 0.00079201 / 0.00079210 CPU ]
  /test_for_transform_to_html_function [ OK    ] [ 0.00084102 / 0.00084091 CPU ]
  /test_for_ftp_function               [ OK    ] [ 0.01143976 / 0.00129126 CPU ]
  /test_for_http_function              [ OK    ] [ 1.00304227 / 0.03937125 CPU ]
  /test_for_send_mail                  [ OK    ] [ 7.45204351 / 0.02348096 CPU ]
  /test_for_check_transform            [ OK    ] [ 0.00813210 / 0.00444104 CPU ]
  8 of 8 (100%) tests successful, 0 (0%) test skipped.
  ```

# Project Layout     
```

├── Daily_Work_Report.md
├── esb_proj
│   ├── src
│   │   └── esb_app
│   │       ├── Authentication.c
│   │       ├── Authentication.h
│   │       ├── esb.h
│   │       ├── ftp_transport.c
│   │       ├── ftp_transport.h
│   │       ├── handle_request.c
│   │       ├── handle_request.h
│   │       ├── http_Transport.c
│   │       ├── http_transport.h
│   │       ├── makefile
│   │       ├── mysqlconnect.c
│   │       ├── mysqlconnect.h
│   │       ├── server
│   │       ├── server.c
│   │       ├── setup.c
│   │       ├── smtp.c
│   │       ├── smtp.h
│   │       ├── status.c
│   │       ├── status.h
│   │       ├── threads.c
│   │       ├── threads.h
│   │       ├── transform.c
│   │       ├── transform.h
│   │       ├── xml_parsing.c
│   │       └── xml_parsing.h
│   └── Test
│       ├── Client
│       │   ├── BMD_CHECKSTATUS.xml
│       │   ├── BMD_EMAIL.xml
│       │   ├── BMD_FAILED1.xml
│       │   ├── BMD_FAILED2.xml
│       │   ├── BMD_FTP.xml
│       │   ├── BMD_HTTP.xml
│       │   ├── client.c
│       │   └── run_client.sh
│       └── Unit_test
│           ├── munit.c
│           ├── munit.h
│           └── test.c
├── mysql_dump.sql
└── README.md

```
