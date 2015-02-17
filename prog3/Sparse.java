//Ryan Brounley 
//SID: 1360826
//CMPS 101
//PA3 Sparse.java

import java.io.*;
import java.util.*;

public class Sparse{
	public static void main(String[] args) throws IOException{
		Scanner in = null;
      		PrintWriter out = null;
      		String[] token = null;
      		int x = 0;
		int y = 0; 
		double val = 0;
		int a,b,n = 0;
                Matrix A;
		Matrix B;
      		String line;
	
      		//reports to stderr if more or less than 2 arguments
      		if(args.length != 2){
        		System.err.println("Incorrect Number of arguments");
     	    		System.exit(1);
      		}
      
      		//initialized the in and out arguments
      		in = new Scanner(new File(args[0]));
      		out = new PrintWriter(new FileWriter(args[1]));
		
		//Parses out the original integers used to determine size and nnz
		line = in.nextLine();
		token = line.split("\\s+");
   	        n = Integer.parseInt(token[0]);
                a = Integer.parseInt(token[1]);
                b = Integer.parseInt(token[2]);

		//Makes the A and B matrices with n size
 		A = new Matrix(n);
		B = new Matrix(n);
		line = in.nextLine();

		//assigns the entries for the a matrix
		for(int i = 0; i < a; i++){
			line = in.nextLine() + " ";
			token = line.split("\\s+");
			x = Integer.parseInt(token[0]);
			y = Integer.parseInt(token[1]);
			val = Double.parseDouble(token[2]);
			A.changeEntry(x,y,val);
		}

		//takes into account the space between the a and b values
		line = in.nextLine();

		//assigns the entries for the b matrix
		for(int i = 0; i < b; i++){
			line = in.nextLine() + " ";
			token = line.split("\\s+");
			x = Integer.parseInt(token[0]);
			y = Integer.parseInt(token[1]);
			val = Double.parseDouble(token[2]);
			B.changeEntry(x,y,val);
		}

		//Prints out the output with the operations from Tantalos webpage
		out.format("A has %s non-zero entries\n", A.getNNZ());
      		out.println(A);

      		out.format("B has %s non-zero entries\n",B.getNNZ());
     		out.println(B);

      		Matrix C = A.scalarMult(1.5);
		out.println("(1.5)*A = ");
     		out.println(C);

      		Matrix D = A.add(B);
		out.println("A+B = ");
      		out.println(D);

      		D = A.add(A);
		out.println("A+A = ");
      		out.println(D);

      		Matrix E = B.sub(A);
		out.println("B-A = ");
      		out.println(E);

      		E = A.sub(A);
		out.println("A-A = ");
      		out.println(E);

      		Matrix F = A.transpose();
		out.println("Transpose(A) = ");
      		out.println(F);

      		F = A.mult(B);
     		out.println("A*B = ");
      		out.println(F);

      		Matrix G = B.mult(B);
      		out.println("B*B = ");
      		out.println(G);

		in.close();
		out.close();
	}
}
