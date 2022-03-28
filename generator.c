#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>

typedef struct Node // docelowo strukura w meinie
{
  int *connected;
  double *weight;
}Node;

double get_random_number(double min_weight, double max_weight){
	double r = (double)rand() / RAND_MAX;
	return(min_weight + (max_weight - min_weight)*r);
}

int edge_exists(int edge_mode){
	double existance_chance = 0.7;		// prawdopodobienstwo istnienia krawedzi
	if(edge_mode == 0){			// wszystkie krawedzie istnieja
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
	for(int r=0; r<rows; r++){
		for(int c=0; c<columns; c++){
			graph[n].connected = malloc(sizeof(int *)*4);
			graph[n].weight = malloc(sizeof(int *)*4);
			for(int i=0; i<4; i++){		//wypelnaimy wszystko -1 bo czemu nie
				graph[n].connected[i] = -1;
				graph[n].weight[i] = -1.0;
			} 
			if(r != 0 && edge_exists(edges) == 0){ 		// nie na gorze i istnieje krawedz
				graph[n].connected[0] = n-columns;
				graph[n].weight[0] = get_random_number(min_weight, max_weight); 
			}
			if(c != 0 && edge_exists(edges) == 0){   // nie po lewej
				graph[n].connected[1] = n-1;
				graph[n].weight[1] = get_random_number(min_weight, max_weight); 
			}
			if(c != columns-1 && edge_exists(edges) == 0){   // nie po prawej
				graph[n].connected[2] = n+1;
				graph[n].weight[2] = get_random_number(min_weight, max_weight); 
			}
			if(r != rows-1 && edge_exists(edges) == 0){   // nie na dole
				graph[n].connected[3] = n+columns;
				graph[n].weight[3] = get_random_number(min_weight, max_weight); 
			}
		n++;
		}
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
}

int main(){ // Szybki test modulu
	int	rows = 5;
	int columns = 5;
	Node *graph = generate(1, 0, columns, rows, 0);
	write(columns, rows, graph, "XDtestmoduługeneratorXD");
	return 0;
}
