
import javax.swing.JPanel;
import java.awt.Graphics; 
import java.awt.Color;
import java.awt.Rectangle;
import java.time.LocalDateTime;
/**
 * This is the JPanel class that does most
 * of the heavy lifting in the lab
 * @author Some Student Programming Pair
 */
public class BallPanel  extends JPanel
{
    // This is a test ball, you should declare more Balls
    Ball myBall;
    

    
    // Default (only) Constructor
    BallPanel()
    {
        // Initialize all Balls that you declared above
        // Be sure to test all constructors
        myBall = new Ball();
    }
    
    // Called to paint/repaint the panel
    // This method should only call the draw method
    // of the Ball objects that were declared and initialized.
    public void paintComponent(Graphics pen) 
    {
        super.paintComponent(pen);
        myBall.draw(pen);
    }
    
    // This method controls the animation
    public void shootBall() throws InterruptedException
    {
        LocalDateTime now = LocalDateTime.now();
        LocalDateTime later = now.plusSeconds(20);
        
        // *** Fix this loop so that it only runs for 20 seconds ***
       while(later.isAfter(LocalDateTime.now()))
       {
           // move each ball
           myBall.move();
           
           // check that the ball is inside the window
           // if not, move into the window and change the velocity
           checkPosition(myBall);{
           Rectangle edgeRect = getBounds();
           
           if (myBall.getxPosition() >  edgeRect.getMaxX() || myBall.getxPosition() < 0){
               
               if (myBall.getxPosition() > edgeRect.getMaxX()){
                   myBall.moveTo(myBall.getxPosition() -2, myBall.getyPosition());
               }
               
               if (myBall.getxPosition() < 0){
                   myBall.moveTo(myBall.getxPosition() +2, myBall.getyPosition());
               }
               
                myBall.setVelocity(myBall.getxVelocity() * -1, myBall.getyVelocity());
            }
           
           if (myBall.getyPosition() > edgeRect.getMaxY() || myBall.getyPosition() < 0){
               
               if (myBall.getyPosition() > edgeRect.getMaxY()){
                   myBall.moveTo(myBall.getxPosition(), myBall.getyPosition() +2);
               }
               
               if (myBall.getyPosition() < 0){
                   myBall.moveTo(myBall.getxPosition(), myBall.getyPosition() +2);
               }
               
                myBall.setVelocity(myBall.getxVelocity(), myBall.getyVelocity() * -1);
            }
           

           }
           
           // force redraw of window to draw balls in new locations
           // ** repaint calls paintComponent
           repaint(); 
           
           // sleep for n milliseconds so the animation doesn''t pass too fast
           Thread.sleep(10);
           
           
    
        
       }
    }
    
    // This method should:
    //      Get the right and bottom coordinates of the panel
    //      Check that the ball is inside the panel (top, left, right, bottom)
    //      If the ball is outside the panel, 
    //          move it back inside the panel
    //          change the velocity for the direction it was outside the panel    
    private void checkPosition(Ball theBall)
    {

    }
}
