#include <stdio.h>
#include <stdlib.h>
int i = 0;
/*transforming to json*/

char *transform_to_json(char *source, char *payload)
{
  i++;
  char filename[50];

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
  char filename[50];

  //char *file=filename;
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

/*transforming to xml*/

char *transform_to_xml(char *source, char *payload)
{
  i++;
  char filename[50];

  //char *file=filename;
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
