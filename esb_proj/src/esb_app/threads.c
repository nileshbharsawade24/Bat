/*gcc -o threads threads.c mysqlconnect.h xml_parsing.c transform.c smtp.c status.c Authentication.c http_Transport.c ftp_transport.c -lpthread -lcurl $(mysql_config --cflags --libs) $(xml2-config --cflags --libs)

./threads
*/

#include "threads.h"
#include "status.h"
#include <unistd.h>
#include "mysqlconnect.h"
#include "http_transport.h"
#include "ftp_transport.h"
#define NUM_THREADS 5
// static char *unix_socket = NULL;
//unsigned int port = 3306; // mysql-server port number
//unsigned int flag = 0;

void cleanup(char * bmd_file, char* output_file){
	remove(bmd_file);
	remove(output_file);
	pthread_exit(NULL);
}

/*below check_transform() function returns the "JSON" or"CSV" or"XML" string as transform_key which extracted from the transform_config table for the perticular sender,dest,msg_type.*/
char *check_transform(bmd *msg)
{
	char t[1001];
	char *transform_key;
	MYSQL *con = connect_mysql();
	MYSQL_ROW row;

	snprintf(t, sizeof(t), ROUTE_ID, msg->envelop.Sender, msg->envelop.Destination, msg->envelop.MessageType);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	MYSQL_RES * res = res = mysql_store_result(con);
	char * route_id;
	while (row = mysql_fetch_row(res))
	{
		route_id = row[0];
	}
  bzero(t,strlen(t));
	snprintf(t, sizeof(t), "select config_value from transform_config where route_id=%s and config_key='format'", route_id);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res = mysql_store_result(con);
	while (row = mysql_fetch_row(res))
	{
		transform_key = row[0];
	}

	t[1001] = '\0';
	res = '\0';
	row = '\0';
	return transform_key;
}

/*below check_transport() function returns the structure that includes transport_key i.e "HTTP" or "SMTP",tansport_value which is extracted from the transport_config table for the perticular sender,dest,msg_type.*/

transport_data* check_transport(bmd * msg)
{
	char t[1001];
	char *transform_key;
	MYSQL *con = connect_mysql();
	MYSQL_ROW row;

	snprintf(t, sizeof(t), ROUTE_ID, msg->envelop.Sender, msg->envelop.Destination, msg->envelop.MessageType);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	MYSQL_RES * res = res = mysql_store_result(con);
	char * route_id;
	while (row = mysql_fetch_row(res))
	{
		route_id = row[0];
	}
  bzero(t,strlen(t));
	snprintf(t, sizeof(t), "select config_key,config_value from transport_config where route_id=%s", route_id);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res = mysql_store_result(con);
	transport_data* td=NULL,*temp;
	while (row = mysql_fetch_row(res))
	{
		if(td==NULL){
			td=malloc(sizeof(transport_data));
			temp=td;
		}
		else{
			temp->next=malloc(sizeof(transport_data));
			temp=temp->next;
		}
		temp->data.key = row[0];
		temp->data.value = row[1];
	}
	temp->next=NULL;
	return td;
}

/*child thread starts*/

