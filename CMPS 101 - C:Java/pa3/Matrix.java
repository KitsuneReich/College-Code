//Nichole Boothroyd     CruzID: nboothro    Assignment: pa3
//-----------------------------------------------------------------------------
//  Matrix.java
//      Matrix ADT that will use List.java to store values and be used by
// Sparse.java to store matrices.
//-----------------------------------------------------------------------------
public class Matrix{

    private class Entry {
        //Fields
        int col;
        double val;

        //Constructor
        Entry(int j, double x) {this.col = j; this.val = x; }

        //toString():
        public String toString() {
            String str = ("(" + col + ", " + val + ")");
            return str;
        }
        //equals():
        public boolean equals(Object x){
        boolean eq = false;
        Entry that;
        if(x instanceof Entry){
            that = (Entry) x;
            eq = (this.val == that.val);
        }
        return eq;
        }
    }
    //Fields
    private int size;
    private int NNZ;
    private List[] row;

    //Constructor: Makes a new n x n zero matrix
    //Pre: n>= 1
    Matrix(int n) {
        if(n < 1){
            throw new RuntimeException(
                                       "Matrix Error: Matrix must have an n >= 1");
        }
        size = (n+1);
        NNZ = 0;
        row = new List[size];		   //Create the row array
        for(int i = 1; i < size; i++) {
            List L = new List();
            row[i] = L;			                //Set each row to hold an empty List
        }
    }

	//Access Functions
    int getSize(){                            //returns n, the # of rows/cols
        return size-1;
    }
    int getNNZ(){                           //return # of non-zero entries
        return NNZ;
    }
    //Manipulation Procedures
    
    //void makeZero()
    // sets this Matrix to the zero state
    void makeZero() {
        for(int i = 1; i < size; i++){
            this.row[i].moveFront();
            
            if(this.row[i].isEmpty()){
                continue;
            }
            else {
                    row[i].clear();
            }
            this.NNZ = 0;
        }
    }
    
    //Matrix copy()
    // returns a new Matrix having the same entries as this Matrix
    Matrix copy() {
        Matrix C = new Matrix(this.getSize());
        
        for(int i = 1; i < size; i++){
            C.row[i].moveFront();
            this.row[i].moveFront();
            
            if(this.row[i].isEmpty()){
                continue;
            }
            else {
                while(this.row[i].index() != -1) {
                    Entry A = (Entry)row[i].get();
                    int j = A.col;
                    double v = A.val;
                    C.changeEntry(i, j, v);
                    row[i].moveNext();
                }
            }
        }
        return C;
    }
    
    //changeEntry
    //changes ith row, jth col of this matrix to x
    //Pre: 1<= i <= getSize(), 1<= j <= getSize();
    void changeEntry(int i, int j, double x) {
        if( i < 1 || i > this.getSize()){
            throw new RuntimeException(
                                       "Matrix Error: changeEntry() has invalid row address");
        }
        else if( j < 1 || j > this.getSize()){
            throw new RuntimeException(
                                   "Matrix Error: changeEntry() has invalid column address");
        }
        else if( x == 0) {
            row[i].moveFront();
            if(row[i].isEmpty()) {                  //The case of inserting 0 to empty list
                return;
            }
            while(row[i].index() != -1){
                int indexCol = ((Entry)row[i].get()).col;
                if(j > indexCol) {
                    row[i].moveNext();
                }
                else if (j < indexCol) {			//The case where A[ij] already contained 0
                    //do nothing
                    return;
                }
                else if (j == indexCol) {           //The case where A[ij] contained a val
                    row[i].delete();                //delete the Entry to "set to 0"
                    this.NNZ--;
                    return;
                }
            }
        }
        else {
            Entry E = new Entry(j, x);
            row[i].moveFront();
            if(row[i].isEmpty()) {
                row[i].append(E);
                this.NNZ++;
                return;
            }
            
            while(row[i].index() != -1) {
                int indexCol = ((Entry)row[i].get()).col;
                if(j > indexCol) {
                    row[i].moveNext();
                    if (row[i].index() == -1) {     //If cursor becomes undefined, append
                        row[i].append(E);
                        this.NNZ++;
                    }
                }
                else if (j < indexCol) {            //The case where A[ij] contained 0
                    row[i].insertBefore(E);
                    this.NNZ++;
                    return;
                }
                else if(j == indexCol) {        //The case where A[ij] contains a value
                    ((Entry)row[i].get()).val = x;
                    return;
                }
            }
        }
    }
    
    // Matrix scalarMult(double x)
    // returns a new Matrix that is the scalar product of this Matrix with x
    Matrix scalarMult(double x) {
        Matrix C = new Matrix(this.getSize());
        
        for(int i = 1; i < size; i++){
            C.row[i].moveFront();
            this.row[i].moveFront();
            
            if(this.row[i].isEmpty()){
                continue;
            }
            else {
                while(this.row[i].index() != -1) {
                    Entry E = (Entry)row[i].get();
                    int j = E.col;
                    double sm = E.val * x;
                    C.changeEntry(i, j, sm);
                    row[i].moveNext();
                }
            }
        }
            
        return C;
    }
    
