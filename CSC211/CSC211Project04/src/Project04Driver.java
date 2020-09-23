/**
 *
 * @author Shannon
 */
import java.util.Random;
import java.util.Scanner;

public class Project04Driver {
    
//Datafields
private Backpack theBackpack;
private int capacity = 10;

    
//default constructor
public Project04Driver()
{
    theBackpack= new Backpack();

       
    String[]SUBJECT_LIST= {"Stats", "English", "Calc", "Marketing", "Philosophy"};
    /*Creates an array SUBJECT LIST*/
    
    Backpack theBackpack= new Backpack();
    
    final int MAX_TEXT =1500;
    /*Sets the maximum number of pages to 1500 */
   
    final int MIN_TEXT =500;
    /*Sets the minimum number of pages to 500*/
    
    Random generator= new Random();
    /*Creates a new random generator */
    
    
    /*
     * This is a for loop in the constructor that randomly generates a new 
     * textbook out of the five potential subject types in the array SUBJECT_LIST
     */
    for(int i=0; i < capacity; i++)
    {     
    String subjectType= SUBJECT_LIST[generator.nextInt(5)];
    /* Randomly selects a subject type from the array SUBJECT_LIST */
    
   int pageCount= generator.nextInt(MAX_TEXT - MIN_TEXT) + MIN_TEXT;
    /*
     * This randomly sets the pageCount to a number between the maximum page
     * number and the minimum page number. 
     */
 
    theBackpack.addBook(new Textbook(subjectType, pageCount));
   
    /*Creates a new textbook*/
     }
    /* This ends the for loop */
  
}

    
//METHODS
public void testBackpack()
{
    System.out.println("The number of books currently in the backpack is: " + theBackpack.numBooks());
    System.out.println("The maximum number of books the backpack can hold is: " + theBackpack.maxBooks());
    System.out.println("The total weight of the books in the backpack are: "+ theBackpack.getTotalWeight());
    System.out.println("The backpack is "+ theBackpack.getFill() +" full");
    System.out.println("The book is" + theBackpack.checkBook() + " in the book");
    System.out.println("You have added another book. The number of books in the backpack is now: " + theBackpack.addBook());
    System.out.println("You have removed a book. The number of books in the backapack is now: " +theBackpack.removeBook());
    System.out.println(theBackpack.removeHeaviest());
    System.out.println(theBackpack.dumpPack());
   

}
//ends the testBackpack method

//ends class Project04Driver
}
