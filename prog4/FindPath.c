//Ryan Brounley
//CMPS 101 Tantalo

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Graph.h"
#define MAX_LEN 165

void printPath(Graph G, int u, int v, List L, FILE* out){
	getPath(L,G,v);
	if(v == -1){
		fprintf(out,"\n");
		fprintf(out,"The Distance from %d to %d is infinity", getSource(G), v);
		fprintf(out,"No %d-%d path exists\n",getSource(G), v);
	}else{
		fprintf(out,"\n");
		fprintf(out,"The distance from %d to %d is %d\n",getSource(G), v, getDist(G,v));
		fprintf(out,"A shortest %d-%d path is: ",getSource(G), v);
		printList(out,L);
		fprintf(out, "\n");
		clear(L);
	}
}

int main(int argc, char * argv[]){

   FILE *in, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
  
   fgets(line, MAX_LEN, in);
   int numOfVertex = 0;
   sscanf(line, "%d", &numOfVertex); 

   Graph G = newGraph(numOfVertex);
   int u = 0;
   int v = 0;

   while(fgets(line, MAX_LEN, in) != NULL){	
        u = 0;
        v = 0;
	sscanf(line,"%d %d", &u, &v);
	if(u == 0 && v == 0) break;
	addEdge(G, u, v);
   }
   printGraph(out,G);

   u = 0;
   v = 0;
   while(fgets(line, MAX_LEN, in) != NULL){
	List L = newList();
	sscanf(line,"%d %d", &u, &v);
	if(u == 0 && v == 0) break;
	else{
		BFS(G, u);
		printPath(G, u, v, L, out);
	}
	freeList(&L);
   }
   freeGraph(&G);
   fclose(out);
   fclose(in);
   return 0;
}
