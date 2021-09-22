#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include"mysqlconnect.h"
#include<mysql/mysql.h>
#include<unistd.h>

#define PORT 4444
#define BUF_SIZE 2000
#define CLADDR_LEN 100
#define SIZE 1024


//struct for input message body and metadata
// typedef struct {
//     char *MessageID;
//     char *Sender;
//     char *Destination;
//     char *MessageType;
//     char *Payload;
// }message_data;





//void do_parse(char *file) which will parse the input file to the actual data(into struct);
message_data* do_parse(char *file);


// to write the file in temporary file in directory with return as that filename
char* write_file(int sockfd){  
  int n;
  FILE *fp;
  char buffer[SIZE];

  //Create unique filename
  char filename[] = "fileXXXXXX";
  mkstemp(filename);
  char *file=filename;
  fp = fopen( filename, "w"); //open that file
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0); //n is number of bytes received or -1 if error occurs
    if (n <= 0){
      break;
      // return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  
  return file;
}


void main() { //workflow starts here
 struct sockaddr_in addr, cl_addr;
 int sockfd, len, ret, newsockfd;
 char buffer[BUF_SIZE];
 pid_t childpid;
 char clientAddr[CLADDR_LEN];
 char* filename;
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Error creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");
 
 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = INADDR_ANY;
 addr.sin_port = PORT;

 ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) {
  printf("Error binding!\n");
  exit(1);
 }
 printf("Binding done...\n");

 printf("Waiting for a connection...\n");
 listen(sockfd, 5);



 


 for (;;) { //infinite loop
  len = sizeof(cl_addr);
  
  newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
  if (newsockfd < 0) {
//    printf("Error accepting connection!\n");  //when client closes, throws error accepting connection
   exit(1);
  }
  printf("Connection accepted...\n");



  inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN); //convert from an internet address in binary format
  if ((childpid = fork()) == 0) { //using fork, creates its another copy i.e. creating a child process
   printf("Child created\n");
   close(sockfd); 
   printf("Main Terminated\n");


//stop listening for new connections by the main process. the child will continue to listen. 
//the main process now handles the connected client.


   
   filename=write_file(newsockfd); //send to write the input file into directory and return that
                                   // filename
   
   printf("Reading done\n");  //to remove
   message_data *request_message; //struct pointer of message_data type
   printf("Parsing the BMD file: %s\n\n",filename);
   request_message=do_parse(filename); //parse that file into valid BMD format and return the BMD 
    //establish connection between the MySql and server
   MYSQL* con = connect_mysql();
   printf("Validating BMD...\n"); 
   
   validation(con, request_message, filename);
        mysql_close(con);
  }
  close(newsockfd);
 }

}




/*Parsing*/





xmlDocPtr load_xml_doc(char *xml_file_path) {
    xmlDocPtr doc = xmlParseFile(xml_file_path);
    if (doc == NULL) {
        fprintf(stderr, "ERROR: Document not parsed successfully. \n");
        return NULL;
    }
    return doc;
}

/**
 * Extract the nodes matching the given xpath from the supplied
 * XML document object.
 */
xmlXPathObjectPtr get_nodes_at_xpath(xmlDocPtr doc, xmlChar *xpath) {

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        printf("ERROR: Failed to create xpath context from the XML document.\n");
        return NULL;
    }
    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);
    if (result == NULL) {
        printf("ERROR: Failed to evaluate xpath expression.\n");
        return NULL;
    }
    if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        xmlXPathFreeObject(result);
        printf("No matching nodes found at the xpath.\n");
        return NULL;
    }
    return result;
}

/**
 * Returns the text value of an XML element. It is expected that
 * there is only one XML element at the given xpath in the XML.
 * 
 *  
 */
xmlChar* get_element_text(char *node_xpath, xmlDocPtr doc) {
    xmlChar *node_text;
    xmlXPathObjectPtr result = get_nodes_at_xpath(doc, 
        (xmlChar*)node_xpath);
    if (result) {
        xmlNodeSetPtr nodeset = result->nodesetval;
        if (nodeset->nodeNr == 1) {
            node_text = xmlNodeListGetString(doc,
                nodeset->nodeTab[0]->xmlChildrenNode, 1);
        } else {
            printf("ERROR: Expected one %s node, found %d\n", node_xpath, nodeset->nodeNr);
        }
        xmlXPathFreeObject(result);
    } else {
        printf("ERROR: Node not found at xpath %s\n", node_xpath);
    }
    return node_text;
}


message_data* do_parse(char *file){
 
    char *docname = file;
    char *password="63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c";
    char *username="INV-PROFILE-889712";
    xmlDocPtr doc = load_xml_doc(docname);
    printf("MessageID = %s\n", get_element_text("//MessageID", doc));
    printf("Sender = %s\n", get_element_text("//Sender", doc));
    printf("Destination = %s\n", get_element_text("//Destination", doc));
    printf("MessageType = %s\n", get_element_text("//MessageType", doc));
    printf("Payload = %s\n", get_element_text("//Payload", doc));
    printf("ReferenceID = %s\n", get_element_text("//ReferenceID", doc));
    printf("Signature = %s\n\n", get_element_text("//Signature", doc));
    printf("Parsing Done\n\n"); 
    /*Authentication of BMD*/
    
    if(((strcmp(get_element_text("//Signature", doc),password))==0)&&((strcmp(get_element_text("//ReferenceID", doc),username))==0)){
    
   		printf("Authentication is successful.\n");}
   	else{
   		printf("Authentication is Wrong\n");
   		exit(1);
    	}  //xmlFreeDoc(doc);
    //xmlFreeDoc(doc); //xmlCleanupParser(); //remove(file);
    message_data *msg;
    msg->Destination=get_element_text("//Destination", doc);
    msg->MessageID=get_element_text("//MessageID", doc);
    msg->MessageType=get_element_text("//MessageType", doc);
    msg->Payload=get_element_text("//Payload", doc);
    msg->Sender=get_element_text("//Sender", doc);
    msg->ReferenceID=get_element_text("//ReferenceID", doc);
    return msg;
    
}











