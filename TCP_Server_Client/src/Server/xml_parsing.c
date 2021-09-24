#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include  <stdio.h>
#include <stdlib.h>
#include"mysqlconnect.h"
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
    char *sender="756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA";
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
    
    if(((strcmp(get_element_text("//Signature", doc),password))==0)&&((strcmp(get_element_text("//Sender", doc),sender))==0)){
    
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