//Brevin Jaramillo and Tim Bowder
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.Point;
import java.awt.Toolkit;
import javax.swing.JPanel;
import java.awt.Graphics; 
import java.awt.Color;
import java.awt.Rectangle;
import java.util.Random;
/**
 * This is the JPanel class that does most
 * of the heavy lifting in the lab
 * @author Some Student Programming Pair
 */
public class Lab09Panel  extends JPanel
                         implements MouseListener
{
    // gets the current time in millis
    long startTime = System.currentTimeMillis();
    final int DEFAULT_SHAPES = 100;
    DrawableInterface[] shapes; //this is where the array for the number of shapes is created
    // This is a test ball, you should declare more Balls
    Ball myBall;
    Ball myBall2;
    Block myBlock;
    Block myBlock2;
    private int mouseX = 0;
    private int mouseY = 0;
    Random generator = new Random();
    
    // Default (only) Constructor
    Lab09Panel()
    {
        // creates and amends to the array a shape for each number of desired shapes
        // Initialize all Balls that you declared above
        // Be sure to test all constructors
        shapes = new DrawableInterface[DEFAULT_SHAPES];
        for(int i = 0; i < shapes.length; i++){
            if(generator.nextInt(2) == 0){
                shapes[i]= new Ball();   // generates either 0 or 1 if 0 create ball, if 1 create block
            }
            else{
                shapes[i] = new Block();
            }
        }
        addMouseListener(this);
        
    }
    
      Lab09Panel(int numberShapes)
    {
        // Initialize all Balls that you declared above
        // Be sure to test all constructors
            // creates and amends to the array a shape for each number of desired shapes
        if (numberShapes > 0){
            shapes = new DrawableInterface[numberShapes];
        }
        else {
            shapes = new DrawableInterface[DEFAULT_SHAPES];
        }
        for(int i = 0; i < shapes.length; i++){
            if(generator.nextInt(2) == 0){
                shapes[i] = new Ball();
            }
            else{
                shapes[i] = new Block();
            }
        }

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
        for (DrawableInterface element : shapes){
            element.draw(pen);
        }
        
    }
      
    
    // This method controls the animation
    public void animateShapes() throws InterruptedException
    {
       // while statement says that the loop runs for 20 seconds
       // code from http://stackoverflow.com/questions/19727109/how-to-exit-a-while-loop-after-a-certain-time
       while((System.currentTimeMillis()-startTime)<20000)
       {
           
           for (DrawableInterface element : shapes){
               
               element.move();
                              
               if (element.getX() == mouseX && element.getY() == mouseY) {
                element.setVelocityX(0);
                element.setVelocityY(0);
                }
               
              else{
                int xDirection = (int)Math.signum((mouseX - element.getX()));
                int yDirection = (int)Math.signum((mouseY - element.getY()));
                element.moveBy(xDirection, yDirection);
               }
               
               checkPosition(element);
               
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
            shape.moveTo(panelRight-20, shape.getY());
            shape.setVelocityX(-1*shape.getVelocityX());
            System.out.println(shape.getVelocityX());
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
