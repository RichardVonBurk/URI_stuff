
import javax.swing.JFrame;
import java.awt.Panel;
import javax.swing.JOptionPane;

/**
 * This is the main class for CSC211 Lab 07

 * @author Logan Misturado and Richard Burke
 */
public class CSC211_Lab09 {

 
    
    
    public static void main(String[] args)  
    {
        //Prompts user for number of shapes
        JOptionPane pane = new JOptionPane();
        String prompt = JOptionPane.showInputDialog("How many shapes do you want to create?");
        int numberShapes = Integer.parseInt(prompt);
        
        JFrame Frame = new JFrame();
        Frame.setSize(800, 600); // width x height 
        Frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        Frame.setTitle("Controlling Shapes"); 
        
        // This is the panel for this Lab
        Lab09Panel panel = new Lab09Panel(numberShapes); 
        Frame.add(panel); 
        
        Frame.setVisible(true); 
        
        // Launch the shape animation
        // We need a try/catch shape because 
        // Thread.sleep may throw an exception
        try
        {
            panel.animateShapes();
        } 
        catch (InterruptedException error)
        {
            System.out.println(error.getMessage());
        }
    }
}
