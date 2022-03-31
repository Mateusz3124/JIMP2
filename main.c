#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>

#include "generator.h"
#include "reader.h"
#include "bfs.h"

#define cgenerate 0
#define cpath 2
#define checkconnection 1

int mode = -1; 
double min_weight = 0.0;
double max_weight = 1.0;
int rows = 1;
int columns = 1;
int m = 1; 
char *output = "text";
char *input = "text";
int check_connection = 0; 
int edges = 1; 
int npaths = 0; 
int *paths; 

int get_options (int argc ,char** argv)
{
    int i = 1;
    if(argc<3)
    { 
        return 1;
    }
    if (!strcmp(argv[i], "--generate"))
    {
        mode = 0;
        if(argc % 2 == 0)
	{ 
            return 1;
        }
        output = argv[++i];
        while(i<argc-1){
            i++;
            if (!strcmp(argv[i], "--min-weight"))
	    {
                if (atof(argv[++i]) != 0 || argv[i+1] == "0") 
                    min_weight = atof(argv[i]);
                else
                   return 1;
            }
		else if (!strcmp(argv[i], "--max-weight"))
	    {
                if (atof(argv[++i]) != 0 || argv[i+1] == "0") 
                    max_weight = atof(argv[i]);
                else
                    return 1;
            }
		else if (!strcmp(argv[i], "--rows"))
		{
                if (atoi(argv[++i]) != 0 || argv[i+1] == "0") 
                    rows = atoi(argv[i]);
                else
                   return 1;
            }
		else if (!strcmp(argv[i], "--columns"))
		{
                if (atoi(argv[++i]) != 0 || argv[i+1] == "0") 
                    columns = atoi(argv[i]);
                else
                    return 1;
            }
		else if (!strcmp(argv[i], "--edges"))
		{
                i++;
                if (!strcmp(argv[i], "all"))
                    edges = 0;
                else if (!strcmp(argv[i], "connected"))
                    edges = 1;
                else if (!strcmp(argv[i], "random"))
                    edges = 2;
                else 
                    return 1;
            }
		else
		{
                return 1;
            }
        }
        return 0;
    }
	else if(!strcmp(argv[i], "--check-connection"))
    {
        mode = 1;
        if(argc != 3)
	{ 
            return 1;
        }
        input = argv[++i];
        return 0;
    }
	else if(!strcmp(argv[i], "--path"))
	{
        mode = 2;
        if(argc<4)
	{
            return 1;
        }
        input = argv[++i];
        i++;
        if (atoi(argv[i]) != 0 || argv[i] == "0") 
            npaths = atoi(argv[i]);
        else
            return 1;
        if(argc != 2*npaths+4)
	{
            return 1;
        }
        paths = malloc(2*npaths*sizeof(int));
        for (int j=0; j<2*npaths; j++)
	{
            i++;
            if (atoi(argv[i]) != 0 || argv[i] == "0")
	    {
                paths[j] = atoi(argv[i]);
            }else{
                return 1;
            }
        }
        return 0;
    }else
	{
        return 1;
    }
}

int check_options(){
    if(rows <= 0)
    {
        fprintf(stderr, "incorrect rows number\n");
        return 1;
    }
    if(columns <= 0)
    {
        fprintf(stderr, "incorrect colums number\n");
        return 1;
    }
    if(min_weight < 0 || max_weight < 0)
    {
        fprintf(stderr, "incorrect lower limit or incorrect higher limit\n");
        return 1;
    }
    if(max_weight < min_weight)
    {
        fprintf(stderr, "higher limit is too low\n");
        return 1;
    }
    for(int i=0; i<2*npaths; i++)
    {
        if(paths[i]<0)
	{
            fprintf(stderr, "node %d does not exist\n", paths[i]);
            return 1;
        }
    }
    return 0;
}

int main  (int argc ,char** argv)
{
	srand(time(NULL));
    if(get_options(argc, argv) != 0)
    {
        fprintf(stderr, "incorrect input\n");
        exit (EXIT_FAILURE);
    }
    if(check_options() != 0)
    {
        exit (EXIT_FAILURE);
    }
    if(mode == cgenerate)
    {   

        Node *graph = generate(max_weight, min_weight, columns, rows, edges);
        write (columns, rows, graph, output);
		for(int i =0; i<rows*columns;i++)
		{
			free(graph[i].connected);
			free(graph[i].weight);
		}
		free(graph);
        exit (EXIT_SUCCESS);
    }
    else if(mode == checkconnection)
    {    
	
		FILE *in = fopen(input,"r");
		if (in == NULL) 
		{
			fprintf (stderr, "can not read from file: %s\n\n",  input);
			exit (EXIT_FAILURE);
		}
		if (fscanf(in, "%i %i", &rows, &columns) != 2)
			fprintf(stderr,"bad data format inside file");
		fclose(in);
	
        Node *graph = reader(input);
        int x = bfs(graph, columns, rows);
		for(int i =0; i<rows*columns;i++)
		{
			free(graph[i].connected);
			free(graph[i].weight);
		}
		free(graph);
        if(x == 0)
	{
            printf("Graph is coherent\n");
            exit(EXIT_SUCCESS);
        }
	    else if(x == 1)
	    {
            printf("Graph is incoherent\n");
            exit(EXIT_SUCCESS);
        }
	    else
	    {
            exit(EXIT_FAILURE);
        }
    }
	
	
	
	
	
	
    else if(mode == cpath)
    {    
        printf("Paths to find:\n");
        for (int i=0; i<2*npaths; i+=2)
	{
            printf("    %d -> %d\n", paths[i], paths[i+1]);
        }
        printf("Will be implemented soon :)\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "mode not chosen\n");
        exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
}
