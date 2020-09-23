/**
 *
 * @author Shannon
 */
import java.util.Random;

public class Backpack extends Textbook{
//starts the class

    
//DATA FIELDS
private final int MAX_CAPACITY=10;
private int actualCapacity;
private int initialCapacity;
private final Textbook[]books;
private double totalWeight;
private int currentCapacity;
Backpack[] thebackpack;
private int currentBooks;


//an array of type textbok called books to hold the books  
    
    
   
//default constructor  
    public Backpack()
    {
    currentCapacity= MAX_CAPACITY;      // this line is redundant
    books= new Textbook[MAX_CAPACITY];
  
    }  
    
//Parameterized constructor
    public Backpack(int initialCapacity)
    {
    currentCapacity= initialCapacity;    // this line is redundant
    books= new Textbook[currentCapacity];     //use initialCapacity instead of currentCapacity
    }
   
    
 //METHODS
    //Accesor Methods
 public int numBooks()
 {
     return currentBooks;               //Throughout these methods you need a loop that looks through every slot in the books array.  for (i=0, i< currentCapacity, i++);  (I will mark the ones that need a loop)
 }                                      //The loop also needs an if statement that makes it ignore any null slots.
                                        // if (book[i] != null)   this reads if the slot at position i is not a null then... 
                                        // if statment needs to add to an int counter variable which it will return at the end (start the counter at =0 before the loop
 /*This method gets the number of books currently in the backpack
and returns it*/
 
 
 public int maxBooks()
 {
     return MAX_CAPACITY;       //this won't work if the backpack is made with the 2nd contructor where the capacity can be different than MAX_CAPACITY
 }                              //use currentCapacity or .length
 /*This method returns the maximum number of textbooks the backpack can hold*/
 
 public double getTotalWeight()
 {
     for(int i=0; i < currentCapacity; i++)
     {
      getPageCount();           //just use book[i].getWeight() and make a double variable that gets added to each time the loop make sure to set it =0 before the loop
      getWeight();              
     return (pageCount * PAGE_WEIGHT);   //no return statement should be here
     }
          
     return totalWeight;      //return said variable here
 }
 /*This method gets the total weight of the books currently in the bacpack
 and returns it*/
 
 public boolean getFill()
 {
     if(true){
         return currentCapacity==currentBooks;     // wut? :/
         }
     else{                                          // for loop through array. check for either no null or is a null... if (book[i] == null) OR if(book[i] != null ) a full back would have no null, a not full backpack would have at least 1 null
         System.out.println("not");                 // depending on what you pick depends on which part reutrns true or false. 
         return currentCapacity!=currentBooks;   
         }
 }

/*This method uses an if statement to return true if the backback
is full and false if it is not*/

 public boolean checkBook(Textbook theBook)         //if you are comparing based on the two books String name this input should be a String I believe? That's what I did at least
 {                                                  
boolean subjectMatch;
boolean pageMatch;
     
    for(int i=0; i < currentCapacity; i++)
        
     if(true){                                      // if (true) is confusing me. like if what variable = true? I just understand if this is a condition that would work
         subjectMatch = subject.equals(theBook.getSubject());       // I dont understand the if condition so the idea is you loop through each slot and you ignore anything that is null 
         pageMatch= theBook.getPageCount()== pageCount;             // then I made the comparison based on the String name of the books which it seems like you have
         return subjectMatch && pageMatch;
     }
     else{
         System.out.println("not");
         return false;                          // no reutrn statements in the else or the if parts, only at the end of the method
     }
    return false;      // this return statement must be a boolean variable otherwise this method will always come out as false. your if and else statements' job is to set that variable to either true or false
 }

 /*This method is used to check if a certain book is in the backpack. 
 It sorts through the array and returns true if the book is in the
 backpack and false if it is not
 */


//Mutator Methods                                              // you're not reutrning anything so public void addBook(Name of book or any other Textbook contructor stuffs only)
public Textbook addBook(Textbook theBook)                   // for loop through array and look for == null. if book[i] == null then make book[i] = new Textbook(constructor stuff hurr) (make sure the loop ends once a book is added)
{                                                           // becareful about what if the backpack IS full. I used an if statement that calls my boolean from the getFill() and this method will only do stuff if that returns false
   
}
//take a textbook object and put it in the array in the next index
 
 //This method adds a book to the backpack
 
 public Textbook removeBook(Textbook specificBook)                               //removeBook is also public void. if you are doing it based on the name of the book for instance (which is a String) be sure the
 {                                                                               // loops ends immediately after that specific book is removed to prevent it from removing multiple books.
     for(int i=0; i < currentCapacity; i++)
     {
     specificBook=null;
     }
     return specificBook;                                       //no return statement
/* This method removes a specific book from the backpack*/
 }
 
public Textbook removeHeaviest()                // public void
{      Textbook theHeaviest = null;             // in the previous individual assignment we made two methods. you can use them by copy paste and slight editing. 1 is for finding what the heaviest book is in an array.
    for(int i=0; i < currentCapacity; i++)      // 2 is used to find that heaviest book's index number. with that number you can then use book[that number] = null   then your done with this
    theHeaviest =null;
    return theHeaviest;                         //no return statement
}
/* This method removes the heaviest book from the array*/
 
 public Textbook[] dumpPack()
{ for(int i=0; i < currentCapacity; i++)        // first make a deep copy of the book array (one that doesn't reference it example: someArray = book[]   is bad) there is a system.arraycopy you use
                                                // then loop through the book array and set everything = null
                                                // then return the deep copy of the book array
}
 // empties the backpack and returns array containing all the textbooks that were in the backpack

    
}
//Ends the Backpack class
