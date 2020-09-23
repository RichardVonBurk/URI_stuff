
import javax.swing.JFrame;
/**
 *
 * @author Richard Burke, Polly Zhou
 */
public class CSC211_Lab11 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        JFrame window = new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setTitle("Fractal Squares");
        
        FractalPanel panel = new FractalPanel();
        window.add(panel);
        window.pack();
        window.setVisible(true);
    }
    
}
