//Nichole Boothroyd     CruzID: nboothro    Assignment: pa3
//-----------------------------------------------------------------------------
//  List.java
//      Modifying List ADT to work with the Matrix ADT.
//-----------------------------------------------------------------------------
public class List{
    
    private class Node{
        // Fields
        Object data;
        Node next;
        Node prev;
        
        // Constructor
        Node(Object x) { this.data = x; next = null; prev = null; }
        
        // toString():  overrides Object's toString() method
        public String toString() {
            return String.valueOf(data);
        }
        
        // equals(): overrides Object's equals() method
        public boolean equals(Object x){
            boolean eq = false;
            Node that;
            if(x instanceof Node){
                that = (Node) x;
                eq = (this.data==that.data);
            }
            return eq;
        }
    }
    
    // Fields
    private Node front;
    private Node back;
    private int length;
    private int index;
    
    // Constructor:  Creates a new list [empty]
    List() {
        front = back = null;
        length = 0;
        index = -1;              //initialized at -1?  May need to come back to this. ..
    }
    
    
    // Access Functions --------------------------------------------------------
    
    // isEmpty()q
    // Returns true if this List is empty, false otherwise.
    public boolean isEmpty() {
        return length==0;
    }
    
    // length()
    // Returns length [number of elements] of this List.
    public int length() {
        return length;
    }
    
    //index()
    //If the cursor is defined; returns the index of the cursor element, otherwise, returns -1
    public int index() {
        return index;       //index initialized at -1, will already return -1 if undefined
    }
    
    // front()
    // Returns front element.
    // Pre: !this.isEmpty()
    public Object front(){
        if( this.isEmpty() ){
            throw new RuntimeException(
                                       "List Error: front() called on empty List");
        }
        return front.data;
    }
    
    //back()
    //Returns back element.
    //Pre: !this.isEmpty()
    public Object back(){
        if( this.isEmpty() ){
            throw new RuntimeException(
                                       "List Error: back() called on an empty List");
        }
        return back.data;
    }
    
    //get()
    //Returns cursor element.
    //Pre: !this.isEmpty()
    //Pre: index needs to be defined
    public Object get(){
        if( this.isEmpty() | this.index() < 0){
            throw new RuntimeException (
                                        "List Error: get() called on empty list or invalid index");
        }
        Node temp = front;
        for(int i = 1; i <= this.index(); i++) {
            temp = temp.next;
        }
        return temp.data;
    }
    
    // equals()
    // Overrides Object's equals() method.  Returns true if x is a List storing
    // the same integer sequence as this List, false otherwise.
    public boolean equals(Object x){
        boolean eq  = false;
        List Q;
        Node N, M;
        
        if(x instanceof List){
            Q = (List)x;
            N = this.front;
            M = Q.front;
            eq = (this.length==Q.length);
            while( eq && N!=null ){
                eq = N.equals(M);
                N = N.next;
                M = M.next;
            }
        }
        return eq;
    }
    // Manipulation Procedures -------------------------------------------------
   
    //clear ()
    //Resets this List to its original empty state
    //Pre: !this.isEmpty()
    void clear() {
/*        if(this.isEmpty()) {
            throw new RuntimeException(
                                       "List Error: List is already empty");
        }
*/      
            front = back = null;
            length = 0;
            index = -1;
        //Should ^this^ be deleting from memory instead of just reassigning?
    }
    
    //moveFront()
    //Places the cursor under front element, or does nothing [not even an error message?]
    //Pre: !this.isEmpty()
    void moveFront(){
            if(!this.isEmpty()){
                index = 0;          //the index for the first element should be 0
            }
    }
    
    //moveBack()
    //If the List is non-empty, places the cursor under the back element, otherwise does nothing
    //[no error message?]
    //Pre: !this.isEmpty()
    void moveBack(){
        if(!this.isEmpty()){
            index = (this.length() - 1);        //The index for the last element == (length-1) of the list
        }
    }
    
    //movePrev ()
    //If cursor is defined and not at front, moves cursor one step toward
    //front of this List, if cursor is defined and at front, cursor becomes
    //undefined, if cursor is undefined does nothing.
    void movePrev() {
        if(this.index() == -1) {        //if the cursor is undefined exit the function
            //do nothing
        }
        else {
            index--;                    //whether or not the cursor is at the front[0], just index - 1
        }                               //cursor will become undefined at [-1]
    }
    
