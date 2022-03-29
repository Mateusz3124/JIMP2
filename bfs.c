#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include "generator.h"
#include "bfs.h"

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
		if(nodes[i]==-1)
			x++;
	}
	if(x == 0)
		return 0;
	else
		return 1;
}

