//remaining : insert, validation, authentication, do_parse
#include "munit.h"
#include "../../src/esb_app/status.h"
#include "../../src/esb_app/transform.h"
#include "../../src/esb_app/ftp_transport.h"
#include "../../src/esb_app/http_transport.h"
#include "../../src/esb_app/smtp.h"
#include "../../src/esb_app/threads.h"
#include "../../src/esb_app/esb.h"
#include "../../src/esb_app/Authentication.h"
#include "../../src/esb_app/handle_request.h"
#include "../../src/esb_app/mysqlconnect.h"
#include "../../src/esb_app/xml_parsing.h"




/* This is just to disable an MSVC warning about conditional
 * expressions being constant, which you shouldn't have to do for your
 * code.  It's only here because we want to be able to do silly things
 * like assert that 0 != 1 for our demo. */
#if defined(_MSC_VER)
#pragma warning(disable: 4127)
#endif

static MunitResult test_transform_to_json(const MunitParameter params[], void* data) {
  munit_assert_string_equal(transform_to_json("948r93844343","nvdiosdnv"), ".tmp/948r93844343.json");
  munit_assert_string_not_equal(transform_to_json("iuen","nqviosdnv"), ".tmp/948r93844343.json");
  munit_assert_string_equal(transform_to_json("t","nosdnv"), ".tmp/t.json");
  if(transform_to_json(NULL,NULL)!=NULL)return MUNIT_FAIL;
  if(transform_to_json(NULL,"abc")!=NULL)return MUNIT_FAIL;
  if(transform_to_json("abc",NULL)!=NULL)return MUNIT_FAIL;
  if(transform_to_json("948r9384/4343","nviosdnv")!=NULL)return MUNIT_FAIL;
  char temp[55];
  for(int i=0;i<54;i++)temp[i]='x';
  temp[54]='\0';
  if(transform_to_json("1",temp)==NULL)return MUNIT_FAIL;
  return MUNIT_OK;
}

static MunitResult test_transform_to_csv(const MunitParameter params[], void* data) {
  munit_assert_string_equal(transform_to_csv("948r93844343","nvdiosdnv"), ".tmp/948r93844343.csv");
  munit_assert_string_not_equal(transform_to_csv("iuen","nqviosdnv"), ".tmp/948r93844343.csv");
  munit_assert_string_equal(transform_to_csv("t","nosdnv"), ".tmp/t.csv");
  if(transform_to_csv(NULL,NULL)!=NULL)return MUNIT_FAIL;
  if(transform_to_csv(NULL,"abc")!=NULL)return MUNIT_FAIL;
  if(transform_to_csv("abc",NULL)!=NULL)return MUNIT_FAIL;
  if(transform_to_csv("948r9384/4343","nviosdnv")!=NULL)return MUNIT_FAIL;
  char temp[55];
  for(int i=0;i<54;i++)temp[i]='x';
  temp[54]='\0';
  if(transform_to_csv("1",temp)==NULL)return MUNIT_FAIL;
  return MUNIT_OK;
}

static MunitResult test_transform_to_html(const MunitParameter params[], void* data) {
  munit_assert_string_equal(transform_to_html("948r93844343","nvdiosdnv"), ".tmp/948r93844343.html");
  munit_assert_string_not_equal(transform_to_html("iuen","nqviosdnv"), ".tmp/948r93844343.html");
  munit_assert_string_equal(transform_to_html("t","nosdnv"), ".tmp/t.html");
  if(transform_to_html(NULL,NULL)!=NULL)return MUNIT_FAIL;
  if(transform_to_html(NULL,"abc")!=NULL)return MUNIT_FAIL;
  if(transform_to_html("abc",NULL)!=NULL)return MUNIT_FAIL;
  if(transform_to_html("948r9384/4343","nviosdnv")!=NULL)return MUNIT_FAIL;
  char temp[55];
  for(int i=0;i<54;i++)temp[i]='x';
  temp[54]='\0';
  if(transform_to_html("1",temp)==NULL)return MUNIT_FAIL;
  return MUNIT_OK;
}

