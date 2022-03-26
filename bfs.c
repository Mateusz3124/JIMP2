#include<stdio.h>
#include<stdlib.h>
#include <time.h>  
#include <string.h>

#define BUFSIZE 8192

typedef struct Node
{
  int *connected;
  double *weight;
}Node;




typedef struct stos{
    int node;
    struct stos *next; 
} stos_t;

stos_t* put_on_stack(stos_t* head, int b){
	if(head == NULL)
	{
		stos_t *tmp = (stos_t*) malloc(sizeof tmp);
		tmp->node = b;
		tmp->next = NULL;
		return tmp;	
	}
	else{
	stos_t *tmp= head;                  
        while( tmp->next != NULL )      
             tmp= tmp->next;         
        tmp->next= malloc( sizeof * (tmp->next) );
        tmp->next->node= b;                       
        tmp->next->next= NULL;                    
		return head;  
	}
}

stos_t* stos_inic(int b){
	stos_t *tmp = (stos_t*) malloc(sizeof tmp);
	tmp->node = b;
	tmp->next = NULL;

	return tmp;	
}

int top_of_stack(stos_t* head){
	return head->node;
}

stos_t* delete(stos_t* head){
	if(head->next != NULL)
		return head->next;
	else
		return NULL;
}


int bfs(struct Node*head,int k, int w)
{
	int *nodes = malloc(w*k*sizeof(int));
	int number = k*w;
	int temp =0;
	int x =0;
	for(int i =0; i<number;i++)
	{
		nodes[i]=-1;
	}
	stos_t *stos = stos_inic(0);
	nodes [0] = 0;
	
	do{ 
		temp = top_of_stack(stos);
		stos = delete(stos);
		x=0;
		while(head[temp].connected[x] != -1)
		{
			if(nodes[head[temp].connected[x]] == -1)
			{
			stos = put_on_stack(stos, head[temp].connected[x]);
			nodes[head[temp].connected[x]]=temp;
			}
			x++;
		}
	}while(stos != NULL);
	
	
	x=0;
	for(int i =0; i<number;i++)
	{
		printf("%d\n",nodes[i]);
		if(nodes[i]==-1)
			x++;
	}
	if(x == 0)
		return 0;
	else
		return 1;
}

void write(double s, double e, int w, int k, int m, char *out1)
{
	int t =1; // symbolizuje obecny wiersz
	int l =0; // obecny punkt w ktorym sie znajdujemy
	
	FILE *out = fopen(out1,"w");

	if (out == NULL) 
	{
      fprintf (stderr, "can not write in file: %s\n\n",  out1);
      exit (EXIT_FAILURE);
	}
	  
	srand(time(NULL));
	
	fprintf(out, "%d %d\n", w, k);
	
	double temp =0.0;
	struct Node* headw = malloc(w*k* sizeof *headw);
	int temp2 = 0;
	int *temp3 = malloc(w*k*sizeof(temp3));
	int g = 0;
	int g2 =0;
	int p = 0;
	int x = 0;
	for(int h=0;h<w;h++)
	{
		
	for(int i=0;i<k; i++)
	{	
		headw[p].connected = malloc(sizeof(int *)*4);
		headw[p].weight = malloc(sizeof(double *)*4);
		double f = (double)rand() / RAND_MAX;
		x=0;
		if(t !=1) //na gorze
		{
			if(temp3[g] !=l)
			{
			fprintf(out,"%d ",l-k);
			fprintf(out,":%f  ",s+(e-s)*f);
			headw[p].connected[x] = l-k;
			headw[p].weight[x] = s+(e-s)*f;
			x++;
			}
			else
				g++;
		}

		f = (double)rand() / RAND_MAX;
		
		if(i != 0 ) // po lewej
		{
			if (temp2 == 0)
			{
			fprintf(out,"%d ",l-1);
			fprintf(out,":%f  ",s+(e-s)*f);
			headw[p].connected[x] = l-1;
			headw[p].weight[x] = s+(e-s)*f;
			x++;
			}
			else 
				temp2++;
		}
		
		f = (double)rand() / RAND_MAX;
		
		if (m !=1)
		{
			double temp = (double)rand() / RAND_MAX;
		}
		if(i !=k-1) // po prawej
		{
			if (temp <= 0.8)
			{
			fprintf(out,"%d ",l+1);
			fprintf(out,":%f  ",s+(e-s)*f);
			headw[p].connected[x] = l+1;
			headw[p].weight[x] = s+(e-s)*f;
			x++;
			}
			else
				temp2=-1;
		}
			
		
		f = (double)rand() / RAND_MAX;
		
		if (m !=1)
		{
			temp = (double)rand() / RAND_MAX;
		}
		if(t !=w) // na dole
		{
			if (temp <= 0.8)
			{
			fprintf(out,"%d ",l+k);
			fprintf(out,":%f  ",s+(e-s)*f);
			headw[p].connected[x] = l+k;
			headw[p].weight[x] = s+(e-s)*f;
			x++;
			}
			else
				temp3[g2++]=l+k;
		}
		fprintf(out,"\n"); // koniec lini(wszystkie polaczenia do danego puntu zostaly juz zapisane)
		l++;
		p++;
	}
	t++;
	}
	if (m ==2)
	{
		if(bfs(headw,k ,w)==1)  
		write(s,  e, w, k, m, out1);
	}
	
	free(headw);
	free(temp3);
	fclose(out);
}

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
	int *nconnected = malloc(sizeof(int)*4);
	double *nweight = malloc(sizeof(double)*4);
	
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
			head[p].connected = malloc(sizeof(int *)*4);
			head[p].weight = malloc(sizeof(double *)*4);
			memcpy(head[p].connected, nconnected,4*sizeof(int));
		    memcpy(head[p].weight, nweight,4*sizeof(double));
		p++;
	}
	fclose(out);
	return head;
}

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



	write(min_weight,max_weight,rows,columns,edges,out1);
	
	
	
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
