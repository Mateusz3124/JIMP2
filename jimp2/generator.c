#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include "generator.h"
#include "bfs.h"

double get_random_number(double min_weight, double max_weight){
	double r = (double)rand() / RAND_MAX;
	return(min_weight + (max_weight - min_weight)*r);
}

int edge_exists(int edge_mode){
	double existance_chance = 0.7;		// prawdopodobienstwo istnienia krawedzi
	if(edge_mode == 1){			// wszystkie krawedzie istnieja
		return 0;
	}
	if(get_random_number(0.0, 1.0) >= (1.0 - existance_chance)){
		return 0;
	}else{
		return 1;
	}
}

Node* generate(int max_weight, int min_weight, int columns, int rows, int edges){
	Node* graph = malloc(columns*rows*sizeof *graph);
	srand(time(NULL));
	int n = 0; 	// numer rozpatrywanego wierzcholka
	int p;
	for(int r=0; r<rows; r++){
		for(int c=0; c<columns; c++){
			graph[n].connected = malloc(sizeof(int *)*5);
			graph[n].weight = malloc(sizeof(int *)*5);
			for(int i=0; i<5; i++){		//wypelnaimy wszystko -1 bo czemu nie
				graph[n].connected[i] = -1;
				graph[n].weight[i] = -1.0;
			} 
			p = 0;
			if(r != 0 && edge_exists(edges) == 0){ 		// nie na gorze i istnieje krawedz
				graph[n].connected[p] = n-columns;
				graph[n].weight[p++] = get_random_number(min_weight, max_weight); 
			}
			if(c != 0 && edge_exists(edges) == 0){   // nie po lewej
				graph[n].connected[p] = n-1;
				graph[n].weight[p++] = get_random_number(min_weight, max_weight); 
			}
			if(c != columns-1 && edge_exists(edges) == 0){   // nie po prawej
				graph[n].connected[p] = n+1;
				graph[n].weight[p++] = get_random_number(min_weight, max_weight); 
			}
			if(r != rows-1 && edge_exists(edges) == 0){   // nie na dole
				graph[n].connected[p] = n+columns;
				graph[n].weight[p++] = get_random_number(min_weight, max_weight); 
			}
		n++;
		}
	}
	if(bfs(graph, columns, rows)==1)  
		{
		generate(max_weight, min_weight, columns, rows, edges);
		}
	return graph;
}

void write(int columns, int rows, struct Node *graph, char *output){
	FILE *out = fopen(output,"w");
	if (out == NULL) 
	{
      fprintf (stderr, "can not write in file: %s\n",  output);
      exit (EXIT_FAILURE);
	}
	fprintf(out, "%d %d\n", rows, columns);
	for(int n=0; n<rows*columns; n++){
		for(int i=0; i<4; i++){
			if(graph[n].connected[i]>=0){ 	// jesli -1 to nie ma polaczenia
				fprintf(out, "%d ", graph[n].connected[i]);
				fprintf(out, ":%f  ", graph[n].weight[i]);
			}
		}
		fprintf(out, "\n");
	}
	fclose(out);
}

