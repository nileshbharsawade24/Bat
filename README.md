# Bat

> XML External Libraries Enviroment Setup
    Enviroment requirement specific commands for debian Linux
    > sudo apt-get install libxml2-dev libxslt1-dev
    Enviroment requirement specific commands for Redhat/Centos/Fedora Distro
    > yum install libxml-devel

>SQL External Libraries Enviroment Setup (On preinstalled MYSQL Client)
    Enviroment requirement specific commands for debian Linux
    > apt-get install libmysqlclient-dev 
    Enviroment requirement specific commands for Redhat/Centos/Fedora Distro
    > yum install mysql-devel -y

> Running ESB_TCP
    > Server
        > run " Source/Server/server.sh " to compile and create executable file on server side
        > run ./main

        
    >Client
        > run " Source/Client/client.sh " to compile and create executable file on client side
        > run ./client