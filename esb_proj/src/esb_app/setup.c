/*
Author : Deepak kumar
Designation : Senior Member Technical
Employer : Broadridge
Description : This c program will setup the database and tables appropriately.
NOTE1 : To run this program make sure to your mysql user have all permission on atleast `CAMEL_DB` database.
NOTE2 : change mysql_user_name and my_sql_password appropritely or just create one same as these.
*/

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define mysql_user_name "test_user"
#define mysql_user_password "test_password"
#define mysql_host "localhost"

//this function will handle error given mysql connection `connection`
void handle_error(MYSQL *connection){
      fprintf(stderr, "%s\n", mysql_error(connection));
      mysql_close(connection);
      exit(1);
}

//setup function will setup the database and table with approprite schema and indexes
void setup(){

  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, mysql_host, mysql_user_name, mysql_user_password, NULL, 0, NULL, 0) == NULL)
  {
      handle_error(con);
  }

  while (mysql_query(con, "create database BAT_DB"))
  {
    fprintf(stderr, "'BAT_DB' database already exists.\n"
    "Deleting and settting up this database (wait for around 30 second) ...\n");
    mysql_query(con, "drop database BAT_DB");
    //return;
  }


  con=mysql_init(NULL);
  if (mysql_real_connect(con, mysql_host, mysql_user_name, mysql_user_password,
          "BAT_DB", 0, NULL, 0) == NULL)
  {
        handle_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE `auth` ("
  	"`id` int NOT NULL AUTO_INCREMENT,"
  	"`signature` varchar(65) DEFAULT NULL,"
  	"PRIMARY KEY (`id`)"
	")")){
        handle_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO `auth` VALUES (1,'63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c')")){
        handle_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE routes ("
  			"route_id INT AUTO_INCREMENT,"
  			"sender VARCHAR(45),"
  			"destination VARCHAR(45),"
  			"message_type VARCHAR(45) NOT NULL,"
  			"is_active bit(1) NOT NULL,"
        "PRIMARY KEY (route_id,sender,destination),"
        "UNIQUE (sender,destination,message_type)"
  			 ")")){
        handle_error(con);
  }

  if (mysql_query(con, "ALTER TABLE routes AUTO_INCREMENT = 1")){
        handle_error(con);
  }

  if (mysql_query(con, "CREATE TABLE esb_request ("
  			"id INT PRIMARY KEY AUTO_INCREMENT ,"
  			"sender_id VARCHAR(45) NOT NULL,"
  			"dest_id VARCHAR(45) NOT NULL,"
  			"message_type VARCHAR(45) NOT NULL,"
  			"reference_id VARCHAR(45) NOT NULL,"
  			"message_id VARCHAR(45) NOT NULL,"
  			"received_on DATETIME NOT NULL,"
  			"data_location TEXT,"
  			"status VARCHAR(20) NOT NULL,"
        "processing_attempts INT DEFAULT 0 NOT NULL,"
  			"status_details TEXT"
  			 ")")){
        handle_error(con);
  }

  if (mysql_query(con, "ALTER TABLE esb_request AUTO_INCREMENT = 1")){
        handle_error(con);
  }

  if (mysql_query(con, "CREATE TABLE transform_config ("
  			"id INT PRIMARY KEY AUTO_INCREMENT ,"
  			"route_id INT NOT NULL,"
  			"config_key VARCHAR(45) NOT NULL,"
  			"config_value TEXT,"
        "UNIQUE (route_id,config_key),"
        "FOREIGN KEY (route_id) REFERENCES routes(route_id)"
  			 ")")){
        handle_error(con);
  }
  // else {return};

  if (mysql_query(con, "ALTER TABLE transform_config AUTO_INCREMENT = 1")){
        handle_error(con);
  }

  if (mysql_query(con, "CREATE INDEX route_idx "
                       "ON transform_config (route_id)")){
        handle_error(con);
  }

  if (mysql_query(con, "CREATE TABLE transport_config ("
  			"id INT PRIMARY KEY AUTO_INCREMENT ,"
  			"route_id INT,"
  			"config_key VARCHAR(45),"
  			"config_value TEXT,"
        "UNIQUE (route_id,config_key),"
        "FOREIGN KEY (route_id) REFERENCES routes(route_id)"
  			 ")")){
        handle_error(con);
  }

  if (mysql_query(con, "ALTER TABLE transport_config AUTO_INCREMENT = 1")){
        handle_error(con);
  }

  if (mysql_query(con, "CREATE INDEX route_idx "
                       "ON transport_config (route_id)")){
        handle_error(con);
  }

  //manual data filling for http based http based destination
  if (mysql_query(con, "insert into routes (sender,destination,message_type,is_active) values "
                       "('user_app_123','http_dest_123','hit_api',1)"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transform_config (route_id,config_key,config_value) values "
                       "(1,'format','json')"
                       )){
        handle_error(con);
  }
  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(1,'method','http')"
                       )){
        handle_error(con);
  }
  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(1,'api','https://reqbin.com/echo/post/json')"
                       )){
        handle_error(con);
  }

  //manual data filling for ftp based application
  if (mysql_query(con, "insert into routes (sender,destination,message_type,is_active) values "
                       "('user_app_123','ftp_dest_123','transfer_file',1)"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transform_config (route_id,config_key,config_value) values "
                       "(2,'format','csv')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(2,'method','ftp')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(2,'server_ip_or_hostname','test.rebex.net:22')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(2,'username','demo')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(2,'password','password')"
                       )){
        handle_error(con);
  }
  
  //manual data filling for email based application
  if (mysql_query(con, "insert into routes (sender,destination,message_type,is_active) values "
                       "('user_app_123','email_dest_123','send_mail',1)"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transform_config (route_id,config_key,config_value) values "
                       "(3,'format','html')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(3,'method','smtp')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(3,'from','esbtest321@gmail.com')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(3,'to','rohitbhamu6@gmail.com')"
                       )){
        handle_error(con);
  }

  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(3,'cc','b17039.880@gmail.com')"
                       )){
        handle_error(con);
  }
  
  if (mysql_query(con, "insert into transport_config (route_id,config_key,config_value) values "
                       "(3,'from_password','testesb@321')"
                       )){
        handle_error(con);
  }

  // if (mysql_query(con, "INSERT INTO esb_request"
  //                    "(sender_id,dest_id,message_type,reference_id,message_id,received_on,data_location,status,processing_attempts,status_details) "
  //                    "VALUES ('t','t','t','t','t',now(),'t','t',0,'t')"
  //                      )){
  //       handle_error(con);
  // }
  //
  // if (mysql_query(con, "INSERT INTO esb_request"
  //                    "(sender_id,dest_id,message_type,reference_id,message_id,received_on,data_location,status,processing_attempts,status_details) "
  //                    "VALUES ('t','t','t','t','t',now(),'t','t',0,'t')"
  //                      )){
  //       handle_error(con);
  // }
  //
  // if (mysql_query(con, "INSERT INTO esb_request"
  //                    "(sender_id,dest_id,message_type,reference_id,message_id,received_on,data_location,status,processing_attempts,status_details) "
  //                    "VALUES ('t','t','t','t','t',now(),'t','t',0,'t')"
  //                      )){
  //       handle_error(con);
  // }

  mysql_close(con);
}

int main(int argc, char **argv)
{
  //run the setup code
  setup();
  return 0;
}
