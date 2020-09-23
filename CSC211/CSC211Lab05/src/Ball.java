import java.awt.Graphics;
import java.awt.Color;

public class Ball {
  
private int xPosition;
private int yPosition;
private double xVelocity;
private double yVelocity;
private double radius;
private Color ballColor;
    
public Ball()
{
xPosition = 0;
yPosition = 0;
xVelocity = Math.random() * 10 - 5;
yVelocity = Math.random() * 10 - 5;
radius = 3;
ballColor = Color.RED; 
}
//Default constructor

public Ball(int posX, int posY, double velX, double velY, double myRadius, Color myColor)
{
xPosition = Math.abs(posX);
yPosition = Math.abs(posY);
if (velX < -5 || velX > 5){
    xVelocity = Math.random() * 10 - 5;
}
if (velY < -5 || velY > 5){
    yVelocity = Math.random() * 10 - 5;
}

if (myRadius <= 1 || myRadius > 15){
    radius = 3;
}
ballColor = myColor; 
    
}
//Constructor

//Data Fields



public int getxPosition()
{
    return xPosition;
}

public int getyPosition()
{
    return yPosition;
}

public double getxVelocity()
{
    return xVelocity;
}

public double getyVelocity()
{
    return yVelocity;
}

public double getradius()
{
    return radius;
}

public Color getballColor()
{
    return ballColor;
 //this method gets the color of the ball and returns it
}

public void setColor(Color theColor)
{
    Color ballColor = theColor;    //sets color of ball
}

public void setVelocity(double velX, double velY)
{
   xVelocity= velX;
   yVelocity= velY;
   //this method sets x and y velocity
}

public void moveTo(int absoluteX, int absoluteY)
{
    absoluteX = Math.abs(absoluteX);
    absoluteY = Math.abs(absoluteY);
    xPosition = absoluteX;
    yPosition = absoluteY;
   //this method moves the ball to position absoluteX and absoluteY
}

public void moveBy(int dx, int dy)
{
    xPosition += dx;
    yPosition += dy;
//This methodmoves ball relative to current positions dx units on X-axis and dy units on Y-axis 
}

public void move()
{
    xPosition += xVelocity;
    yPosition += yVelocity;    
 //This method moves ball relative to current positions xVelocity units on X-axis and yVelocity units on Y-axis
 //moves ball based on its velocity
}

public void draw(Graphics pen)
{
    pen.drawOval(xPosition, yPosition,(int) radius,(int) radius);
}
public String toString()
{
    String retVal = "Position = (" + xPosition +", "+ yPosition+")\n";
    retVal = retVal + "Velocity (dx, dy) = (" + xVelocity +", "+ yVelocity+")\n";
    retVal = retVal + "Radius = (" + radius +")\n";
    retVal = retVal + "Ball Color = (" + ballColor +")\n";
    
    return retVal;
}
        
        
        
       
        
        
           
        
        
        
}

