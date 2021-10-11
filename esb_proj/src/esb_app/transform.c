#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// int i = 0;
/*transforming to json*/

char *transform_to_json(char *token, char *payload)
{
  char *file = malloc(50*(sizeof(char)));
  char op[20001];
  sprintf(file, "./%s.json",token);  char* sender=NULL;
  char* field1=strtok(payload,",");
  char* field2=payload;
  snprintf(op, sizeof(op), "{\n\t\"acc_no\": \"%s\",\n\t\"acc_type\": \"%s\"\n}", field1, field2);
  FILE *fp = fopen(file, "w"); //open that file
  fprintf(fp, "%s", op);
  fclose(fp);
  return file;
}

/*transforming to csv*/
char * transform_to_csv(char *token, char *payload)
{
  char * fpath=malloc(50*(sizeof(char)));
  sprintf(fpath, ".tmp/%s.csv",token);
  FILE *fp = fopen(fpath, "w"); //open that file
  fprintf(fp, "%s",payload);
  fclose(fp);
  return fpath;
}

//transforming to html

char * transform_to_html(char *token, char *payload){

  char * filename=malloc(50*(sizeof(char)));
  sprintf(filename,".tmp/%s.html",token);

  FILE *fp= fopen(filename,"w");
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
