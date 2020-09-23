import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Font;
import java.awt.Rectangle;


public class DrawableTextbook extends Textbook
{
//Data Fields
    Point Location;
    double xVelocity;
    double yVelocity;
    Color bookColor;
    int xPosition;
    int yPosition;
    int absX;
    int absY;
    int dX;
    int dY;
    Point whereToMove;
    private DrawableTextbook myBook;
    
    
//Methods
   
@Override
    public void draw(Graphics pen)
    {
        checkBounds(pen); //checks the book position in order to validate it before drawing
        pen.setColor(bookColor);
        pen.fillRect(xPosition, yPosition, 50, 70);
        pen.setColor(Color.DARK_GRAY);
        pen.setFont(new Font("Monospaced", Font.BOLD, 20));
        pen.drawString(getBookInitials(), xPosition, yPosition+50);
        //draws the textbook
    }
    
    private String getBookInitials() //getBookInitials Method
    {
        String bookSubject = getSubject(); 
        String initials = bookSubject.substring(0,1);
        for (int i = 0; i<bookSubject.length()-1; i++)
        {
        if (bookSubject.charAt(i)==' ')
        initials += bookSubject.substring(i+1, i+2);
        }
        return initials;
        //gets initials of the subject
    }
    
    private void checkBounds(Graphics pen) //checkBounds method
    {
        Rectangle edgeRect = pen.getClipBounds();
        int right = (int)edgeRect.getMaxX();
        int bottom = (int)edgeRect.getMaxY();

        if (myBook.getX() > right)
        {
        moveTo(right, myBook.getY());
        setVelocity(myBook.-(getVelocityX()), myBook.getVelocityY()); 
        }
        
        else if (myBook.getX() < 0)
        {
        setVelocity(myBook.-getVelocityX(), myBook.getVelocityY());
        }

        if (myBook.getY() > bottom)
        {
        moveTo(myBook.getX(), bottom);
        setVelocity(myBook.getVelocityX(), myBook.-getVelocityY()); 
        }
        
        else if (getY() < 0)
        {
         setVelocity(myBook.getVelocityX(), myBook.-getVelocityY()); 
        }
         //checks the textbook is in the window   
     }

    @Override
    private int getX() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    private int getY() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    private void moveTo(int right, int y) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    private int getVelocityX() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    private double getVelocityY() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Point getLocation() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void moveTo(Point whereToMove) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void moveBy(int dX, int dY) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void move() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void setVelocity(double dvX, double dvY) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Color getColor() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Color setColor() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void setColor(Color theColor) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}

          
        
   
         
// Data Fields
 // Constructors
 // Accessor methods
 // Mutator methods
 // Other public methods that do fun things
 // Private helper methods 

