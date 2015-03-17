#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "List.h"

typedef struct GraphObj * Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

void DFS(Graph G, List S);

void visit(Graph G, List S, int x);

/*** Other operations ***/
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif