#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include"ELTPRIM.h"

typedef struct structNode {
ELEMENT info;
int weight;
struct structNode* next;
} structNode, *Node;

typedef struct {
int V;
Node adjList[100];
} strucGraph, *Graph;


#endif // GRAPH_H_INCLUDED
