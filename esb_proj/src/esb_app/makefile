#\
Author : Deepak kumar\
Designation : Senior Member Technical\
Employer : Broadridge\
Description : This is makefile with two main target `all` and `setup` with `clean`.\
#
headers=-I/usr/include/mysql/ -I/usr/include/libxml2/
libraries=-lxml2 -lcurl -lpthread `mysql_config --libs`
OBJ= handle_request.o server.o threads.o transform.o smtp.o status.o http_Transport.o ftp_transport.o  xml_parsing.o mysqlconnect.o  Authentication.o
# all:$(OBJ)
# 	gcc -o handle_request $(OBJ) $(libraries)
# 	rm *.o
# 	mkdir -p tmp

server: $(OBJ)
	gcc -o server $(OBJ) $(libraries)
	rm *.o

server.o: server.c
	gcc -c server.c $(headers)

# handle_request : handle_request.o xml_parsing.o mysqlconnect.o Authentication.o
# 	gcc -o handle_request handle_request.o xml_parsing.o mysqlconnect.o Authentication.o $(libraries)
# 	rm *.o

# thread : threads.o xml_parsing.o transform.o smtp.o status.o Authentication.o http_Transport.o
# 	gcc -o thread threads.o mysqlconnect.h xml_parsing.o transform.o smtp.o status.o Authentication.o http_Transport.o $(libraries)


threads.o: threads.c
	gcc -c threads.c $(headers)

transform.o: transform.c
	gcc -c transform.c

smtp.o: smtp.c
	gcc -c smtp.c

status.o : status.c
	gcc -c status.c $(headers)

http_Transport.o: http_Transport.c
	gcc -c http_Transport.c

ftp_transport.o : ftp_transport.c
	gcc -c ftp_transport.c


handle_request.o: handle_request.c
	gcc -c $(headers) handle_request.c $(libraries)
xml_parsing.o: xml_parsing.c
	gcc -c $(headers) xml_parsing.c
mysqlconnect.o: mysqlconnect.c
	gcc -c $(headers) mysqlconnect.c
Authentication.o: Authentication.c
	gcc -c $(headers) Authentication.c


setup: setup.c
	gcc $(headers) -o setup setup.c $(libraries)

clean:
	rm *.o setup server
