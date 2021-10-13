# ESB Application
An [ESB](https://en.wikipedia.org/wiki/Enterprise_service_bus) can be considered as an enterprise application integration solution. The ESB allows a uniform integration of enterprise applications over a standard protocol. In this project, we developed this application using C language given [project specification](https://docs.google.com/document/d/e/2PACX-1vS7DqPrm7u3Ril-yrpdw5VjW4owi3hx-nD7vsvrBV4SCSXZU9k5gYXLXssyfKfMln1qUHp6WH_zTCFc/pub).

# Installation required
    sudo apt update
    sudo apt install mysql-server
    sudo apt install libmysqlclient-dev
    sudo apt install libxml2-dev
    sudo apt install libcurl4-openssl-dev

# Setup Database
* **Create user and Database**    
In your mysql server, create a user with  name *test_user*, password *test_password* and have all access grant on *BAT_DB* database.One can do this with following steps:<br />
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
* **Populate created Database**
    1. you can find the SQL dump file "mysq_dump.sql" in main directory. Dump that using below command :<br/>
        ```
        mysql -u test_user -p BAT_DB < mysql_dump.sql
        ```
    2. OR use setup.c file. Go inside this path "esb_proj/src/esb_app/" and use below commands :<br/>
        ```
          make clean
          make setup
          ./setup
         ```


# Run ESB Application
Make sure no process is running on port number 4444 .
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
│           ├── makefile
│           ├── munit.c
│           ├── munit.h
│           └── test.c
├── mysql_dump.sql
└── README.md
└── unit_testing_report.png

```

# UNIT Testing
* Go inside this path mentioned "esb_proj/Test/Unit_test/" and run server using below commands :<br/>
    ```
      make clean
      make test
      ./test
     ```
* Unit Testing Report

  Unit testing of 'database poller' and 'esb request handler' function has been skipped since they are threads shared continuously running void functions.

  <img src="/unit_testing_report.png" width=auto height=auto>

# HTTP Api used for testing

    https://reqbin.com/echo/post/json


# References
[The libcurl C API](https://curl.se/libcurl/c/)  
[The MySQL C API](https://dev.mysql.com/doc/c-api/8.0/en/c-api-function-reference.html)  
[µnit - Testing framework for C ](https://nemequ.github.io/munit/)

# Authors
[Nilesh Bharsawade](https://github.com/nileshbharsawade24)  
[Pavan Kolur](https://github.com/pavankolur123)  
[Deepak kumar](https://github.com/deepakjnv880)  
[Rohit bhamu](https://github.com/rohitbhamu)

# Happy coding :slightly_smiling_face: .
