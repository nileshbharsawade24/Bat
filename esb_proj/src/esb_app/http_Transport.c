#include <stdio.h>
#include "http_transport.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <string.h>

int http(char *http_url, char *filename)
{
    FILE *fp, *f;
    fp = fopen(filename, "r");
    int c;
    int i = 0;
    //reading the file size
    while ((c = fgetc(fp)) != EOF)
    {
        i++;
    }
    fclose(fp); //close the resource

    //create new buffer to copy file input
    f = fopen(filename, "r");
    char buffer[i];
    int j = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == 10)
            continue;
        buffer[j] = c;
        j++;
    }
    char *string = buffer; //assiging string to store the input file data
    fclose(f);             //close the resource

    int status = 0;
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        //printf("\nString: %s \ndone\n", string);
        curl_easy_setopt(curl, CURLOPT_URL, http_url);      //server's url
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, string); //post the file data
        res = curl_easy_perform(curl);

        //checking status code
        if (res == CURLE_OK)
        {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code >= 200 && response_code <= 299 && response_code != CURLE_ABORTED_BY_CALLBACK)
            {
                printf("\nrequest succesfully sent with response Code %ld\n", response_code);
                status = 1;
            }
        }

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return status;
}

/*void main()
{
    char* url="https://reqbin.com/echo/post/json";
    //char* url="https://httpbin.org/anything";
    //char *url = "https://getpantry.cloud/apiv1/pantry/5593b275-131d-46e5-800a-016b65c587b1/basket/testBasket";
    char *filename = "BMD.xml";
    http(url, filename); //call http function
  }*/
