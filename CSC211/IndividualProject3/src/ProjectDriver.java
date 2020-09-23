import java.util.Random;
import java.util.Scanner;

/** 
 * Creates the array with all subjects to later be randomly assigned  
 * Random generator is used to generate page numbers and used in a switch to determine the books subject
 * Textbook [] library is the array and the number of elements
 * @author Burke
 */
public class ProjectDriver {
    String[] SUBJECT_LIST = {"Python", "Java", "C++", "Javascript", "C#"};
    
    Random generator = new Random();    
    
    Textbook[] library = new Textbook[10000];
    
    /**
     * heaviestBook is for the weight
     * heaviestIndex is where that book is located in the array
     */
    private double heaviestBook;
    private int heaviestIndex;
    
    /**
     * createLibrary 
     * loops and puts a textbook in each element
     * the randomly select a subject for each Textbook from SUBJECT_LIST and a  
     * random pageCount  for each Textbook between 500 and 1500.
     */
    public void createLibrary(){
        for (int i = 0; i < library.length; i++){
        
            int newPageCount = (generator.nextInt(1001) + 500);
        
        
            switch (generator.nextInt(5)) {
                case 0:
                    library[i] = new Textbook(SUBJECT_LIST[0], newPageCount) ;
                    break;
                case 1:
                    library[i] = new Textbook(SUBJECT_LIST[1], newPageCount) ;
                    break;
                case 2:
                    library[i] = new Textbook(SUBJECT_LIST[2], newPageCount) ;
                    break;
                case 3:
                    library[i] = new Textbook(SUBJECT_LIST[3], newPageCount) ;
                    break;
                case 4:
                    library[i] = new Textbook(SUBJECT_LIST[4], newPageCount) ;
                    break;
                default:
                    break;
            }
            
            
        }
    }
 
    /**
     * findHeaviest returns the weight of the heaviest textbook in the library 
     */
    public double findHeaviest(){
        heaviestBook = 0.0;
        for (int i = 0; i < library.length; i++) {
            if (heaviestBook < library[i].getWeight()) {
                heaviestBook = library[i].getWeight();
            }
        }
        return heaviestBook;
    }
    
    /**
     * getHeaviest returns the index of the heaviest textbook in the library 
     */
    
    public int getHeaviest(){
        heaviestBook = findHeaviest();
        boolean foundHeaviest = false;
        for (int i = 0; i < library.length; i++){
            
            if (library[i].getWeight() == heaviestBook && foundHeaviest == false){
                foundHeaviest = true;
                heaviestIndex = i;
            }
            
        }
        return heaviestIndex;
    }
    
    /**
     * computeAverageSize returns the average page count for all the textbooks 
     */
    
    public int computeAverageSize(){
        int totalPages = 0;
        for (int i = 0; i < library.length; i++){
            totalPages += library[i].getPageCount();
        }
        int averageNumPages = totalPages / library.length;
        return averageNumPages;
    }
    
    /**
     * computeTotalPages returns the total number of pages in all the textbooks in library 
     */
    
    public int computeTotalPages(){
        int totalPages = 0;
        for (int i = 0; i < library.length; i++){
            totalPages += library[i].getPageCount();
        }
        return totalPages;
    }
    
    /**
     * getLibraryStats calls all of the above methods and reports on the library’s stats, 
     * including how many total textbooks are int eh library. This is the method called from the main() class.
     */
    
    public void getLibraryStats(){
        Scanner reader = new Scanner(System.in);
        this.createLibrary();
        
        System.out.println("Hello!");
        System.out.println("Here are some of the stats on the Library:");
        System.out.println("There are " + library.length + " books.");
        System.out.println("The heaviest book weighs " + this.findHeaviest() + " kgs.");
        System.out.println("The heaviest book is book no. " + this.getHeaviest() + ".");
        System.out.println("The average number of pages across all the books is " + this.computeAverageSize() + " pgs." );
        System.out.println("The total number of pages across all the books is " + this.computeTotalPages() + " pgs.");

    }
    
    
    
    
    
    
    
    
    
    
    
}