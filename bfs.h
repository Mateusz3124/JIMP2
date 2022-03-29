#ifndef bfs_H
#define bfs_H

typedef struct stos{
    int node;
    struct stos *next; 
} stos_t;

int bfs(struct Node*head,int k, int w);
#endif