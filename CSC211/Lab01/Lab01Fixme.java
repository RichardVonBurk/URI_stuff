//Richard Burke, Matthew Beaudreault

import java.util.Scanner;
//import library
public class Lab01Fixme {
    public static void main(String[] args) {
        // Initializing variables 
	String userInput;
	String trimmedUserInput;
        String firstWord;
        String lastWord;
	int pos1Index = 0;
        int pos2Index;
        
        //Scan for keyboard
        Scanner keyboard = new Scanner(System.in);
        
	//begin printing
        System.out.println("Hello World!");
	System.out.println("Could you say a few words?" );
            // ask for user input
            userInput = keyboard.nextLine();
            
        //Prints string with user input
        System.out.println("You have typed in "+ userInput.length() + " characters." );
        //Trims string and give value to variables
        trimmedUserInput = userInput.trim();
        //Set to beginning of string
	
        //Takes index of the first space
        pos2Index = trimmedUserInput.indexOf(" ");
        //Make a substring of word inbetween index 0 & the index of first space
	firstWord = trimmedUserInput.substring(pos1Index, pos2Index);
        
        //prints out first word
	System.out.println("Your first word is:\"" + firstWord + "\"," );
        
        //Grabs index of last space
        pos1Index = trimmedUserInput.lastIndexOf(" ") + 1;
	//Takes the index of the entire string
        pos2Index = trimmedUserInput.length();
        //Make a string of the last word of the index
        lastWord = trimmedUserInput.substring(pos1Index, pos2Index);
        
        //prints last word and print bye
	System.out.println("and your last word is:\""+ lastWord + "\"." );		
	System.out.println("Bye!");
}
}
			
