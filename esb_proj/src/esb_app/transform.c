#include<stdio.h>
#include<stdlib.h>

/*transforming to json*/

char* transform_to_json(char* source, char* payload)
{
  char filename[] = "Output.json";
  char *file=filename;
  char op[20001];
  snprintf(op,sizeof(op),"{\n\tsource: %s,\n\tpayload: %s\n}",source,payload);
  printf("successfully transformed to json with data....\n%s\n",op);
  FILE *fp = fopen( filename, "w"); //open that file
  fprintf(fp, "%s", op);
  fclose(fp);
  
  return filename;
}

/*transforming to csv*/

char* transform_to_csv(char* source, char* payload)
{
  char filename[] = "output.csv";
  mkstemp(filename);
  char *file=filename;
  char op[20001];
  snprintf(op,sizeof(op),"source\tpayload\n%s\t%s\n",source,payload);
  printf("successfully transformed to csv with data....\n%s\n",op);
  FILE *fp = fopen( filename, "w"); //open that file
  fprintf(fp, "%s", op);
  fclose(fp);
  return filename;
}

	
  
