gcc server.c -o server.o -c $(xml2-config --cflags --libs) `mysql_config --cflags --libs` 
gcc xml_parsing.c -o xml_parsing.o -c $(xml2-config --cflags --libs)
gcc mysqlconnect.c -o mysqlconnect.o -c `mysql_config --cflags --libs`
gcc Authentication.c -o Authentication.o -c `mysql_config --cflags --libs`
gcc -o server xml_parsing.o server.o mysqlconnect.o Authentication.o `mysql_config --cflags --libs` $(xml2-config --cflags --libs)

