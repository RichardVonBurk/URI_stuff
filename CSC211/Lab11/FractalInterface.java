/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.awt.Graphics;
/** Class to draw recursive Fractals
 * @author tim
 */
public interface FractalInterface 
{
    /** Primary drawing method -- this method is not recursive <br>
     *   Instead, this method calls a private recursive helper method
     * @param pen Graphics object of where to draw
     * @param levels Maximum number of recursive levels
     */
    void drawFractal(Graphics pen, int levels);
}
