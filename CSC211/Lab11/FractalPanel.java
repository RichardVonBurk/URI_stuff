import javax.swing.JPanel;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import javax.swing.JOptionPane;


/**
 *
 * @author labuser
 */
class FractalPanel extends JPanel {
    
    private static final int PANEL_SIDE = 300;
    private final QuadSquare painting;
    private int maxLevels;
    private static final int MAX_LEVELS = 7;
        
    public FractalPanel(){
        setLevels();
        painting = new QuadSquare(new Point(0, 0), 300, maxLevels);
        setPreferredSize(new Dimension(PANEL_SIDE, PANEL_SIDE));

    }
    
    public void paintComponent(Graphics pen){
        painting.drawSquare(pen);
    }
    
    //fuer mann recursion verstehen, man muss recursion verstehen.
    public void setLevels()
    {
        boolean validUserInput = false;
        do
        {
            String userResponse = JOptionPane.showInputDialog("How many recursion levels do you want?\nValid values: 1 to " + MAX_LEVELS);
            maxLevels = Integer.parseInt(userResponse);
            validUserInput = (maxLevels >= 1) && (maxLevels <= MAX_LEVELS);
        } while (!validUserInput);
    }
}
