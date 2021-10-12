# Bat

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

### Setting up database:
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
    * Go inside this path mentioned " esb_proj/src/esb_app/ " and run server using below commands :<br/>
        ```
          make clean
          make server  
          ./server
        ```



* Client
    * Go inside this path mentioned " esb_proj/test/Client/" and run client using below commands :<br/>
        ```
          chmod 777 run_client.sh
          ./run_client.sh
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
