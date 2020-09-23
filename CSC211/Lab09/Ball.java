import java.util.Random;
import java.awt.Color;
import java.awt.Graphics;

public class Ball implements DrawableInterface
{
    Random generator = new Random();
    
    // Data Fields
    private int xPosition;
    private int yPosition;
    private double xVelocity;
    private double yVelocity;
    private double radius;
    private Color ballColor;
    
    // defualt constructor
    public Ball()
    {
        xPosition = generator.nextInt(101);
        yPosition = generator.nextInt(101);
        xVelocity = (generator.nextDouble()*9.0)+1.0;
        yVelocity = (generator.nextDouble()*9.0)+1.0;
        radius = (generator.nextDouble()*14.0)+1.0;
        ballColor = new Color(generator.nextInt(Integer.MAX_VALUE));
    }
    
    // contructor with inputs
    public Ball(int posX, int posY, double velX, double velY, double myRadius, Color myColor)
    {
        xPosition = posX;
        // if statements determine if the user inputs are valid, if they are not, they are reset to default values
        if (xPosition < 0)
        {
            xPosition = 0;
        }
        yPosition = posY;
        if (yPosition < 0)
        {
            yPosition = 0;
        }
        xVelocity = velX;
        if (xVelocity < -5 || xVelocity > 5)
        {
           xVelocity = Math.floor(Math.random()*11)-5; 
        }
        yVelocity = velY;
        if (yVelocity < -5 || yVelocity > 5)
        {
            yVelocity = Math.floor(Math.random()*11)-5;
        }
        radius = myRadius;
        if (radius < 1 || radius > 15)
        {
            radius = 3;
        }
        ballColor = myColor;
    }
    
    // Accessor methods
    public int getX()
    {
        return xPosition;
    }
    
    public int getY()
    {
        return yPosition;
    }
    
    public double getVelocityX()
    {
        return xVelocity;
    }
    
    public double getVelocityY()
    {
        return yVelocity;
    }
    
    public double getRad()
    {
        return radius;
    }
    
    public Color getColor()
    {
        return ballColor;
    }
    
    // mutator methods
    public double setVelocityX(double velX)
    {
        if (xVelocity < -11 || xVelocity > 11)
        {
            return xVelocity;
        }
        xVelocity = velX;
        return xVelocity;   
    }
    
    public double setVelocityY(double velY)
    {
        if (yVelocity < -11 || yVelocity > 11)
        {
            return yVelocity;
        }
        yVelocity = velY;
        return yVelocity;
    }
    
    public Color setColor(Color theColor)
    {
        ballColor = theColor;
        return ballColor;
    }
    
    // moves the ball to the position input
    public void moveTo(int absoluteX, int absoluteY)
    {
        xPosition = absoluteX;
        yPosition = absoluteY;
    }
    
    // moves ball relative to current positions dx units on
    // X-axis and dy units on Y-axis
    public void moveBy(int dx, int dy)
    {
        xPosition  = xPosition + dx;
        yPosition = yPosition + dy;
    }
    
    // moves ball relative to current positions xVelocity units on X-axis and yVelocity units on Y-axis (moves ball based on its velocity)
    public void move()
    {
        xPosition = xPosition + (int)xVelocity;
        yPosition = yPosition + (int)yVelocity;
    }
    
    // draws the ball
    public void draw(Graphics pen)
    {
        pen.setColor(ballColor);
        pen.fillOval(xPosition, yPosition, (int)radius, (int)radius);
        pen.drawOval(xPosition, yPosition, (int)radius, (int)radius);
    }
    
    // converts the balls attributes to a readable string
    public String toString()
    {
        return ballColor + " Circle with radius " + radius + " is at position " + xPosition + "," + yPosition + " and it has an x velocity of " + xVelocity + "and a y velocity of" + yVelocity;
    }
}
