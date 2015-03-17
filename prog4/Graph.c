//Ryan Brounley
//CMPS 101 Tantalo Winter 2015

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define WHITE 444
#define GRAY 666
#define BLACK 888
#define NIL -1
#define INF 0

/**Constructors - Destructors */
    //Creates a constructor for a graph object
    typedef struct GraphObj{
       	List* adj;
        int* color;
	int* parent;
	int* distance;
	int edges;
	int verts;
	int source;
    }GraphObj;	

    //creates a new Graph
    Graph newGraph(int n){
	Graph newGraph = malloc(sizeof(GraphObj));	
	newGraph->adj = calloc(n+1,sizeof(List));
	newGraph->color = calloc(n+1,sizeof(int));
	newGraph->parent = calloc(n+1,sizeof(int));
	newGraph->distance = calloc(n+1,sizeof(int));
	newGraph->edges = 0;
	newGraph->verts = n;
	newGraph->source = NIL;
	for(int i = 1; i <= n; i++){
		newGraph->adj[i] = newList();
		newGraph->color[i] = WHITE;
		newGraph->distance[i] = INF;
		newGraph->parent[i] = NIL;
	}
	return newGraph;	
    }

    //frees all the memory for Graph pG
    void freeGraph(Graph* pG){
	if(pG != NULL && *pG != NULL){
		for(int i = 0; i < (*pG)->verts; i++) freeList(&(*pG)->adj[i]);
		free((*pG)->distance);
		free((*pG)->parent);
		free((*pG)->color);
		free((*pG)->adj);
		free(*pG);
		*pG = NULL;
		return;
	}
    }

/**Access functions**/

    //returns the number of vertices in Graph G
    int getOrder(Graph G){
	if(G == NULL){
		fprintf(stderr, "G is NULL getSource()");
		exit(1);}
	return G->verts;
    }

    //returns the number of edges in Graph G
    int getSize(Graph G){
	if(G == NULL){
		fprintf(stderr, "G is NULL getSource()");
		exit(1);}
	return G->edges;
    }

    //returns the source vertix most recently used in BFS
    int getSource(Graph G){
	if(G == NULL){
		fprintf(stderr, "G is NULL getSource()");
		exit(1);}
	return G->source;
    }

    //returns the parent of int u
    int getParent(Graph G, int u){
	if(1 <= u && u <= getOrder(G)){ 
		fprintf(stderr, "u is not a valid part of the graph G getParent() "); 
		exit(1);}
	return G->parent[u];
    }

    //returns the distance of int u
    int getDist(Graph G, int u){
	if(getSource(G) == NIL) return INF;
	if(1 > u || u > getOrder(G)){ 
		fprintf(stderr, "u is not a valid part of the graph G getDist() "); 
		return 0;}
	return G->distance[u];
    }

    //calculates the path from 
    void getPath(List L, Graph G, int u){
	if(getSource(G) == NIL){
		 fprintf(stderr, "the Graph is NIL");
		 exit(1);}
	if(1 > u || u > getOrder(G)){
		 fprintf(stderr, "u is not a valid part of the graph G getPath() ");
		 exit(1);}
	if(G == NULL){
		fprintf(stderr,"G graph is equal to NULL getPath()");
		exit(1);}
	int curr = u;
	append(L, curr);
	while(G->parent[curr] != -1){
		prepend(L,G->parent[curr]);
		curr=G->parent[curr];
	}
	if(curr != getSource(G)) append(L,NIL); 
    }

/**Manipulation procedures**/
    //makes the Graph G null by setting array values to NIL
    void makeNull(Graph G){
	for(int i = 1; i <= getOrder(G); i++) {
		clear(G->adj[i]);
		G->distance[i] = INF;
		G->color[i] = WHITE;
		G->parent[i] = NIL;
	}
     }
	    //calls addArc() and places edges in respected adjaceny arrays in order
    void addEdge(Graph G, int u, int v){
	if(0 > u || u > getOrder(G)){
		fprintf(stderr, "u is out of Graph boundries addEdge() ");
		exit(1);}
	if(0 > v || v > getOrder(G)){
		fprintf(stderr, "v is out of Graph boundries addEdge() ");
		exit(1); }
	addArc(G,u,v);
	addArc(G,v,u);
	G->edges++;
	}

    //holds the funcitonality for the addEdge()
    void addArc(Graph G, int u, int v){
	if(1 > u || u > getOrder(G)){
		fprintf(stderr, "u is out of Graph boundries addArc()");
		exit(1);}
	if(1 > v || v > getOrder(G)){
		fprintf(stderr, "v is out of Graph boundries addArc()");
		exit(1); } 
	List uList = G->adj[u];
	if(length(uList) == 0){ append(uList, v); return;}
	else{
		moveTo(uList, 0);
		while(getIndex(uList) != -1){
			if(v == getElement(uList)) return;
			else if(getElement(uList) < v) moveNext(uList); 
			else{ insertBefore(uList,v); return; }
		}
		append(uList,v);
	}
	
    }

    //Implementation of the BFS algorithm
    void BFS(Graph G, int s){
	G->source = s;
	for(int i = 1; i <= G->verts; i++){
		if(i != s){
			G->color[i] = WHITE;
			G->distance[i] = INF;
			G->parent[i] = NIL;
		}
	}
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List Q = newList();
	prepend(Q,s);
	while(length(Q) > 0){
		int u = back(Q);
		deleteBack(Q);
		List y = G->adj[u];
		for(moveTo(y, 0); getIndex(y) > 0; moveNext(y)){
			int v  = getElement(y);
			if(G->color[v] == WHITE){
				G->color[v] = GRAY;
				G->distance[v] = G->distance[u] + 1;
				G->parent[v] = u;
				prepend(Q, v);
			}
			G->color[u] = BLACK;
			}
		}		 
	freeList(&Q);
	}
    

    /** Other operations **/
    //prints out the Graph G
    void printGraph(FILE* out, Graph G){
	for(int i = 1; i <= G->verts; i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
    }
