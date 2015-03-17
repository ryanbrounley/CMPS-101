//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
// Ryan Brounley CMPS 101
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=22;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   //inputs a 22 vertex Graph
   addArc(G, 1,2);
   addArc(G, 2,3);
   addArc(G, 2,8);
   addArc(G, 2,9);
   addArc(G, 3,10);
   addArc(G, 4,3);
   addArc(G, 4,5);
   addArc(G, 4,11);
   addArc(G, 5,6);
   addArc(G, 6,7);
   addArc(G, 6,13);
   addArc(G, 7,15);
   addArc(G, 8,1);
   addArc(G, 8,9);
   addArc(G, 8,16);
   addArc(G, 9,3);
   addArc(G, 10,9);
   addArc(G, 11,4);
   addArc(G, 11,10);
   addArc(G, 11,12);
   addArc(G, 11,19);
   addArc(G, 12,5);
   addArc(G, 12,20);
   addArc(G, 13,12);
   addArc(G, 13,15);
   addArc(G, 14,7);
   addArc(G, 15,14);
   addArc(G, 15,21);
   addArc(G, 16,17);
   addArc(G, 17,18);
   addArc(G, 18,10); 
   addArc(G, 18,11);
   addArc(G, 19,18);
   addArc(G, 19,20);
   addArc(G, 20,15);
   addArc(G, 21,20);
   addArc(G, 21,22);
   addArc(G, 22,14); 
 
   //prints the Graph
   fprintf(stdout, "Adjacency List representation of G:\n");
   printGraph(stdout, G);

   
   fprintf(stdout, "\n");
   DFS(G, S);
   fprintf(stdout, "The Results of the DFS on Graph G are:\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n"); 
   fprintf(stdout, "The stack of the original is:\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   fprintf(stdout, "The copyGraph function with G created: \n");
   printGraph(stdout, C);
   fprintf(stdout, "\n"); 
   fprintf(stdout, "The Transpose function with G created: \n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n"); 
   fprintf(stdout, "The DFS run on the transpose created: \n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n"); 
   fprintf(stdout, "The transpose stack is:\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
