#ifndef GENERATOR_H
#define GENERATOR_H

typedef struct Node
{
  int *connected;
  double *weight;
}Node;

Node* generate (int max_weight, int min_weight, int columns, int rows, int edges);
void write (int columns, int rows, Node* graph, char *out1);
double get_random_number(double min_weight, double max_weight);
int edge_exists(int edge_mode);

#endif