static MunitResult test_ftp(const MunitParameter params[], void* data) {
  munit_assert_true(ftp("948r93844343","nvdiosdnv","subifuds","munit.h","ifdis"));
  munit_assert_false(ftp("948r93844343","nvdiosdnv","subifuds","nsdn","ifdis"));
  munit_assert_false(ftp("948r93844343","nvdiosdnv","subifuds","nsdn","ifd0000000000000000000000000000000000000000000000000000000000000000000000000000000is"));
  munit_assert_false(ftp(NULL,"nvdiosdnv","subifuds","nsdn","ifdis"));
  munit_assert_false(ftp("948r93844343",NULL,"subifuds","nsdn","ifdis"));
  munit_assert_false(ftp("948r93844343","nvdiosdnv",NULL,"nsdn","ifdis"));
  munit_assert_false(ftp("948r93844343","nvdiosdnv","subifuds",NULL,"ifdis"));
  munit_assert_false(ftp("948r93844343","nvdiosdnv","subifuds","nsdn",NULL));
  munit_assert_false(ftp(NULL,NULL,NULL,NULL,NULL));
  return MUNIT_OK;
}

static MunitResult test_http(const MunitParameter params[], void* data) {
  FILE * fp =fopen("test.txt","w");
  fprintf(fp, "HEY, I AM DOING HTTP TESTING.\n");
  fclose(fp);
  munit_assert_true(http("https://reqbin.com/echo/post/json","test.txt"));
  remove("test.txt");
  munit_assert_false(http("https://reqbin.com/echo/post/json","munit.h"));
  munit_assert_false(http("948r93844343","munit.h"));
  munit_assert_false(http(NULL,"munit.h"));
  munit_assert_false(http("https://reqbin.com/echo/post/json",NULL));
  munit_assert_false(http(NULL,NULL));
  return MUNIT_OK;
}

static MunitResult test_send_mail(const MunitParameter params[], void* data) {
  FILE * fp =fopen("test.txt","w");
  fprintf(fp, "HEY, I AM DOING EMAIL TESTING.\n");
  fclose(fp);
  munit_assert_true(send_mail("rohitbhamu6@gmail.com","esbtest321@gmail.com","testesb@321","b17039.880@gmail.com","test.txt"));
  remove("test.txt");
  munit_assert_false(send_mail("948r93844343","nvdiosdnv","subifuds","nsdn","ifdis"));
  munit_assert_false(send_mail("948r93844343","nvdiosdnv","subifuds","nsdn","ifd0000000000000000000000000000000000000000000000000000000000000000000000000000000is"));
  munit_assert_false(send_mail(NULL,"nvdiosdnv","subifuds","nsdn","ifdis"));
  munit_assert_false(send_mail("948r93844343",NULL,"subifuds","nsdn","ifdis"));
  munit_assert_false(send_mail("948r93844343","nvdiosdnv",NULL,"nsdn","ifdis"));
  munit_assert_false(send_mail("948r93844343","nvdiosdnv","subifuds",NULL,"ifdis"));
  munit_assert_false(send_mail("948r93844343","nvdiosdnv","subifuds","nsdn",NULL));
  munit_assert_false(send_mail(NULL,NULL,NULL,NULL,NULL));
  return MUNIT_OK;
}

bmd * create_bmd_structure(char* f1,char * f2,char * f3){
  bmd *msg=malloc(sizeof(bmd));//Ihtout malloc : use of uninitialised value of size 8
  msg->envelop.Sender=f1;
  msg->envelop.Destination=f2;
  msg->envelop.MessageID="dummy";
  msg->envelop.MessageType=f3;
  msg->payload="dummy";
  msg->envelop.ReferenceID="dummy";
  msg->envelop.Signature="dummy";
  msg->envelop.CreationDateTime="dummy";

  if(msg->envelop.Destination==NULL)msg->envelop.Destination="";
  if(msg->envelop.MessageType==NULL)msg->envelop.MessageType="";
  if(msg->envelop.Sender==NULL)msg->envelop.Sender="";

  return msg;
}

static MunitResult test_check_transform(const MunitParameter params[], void* data) {
  munit_assert_string_equal(check_transform(create_bmd_structure("user_app_123","http_dest_123","hit_api")),"json");
  munit_assert_string_equal(check_transform(create_bmd_structure("user_app_123","ftp_dest_123","transfer_file")),"csv");
  munit_assert_string_equal(check_transform(create_bmd_structure("user_app_123","email_dest_123","send_mail")),"html");
  if(check_transform(create_bmd_structure("user_app_123x","email_dest_123","send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure("user_app_123","email_dest_123x","send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure("user_app_123","email_dest_123","send_mailx"))!=NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure("user_app,_123","email_dest_123","send_mailx"))!=NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure(NULL,"email_dest_123","send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure("user_app_123",NULL,"send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure("user_app_123","email_dest_123",NULL))!=NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure(NULL,NULL,NULL))!=NULL)return MUNIT_FAIL;
  if(check_transform(NULL)!=NULL)return MUNIT_FAIL;
  return MUNIT_OK;
}

