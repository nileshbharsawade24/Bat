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



## Running ESB_TCP

* Server
    * Go inside this path mentioned " esb_proj/src/esb_app/ " You will find "run_server.sh" file.
    * run "./run_server.sh" to compile and create executable file on server side. if something error rised like permission denied, run "chmod +x run_server.sh" after debugging the error run above mentioned again.

        
* Client
    * Go inside this path mentioned " esb_proj/test/Client/ "You will find "run_client.sh" file. 
    * run "./run_client.sh" to compile and create executable file on server side. if something error rised like permission denied, run "chmod +x run_client.sh" after debugging the error run above mentioned again.
