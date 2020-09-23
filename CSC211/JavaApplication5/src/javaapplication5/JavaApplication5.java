/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication5;

/**
 *
 * @author Rich
 */
public class JavaApplication5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    //boolean rolled_a_six = false;
    
    while (boolean rolled_a_six == false) {

         int rollDie = (int) ((Math.random() *6) +1);   //http://math.hws.edu/javanotes/c2/ex2-ans.html

         System.out.println (rollDie);

         if (rollDie == 6) {

         rolled_a_six = true;

         }
    }
    }

    
}
