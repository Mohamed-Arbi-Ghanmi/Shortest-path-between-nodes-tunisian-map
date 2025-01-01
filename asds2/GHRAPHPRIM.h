#ifndef GHRAPHPRIM_H_INCLUDED
#define GHRAPHPRIM_H_INCLUDED
#include "GRAPHSDD.h"
#include"ELTPRIM.h"
Node createNode(ELEMENT , int );
Graph creategraph(int );
void addEdge(Graph , ELEMENT , ELEMENT , int );
void printgraph(Graph );
void shortestpath(Graph , char , char );
void welcome();

#endif // GHRAPHPRIM_H_INCLUDED
