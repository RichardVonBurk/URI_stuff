import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

/**
 *
 * @author labuser
 */
public class QuadSquare {
    
    
    /**
     * declarations for dimensions
     */
    
    private int xCorner;
    private int yCorner;
    private int side;
    private int maxLevels;
    
    /**
     * default constructor takes input of a point and a side of the square
     * converts the point of the corner to the center of the square
     */
    
    public QuadSquare(Point corner, int newSide, int level){ //newside = 5
        
        xCorner = (int)corner.getX() + (newSide/2);
        yCorner = (int)corner.getY() + (newSide/2);
        side = newSide;
        maxLevels = level;
    }
    
    /**
     * this method is called to enable recursion 
     */
    
    
    public void drawSquare(Graphics pen){
        this.drawQuads(xCorner, yCorner, side, pen, maxLevels);
    }
    
    private void drawQuads(int x, int y, int newSide, Graphics pen, int levels){
        
        // levels are to the amount of recursion 
        if (levels > 0){
            
            //to figure out where to draw the side of the corner square
            newSide = newSide /3;
            pen.setColor(Color.BLACK);
        
            // Big center square
            pen.drawRect(x - newSide/2, y - newSide/2, newSide, newSide);
        
            //call for each corner recursively
            
            drawQuads(x - newSide/2, y - newSide/2, newSide, pen, levels-1);
            drawQuads(x + newSide/2, y - newSide/2, newSide, pen, levels-1);
            drawQuads(x - newSide/2, y + newSide/2, newSide, pen, levels-1);
            drawQuads(x + newSide/2, y + newSide/2, newSide, pen, levels-1);
        }
        
    }
   


    
}