void *child_thread(void *_task)
{
	task * taken_task=(task*)_task;
	// char *id=(char*)request_id;
	// char * BMD_filename=(char*)fname;
	printf("Child thread started to process the polled task with %s...\n",taken_task->id);
	char *output_fname;

	bmd * data = do_parse(taken_task->fpath);

	char *transform_key = check_transform(data); //look at line no 9.
	char token[20];
  int x=11;
  while(x<strlen(taken_task->fpath)-4){
    token[x-11]=taken_task->fpath[x];
    x++;
  }
  token[x-11]='\0';

	/* transformation process*/

	if (strcmp(transform_key, "csv") == 0) //comparing for CSV.
	{
		output_fname = transform_to_csv(token,data->payload);
		if (output_fname == NULL)
		{
			printf("Unable to transform\n");
			update_status(taken_task->id,"failed","Failed in transformation operation.");
			cleanup(taken_task->fpath,output_fname);
		}
		else{
			printf("[+] Transformed to CSV for task_id..%s\n",taken_task->id);
		}
	}

	if (strcmp(transform_key, "html") == 0) //comparing to html.
	{
		output_fname = transform_to_html(token,data->payload);
		if (output_fname == NULL)
		{
			printf("Unable to transform\n");
			update_status(taken_task->id,"failed","Failed in transformation operation.");
			cleanup(taken_task->fpath,output_fname);
		}
		else{
			printf("[+] Transformed to HTML for task_id..%s\n",taken_task->id);
		}
	}


	// if (strcmp(transform_key, "XML") == 0)//comparing for xml
	// {
	// 	printf("No transformation Needed\n");
	// 	xmlfile = transform_to_xml(Source, payload);
	// 	if (xmlfile == NULL)
	// 	{
	// 		printf("Unable to transform\n");
	// 		exit(1);
	// 	}
	//
	// }


	/*transport process*/

	transport_data * td = check_transport(data); //look at line no 72.
	transport_data * temp=td;
	char * transport_key;
	while(temp){
		if(strcmp(temp->data.key,"method")==0){
			transport_key=temp->data.value;
			temp=NULL;
			break;
		}
		temp=temp->next;
	}


	// via SFTP transport
	if (strcmp(transport_key, "ftp") == 0)
	{
		temp=td;
		char * hostname_or_ip,*username,*password;
		while(temp){
			if(strcmp(temp->data.key,"server_ip_or_hostname")==0){
				hostname_or_ip=temp->data.value;
			}
			else if(strcmp(temp->data.key,"username")==0){
				username=temp->data.value;
			}
			else if(strcmp(temp->data.key,"password")==0){
				password=temp->data.value;
			}
			temp=temp->next;
		}
		if (ftp(hostname_or_ip, username, password, output_fname, token)==false)//put function call for transport via HTTP here;
		{
			printf("[-]Error in sending via FTP\n");
			update_status(taken_task->id,"failed","Failed in transportation operation.");
			cleanup(taken_task->fpath,output_fname);
		}
		else{
			printf("[+] Transported via FTP\n");
			update_status(taken_task->id,"done","Successfully reached the destination.");
			cleanup(taken_task->fpath,output_fname);
		}
	}

	//via email transport
	if (strcmp(transport_key,"smtp") == 0)
	{
		printf("transporting via SMTP\n");

		if (send_mail(t.transport_value, jsonfile)) //sending the converted jsonfile via email.
		{
			printf("[-]Error in send_mail\n");
			exit(1);
		}
	}
	//
	// //via HTTP transport
	//
	// if (strcmp(t.transport_key, "HTTP") == 0)
	// {
	// 	printf("transporting via HTTP\n");
	// 	if (!(http(t.transport_value, csvfile)))//put function call for transport via HTTP here;
	// 	{
	// 		printf("[-]Error in sending via http\n");
	// 		exit(1);
	// 	}
	// }

	/*status Done*/
	// update_status(taken_task->id,"done","Successfully reached the destination.");
	// cleanup(taken_task->fpath,output_fname);
}

/*polling request starts here*/

void start_esb_request_poller_thread()
{
	MYSQL *con = connect_mysql();

	printf("TASK POLLER Connected to mysql-server\n");

	pthread_t childthread[NUM_THREADS];
	unsigned int count=0;
	while (true)
	{
		if ((mysql_query(con, "select *from esb_request where (status = 'Available' && processing_attempts <5) limit 1 ")))
		{
			fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
			exit(1);
		}

		MYSQL_RES* res = mysql_store_result(con);
		task *_task=malloc(sizeof(task));
		MYSQL_ROW row;
		bool flag=false;
		while (row = mysql_fetch_row(res))
		{
			flag=true;
			for (int i = 0; i <= 10; i++)
			{

				// printf("%s | ",row[i]);
				if (i == 10)
				{
					_task->id = row[0];
					// status = row[8];
					_task->fpath=row[7];
					// attempts = atoi(row[10]);
				}
			}
		}

		if (flag)
		{
			printf("\nNew TASK polled from DATABASE, Ready to process the BMD.\n");

			char p[1001];
			snprintf(p, sizeof(p), "update esb_request set status='Taken',processing_attempts=processing_attempts+1 where id=%s",_task->id);
			if (mysql_query(con, p))
			{
				fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
				exit(1);
			}

			if (pthread_create(&childthread[count%NUM_THREADS], NULL, &child_thread, _task))
			{
				printf("unable to create the Childthread\n");
			}
		}
		else
		{
			printf("\n++++| No Request Available in esb_request.|++++\n");
		}

		printf("\n");
		sleep(5);
		count++;
	}

	mysql_close(con);

}
