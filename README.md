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

## Running ESB_TCP

* Server
    * Go inside this path mentioned " TCP_Server_Client/src/Server/ " You will find "run_server.sh" file.
    * run "./run_server.sh" to compile and create executable file on server side. if something error rised like permission denied, run "chmod +x run_server.sh" after debugging the error run above mentioned again. Then,
    * run "./server" To run the server.

        
* Client
    * Go inside this path mentioned " TCP_Server_Client/src/Client/ "You will find "run_client.sh" file. 
    * run "./run_client.sh" to compile and create executable file on server side. if something error rised like permission denied, run "chmod +x run_client.sh" after debugging the error run above mentioned again. Then,
    * run "./client filename"  mention the filename that you are going to send then run the command to send file to server.
