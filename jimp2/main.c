#include<stdio.h>
#include<stdlib.h>
#include <time.h>  
#include <string.h>
#include "generator.h"
#include "bfs.h"
#include "reader.h"

#define BUFSIZE 8192





int main(int argc, char **argv )
{
	double min_weight = 0.0;
	double max_weight = 1.0;
	int rows = 1;
	int columns = 1;
	int m = 1; // 1 all, 2 connected, 3 random 
	char *out1 = "text";
	char *in = malloc(286*sizeof(char));
    int check_connection = 0; // czy odpalac BFSa
    int edges = 1; // metoda tworzenia krawedzi
    int npaths = 0; // liczba siciezek ktore trza znalezc
    int *paths; // tablic przehowujaca poczatki i konce sciezek ktore trzeba znalezc w formacie pocz1 kon1 pocz2 ...


	char **arguments = malloc((argc+1)*sizeof(char[10])); // przepisujemy argv do innej listy
	for (int i=0; i<argc; i++)
        arguments[i] = argv[i];
    arguments[argc] = "END"; // wstawiamy znacznik konca listy argumentow


    int i = 1; // zmienna do iterowania po argumentach
    int bad_input = 0; // sprawdzamy na koncu petli
	while (i < argc) { 
		char *x = arguments[i];

		if (!strcmp(x, "--output"))
            out1 = arguments[++i];
		else if (!strcmp(x, "--min-weight")){
            if (atof(arguments[++i]) != 0 || arguments[i+1] == "0") 
			    min_weight = atof(arguments[i]);
            else
                bad_input = 1;
        }
		else if (!strcmp(x, "--max-weight")){
			if (atof(arguments[++i]) != 0 || arguments[i+1] == "0") 
			    max_weight = atof(arguments[i]);
            else
                bad_input = 1;
        }
		else if (!strcmp(x, "--rows")){
			if (atoi(arguments[++i]) != 0 || arguments[i+1] == "0") 
			    rows = atoi(arguments[i]);
            else
                bad_input = 1;
        }
		else if (!strcmp(x, "--columns")){
			if (atoi(arguments[++i]) != 0 || arguments[i+1] == "0") 
			    columns = atoi(arguments[i]);
            else
                bad_input = 1;
        }
        else if (!strcmp(x, "--check-connection"))
			check_connection = 1;

		else if (!strcmp(x, "--path")){ // sciezki do znalezienia --path liczba_sciezek poczatek1 koniec1 poczatek2 ..
			if (atoi(arguments[++i]) <= 0){
                fprintf(stderr, "incorrect input\n"); // tutaj zamiast bad_input ubijamy program odrazu bo bylby blad
	        	exit (EXIT_FAILURE);
	        }
            npaths = atoi(arguments[i]);
            paths = malloc(2*npaths*sizeof(int)); // trzeba pamietac zeby free() potem zrobic 
            for (int j=0; j<2*npaths; j++){
                if (atoi(arguments[i+1]) != 0 || arguments[i+1] == "0") 
                    paths[j] = atoi(arguments[++i]);
                else {
                    fprintf (stderr, "incorrect input\n");
			        exit (EXIT_FAILURE);
                }
            }
        }
    	else if (!strcmp(x, "--edges")){
            char *y = arguments[++i];
			if (!strcmp(y, "all"))
				edges = 1;
			else if (!strcmp(y, "connected"))
				edges = 2;
			else if (!strcmp(y, "random"))
				edges = 3;
			else 
                bad_input = 1;
        }
		else 
			bad_input = 1;
        
        if (bad_input == 1){
            fprintf (stderr, "incorrect input\n");
			exit (EXIT_FAILURE);
        }
		i++;
	}
    free(arguments);
	if(rows <= 0){
		fprintf(stderr, "incorrect lines number\n");
		exit (EXIT_FAILURE);
	}
	if(columns <= 0){
		fprintf(stderr, "incorrect colums number\n");
		exit (EXIT_FAILURE);
	}
	if(min_weight < 0 || max_weight < 0){
		fprintf(stderr, "incorrect lower limit or incorrect higher limit\n");
		exit (EXIT_FAILURE);
	}
	if(max_weight < min_weight){
		fprintf(stderr, "higher limit is too low\n");
		exit (EXIT_FAILURE);
	}

    printf("rows: %d, columns: %d\n", rows, columns); // TEST
	printf("edge mode: %d\n", edges);
    printf("Paths: ");
    for (int i=0; i<2*npaths; i++)
        printf("%d ", paths[i]);
    printf("\n");
    printf("min_weight: %f, max_weight: %f\n", min_weight, max_weight);
    printf("output file name: %s\n", out1); // KONIEC TESTU



	
	
	struct Node* graph = malloc(rows*columns* sizeof *graph);
	
	graph =generate (max_weight, min_weight, columns, rows, edges);
	write (columns, rows, graph, out1);
	

	
	FILE *out = fopen(out1,"r");
	
	if (out == NULL) 
	{
      fprintf (stderr, "can not write in file: %s\n\n",  out1);
      exit (EXIT_FAILURE);
	}
		if (fscanf(out, "%i %i", &rows, &columns) != 2)
		fprintf(stderr,"bad data format inside file");
	fclose(out);
	
	struct Node* main = malloc(rows*columns* sizeof *main);
	

	
	main = reader(out1);
	if( bfs(main,columns ,rows) == 0)
		printf("\ncoherent graph\n");
	else
		printf("\nincoherent graph\n");
	return 0;

}