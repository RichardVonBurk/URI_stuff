
import java.awt.Color;
import java.awt.Point;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Rich
 */
public class Filler {
        

    private int[] locateColor(Color[] pixels, Color target, double thresh){
       int[] indices = new int[0];
       double threshMin = target.getRGB() - (thresh * target.getRGB());
       double threshMax = target.getRGB() + (thresh * target.getRGB());
       
       for(int i = 0; i < pixels.length ; i++ ){
           if (pixels[i].getRGB() >= threshMin && pixels[i].getRGB() <= threshMax){
               
           }
           
       }
    
                
       return indices;         
}
