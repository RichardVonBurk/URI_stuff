import javax.swing.JFrame;
import java.awt.Panel;

public class CSC211Lab05 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)throws InterruptedException
    {
        JFrame lab05Window = new JFrame();
        lab05Window.setSize(800, 600); // width x height 
        lab05Window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        lab05Window.setTitle("Lab05: Fire the Ball!"); 
        
        // This is the panel for this Lab
        BallPanel panel = new BallPanel(); 
        lab05Window.add(panel); 
        
        lab05Window.setVisible(true); 
        
        // Launch the ball animation
            panel.shootBall();
      }
}
