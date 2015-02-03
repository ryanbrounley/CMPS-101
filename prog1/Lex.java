import java.io.*;
import java.util.Scanner;
   
class Lex{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      int i, n, lineNumber = 0;
      
      
      //reports to stderr if more or less than 2 arguments
      if(args.length != 2){
         System.err.println("Incorrect Number of arguments");
         System.exit(1);
      }
      
      //initialized the in and out arguments
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      int test = countLineNumber(in);
      String[] lineArray = new String[test];
      
      //inserts the strings from the file into the string array
      Scanner in2 = new Scanner(new File(args[0]));
      while(in2.hasNextLine()){
      for(int a = 0;a < test;a++){
	  lineArray[a] = in2.nextLine();
        }
      }

      //call lexSort which sorts the indices according to array
      List lex = lexSort(lineArray);

      //prints the values of lexSort indices as they are in lineArray
      for(lex.moveTo(0); lex.getIndex() >= 0; lex.moveNext()){
	   out.println(lineArray[lex.getElement()]);  
      }

      in.close();
      out.close();
   }

    //function to count the number of lines in the file
    public static int countLineNumber(Scanner in){
       int lineNumber = 0;
       while(in.hasNextLine()){
	   lineNumber++;
	   in.nextLine();
       }
       return lineNumber;
   }

   public static List lexSort(String [] lineArray){
       List lex = new List();
       //append 0 to the front of empty list
       if(lex.length() == 0) lex.append(0);

       //follows the pseudo-code for insertionSort
       for(int i = 1; i < lineArray.length; i++){
	   //temporary string that contains the array index being compared to the cursor string index
	   String tmp = lineArray[i];
           int j = i - 1;
	   lex.moveTo(j);
	   //if the tmp string compared to the element of the cursor is less then it comes before. 
           while(j > -1 && tmp.compareTo(lineArray[lex.getElement()]) < 0){
	           lex.movePrev();
		   j--;
		   }
	   //if cursor falls off then add to front
	   if(lex.getIndex() == -1){
	       lex.prepend(i);
	       //if not then insert after the cursor location.
	   } else {
	       lex.insertAfter(i);
	   }
	 } return lex;
  }
} 

