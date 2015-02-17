//Ryan Brounley
//CMPS 101

import java.util.*;

public class List{

  private class Node{
	Object data;
	Node prev;
	Node next;
	//Constructor
	Node(Object data){
		this.data = data;
		next = null; 
		prev = null;
	}
	public String toString() { 
		return String.valueOf(data); }
  }

  private Node front;
  private Node curr;
  private Node back;
  private int length;

  //Constructor
  List(){
	front = curr = back = null;
	length = 0;
  } 
	
  //Access functions
  //Returns length of the this
  int length(){
      if(front == null) return 0;
      else 
	  return this.length; 
  }

  //Returns the index of the cursor element in this list
  //or returns -1 if the cursor element is undefined.	
  int getIndex(){
    Node A = front;
    int count = 0;
    if( curr != null){
      if(curr.data == A.data){ return (count + 1); }
      while( A != null){
        count++;
        if(curr.data == A.next.data){
          return count; 
        }
        A = A.next;  
        }  
     }return -1;
  }
     
  //returns whether or not the cursor is on the List
  boolean offList(){
        if(this.length()== 0)return true;
        else if(this.curr == null)return true;
        else
            return false;
    }

  boolean isFront(){
        if(this.length() == 0) return false;
        else if(this.curr == front) return true;
        else   return false;
  }

  //Returns front element in this list.
  Object front(){
      Node A = front;
      if(this.length() > 0) return A.data;
      else 
	throw new 
        RuntimeException("this Error: front() called on empty list");
  }
 
  //Return back element in this list.
  Object back(){ 
      Node B = back;
      if(this.length() > 0) return B.data;
      else
	  throw new 
          RuntimeException("this Error: back() called on empty list");
  }

  //returns cursor element in this list
  //Pre: length()>0, getIndex()>0
  Object getElement(){
      if((this.getIndex() > -1) && (this.length() > 0)) return curr.data;
      else
	  throw new 
          RuntimeException("this Error: getElement() called on empty list");
  }

  //Returns true if this List and L are the same integer
  //sequence. 
  public boolean equals(List L){
      boolean equalsflag = true;
      Node A = this.front;
      Node B = L.front;

      if(this.length() == L.length()){
	  while(equalsflag && A!= null){
	      equalsflag = (A.data == B.data);
	      A = A.next;
	      B = B.next;
	  }
	  return equalsflag;}
      else{
	  return false;
      }
  }

  //Manipulation procedure
  //Re-sets the List to empty
  void clear(){
      if(front == null) return;
      else{
	  front.next = null;
	  front = null;
	  length = 0;
      }
  }

  //Moves the cursor to the element at index i, otherwise
  //the cursor becomes undefined.
  void moveTo(int i){
      Node cursor = front;
      if ((0 <= i) && (i <= (this.length() - 1))){
	 int newcounter = 0;
	 while(newcounter < i){
	 	cursor = cursor.next;
		newcounter++;
	 }
	 curr = cursor;
      } else {
	 curr = null;
      }
  } 

  //Moves the cursor one step toward the front of the list.	  
  void movePrev(){ 
     Node A;
     if((this.length() == 0)||(this.curr == null))
	throw new 
        RuntimeException("this Error: movePrev() called on empty list");
     else{ 
	A = curr;
	curr = A.prev;
      }
  }

  //Moves the cursor one step toward the back of the list.
  void moveNext(){
     //Node A;
     if(this.length() == 0)
	throw new 
        RuntimeException("this Error: moveNext() called on empty list");
     else{
	if(curr != null)
		curr = curr.next;
	else
		System.out.println("curr was null!!");
	//A = this.curr;
	//this.curr = A.next;
	}
  }

  //Inserts new element before front element in the List.
  void prepend(Object data){
      Node tmp;
      Node node = new Node(data);
      if(this.length() == 0)
	  front = back = node;
      else{
	  tmp = front;
	  tmp.prev = node;
          front = node;
	  front.next = tmp;
      }
      length++;
  }

  //Inserts new element after back element in the List.
  void append(Object data){
      Node tmp;
      Node node = new Node(data);
      if(this.length() == 0){ 
	  front = back = node;}
      else{
	  tmp = back;
	  tmp.next = node;
	  back = node;
	  back.prev = tmp;
      }
      this.length++;
  }

  //Inserts new element before cursor element into this List.
  void insertBefore(Object data){
	if(this.length() == 0){
		throw new 
                RuntimeException("this Error: insertBefore() called on empty list");
	}
	length++;
	Node before = new Node(data);
	before.next = curr;
	if(curr != front){
		curr.prev.next = before;
		before.prev = curr.next;
	}
	curr.prev = before;
	if(curr == back) front = before;
  }

  //Inserts new element before cursor element in this List.
  void insertAfter(Object data){
	if(this.length() == 0){
		throw new 
                RuntimeException("this Error: insertAfter() called on empty list");
	}
	length++;
	Node after = new Node(data);
	after.prev = curr;
	if(curr != back){
		curr.next.prev = after;
		after.next = curr.next;
	}
	curr.next = after;

	if(curr == back) back = after;
  }
 
  //Deletes the front element of this List.
  void deleteFront(){
      if(this.length() == 0) 
	  throw new 
	  RuntimeException("this Error: deleteFront() called on empty this"); 
      if(this.length() > 1){
	  front = front.next;
	  front.prev = null;}
      else{
	  front = back = null;}
      length--;
  }
	
  //Deletes the back element of this List.
  void deleteBack(){
      if(this.length() == 0) 
	  throw new NoSuchElementException();
      else{
	  back = back.prev;
          back.next = null;
          }
  }

  //Destes cursor element from this List. Cursor is undefined after this.
  void delete(){
      if(this.length() <= 0 && this.getIndex() < 0) 
	  throw new NoSuchElementException();
      else{
	  Node temp = curr.prev;
	  temp.next = curr.next;
	  if(temp != null){
	      curr = curr.next;
	      curr.prev = temp;
	  }
      }
  }

   void deletePrev(){
      if(this.length() <= 0 && this.getIndex() < 0) 
	  throw new NoSuchElementException();
      else{
          if(curr.prev != null){
	     Node temp = curr.prev.prev;
	     temp.next = curr;
	     if(temp != null){
	        curr.prev = temp;
		curr.prev.prev.next = curr;
	     }else this.deleteFront();
      }
      else{ this.deleteFront();}
  }
  }
 

  //Other methods
  //Overrides toString method in Node class
      public String toString(){
	  String str = "";
	  for(Node N = front; N != null; N = N.next){
	      str += N.toString() + " ";
	  }
	  return str;
      }
}
