
import javax.swing.JFrame;
import java.awt.Panel;

/**
 * This is the main class for CSC211 Lab 07

 * @author Z. Liang and Richard Burke
 */
public class ControllShapes_Lab07 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        JFrame lab07Window = new JFrame();
        lab07Window.setSize(800, 600); // width x height 
        lab07Window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        lab07Window.setTitle("Controlling Shapes"); 
        
        // This is the panel for this Lab
        ShapePanel panel = new ShapePanel(); 
        lab07Window.add(panel); 
        
        lab07Window.setVisible(true); 
        
        // Launch the shape animation
        // We need a try/catch shape because 
        // Thread.sleep may throw an exception
        try
        {
            panel.shootShape();
        } 
        catch (InterruptedException error)
        {
            System.out.println(error.getMessage());
        }
    }
}
