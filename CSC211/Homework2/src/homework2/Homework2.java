/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package homework2;


/**
 *
 * @author Rich
 */
public class Homework2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        String myCoolMessage = new String("If I could program in Java every day, my life would be great!") ;
        
        int commaLocation = myCoolMessage.indexOf(",");
        
        System.out.println("The letter immediately preceding the first comma is " + myCoolMessage.substring(commaLocation-1, commaLocation) + "." );

        
        
           // TODO code application logic here
    }
    
}
