#\
Author : Deepak kumar\
Designation : Senior Member Technical\
Employer : Broadridge\
Description : This is makefile with two main target `all` and `setup` with `clean`.\
#
headers=-I/usr/include/mysql/ -I/usr/include/libxml2/
libraries=-lxml2 -lcurl -lpthread `mysql_config --libs`
DIR = ../../src/esb_app/
OBJ= handle_request.o test.o threads.o transform.o smtp.o status.o http_Transport.o ftp_transport.o  xml_parsing.o mysqlconnect.o  Authentication.o
# all:$(OBJ)
# 	gcc -o handle_request $(OBJ) $(libraries)
# 	rm *.o
# 	mkdir -p tmp

test: $(OBJ)
	gcc -o test munit.c $(OBJ) $(libraries)
	rm *.o

test.o: test.c
	gcc -c test.c $(headers)

# handle_request : handle_request.o xml_parsing.o mysqlconnect.o Authentication.o
# 	gcc -o handle_request handle_request.o xml_parsing.o mysqlconnect.o Authentication.o $(libraries)
# 	rm *.o

# thread : threads.o xml_parsing.o transform.o smtp.o status.o Authentication.o http_Transport.o
# 	gcc -o thread threads.o mysqlconnect.h xml_parsing.o transform.o smtp.o status.o Authentication.o http_Transport.o $(libraries)


threads.o: $(DIR)threads.c
	gcc -c $(DIR)threads.c $(headers)

transform.o: $(DIR)transform.c
	gcc -c $(DIR)transform.c

smtp.o: $(DIR)smtp.c
	gcc -c $(DIR)smtp.c

status.o : $(DIR)status.c
	gcc -c $(DIR)status.c $(headers)

http_Transport.o: $(DIR)http_Transport.c
	gcc -c $(DIR)http_Transport.c

ftp_transport.o : $(DIR)ftp_transport.c
	gcc -c $(DIR)ftp_transport.c


handle_request.o: $(DIR)handle_request.c
	gcc -c $(headers) $(DIR)handle_request.c $(libraries)
xml_parsing.o: $(DIR)xml_parsing.c
	gcc -c $(headers) $(DIR)xml_parsing.c
mysqlconnect.o: $(DIR)mysqlconnect.c
	gcc -c $(headers) $(DIR)mysqlconnect.c
Authentication.o: $(DIR)Authentication.c
	gcc -c $(headers) $(DIR)Authentication.c


setup: $(DIR)setup.c
	gcc $(headers) -o setup $(DIR)setup.c $(libraries)

clean:
	rm *.o test .tmp/* .transport_dump/*
