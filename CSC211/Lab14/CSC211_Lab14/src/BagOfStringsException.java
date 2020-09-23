import java.io.IOException;


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author labuser
 */
public class BagOfStringsException extends RuntimeException{
    
    
    public BagOfStringsException(){
        super("Illegal operation on BagOfStrings.");
    }
    
    public BagOfStringsException(String message){
        super(message);
    } 
    
}