    //Matrix add(Matrix M)
    // returns a new Matrix that is the sum of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix add(Matrix M) {
        Matrix C = new Matrix(this.getSize());
        for(int i = 1; i < size; i++){
            C.row[i].moveFront();
            this.row[i].moveFront();
            M.row[i].moveFront();
            
            while(this.row[i].index() != -1) {
                    Entry A = (Entry)row[i].get();
                    if (M.row[i].index() != -1) {
                        Entry B =(Entry)M.row[i].get();
                        int j = A.col;
                        double v = A.val + B.val;
                        C.changeEntry(i, j, v);
                        row[i].moveNext();
                    }
                    else {
                        int j = A.col;
                        double v = A.val;
                        C.changeEntry(i, j, v);
                        row[i].moveNext();
                    }
                }
            
            if(this.row[i].index() == -1 && M.row[i].index() != -1) {
                Entry B =(Entry)M.row[i].get();
                int j = B.col;
                double v = B.val;
                C.changeEntry(i, j, v);
            }
        }
        return C;
    }
    
    //Matrix sub(Matrix M)
    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix sub(Matrix M) {
        Matrix C = new Matrix(this.getSize());
        for(int i = 1; i < size; i++){
            C.row[i].moveFront();
            this.row[i].moveFront();
            M.row[i].moveFront();
            
            while(this.row[i].index() != -1) {
                Entry A = (Entry)row[i].get();
                if (M.row[i].index() != -1) {
                    Entry B =(Entry)M.row[i].get();
                    int j = A.col;
                    double v = A.val - B.val;
                    C.changeEntry(i, j, v);
                    row[i].moveNext();
                }
                else {
                    int j = A.col;
                    double v = A.val;
                    C.changeEntry(i, j, v);
                    row[i].moveNext();
                }
            }
            
            if(this.row[i].index() == -1 && M.row[i].index() != -1) {
                Entry B =(Entry)M.row[i].get();
                int j = B.col;
                double v = -(B.val);
                C.changeEntry(i, j, v);
            }
        }
        return C;
    }
    
    //Matrix transpose()
    // returns a new Matrix that is the transpose of this Matrix
    Matrix transpose() {
        Matrix T = new Matrix(this.getSize());
        for(int i = 1; i < size; i++){
            T.row[i].moveFront();
            this.row[i].moveFront();
            
            if(this.row[i].isEmpty()){
                continue;
            }
            else {
                while(this.row[i].index() != -1) {
                    Entry A = (Entry)row[i].get();
                    int j = A.col;
                    double v = A.val;
                    T.changeEntry(j, i, v);
                    row[i].moveNext();
                }
            }
        }
        return T;
    }
    
    //Matrix mult(Matrix M)
    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix mult(Matrix M) {
        int n = this.getSize();
        Matrix C = new Matrix(n);
        Matrix T = M.transpose();
        
       for(int i = 1; i < size; i++){
            C.row[i].moveFront();
            this.row[i].moveFront();
            
            if(this.row[i].isEmpty()){
                continue;
            }
            for(int j = 1; j < size; j++) {
                double v = dot(this.row[i], T.row[i]);
                C.changeEntry(i, j, v);
                }
            }
        return C;
    }
    
    // Other Functions ---------------------------------------------------------
    
    //dot()
    //Returns the dot product of two Lists
    private static double dot(List A, List T) {
        double sum = 0.0;
        A.moveFront();
        T.moveFront();
 
        if(A.isEmpty() || T.isEmpty()){     //if either row is 0
            return sum;                     //the result is 0
        }
        else {
            while(A.index() != -1) {
                Entry C = (Entry)A.get();
                Entry D =(Entry)T.get();
                
                if ( C.col == D.col) {          //if the col values match
                double v = C.val * (D.val);     //multiply and add to sum
                sum += v;
                A.moveNext();
                T.moveNext();
                }
                else if (C.col < D.col) {       //if A's col is smaller -> multiplying by 0
                    A.moveNext();               //no need to add, move A's index
                }
                else if (C.col > D.col) {       //if A's col is greater -> multiplying by 0
                    T.moveNext();               //no add, move Transpose index
                }
            }
        }
        return sum;
    }
    
    // toString()
    // Overides Object's toString() method.
    public String toString(){
        StringBuffer sb = new StringBuffer();
        if (this.NNZ == 0) {
            return new String(sb);
        }

        for(int i = 1; i < size; i++){
            if(row[i].isEmpty()){
                continue;
            }
            else if (row[i].front() != null) {
                sb.append(i);
                sb.append(": ");
                row[i].moveFront();
                while(row[i].index() != -1) {
                    Entry E = (Entry)row[i].get();
                    sb.append(E);
                    row[i].moveNext();
                    if (row[i].index() != -1) {
                        sb.append(" ");
                    }
                }
                sb.append("\n");
            }
        }
        return new String(sb);
    }
    
    //equals():
    //Overrides Matrix equals() method
    public boolean equals(Matrix M){
        boolean eq = false;
        Matrix  that = M;
        
        if (this.getSize() != that.getSize()) {
            return eq;
        }
        else if(this.getNNZ() == that.getNNZ()){
            for(int i = 1; i < size; i++){
                this.row[i].moveFront();
                that.row[i].moveFront();
                
                if(this.row[i].isEmpty() && that.row[i].isEmpty()) {
                    continue;
                }
                
                while(this.row[i].index() != -1) {
                    Entry A = (Entry)this.row[i].get();
                    Entry B = (Entry)that.row[i].get();
                    
                    if((A.val != B.val) || (A.col != B.col)){
                        break;
                    }
                    else {
                        row[i].moveNext();
                    }
                }
            }
            eq = true;
        }
        return eq;
    }
}
