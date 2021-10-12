gcc -o client client.c
for i in {1..5}
do
   ./client BMD_FTP.xml &
   ./client BMD_EMAIL.xml &
   ./client BMD_HTTP.xml &
   ./client BMD_CHECKSTATUS.xml &
   ./client BMD_FAILED1.xml &
   ./client BMD_FAILED2.xml &
   sleep 1
done
rm client
