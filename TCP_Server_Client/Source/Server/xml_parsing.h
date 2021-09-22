#pragma once
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xmlversion.h>
#include  <stdio.h>
#include <stdlib.h>
xmlDocPtr load_xml_doc(char *xml_file_path);
xmlXPathObjectPtr get_nodes_at_xpath(xmlDocPtr doc, xmlChar *xpath);
xmlChar* get_element_text(char *node_xpath, xmlDocPtr doc);
void do_parse(char *doc);