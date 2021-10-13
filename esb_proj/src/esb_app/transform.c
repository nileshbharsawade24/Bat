#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*transforming to json*/

char *transform_to_json(char *token, char *payload)
{
  if(!token || !payload)return NULL;

  char *file = malloc(50*(sizeof(char)));
  char op[1001];
  if(sprintf(file, ".tmp/%s.json",token)>49){ //creating file in tmp folder
    return NULL;
  }
  char* field1=strtok(payload,",");
  char* field2=payload;
  if(strlen(payload)>900)return NULL;
  snprintf(op, sizeof(op), "{\n\t\"acc_no\": \"%s\",\n\t\"acc_type\": \"%s\"\n}", field1, field2);
  FILE *fp = fopen(file, "w"); //opening file in writing mode
  if(fp==NULL){
    return NULL;
  }
  fprintf(fp, "%s", op);
  fclose(fp);
  return file;
}

/*transforming to csv*/
char * transform_to_csv(char *token, char *payload)
{
  if(!token || !payload)return NULL;
  char * fpath=malloc(50*(sizeof(char)));

  if(sprintf(fpath, ".tmp/%s.csv",token)>49)return NULL;

  FILE *fp = fopen(fpath, "w"); //opening the file in w mode
  if(fp==NULL)return NULL;
  fprintf(fp, "%s",payload);
  fclose(fp);
  return fpath;
}

//transforming to html

char * transform_to_html(char *token, char *payload){
  if(!token || !payload)return NULL;
  char * filename=malloc(50*(sizeof(char)));
  if(sprintf(filename,".tmp/%s.html",token)>49)return NULL;

  FILE *fp= fopen(filename,"w");
  if(fp==NULL)return NULL;
    fprintf(fp,"<!DOCTYPE html>\n");
    fprintf(fp,"    <html>\n");
    fprintf(fp,"        <head>\n");
    fprintf(fp,"            <meta charset='UTF-8'>\n");
    fprintf(fp,"                <title>XML To HTML</title>\n");
    fprintf(fp,"        </head>\n");
    fprintf(fp,"    <body>\n");
    fprintf(fp,"        <table border=1>\n");
    fprintf(fp,"            <thead>\n");
    fprintf(fp,"                <tr>\n");
    fprintf(fp,"                    <th>Payload</th>\n");
    fprintf(fp,"                </tr>\n");
    fprintf(fp,"            </thead>\n");
    fprintf(fp,"            <tbody>\n");
    fprintf(fp,"                <tr>\n");
    fprintf(fp,"                    <td>\n%s\n</td>\n",payload);
    fprintf(fp,"                </tr>\n");
    fprintf(fp,"            </tbody>\n");
    fprintf(fp,"        </table>\n");
    fprintf(fp,"    </body>\n");
    fprintf(fp,"</html>\n");

    fclose(fp);

    return filename;
}


// /*transforming to xml*/
//
// char *transform_to_xml(char *source, char *payload)
// {
//   // i++;
//
//   char * filename=malloc(50*sizeof(char));
//   char op[20001];
//   sprintf(filename, "output_%d.xml", i);
//   snprintf(op, sizeof(op), "<BMD>\n\t<Envelop>\n\t\t<source>%s</source>\n\t\t<payload>%s</payload>\n\t</Envelop>\n</BMD>", source, payload);
//   printf("successfully transformed to XML, filename=%s\n",filename);
//   FILE *fp = fopen(filename, "w"); //open that file
//   fprintf(fp, "%s", op);
//   fclose(fp);
//   return filename;
// }
