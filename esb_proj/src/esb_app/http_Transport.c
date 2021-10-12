#include <stdio.h>
#include "http_transport.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <string.h>

bool http(char *http_url, char *filename)
{
    if(!http_url || !filename)return false;
    //create new buffer to copy file input
    FILE * fp = fopen(filename, "r");
    if(fp==NULL)return false;
    char buffer[1024];
    char c;
    int j=0;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == 10)
            continue;
        if(j==1023)return false;
        buffer[j++] = c;
    }
    buffer[j]='\0';
    fclose(fp);             //close the resource

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        //printf("\nString: %s \ndone\n", string);
        curl_easy_setopt(curl, CURLOPT_URL, http_url);      //server's url
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer); //post the file data
        FILE *wfd = fopen("foo.txt", "w");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, wfd);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        res = curl_easy_perform(curl);
        remove("foo.txt");
        //checking status code
        if (res == CURLE_OK)
        {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code >= 200 && response_code <= 299 && response_code != CURLE_ABORTED_BY_CALLBACK)
            {
                return true;
            }
            else{
              return false;
            }
        }
        else
        {
            return false;
        }

        curl_easy_cleanup(curl);
    }
    else{
      curl_global_cleanup();
      return false;
    }
}

/*void main()
{
    char* url="https://reqbin.com/echo/post/json";
    //char* url="https://httpbin.org/anything";
    //char *url = "https://getpantry.cloud/apiv1/pantry/5593b275-131d-46e5-800a-016b65c587b1/basket/testBasket";
    char *filename = "BMD.xml";
    http(url, filename); //call http function
  }*/
