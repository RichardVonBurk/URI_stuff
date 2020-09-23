
import java.awt.Color;
import java.awt.Graphics;

/**
 *
 * @author Tim
 */
public interface DrawableInterface {
    
    
      // Accessor methods
    public int getX();

    
    public int getY();
    
    
    public double getVelocityX();

    
    public double getVelocityY();
   
    
     public Color getColor();
    
    
       // mutator methods
    
    public Color setColor(Color theColor);
      
      
    public double setVelocityX(double velX);
    
    public double setVelocityY(double velY);
    
     // moves the ball to the position input
    public void moveTo(int absoluteX, int absoluteY);
    
    // moves ball relative to current positions dx units on
    // X-axis and dy units on Y-axis
    public void moveBy(int dx, int dy);
    
    // moves ball relative to current positions xVelocity units on X-axis and yVelocity units on Y-axis (moves ball based on its velocity)
    public void move();
    
 
     public void draw(Graphics pen);
}