static MunitResult test_check_transport(const MunitParameter params[], void* data) {
  if(check_transform(create_bmd_structure("user_app_123","http_dest_123","hit_api"))==NULL)return MUNIT_FAIL;
  if(check_transform(create_bmd_structure("user_app_123","ftp_dest_123","transfer_file"))==NULL)return MUNIT_FAIL;;
  if(check_transform(create_bmd_structure("user_app_123","email_dest_123","send_mail"))==NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure("user_app_123x","email_dest_123","send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure("user_app_123","email_dest_123x","send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure("user_app_123","email_dest_123","send_mailx"))!=NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure("user_app,_123","email_dest_123","send_mailx"))!=NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure(NULL,"email_dest_123","send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure("user_app_123",NULL,"send_mail"))!=NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure("user_app_123","email_dest_123",NULL))!=NULL)return MUNIT_FAIL;
  if(check_transport(create_bmd_structure(NULL,NULL,NULL))!=NULL)return MUNIT_FAIL;
  if(check_transport(NULL)!=NULL)return MUNIT_FAIL;
  return MUNIT_OK;
}

static MunitResult test_update_status(const MunitParameter params[], void* user_data) {

  munit_assert_false((update_status("udusd","failed","fail ho gya")));
  munit_assert_true((update_status("1","failed","fail ho gya due to testing")));
  munit_assert_true((update_status("10","failed","fail ho gya due to testing")));
  munit_assert_false((update_status("10d0","failed","fail ho gya due to testing")));
  munit_assert_true((update_status("1000","failed","fail ho gya due to binary testing")));
  munit_assert_false((update_status("o*o*o*o","failed","fail ho gya due to binary testing")));
  return MUNIT_OK;
}

static MunitResult test_validation(const MunitParameter params[], void* user_data){
  MYSQL *con = connect_mysql();

  munit_assert_true((validation(con, create_bmd_structure("user_app_123","email_dest_123","send_mail"),"json")));
  munit_assert_false((validation(con, create_bmd_structure("user_app_123","email_dest_123","send_mail"),NULL)));
  munit_assert_false((validation(NULL, create_bmd_structure("user_app_123","email_dest_123","send_mail"),"json")));
  munit_assert_false((validation(con, create_bmd_structure("invalid_sender","email_dest_123","send_mail"),"json")));
  munit_assert_false((validation(con, create_bmd_structure("user_app_123","invalid_destination","send_mail"),"json")));
  munit_assert_false((validation(con, create_bmd_structure("user_app_123","email_dest_123","wrong_message_type"),"json")));
  munit_assert_false((validation(con, NULL,"json")));
  return MUNIT_OK;
}

static MunitResult test_authentication(const MunitParameter params[], void* user_data){
  munit_assert_true(Authentication("63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c"));
  munit_assert_false(Authentication("63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113d"));
  munit_assert_false(Authentication("wrong_auth_token"));
  munit_assert_false(Authentication("it_should_fail"));
  munit_assert_false(Authentication("testing_is_going_in_right_direction"));
  munit_assert_false(Authentication(NULL));

  return MUNIT_OK;
}

char* build_bmd_file(bmd * msg){
  char * file_name="bmd.xml";
  FILE * fp=fopen(file_name,"w");
  fprintf(fp,
  "<BMD>\n\
  <Envelop>\n\
      <MessageID>%s</MessageID>\n\
      <MessageType>%s</MessageType>\n\
      <Sender>%s</Sender>\n\
      <Destination>%s</Destination>\n\
      <CreationDateTime>%s</CreationDateTime>\n\
      <Signature>%s</Signature>\n\
      <ReferenceID>%s</ReferenceID>\n\
  </Envelop>\n\
  <Payload>%s</Payload>\n\
  </BMD>",\
  msg->envelop.MessageID,msg->envelop.MessageType,msg->envelop.Sender,msg->envelop.Destination,\
  msg->envelop.CreationDateTime,msg->envelop.Signature,msg->envelop.ReferenceID,msg->payload);
  fclose(fp);
  return file_name;
}

bool compare_object(bmd* b1, bmd* b2){
  return (
    strcmp(b1->envelop.MessageID,b2->envelop.MessageID)==0 && \
    strcmp(b1->envelop.MessageType,b2->envelop.MessageType)==0 && \
    strcmp(b1->envelop.Sender,b2->envelop.Sender)==0 && \
    strcmp(b1->envelop.Destination,b2->envelop.Destination)==0 && \
    strcmp(b1->envelop.CreationDateTime,b2->envelop.CreationDateTime)==0 && \
    strcmp(b1->envelop.Signature,b2->envelop.Signature)==0 && \
    strcmp(b1->envelop.ReferenceID,b2->envelop.ReferenceID)==0 && \
    strcmp(b1->payload,b2->payload)==0
  );
}

static MunitResult test_xml_parsing(const MunitParameter params[], void* user_data){
  bmd * B=create_bmd_structure("user_app_123","email_dest_123","send_mail");
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  if(do_parse(NULL)!=NULL)return MUNIT_FAIL;
  if(do_parse("isdvn")!=NULL)return MUNIT_FAIL;
  B=create_bmd_structure("user_app_123","","send_mail");
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  B=create_bmd_structure("","email_dest_123","send_mail");
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  B=create_bmd_structure("user_app_123","email_dest_123","");
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  B=create_bmd_structure("user_app_123",NULL,"send_mail");
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  B=create_bmd_structure(NULL,"email_dest_123","send_mail");
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  B=create_bmd_structure("user_app_123","email_dest_123",NULL);
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  B=create_bmd_structure(NULL,NULL,NULL);
  munit_assert_true(compare_object(do_parse(build_bmd_file(B)),B));
  free(B);
  remove("bmd.xml");
  return MUNIT_OK;
}

static MunitResult test_insert(const MunitParameter params[], void* data) {
  MYSQL * con =connect_mysql();
  if(insert(con,create_bmd_structure("user_app_123","http_dest_123","hit_api"),"munit.h")==NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure("user_app_123","email_dest_123","send_mail"),"munit.h")==NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure("user_app_123","ftp_dest_123","transfer_file"),"munit.h")==NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure(NULL,"http_dest_123","hit_api"),"munit.h")==NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure("user_app_123",NULL,"send_mail"),"munit.h")==NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure("user_app_123","ftp_dest_123",NULL),"munit.h")==NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure("user_app_123","http_dest_123","hit_api"),NULL)!=NULL)return MUNIT_FAIL;
  if(insert(NULL,create_bmd_structure("user_app_123","http_dest_123","hit_api"),"munit.h")!=NULL)return MUNIT_FAIL;
  if(insert(con,NULL,"munit.h")!=NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure("user_,,,,app_123","http_dest_123","hit_api"),"munit.h")==NULL)return MUNIT_FAIL;
  if(insert(con,create_bmd_structure("user_app_123","http_dest_123","hit_api"),"mufdnit.h")!=NULL)return MUNIT_FAIL;
  if(insert(NULL,NULL,NULL)!=NULL)return MUNIT_FAIL;
  return MUNIT_OK;
}

