gcc -o client client.c
for i in {1..4}
do
   ./client BMD_FTP.xml -fg
   ./client BMD_EMAIL.xml -fg
   ./client BMD_HTTP.xml -fg
   sleep 1
done
rm client
