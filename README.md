# Bat

## XML External Libraries Enviroment Setup
    * Enviroment requirement specific commands for debian Linux
        * sudo apt-get install libxml2-dev libxslt1-dev
    * Enviroment requirement specific commands for Redhat/Centos/Fedora Distro
        * yum install libxml-devel

## SQL External Libraries Enviroment Setup (On preinstalled MYSQL Client)
    * Enviroment requirement specific commands for debian Linux
        * apt-get install libmysqlclient-dev 
    * Enviroment requirement specific commands for Redhat/Centos/Fedora Distro
        * yum install mysql-devel -y
  
## JSON External Libraries Enviroment Setup
    * Enviroment requirement specific commands for debian Linux
        * sudo apt install libjson-c-dev

##  CURL External Libraries Enviroment Setup
    * Enviroment requirement specific commands for debian Linux
        * sudo apt-get install libcurl4-openssl-dev

## HTTP api to test http_transport() external api (Reference)
    * https://github.com/public-apis/public-apis

### Database file:

* you can find the SQL file here : "esb_proj/db.sql"  

## Running ESB_TCP

* Compiling threads.c file to test the thread api:
  * run : <span style="background-color: #F0D3C7">gcc -o threads threads.c mysqlconnect.h xml_parsing.c transform.c smtp.c status.c Authentication.c http_Transport.c ftp_transport.c -lpthread -lcurl $(mysql_config --cflags --libs) $(xml2-config --cflags --libs)</span>

* Server
    * Go inside this path mentioned " esb_proj/src/esb_app/ " You will find "run_server.sh" file.
    * run "./run_server.sh" to compile and create executable file on server side. if something error rised like permission denied, run "chmod +x run_server.sh" after debugging the error run above mentioned again.

        
* Client
    * Go inside this path mentioned " esb_proj/test/Client/ "You will find "run_client.sh" file. 
    * run "./run_client.sh" to compile and create executable file on server side. if something error rised like permission denied, run "chmod +x run_client.sh" after debugging the error run above mentioned again.