static MunitResult test_mysql_connection(const MunitParameter params[], void* user_data){
  if(connect_mysql()==NULL)return MUNIT_SKIP;
  return MUNIT_OK;
}

static MunitResult test_esb_request_handler(const MunitParameter params[], void* user_data){
  return MUNIT_SKIP;
}

static MunitResult test_database_poller(const MunitParameter params[], void* user_data){
  return MUNIT_SKIP;
}

/* The setup function, if you provide one, for a test will be run
 * before the test, and the return value will be passed as the sole
 * parameter to the test function. */
static void*
test_compare_setup(const MunitParameter params[], void* user_data) {
  (void) params;

  munit_assert_string_equal(user_data, "µnit");
  return (void*) (uintptr_t) 0xdeadbeef;
}

/* To clean up after a test, you can use a tear down function.  The
 * fixture argument is the value returned by the setup function
 * above. */
static void
test_compare_tear_down(void* fixture) {
  munit_assert_ptr_equal(fixture, (void*)(uintptr_t)0xdeadbeef);
}

static MunitParameterEnum test_params[]={NULL};

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
  { (char*)"/test_for_update_status_function", test_update_status, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_transform_to_json_function", test_transform_to_json, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_transform_to_csv_function", test_transform_to_csv, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_transform_to_html_function", test_transform_to_html, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_ftp_function", test_ftp, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_http_function", test_http, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_send_mail", test_send_mail, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_check_transport", test_check_transport, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { (char*)"/test_for_check_transform", test_check_transform, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*)"/test_for_authentication", test_authentication, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*)"/test_for_validation", test_validation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*)"/test_for_xml_parsing", test_xml_parsing, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*)"/test_for_mysql_connection", test_mysql_connection, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*)"/test_for_insert", test_insert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*)"/test_for_esb_request_handler", test_esb_request_handler, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {(char*)"/test_for_database_poller", test_database_poller, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "",
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

#include <stdlib.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
