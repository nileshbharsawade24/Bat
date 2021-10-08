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
    create database BAT_DB
    ```
4. Grant all access on *BAT_DB* database to user *test_user*
    ```
    GRANT ALL ON BAT_DB.* TO 'test_user';
    ```

## HTTP api to test http_transport() external api (Reference)
    * https://github.com/public-apis/public-apis

### Database file:
* you can find the SQL dump file here : "esb_proj/db.sql" . Dump that using below command :
`mysql -u test_user -p BAT_DB < db.sql`

## Running ESB_TCP
* Server
    * Go inside this path mentioned " esb_proj/src/esb_app/ " Run server using below commands :<br/>
    ```
      make server  
      ./server
    ```



* Client
    * Go inside this path mentioned " esb_proj/test/Client/ "You will find "run_client.sh" file.
    * run "./run_client.sh" to compile and create executable file on server side. if something error rised like permission denied, run "chmod +x run_client.sh" after debugging the error run above mentioned again.
