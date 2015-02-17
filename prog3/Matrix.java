//Ryan Brounley
//CMPS 101 Tantalo
//Matrix.java

public class Matrix{
   
    //class for the entry object that is put into the DD Lists 
    private class Entry{
        int column;
	double value;
	Entry(int column, double value){
		this.column = column;
		this.value = value;
	}
		public boolean equals(Object object){
			return ((Entry)object).value == value && ((Entry)object).column == column;
		}
        	public String toString(){ return ("(" + column + "," + value+ ")"); }
        }

        //Matrix Constructor with size, nnz, and creation of matrix which represents list rows in the matrix
	int nnz;
	int size;
	List[] matrix;
	Matrix(int n){
	    if(n >= 1){
		this.size = n;
                this.nnz = 0;
		matrix = new List[n + 1];
	        for(int i = 0; i < n; i++){
			matrix[i] = new List();
		}
	    }
	    else throw new RuntimeException("n is equal to 0");
        }


// Access functions
// Returns n, the number of rows and columns of this Matrix
int getSize(){ return size; }

// Returns the number of non-zero entries in this Matrix
int getNNZ(){ return nnz; }

 // overrides Object's equals() method
public boolean equals(Object x){
	if(((Matrix) x).getSize() == this.getSize()){
		boolean equal = true;
		int i = 0;
		while((i < this.getSize()) && equal){
			equal = (this.matrix[i].equals(((Matrix)x).matrix[i]));
			i++;
		} return equal;
	}else return false;
}

// Manipulation procedures
// sets this Matrix to the zero state
void makeZero(){
        for(int i = 0; i < this.getSize(); i++) this.matrix[i].clear();
        nnz = 0;
}

// returns a new Matrix having the same entries as this Matrix
public Matrix copy(){
        Matrix copy = new Matrix(this.getSize());
        List row;
        Entry obj;
        for(int a = 0; a < copy.getSize(); a++){
                row = this.matrix[a];
                row.moveTo(0);
                while(!row.offList()){
                    obj = (Entry)row.getElement();
                    obj = new Entry(obj.column, obj.value);
                    copy.matrix[a].append(obj);
                    row.moveNext();                    
                }
        }
	copy.nnz = this.nnz;
        return copy;
}

// changes ith row, jth column of this Matrix to x
// pre: 1<=i<=getSize(), 1<=j<=getSize()
// returns a new Matrix that is the scalar product of this Matrix with x
void changeEntry(int i, int j, double x){
	if(1 > i || i > this.getSize()) throw new RuntimeException("i is invalid size changeEntry()");
	if(1 > j || j > this.getSize()) throw new RuntimeException("j is invalid size changeEntry()");
        List row = this.matrix[i - 1];
        Entry coord;
        if(row.length() == 0 && x != 0) row.append(new Entry(j, x));
        else if(x != 0 && !row.offList()){
            row.moveTo(0);
            while(x != 0 && !row.offList()){
                     coord = (Entry)row.getElement();
                     if(coord.column < j) {row.moveNext();}
                     else if(coord.column == j){
                          coord = new Entry(coord.column, x);
                          row.insertAfter(coord);
                          row.delete();
                          return;
                     }else{
                          coord = new Entry(coord.column, x); 
                          row.insertBefore(coord);
                          return;
		      }
            }
            while(x == 0 && !row.offList()){
                     coord = (Entry)row.getElement();
                     if(coord.column < j) row.moveNext();
                     else if(coord.column == j){
                           row.delete();
                           return;
                     }else return;
            }
        }
	else if(x != 0 && row.offList()) row.append(new Entry(j, x));
        if(x != 0) this.nnz++;
}

//return a new Matrix that is the scalar product of this Matrix with x
public Matrix scalarMult(double x){
     Matrix scal = new Matrix(this.getSize());
     List row;
     Entry obj;
     if(x == 0){ scal.nnz = 0; return scal;}
     else{
        for(int i = 0; i < scal.getSize(); i++){
		row = this.matrix[i];
        	if(row.length() > 0){
		        row.moveTo(0);
			while(!row.offList()){
	 	        	obj = (Entry)row.getElement();
		        	obj = new Entry(obj.column, obj.value);
			        obj.value = (obj.value * x);
			        scal.matrix[i].append(obj);
			        row.moveNext();
	                }
               }
      }
      scal.nnz = this.nnz;
      return scal;	
      }
}  
 
// returns a new Matrix that is the sum of this Matrix with M
// pre: getSize()==M.getSize()
public Matrix add(Matrix M){
     if(this.getSize() == M.getSize()){
        Matrix add = new Matrix(this.getSize());
 	List thisrow;
	List mrow;
	Entry thisadd;
	Entry madd;
	Entry total;
	if(M == this) return this.scalarMult(2);
	for(int i = 0; i < M.getSize(); i++){
               	if(M.matrix[i].length() > 0 || this.matrix[i].length() > 0){
			thisrow = this.matrix[i];
			mrow = M.matrix[i];
			thisrow.moveTo(0);
			mrow.moveTo(0);	
			while(!thisrow.offList() || !mrow.offList()){	
				if(thisrow.offList()){
					while(!mrow.offList()){
						madd = (Entry)mrow.getElement();
						total = new Entry(madd.column,madd.value);
						add.matrix[i].append(total);
						mrow.moveNext();
					}
				}
				else if(mrow.offList()){	
					while(!thisrow.offList()){
						thisadd = (Entry)thisrow.getElement();
						total = new Entry(thisadd.column, thisadd.value);
						add.matrix[i].append(total);
						thisrow.moveNext();
					}
				}
				else{
					thisadd = (Entry)thisrow.getElement();
					madd = (Entry)mrow.getElement();
					if(madd.column == thisadd.column){
						total = new Entry(madd.column, 1);
						total.value = (madd.value + thisadd.value);	
						add.matrix[i].append(total);
						thisrow.moveNext();
						mrow.moveNext();
					}else if(madd.column > thisadd.column){
						total = new Entry(thisadd.column, thisadd.value);
						add.matrix[i].append(total);
						thisrow.moveNext();
					}else{
						total = new Entry(madd.column, madd.value);
						add.matrix[i].append(total);
						mrow.moveNext();
					}		
				}
			}
		}
     }		
     add.nnz = M.nnz;
     return add;	
     }else{ throw new RuntimeException("Matrix sizes don't match add()");}
}

// returns a new Matrix that is the difference of this Matrix with M
// pre: getSize()==M.getSize()
Matrix sub(Matrix M){
	if(M.getSize() == this.getSize()){
		Matrix sub = new Matrix(M.getSize());
		sub = this.add(M.scalarMult(-1));
                sub.nnz = M.nnz;
		Entry checker;
		for(int i = 0; i < sub.getSize(); i++){
			sub.matrix[i].moveTo(0);
			while(!sub.matrix[i].offList()){
				checker = (Entry)sub.matrix[i].getElement();
				if(checker.value == 0.0){ 
					sub.nnz--;
					if(sub.matrix[i].isFront()){
						 sub.matrix[i].moveNext(); 
					         sub.matrix[i].deleteFront(); 
					}else    sub.matrix[i].delete();
			 	}
				else sub.matrix[i].moveNext();
			}
		}
	return sub;
	}else{ throw new RuntimeException("invalid matrix sizes sub()");}
}


// returns a new Matrix that is the transpose of this Matrix
Matrix transpose(){
       Matrix transMat = new Matrix(this.getSize());
       Entry temp;
       List transrow;
       for(int i = 0; i < this.getSize(); i++){
	   if(this.matrix[i].length() > 0){ 
		transrow = this.matrix[i];
        	transrow.moveTo(0); 
	        while(!transrow.offList()){ 
                	temp = (Entry)transrow.getElement(); 
			transMat.changeEntry(temp.column, i + 1, temp.value);  
			transrow.moveNext();
                }
                }
            }
	transMat.nnz = this.nnz;
	return transMat;
}

// returns a new Matrix that is the product of this Matrix with M
// pre: getSize()==M.getSize()
Matrix mult(Matrix M){
       if(this.getSize() == M.getSize()){
           Matrix transMult = M.transpose();
	   Matrix multMat = new Matrix(M.getSize());
	   List temp1;
	   List temp2;
           double mult = 0;
	   for(int i = 0; i < this.getSize(); i++){
	   temp1 = transMult.matrix[i];
	   temp2 = this.matrix[i];
	   if(temp1.length() > 0 || temp2.length() > 0){
               for(int j = 0; j < M.getSize(); j++){
		   mult = dot(this.matrix[i], transMult.matrix[j]);
		   if(mult != 0) multMat.changeEntry(i + 1, j + 1, mult); 
               }
            }
            }return multMat;
       }else{ throw new RuntimeException("two matrices of different sizes mult()");}
}

//a method that takes the dot products of two lists -- made to assist the mult method along with transpose
private static double dot(List P, List Q){
      double dotanswer = 0;
      Q.moveTo(0);
      P.moveTo(0);
      while(!Q.offList() && !P.offList()){
           if(((Entry)Q.getElement()).column > ((Entry)P.getElement()).column){
              P.moveNext();
           }else if(((Entry) Q.getElement()).column < ((Entry)P.getElement()).column){
              Q.moveNext();
           }else{
              dotanswer += (((Entry)P.getElement()).value * ((Entry)Q.getElement()).value);
              P.moveNext();
              Q.moveNext();
           }
      } 
      return dotanswer;
}

//Overwrites the toString method
public String toString(){
        String printmat = "";
        for(int i = 0; i < this.getSize(); i++){
            if(this.matrix[i].length() > 0){
              printmat += (i+1) + ":";
              printmat += this.matrix[i].toString() + "\n";                   
	    }
         } 
  return printmat;
}

}
