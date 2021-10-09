gcc -o client client.c
for i in {1..10}
do
   ./client BMD_FTP.xml
   sleep 1
done
rm client
