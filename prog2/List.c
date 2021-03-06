#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj{
     int data;
     struct NodeObj *prev; 
     struct NodeObj *next;
} NodeObj;

typedef struct NodeObj* Node;

typedef struct ListObj{
     Node front;
     Node curr;
     Node back;
     int length;
} ListObj;

//creates a new node with NodeObj qualities
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   return(N);
}

// // Frees heap memory pointed to by *pN, sets *pN to NULL.
// // Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
          free(*pN);
          *pN = NULL;
     }
}

//creates a new ListObj
List newList(void){
     List L = malloc(sizeof(ListObj));
     L->front = L->curr = L->back = NULL;
     L->length = 0;
     return L;
}

//free the allocs in lists
void freeList(List* pL){ 
   if(pL!=NULL && *pL!=NULL) { 
        while(length(*pL) != 0) { 
           deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }    
}
// Access functions -----------------------------------------------------------

// Returns number of elements in this list.
int length(List L){
     if(L->front == NULL) return 0;
     return L->length;
} 

// Returns the index of the cursor element in this list, or
// returns -1 if the cursor element is undefined.
int getIndex(List L){
     Node a = L->front;
     int count = 0;
     if(L->curr != NULL){
       if(L->curr->data == a->data){ return (count + 1); }
       while(a != NULL){
          count++;
          if(L->curr->data == a->next->data){
             return count;
          }
          a = a->next;
          }
     }
     return -1;
}

//Return the front element
int front(List L){
    if(length(L) > 0) return L->front->data;
    else{
       return -1;}
}

//Returns the back element
int back(List L){
    if(length(L) > 0){ return L->back->data;
    }else{
       return -1;
    }
}

//Returns cursor element on the list
int getElement(List L){
    if((getIndex(L) > -1) && (length(L) > 0)) return L->curr->data;
    else{  
       fprintf(stderr,"cursor is off the List");
       return -1;
    }
}

//Checks to see if two lists are identical or different
int equals(List A, List B){
      bool equalsflag = true;
      Node a = A->front;
      Node b = B->front;
      while(equalsflag && a != NULL){
            equalsflag = (a->data == b->data);
            a = a->next;
            b = b->next;
          }
      return equalsflag;
}

// Manipulation procedures ----------------------------------------------------

// Re-sets this List to the empty state.
void clear(List L){
    if(L->front == NULL) return;
    else{
        Node fronttmp = L->front;
        while(fronttmp != NULL){
           Node tmp = fronttmp->next;
           free(fronttmp);
           fronttmp = tmp;
    }
    L->front = L->back = L->curr = NULL;
    L->length = 0;
    }
}

// If 0<=i<=length()-1, moves the cursor to the element
// at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i){
    Node cursor = L->front;
    if((0 <= i) && (i <= (length(L) - 1))){
       int newcounter = 0;
       while(newcounter < i){
            cursor = cursor->next;
            newcounter++;
       }
       L->curr = cursor;
       } else {
         L->curr = NULL;
       }
} 

// Moves the cursor one step towards the front of the list
void movePrev(List L){
    Node a;
    if((length(L) == 0)||(L->curr == NULL)){
        //opposite if for the preconditions^
        fprintf(stderr,"Empty list movePrev()");
        exit(EXIT_FAILURE);
    }else{
      a = L->curr;
      L->curr = a->prev;
    }
}

// Moves the cursor one step toward the back of the list
void moveNext(List L){
     Node a;
     if(length(L) == 0){ 
        fprintf(stderr,"empty List moveNext()");
        exit(EXIT_FAILURE);
     }else{
        a = L->curr;
        L->curr = a->next;
     }
}

//inserts element to front  of the list
void prepend(List L, int data){ 
     if(L == NULL){
        fprintf(stderr,"error L == NULL prepend");
        return;}
     Node n = malloc(sizeof(struct NodeObj));
     n->data = data;
     n->prev = NULL;
     n->next = L->front;
     if(L->front == NULL){
        L->back = n;
     }else{
        L->front->prev = n;
     }
     L->front = n;
     L->length++;
}

//inserts element to back fo the list
void append(List L, int data){
    if(L == NULL){
        fprintf(stderr,"error L == NULL prepend");
        return;}
     Node n = malloc(sizeof(struct NodeObj));
     n->data = data;
     n->next = NULL;
     n->prev = L->back;
     if(L->back == NULL){
        L->front = n;
    }else{
        L->back->next = n;
    }
    L->back = n;
    L->length++;
}
 
//Inserts new element before the cursor element
void insertBefore(List L, int data){
     if(length(L) < 0 && getIndex(L) <= 0){
          fprintf(stderr, "empty List insertBefore()");
          exit(EXIT_FAILURE);
     }
     L->length++;
     Node before = newNode(data);
     before->next = L->curr;
     if(L->curr != L->front){
          L->curr->prev->next = before;
          before->prev = L->curr->next;
     }
     L->curr->prev = before;
     if(L->curr == L->back) L->front = before;
}

//inserts new element after the cursor element
void insertAfter(List L, int data){
     if(length(L) == 0){
          fprintf(stderr, "empty List InsertAfter()");
          exit(EXIT_FAILURE);}
     L->length++;
     Node after = newNode(data);
     after->prev = L->curr;
     if(L->curr != L->back){
           L->curr->next->prev = after;
           after->next = L->curr->next;
     }
     L->curr->next = after;
     if(L->curr == L->back) L->back = after;
}

//Deletes the front element in this list
void deleteFront(List L){
     Node tmp;
     if(length(L) == 0){
            fprintf(stderr,"empty list deleteFront()");
            exit(EXIT_FAILURE);}
     if(length(L) > 1){
        tmp = L->front;
        L->front = L->front->next;
        L->front->prev = NULL;}
     else{
        tmp = L->front;
        L->front = L->back = NULL;}
     freeNode(&tmp);
     L->length--;
}

//Deletes the back element in this list
void deleteBack(List L){
     Node tmp;
     if(length(L) == 0) {
             fprintf(stderr,"empty list deleteBack()");
             exit(EXIT_FAILURE);}
     if(length(L) > 1){
        tmp = L->back;
        L->back = L->back->prev;
        L->back->next = NULL;}
     else{
        tmp = L->back;
        L->back = L->front = NULL;}
     freeNode(&tmp);
     L->length--;
}

//Deletes cursor element in this list
void delete(List L){
     Node tmp;
     if(length(L) <= 0 && getIndex(L) < 0)
        exit(EXIT_FAILURE);
     else{
        tmp = L->curr->prev;
        tmp->next = L->curr->next;
        if(tmp != NULL){
           L->curr = L->curr->next;
           L->curr->prev = tmp;
        }
     }
}

// Other operations -----------------------------------------------------------

//prints the list out
void printList(FILE* out, List L){
    if(L == NULL){
       fprintf(stderr,"Empty List printlist()");
       exit(EXIT_FAILURE);
    }
    if(out == NULL){
       fprintf(stderr,"no out FILE printlist()");
       return;
    }
    Node n = L->front;
    while(n != NULL){
         fprintf(out, "%d ",n->data);
         n = n->next;
    }
}

//copys the input list and returns it into a new list.
List copyList(List L){
    List cpy = newList();
    Node A = L->front;
    while(A != NULL){
        append(cpy, A->data);
        A = A->next;
    }
    return cpy;
}

