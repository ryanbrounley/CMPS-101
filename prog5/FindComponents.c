//Ryan Brounley
//CMPS 101 Tantalo

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Graph.h"
#define MAX_LEN 165

//runs the DFS on the original and then on the transpose using the stack. Then searches from the back of the stack for 
//the components that have no parents and the vertices that are strongly attached to those.
void printComponents(FILE* out, Graph G){
   List stack = newList();
   for(int i = 1; i <= getOrder(G); i++) append(stack, i);
   DFS(G, stack);
   Graph trans = transpose(G);
   DFS(trans, stack);
   int count = 0;
   for(moveTo(stack, 0); getIndex(stack) > -1; moveNext(stack)){
   	if(getParent(trans,getElement(stack)) == 0) count++;
   }
   fprintf(out,"\n"); 
   fprintf(out, "G contains %d strongly connected components:\n", count);

   	List N = newList();
	int i = 0;
	for(moveTo(stack,(length(stack)-1)); getIndex(stack) != -1;){
   		int v = getElement(stack);
 		movePrev(stack);
		prepend(N, v);
		if(getParent(trans, v) == 0) {
			fprintf(out,"Component %d: ", ++i);
			printList(out, N);
			fprintf(out, "\n");
			clear(N);
		}
		deleteBack(stack);
	}
	freeList(&N);
	freeList(&stack);
	freeGraph(&G);
	freeGraph(&trans);
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
	addArc(G, u, v);
   }

   //prints the Graph with the input stats and runs the printComponents function
   //for the strongly connected components portion
   fprintf(out,"Adjacency list representation of G: \n");
   printGraph(out,G);
   printComponents(out,G);

   freeGraph(&G);
   fclose(out);
   fclose(in);
   return 0;
}
