#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"

#define MAX_LEN 160

//method for the strdup
char *strdup(const char *a){
    char *dup = malloc(strlen(a) + 1);
    if (dup == NULL) return NULL;
    strcpy(dup, a);
    return dup;
}

List lexSort(char** lineArray, int length){
       List lex = newList();
       //append 0 to the front of empty list
       if(length > 0) append(lex,0);
       //follows the pseudo-code for insertionSort
       for(int i = 1; i < length; i++){
	   //temporary string that contains the array index being compared to the cursor string index
	   char* tmp = lineArray[i];
           int j = i - 1;
	   moveTo(lex,j);
	   //if the tmp string compared to the element of the cursor is less then it comes before. 
           while(j > -1 && (strcmp(tmp,lineArray[getElement(lex)]) < 1)){
	           movePrev(lex);
		   j--;
		   }
	   //if cursor falls off then add to front
	   if(getIndex(lex) == -1){
	       prepend(lex,i);
	       //if not then insert after the cursor location.
	   } else {
	       insertAfter(lex,i);
	   }
	 } return lex;
  }

int main(int argc, char * argv[]){

   int count=0;
   FILE *in, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out == NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   //loops through the file and counts the strings
   while(fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }

   //closes the counter scanner on the file in
   fclose(in);
   FILE *in2 = fopen(argv[1], "r");
 
   //creates a new string array called lineArray
   char** lineArray = malloc(sizeof(char**) * count);

   //for loop that 
   for(int i = 0; i < count; i++){
       fgets(line, MAX_LEN, in2);
       lineArray[i] = strdup(line);
   } 

   //references the lexSort function that alphabetizes the indecies
   List lex = lexSort(lineArray, count); 

   //print the sorted List's elements
   for(moveTo(lex,0); getIndex(lex) >= 0; moveNext(lex)){
        fprintf(out, "%s", lineArray[getElement(lex)]);
   }

   //frees the array and list
   free(lineArray); 
   freeList(&lex);

   /* close files */
   fclose(out);
   fclose(in2);

   return(0);
}

