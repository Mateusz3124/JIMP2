#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include "generator.h"
#include "bfs.h"

stos_t* put_on_stack(stos_t* head, int b){
	if(head == NULL)
	{
		stos_t *nw = malloc(sizeof *nw);
		nw->node = b;
		nw->next = NULL;
		return nw;	
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

int top_of_stack(stos_t* head){
	return head->node;
}

stos_t* delete(stos_t* head){
	if(head->next != NULL)
	{
		stos_t* tmp = head;
		head = head->next;
		free(tmp);
		return head;
	}
	else
	{
		free(head);
		return NULL;
	}
}


int bfs(struct Node*head,int k, int w)
{
	int *nodes = malloc(w*k* sizeof(int));
	int number = k*w;
	int temp =0;
	int x =0;
	for(int i =0; i<number;i++)
	{
		nodes[i]=-1;
	}
	stos_t *stos = NULL;
	stos = put_on_stack(stos, 0);
	nodes[0]=0;
	
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
	free(nodes);
	if(x == 0)
		return 0;
	else
		return 1;
}

