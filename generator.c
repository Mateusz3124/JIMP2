#include<stdio.h>
#include<stdlib.h>
#include <time.h>  
#include <getopt.h>

void write(double s, double e, int w, int k, int m, char *out1)
{
	int t =1; // symbolizuje obecny wiersz
	int l =0; // obecny punkt w ktorym sie znajdujemy
	
	FILE *out = fopen(out1,"w");

	if (out == NULL) 
	{
      fprintf (stderr, "can not read file: %s\n\n",  out1);
      exit (EXIT_FAILURE);
	}
	  
	srand(time(NULL));
	
	fprintf(out, "%d %d\n", w, k);
	
	double temp =0.0;

	int temp2 = 0;
	int *temp3 = malloc(w*k*sizeof(temp3));
	int g = 0;
	int g2 =0;
	
	for(int h=0;h<w;h++)
	{
		
	for(int i=0;i<k; i++)
	{	

		double f = (double)rand() / RAND_MAX;
		
		if(t !=1) //na gorze
		{
			if(temp3[g] !=l)
			{
			fprintf(out,"%d ",l-k);
			fprintf(out,":%f  ",s+(e-s)*f);
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
			}
			else
				temp3[g2++]=l+k;
		}

		fprintf(out,"\n"); // koniec lini(wszystkie polaczenia do danego puntu zostaly juz zapisane)
		l++;
	}
	
	t++;
	
	}
	free(temp3);
}

int main(int argc, char **argv )
{
	
	double s =0.0;
	double e =1.0;
	int w = 7;
	int k =4;
	int m = 1; // zawsze sa polaczenia
	char *out1 = "text";
	int opt;
	
	while ((opt = getopt (argc, argv, "w:k:s:e:o:m:")) != -1) 
	{
		
	switch (opt) 
	{
	case 'o':
	out1= optarg; // gdzie zapisywac automatycznie do pliku text
	break;
	case 's':
	s= atoi(optarg);// dolny limit wagi
	break;
	case 'e':
	e= atoi(optarg); // gorny limit wagi
	break;
	case 'w':
	w = atoi(optarg); // liczba wierszy
	break;
	case 'k':
	k = atoi(optarg);  // liczba kolumn
	break;
	case 'm':
	m = atoi(optarg); //
	break;
	
	default:                   
      fprintf (stderr, "bad input");
      exit (EXIT_FAILURE);
	}
	
	}
	
	write(s,e,w,k,m,out1);
	
	return 0;
}
