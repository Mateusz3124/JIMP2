#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include "generator.h"
#include "reader.h"

#define BUFSIZE 8192

struct Node* reader(char*out1)
{
	FILE *out = fopen(out1,"r");
	
	if (out == NULL) 
	{
      fprintf (stderr, "can not write in file: %s\n\n",  out1);
      exit (EXIT_FAILURE);
	}
	
	
	int rows;
	int columns;
	int i =0;
	int k=0;
	int p=0;
	char buf[BUFSIZE];
	int *nconnected = malloc(sizeof(int)*5);
	double *nweight = malloc(sizeof(double)*5);
	
	if (fscanf(out, "%i %i", &rows, &columns) != 2)
		fprintf(stderr,"bad data format inside file");
	
	struct Node* head = malloc(rows*columns* sizeof *head);
	char *w;
	fgets( buf, BUFSIZE, out );
	while( fgets( buf, BUFSIZE, out ) != NULL ) {
		for(i =0; i<5;i++)
		{
			nconnected[i]=-1;
			nweight[i]=-1;
		}
		w = buf;
		k=0;
		sscanf(w,"%i :%lf %i :%lf %i :%lf %i :%lf",&(nconnected[k]),&(nweight[k]), &(nconnected[k+1]),&(nweight[k+1]) ,&(nconnected[k+2]),&(nweight[k+2]), &(nconnected[k+3]),&(nweight[k+3]));
		k =0;
			head[p].connected = malloc(sizeof(int *)*5);
			head[p].weight = malloc(sizeof(double *)*5);
			memcpy(head[p].connected, nconnected,5*sizeof(int));
		    memcpy(head[p].weight, nweight,5*sizeof(double));
		p++;
	}
	fclose(out);
	return head;
}

