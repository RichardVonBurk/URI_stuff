
package csc211_richardburke_individualassignment_01;
import java.util.Scanner;

public class StudentDriver {
    
    public static void testStudent(){
        
        Scanner reader = new Scanner(System.in);   
        Student student = new Student();            //create default student to be mutated or not
        
                
        System.out.println("Hello!");
        System.out.println("Type in a name for a student.");
        String inputName = "";                       //source used for this part http://stackoverflow.com/questions/5689325/blank-input-from-scanner-java
        inputName = reader.nextLine();               //uses default name if enduser does not put anything in
                
        if(inputName.equals("")){       //uses defualt name
            System.out.println("No name? Fine, the name will be " + student.getName());
        }
        else{
            student.setName(inputName);     //uses inputted name
            System.out.println(student.getName() + "? That's a nice name.");
        }
        
        System.out.println(student.getName() + " has " + student.getHealth() + " health with " + student.getKnowledge() + " knowledge." );      //tell the info of student
        System.out.print("Also " + student.getName() + " has a new textbook with the subject " + student.getBook());                            //tell the info of book
        System.out.println(". It is " + student.book.getPageCount() + " pages long.");
        System.out.println("The textbook weighs " + student.book.getWeight() + " kgs.");
        
        System.out.println("How many pages will " + student.getName() + " read? (Note: extra read pages will only count as reviewing pages)");  //ask for numPages to be read
        int numPages = reader.nextInt();
        student.learnSomething(numPages); //calls this method to calculate knowledge gain and unread pages if any are left
        
        System.out.println(student.getName() + " has gained " + student.getKnowledge() + " knowledge!");       //Tell enduser results of calculation
        System.out.println(student.book.getSubject() + " now has " + student.book.getUnreadPageCount() + " unread page(s) out of " + student.book.getPageCount() + " pages.");
       
        
    }
}
