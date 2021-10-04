#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "smtp.h"
#define FROM_ADDR    "<pavankolur2000@gmail.com>"
#define CC_ADDR      "<pavankolur121@gmail.com>"

int send_mail(char *to, char *text) { 
  //text is file path for JSON

    printf("Sending mail to %s\n", to);

  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  
  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */ 
    curl_easy_setopt(curl, CURLOPT_USERNAME, "pavankolur2000@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "prideoflion");//enter password

    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
 
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);
 
    recipients = curl_slist_append(recipients, to);
    recipients = curl_slist_append(recipients, CC_ADDR);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
 
    //JSON file to be send 
    char* filepath= text;
    FILE *fd = fopen(filepath, "r");
//         curl_easy_setopt(curl, CURLOPT_READDATA, fp);
    curl_easy_setopt(curl, CURLOPT_READDATA,fd);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
    /* Send the message */ 
    res = curl_easy_perform(curl);
 
    /* Check for errors */ 
    if(res != CURLE_OK)
     { fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
              return -1;
     }
    /* Free the list of recipients */ 
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
  }
  printf("...............................Mail sent successfully..............................\n");
 return 0;
}
int main()
{
 // char *s = "HELL0";
  int n=send_mail("pavana.1si17ee023@gmail.com","/home/pavankolur/Bat/esb_proj/src/esb_app/Output.json");
  
}

