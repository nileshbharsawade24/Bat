#include <stdio.h>
#include <stdlib.h>
int i = 0;
/*transforming to json*/

char *transform_to_json(char *source, char *payload)
{
  i++;

  char filename[20];
  char *file = malloc(20);
  strcpy(file,filename);

  char op[20001];
  snprintf(filename, sizeof(filename), "output_%d.json", i);
  snprintf(op, sizeof(op), "{\n\t\"source\": \"%s\",\n\t\"payload\": \"%s\"\n}", source, payload);
  printf("successfully transformed to JSON, filename=%s\n",filename);
  FILE *fp = fopen(filename, "w"); //open that file
  fprintf(fp, "%s", op);
  fclose(fp);
  char *file = filename;
  return file;
}

/*transforming to csv*/

char *transform_to_csv(char *source, char *payload)
{
  i++;

  char filename[20];
  char *file = malloc(20);
  strcpy(file,filename);

  char op[20001];
  snprintf(filename, sizeof(filename), "output_%d.csv", i);
  snprintf(op, sizeof(op), "source\tpayload\n%s\t%s\n", source, payload);
  printf("successfully transformed to CSV, filename=%s\n",filename);
  FILE *fp = fopen(filename, "w"); //open that file
  fprintf(fp, "%s", op);
  fclose(fp);
  char *file = filename;
  return file;
}

//transforming to html

char * transform_to_html(char *source, char *payload){

  i++;
  char filename[20];
  char *file = malloc(20);
  strcpy(file,filename);
  sprintf(filename,sizeof(filename), "output_%d.html",i);

  FILE *fp= fopen(filename,"w");
    fprintf(fp,"<!DOCTYPE html>");
    fprintf(fp,"    <html>");
    fprintf(fp,"        <head>");
    fprintf(fp,"            <meta charset='UTF-8'>");
    fprintf(fp,"                <title>XML To HTML</title>");
    fprintf(fp,"        </head>");
    fprintf(fp,"    <body>");
    fprintf(fp,"        <table border=1>\n");
    fprintf(fp,"            <thead>\n");
    fprintf(fp,"                <tr>\n");
    fprintf(fp,"                    <th>Payload</th>\n");
    fprintf(fp,"                </tr>\n");
    fprintf(fp,"            </thead>\n");
    fprintf(fp,"            <tbody>\n");
    fprintf(fp,"                <tr>\n");
    fprintf(fp,"                    <td>%s</td>\n",payload);
    fprintf(fp,"                </tr>\n");
    fprintf(fp,"            </tbody>\n");
    fprintf(fp,"        </table>\n");
    fprintf(fp,"    </body>\n");
    fprintf(fp,"</html>\n");

    fclose(fp);

    return file;

}


/*transforming to xml*/

char *transform_to_xml(char *source, char *payload)
{
  i++;

  char filename[20];
  char *file = malloc(20);
  strcpy(file,filename);

  char op[20001];
  snprintf(filename, sizeof(filename), "output_%d.xml", i);
  snprintf(op, sizeof(op), "<BMD>\n\t<Envelop>\n\t\t<source>%s</source>\n\t\t<payload>%s</payload>\n\t</Envelop>\n</BMD>", source, payload);
  printf("successfully transformed to XML, filename=%s\n",filename);
  FILE *fp = fopen(filename, "w"); //open that file
  fprintf(fp, "%s", op);
  fclose(fp);
  char *file = filename;
  return file;
}
