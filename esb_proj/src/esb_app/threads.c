/*gcc -o threads threads.c mysqlconnect.h xml_parsing.c transform.c smtp.c status.c -lpthread -lcurl $(mysql_config --cflags --libs) $(xml2-config --cflags --libs)

./threads
*/

#include "threads.h"
#include "status.h"
static char *unix_socket = NULL;
unsigned int port = 3306; // mysql-server port number
unsigned int flag = 0;

/*below check_transform() function returns the "JSON" or"CSV" or"XML" string as transform_key which extracted from the transform_config table for the perticular sender,dest,msg_type.*/

char *check_transform(char *id)
{
	char t[1001];
	char *transform_key;
	snprintf(t, sizeof(t), DETAILS, id);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res2 = mysql_store_result(con);
	while (row1 = mysql_fetch_row(res2))
	{
		for (int i = 0; i < 3; i++)
		{

			//printf("%s | ",row1[i]);
			if (i == 2)
			{
				sender = row1[0];
				dest = row1[1];
				msg_type = row1[2];
			}
		}
	}
	t[1001] = '\0';
	res2 = '\0';
	snprintf(t, sizeof(t), ROUTE_ID, sender, dest, msg_type);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res2 = mysql_store_result(con);
	while (row1 = mysql_fetch_row(res2))
	{
		route_id = row1[0];
	}
	t[1001] = '\0';
	res2 = '\0';
	row1 = '\0';

	snprintf(t, sizeof(t), "select config_key from transform_config where route_id=%s", route_id);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res2 = mysql_store_result(con);
	while (row1 = mysql_fetch_row(res2))
	{
		transform_key = row1[0];
	}

	t[1001] = '\0';
	res2 = '\0';
	row1 = '\0';
	return transform_key;
}

/*below check_transport() function returns the structure that includes transport_key i.e "HTTP" or "SMTP",tansport_value which is extracted from the transport_config table for the perticular sender,dest,msg_type.*/

transport check_transport(char *id)
{
	char t[1001];
	transport data;
	snprintf(t, sizeof(t), DETAILS, id);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res2 = mysql_store_result(con);
	while (row1 = mysql_fetch_row(res2))
	{
		for (int i = 0; i < 3; i++)
		{

			//printf("%s | ",row1[i]);
			if (i == 2)
			{
				sender = row1[0];
				dest = row1[1];
				msg_type = row1[2];
			}
		}
	}
	t[1001] = '\0';
	res2 = '\0';
	snprintf(t, sizeof(t), ROUTE_ID, sender, dest, msg_type);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res2 = mysql_store_result(con);
	while (row1 = mysql_fetch_row(res2))
	{
		route_id = row1[0];
	}

	t[1001] = '\0';
	res2 = '\0';
	snprintf(t, sizeof(t), "select config_key,config_value from transport_config where route_id=%s", route_id);
	if (mysql_query(con, t))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	res2 = mysql_store_result(con);
	while (row1 = mysql_fetch_row(res2))
	{
		data.transport_key = row1[0];
		data.transport_value = row1[1];
	}
	t[1001] = '\0';
	res2 = '\0';
	row1 = '\0';
	return data;
}

/*child thread starts*/

void *child_thread(char *id)
{

	printf("Child thread started to process the received BMD request\n");
	char *jsonfile;
	char *csvfile;
	char p[1001];
	snprintf(p, sizeof(p), "update esb_request set status='Taken',processing_attempts=processing_attempts+1 where id=%s", id);

	if (mysql_query(con, p))
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}

	printf("\n************** Status Updated Sucessfully at id=%s ****************\n\n", id);

	p[1001] = '\0';

	xmlDocPtr BMD = load_xml_doc("BMD.xml");
	char *payload = get_element_text("//Payload", BMD);
	char *Source = get_element_text("//Sender", BMD);

	char *transform_key = check_transform(id); //look at line no 9.

	/* transformation process*/

	if (strcmp(transform_key, "JSON") == 0) //comparing to json.
	{
		printf("Transforming to JSON\n");
		jsonfile = transform_to_json(Source, payload);
		if (jsonfile == '\0')
		{
			printf("Unable to transform\n");
		}
	}
	else
	{
		printf("Unable to compare with JSON\n");
	}
	if (strcmp(transform_key, "CSV") == 0) //comparing for CSV.
	{
		printf("Transforming to CSV\n");
		csvfile = transform_to_csv(Source, payload);
		if (csvfile == '\0')
		{
			printf("Unable to transform\n");
		}
	}
	else
	{
		printf("Unable to compare with CSV\n");
	}
	if (strcmp(transform_key, "XML") == 0)
	{
		printf("No Transformation Needed\n");
	}
	/*transport process*/

	transport t = check_transport(id); //look at line no 72.

	//via email tranfport

	if (strcmp(t.transport_key, "SMTP") == 0)
	{
		printf("transporting via SMTP\n");

		if (send_mail(t.transport_value, jsonfile)) //sending the converted jsonfile via email.
		{
			printf("[-]Error in send_mail\n");
			exit(1);
		}
	}

	//via email tranfport

	if (strcmp(t.transport_key, "HTTP") == 0)
	{
		printf("transporting via HTTP\n");
		//put function call for transport via HTTP here;
	}

	/*status Done*/
	status_done(id);
}

/*polling request starts here*/

void start_esb_request_poller_thread()
{
	pthread_t childthread;

	while (true)
	{
		if ((mysql_query(con, "select *from esb_request where (status = 'Available' && processing_attempts <5) limit 1 ")))
		{
			fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
			exit(1);
		}

		res = mysql_store_result(con);

		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i <= 10; i++)
			{

				//printf("%s | ",row[i]);
				if (i == 10)
				{
					id = row[0];
					status = row[8];
					attempts = row[10];
				}
			}
		}

		if (status != '\0')
		{
			printf("\nReceived New BMD request, Ready to process the BMD.\n");
			if (pthread_create(&childthread, NULL, &child_thread, id))
			{
				printf("unable to create the Childthread\n");
			}
			status = '\0';
		}
		else
		{
			printf("\n------| No Request Available in esb_request.|------\n");
		}

		printf("\n");
		sleep(5);
	}
}

/*main starts here*/

int main(int argc, char *argv[])
{

	pthread_t mainthread;

	con = mysql_init(NULL); // this fun initalizes the headerfiles i.e mysql.h

	if (!(mysql_real_connect(con, host, user, pass, dbname, port, unix_socket, flag))) //this is the real fun which connects to 																						  mysql-server.
	{
		fprintf(stderr, "ERROR: %s [%d]\n", mysql_error(con), mysql_errno(con));
		exit(1);
	}

	printf("Connected to mysql-server\n");
	if (pthread_create(&mainthread, NULL, &start_esb_request_poller_thread, NULL)) //mainthread created to poll requests.
	{
		printf("unable to create the thread\n");
	}
	pthread_join(&mainthread, NULL);

	mysql_close(con);
	return 0;
}
