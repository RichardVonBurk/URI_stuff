//Brevin Jaramillo and Tim Bowder
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.Point;
import java.awt.Toolkit;
import javax.swing.JPanel;
import java.awt.Graphics; 
import java.awt.Color;
import java.awt.Rectangle;
/**
 * This is the JPanel class that does most
 * of the heavy lifting in the lab
 * @author Some Student Programming Pair
 */
public class ShapePanel  extends JPanel
                         implements MouseListener
{
    // gets the current time in millis
    long startTime = System.currentTimeMillis();
    
    // This is a test ball, you should declare more Balls
    Ball myBall;
    Ball myBall2;
    Block myBlock;
    Block myBlock2;
    private int mouseX = 0;
    private int mouseY = 0;
    // Default (only) Constructor
    ShapePanel()
    {
        // Initialize all Balls that you declared above
        // Be sure to test all constructors
        myBall = new Ball();
        myBall2 = new Ball(100,100,3,-2,7,Color.BLUE);
        myBlock = new Block();
        myBlock2 = new Block(150,150,7,-5,7,Color.GREEN);
        addMouseListener(this);
        
    }
    
    @Override
    public void mouseClicked (MouseEvent mouseClick) {
        myBall.moveTo(mouseClick.getX(), mouseClick.getY());
        myBall.setVelocityX(0);
        myBall.setVelocityY(0);
        mouseX = mouseClick.getX();
        mouseY = mouseClick.getY();
    }
    @Override
    public void mousePressed (MouseEvent e){
        
    }
    @Override
    public void mouseReleased (MouseEvent e){
        
    }
    @Override
    public void mouseEntered (MouseEvent e){
        Toolkit.getDefaultToolkit().beep();
    }
    @Override
    public void mouseExited (MouseEvent e){
        Toolkit.getDefaultToolkit().beep();
    }
    
    // Called to paint/repaint the panel
    // This method should only call the draw method
    // of the Ball objects that were declared and initialized.
     public void paintComponent(Graphics pen) 
    {
        pen.setColor(Color.WHITE);
        pen.fillRect(0,0,2000,2000);
        myBall.draw(pen);
        myBall2.draw(pen);
        myBlock.draw(pen);
        myBlock2.draw(pen);
        
    }
      
    
    // This method controls the animation
    public void shootShape() throws InterruptedException
    {
       // while statement says that the loop runs for 20 seconds
       // code from http://stackoverflow.com/questions/19727109/how-to-exit-a-while-loop-after-a-certain-time
       while((System.currentTimeMillis()-startTime)<20000)
       {
           // move each shape
           myBall.move();
           myBall2.move();
           
           // checks to see if the block is at mouse click position if so set velocities to 0
           // if not moves the block to clicked postion
           if (myBlock.getX() == mouseX && myBlock.getY() == mouseY) {
               myBlock.setVelocityX(0);
               myBlock.setVelocityY(0);
           }
           else{
               int xDirection = (int)Math.signum((mouseX - myBlock.getX()));
               int yDirection = (int)Math.signum((mouseY - myBlock.getY()));
               myBlock.moveBy(xDirection, yDirection);
           }
           //myBlock.move();
           myBlock2.move();
           
           // check that the ball is inside the window
           // if not, move into the window and change the velocity
           checkPosition(myBall);
           checkPosition(myBall2);
           checkPosition(myBlock);
           checkPosition(myBlock2);
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
    private void checkPosition(DrawableInterface shape)
    {
        Rectangle edgeRect = getBounds(); // gets boundary of panel
        int panelRight = (int)edgeRect.getMaxX(); // gets max right X
        int panelBottom = (int)edgeRect.getMaxY(); // gets max bottom Y
        
        // determines if the ball has left the screen and if so changes its velocity to negative so it looks like the ball has bounced off the wall
        if (shape.getX() < 0)
        {
            shape.moveTo(1, shape.getY());
            shape.setVelocityX(-1*shape.getVelocityX());
        }
        
        else if (shape.getX() > panelRight)
        {
            shape.moveTo(panelRight-1, shape.getY());
            shape.setVelocityX(-1*shape.getVelocityX());
        }
        
        // determines if the ball has left the screen and if so changes its velocity to negative so it looks like the ball has bounced off the wall
        if (shape.getY() < 0)
        {
            shape.moveTo(shape.getX(), 1);
            shape.setVelocityY(-1*shape.getVelocityY());
        }
        
        else if (shape.getY() > panelBottom)
        {
            shape.setVelocityY(-1*shape.getVelocityY());
            shape.moveTo(shape.getX(), panelBottom-1);
        }
    }
}