    //moveNext()
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void moveNext() {
        if(this.index() == -1) {
         //do nothing
        }
       else {
           index++;
           if(this.index() >= this.length()) {      //if cursor goes past the back
               index = -1;							//cursor becomes undefined
           }
       }
    }
    
    // append()
    // Appends data to back of this List.
    void append(Object data){
        Node N = new Node(data);
        if( this.isEmpty() ) {
            front = back = N;
        }
        else{
            back.next = N;
            N.prev = back;
            back = N;
        }
        length++;
    }
   //prepend()
   //Insert new element into this List. If List is non-empty, insertion takes place before front element
    void prepend(Object data) {
        Node N = new Node(data);
        if(this.isEmpty()) {
            front = back = N;
        }
        else {
            N.next = front;     //N.next is now pointing to what was originally the front element
            front.prev = N;     //set front.prev to point to the new N
            front = N;          //Set N as the new front
        }
        length++;
        index++;
    }
   
    //insertBefore()
    //Insert new element before cursor
    //Pre: length()>0, index()>=0
    void insertBefore(Object data) {
        if(this.length() == 0 | this.index() < 0) {
            throw new RuntimeException (
                                        "List Error: insertBefore() called on empty list or bad cursor");
        }
        else if (this.index() == 0) {
            this.prepend(data);
        }
        else {
            Node N = new Node(data);
            Node temp = front;
            for(int i = 1; i <= this.index(); i++) {   //Traverse to cursor. If cursor is at front [0]: skip
                temp = temp.next;
            }
            N.next = temp;                     //Clean up all the node pointers
            N.prev = temp.prev;
            temp.prev.next = N;
            temp.prev = N;
            length++;
            index++;                            //move index up one to maintain cursor
        }
    }
    
    //insertAfter()
    //Inserts new element after cursor.
    //Pre: length()> 0, index()>=0
    void insertAfter(Object data) {
        if(this.length() == 0 | this.index() < 0) {
            throw new RuntimeException (
                                        "List Error: insertAfter() called on empty list or bad cursor");
        }
        else if (this.index() == (this.length() - 1)) {
            this.append(data);
        }
        
        else {
            Node N = new Node(data);
            Node temp = front;
            for(int i = 1; i <= this.index(); i++) {
                temp = temp.next;
            }
            temp.next.prev = N;         //The node after temp now points its prev to
            N.next = temp.next;         //New node's next points to cursor's next element
            N.prev = temp;              //New node's prev points to cursor
            temp.next = N;              //Cursor's next points to new node
            length++;
        }
    }
    
    // deleteFront()
    // Deletes front element from this List.
    // Pre: !this.isEmpty()
    void deleteFront(){
        if(this.isEmpty()){
            throw new RuntimeException(
                                       "List Error: deleteFront() called on empty List");
        }
        if(this.length() > 1){
            front = front.next;
            front.prev = null;
            if (this.index() == 0) {
                index = -1;
            }
            else {
                index--;
            }
        }else{
            front = back = null;
        }
        length--;
    }
    
    //deleteBack()
    //Deletes the back element
    //Pre: !this.isEmpty()
    void deleteBack() {
        if(this.isEmpty()){
            throw new RuntimeException(
                                       "List Error: deleteBack() called on empty List");
        }
        if(this.length() > 1) {
            back = back.prev;
            back.next = null;
            if (this.index() == (this.length() - 1)) {
                index = -1;
            }
        }
        else {
            front = back = null;
            index = -1;
        }
        length--;
    }
    
    //delete()
    //Deletes cursor element, making it undefined
    //Pre: length()>0, index()>=0;
    void delete() {
        if( this.isEmpty() |this.index() < 0) {
            throw new RuntimeException(
                                       "List Error: delete() called on empty List or bad cursor");
        }
        else if (this.index() == 0) {
            this.deleteFront();
        }
        else if (this.index() == (this.length() - 1)) {
            this.deleteBack();
        }
        else {
            Node temp = front;
            for(int i = 1; i <= this.index(); i++) {
                temp = temp.next;
            }
            temp.next.prev = temp.prev;
            temp.prev.next = temp.next;
            index = -1;                 //Cursor now undefined
            length--;
        }
    }
    
    
    // Other Functions ---------------------------------------------------------
    
    // toString()
    // Overides Object's toString() method.
    public String toString(){
        StringBuffer sb = new StringBuffer();
        Node N = front;
        while(N!=null){
            //sb.append(" ");
            sb.append(N.toString());
            N = N.next;
            if(N != null) {
                sb.append(" ");
            }
        }
        return new String(sb);
    }
    
}
