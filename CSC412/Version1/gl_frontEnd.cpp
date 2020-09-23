//
//  gl_frontEnd.c
//  GL threads
//
//  Created by Jean-Yves Hervé on 2018-12-05

 /*-------------------------------------------------------------------------+
 |	A graphic front end for a grid+state simulation.						|
 |																			|
 |	This application simply creates a glut window with a pane to display	|
 |	a colored grid and the other to display some state information.			|
 |	Sets up callback functions to handle menu, mouse and keyboard events.	|
 |	Normally, you shouldn't have to touch anything in this code, unless		|
 |	you want to change some of the things displayed, add menus, etc.		|
 |	Only mess with this after everything else works and making a backup		|
 |	copy of your project.  OpenGL & glut are tricky and it's really easy	|
 |	to break everything with a single line of code.							|
 |																			|
 +-------------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//
#include "gl_frontEnd.h"


const extern int MAX_NUM_MESSAGES;
const extern int MAX_LENGTH_MESSAGE;

extern SquareType** grid;
extern unsigned int numRows;	//	height of the grid
extern unsigned int numCols;	//	width
extern unsigned int numLiveThreads;		//	the number of live traveler threads


//---------------------------------------------------------------------------
//  Private functions' prototypes
//---------------------------------------------------------------------------

void myResize(int w, int h);
void displayTextualInfo(const char* infoStr, int x, int y, int isLarge);
void myMouse(int b, int s, int x, int y);
void myGridPaneMouse(int b, int s, int x, int y);
void myStatePaneMouse(int b, int s, int x, int y);
void myKeyboard(unsigned char c, int x, int y);
void myTimerFunc(int val);
void createtravelerColors(void);
void freetravelerColors(void);

//---------------------------------------------------------------------------
//  Interface constants
//---------------------------------------------------------------------------


#define SMALL_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_10
#define MEDIUM_DISPLAY_FONT   GLUT_BITMAP_HELVETICA_12
#define LARGE_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_18
const int SMALL_FONT_HEIGHT = 12;
const int LARGE_FONT_HEIGHT = 18;
const int TEXT_PADDING = 0;
const float TEXT_COLOR[4] = {1.f, 1.f, 1.f, 1.f};

const float WALL_COLOR[4] = {0.6f, 0.3f, 0.1f, 1.f};
const float PART_COLOR[4] = {0.6f, 0.6f, 0.6f, 1.f};
const float EXIT_COLOR[4] = {1.f, 1.f, 1.f, 1.f};

const int   INIT_WIN_X = 50,
            INIT_WIN_Y = 40;

//	Wow!  gcc on Linux is really dumb!  The code below doesn't even compile there.
//const int	GRID_PANE_WIDTH = 600,
//			GRID_PANE_HEIGHT = GRID_PANE_WIDTH,	//	--> claims GRID_PANE_WIDTH not constant!
//			STATE_PANE_WIDTH = 300,
//			STATE_PANE_HEIGHT = GRID_PANE_HEIGHT,
//			H_PADDING = 5,
//			WINDOW_WIDTH = GRID_PANE_WIDTH + STATE_PANE_WIDTH + H_PADDING,
//			WINDOW_HEIGHT = GRID_PANE_HEIGHT;
//	(sigh!)	This completely negates the point of using constants for this kind of setup.
//	No wonder most Linux apps look so bad
const int GRID_PANE_WIDTH = 900;
const int GRID_PANE_HEIGHT = 800;
const int STATE_PANE_WIDTH = 400;
const int STATE_PANE_HEIGHT = 800;
const int H_PADDING = 0;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;


//---------------------------------------------------------------------------
//  File-level global variables
//---------------------------------------------------------------------------

//	We use a window split into two panes/subwindows.  The subwindows
//	will be accessed by an index.
const int	GRID_PANE = 0,
			STATE_PANE = 1;
int	gMainWindow,
	gSubwindow[2];

GLfloat** travelerColor;

//---------------------------------------------------------------------------
#if 0
#pragma mark -
#pragma mark Drawing Functions
#endif
//---------------------------------------------------------------------------

void drawTraveler(const Traveler& traveler)
{
	//	Yes, I know that it's inefficient to recompute this each and every time,
	//	but gcc on Ubuntu doesn't let me define these as static [!??]
	const GLfloat	DH = (GRID_PANE_WIDTH - 2.f)/ numCols,
					DV = (GRID_PANE_HEIGHT - 2.f) / numRows;
	GLfloat segMove[4][2] = {
								{0, DV},	//	NORTH
								{DH, 0},	//	WEST
								{0, -DV},	//	SOUTH
								{-DH, 0}};	//	EAST

	glColor4fv(traveler.rgba);
	glPushMatrix();
	//	The first segment is different
	glTranslatef((traveler.segmentList[0].col + 0.5f)*DH,
				 (traveler.segmentList[0].row + 0.5f)*DV, 0.f);
	//	draw the "head"
	glPushMatrix();
	glScalef(0.2f, 0.2f, 1.f);
	glBegin(GL_POLYGON);
		glVertex2f(0, DV);
		glVertex2f(-DH, 0);
		glVertex2f(0, -DV);
		glVertex2f(DH, 0);
	glEnd();
	glPopMatrix();
	if (traveler.segmentList.size() > 1)
	{
		unsigned int currSegIndex;
		for (currSegIndex=0; currSegIndex<traveler.segmentList.size(); currSegIndex++)
		{
			//	draw a segment to the center of the next square
			glBegin(GL_LINES);
				glVertex2f(0, 0);
				glVertex2f(segMove[traveler.segmentList[currSegIndex].dir][0],
						   segMove[traveler.segmentList[currSegIndex].dir][1]);
			glEnd();
			
			//	and move to that point
			glTranslatef(segMove[traveler.segmentList[currSegIndex].dir][0],
						 segMove[traveler.segmentList[currSegIndex].dir][1],
						 0.f);

		}
	}
	else
	{
		//	draw the only segment
		glBegin(GL_LINES);
			glVertex2f(0, 0);
			glVertex2f(segMove[traveler.segmentList[0].dir][0]*0.3f,
					   segMove[traveler.segmentList[0].dir][1]*0.3f);
		glEnd();	}
	
	glPopMatrix();

}


//	This is the function that does the actual grid drawing
void drawGrid(void)
{
	const GLfloat	DH = (GRID_PANE_WIDTH - 2.f)/ numCols,
					DV = (GRID_PANE_HEIGHT - 2.f) / numRows;
	const GLfloat	PS = 0.3f, PE = 1.f - PS;

	//	draw the walls and partitions
	for (unsigned int i=0; i< numRows; i++)
	{
		for (unsigned int j=0; j< numCols; j++)
		{
			switch (grid[i][j])
			{
				case WALL:
					glColor4fv(WALL_COLOR);
					glBegin(GL_POLYGON);
						glVertex2f(j*DH, i*DV);
						glVertex2f((j+1)*DH, i*DV);
						glVertex2f((j+1)*DH, (i+1)*DV);
						glVertex2f(j*DH, (i+1)*DV);
					glEnd();
					break;
					
					
				case VERTICAL_PARTITION:
					glColor4fv(PART_COLOR);
					glBegin(GL_POLYGON);
						glVertex2f((j+PS)*DH, i*DV);
						glVertex2f((j+PE)*DH, i*DV);
						glVertex2f((j+PE)*DH, (i+1)*DV);
						glVertex2f((j+PS)*DH, (i+1)*DV);
					glEnd();
					break;
					
				case HORIZONTAL_PARTITION:
					glColor4fv(PART_COLOR);
					glBegin(GL_POLYGON);
						glVertex2f(j*DH, (i+PS)*DV);
						glVertex2f((j+1)*DH, (i+PS)*DV);
						glVertex2f((j+1)*DH, (i+PE)*DV);
						glVertex2f(j*DH, (i+PE)*DV);
					glEnd();
					break;
					
				case EXIT:
					glColor4fv(EXIT_COLOR);
					glBegin(GL_POLYGON);
						glVertex2f(j*DH, i*DV);
						glVertex2f((j+1)*DH, i*DV);
						glVertex2f((j+1)*DH, (i+1)*DV);
						glVertex2f(j*DH, (i+1)*DV);
					glEnd();
					glColor4f(0.f, 0.f, 0.f, 1.f);
					glBegin(GL_LINES);
						glVertex2f(j*DH, i*DV);
						glVertex2f((j+1)*DH, (i+1)*DV);
						glVertex2f((j+1)*DH, i*DV);
						glVertex2f(j*DH, (i+1)*DV);
					glEnd();
					break;
				
				default:
					//	nothing
					break;
			}
		}
	}
	
	//	Then draw a grid of lines on top of the squares
	glColor4f(0.5f, 0.5f, 0.5f, 1.f);
	glBegin(GL_LINES);
		//	Horizontal
		for (unsigned int i=0; i<= numRows+1; i++)
		{
			glVertex2f(1.f, 1.f + i*DV);
			glVertex2f(1.f + numCols*DH, 1.f + i*DV);
		}
		//	Vertical
		for (unsigned int j=0; j<= numCols+1; j++)
		{
			glVertex2f(1.f + j*DH, 1.f);
			glVertex2f(1.f + j*DH, 1.f + numRows*DV);
		}
	glEnd();
	
}



void displayTextualInfo(const char* infoStr, int xPos, int yPos, int fontSize)
{
    //-----------------------------------------------
    //  0.  get current material properties
    //-----------------------------------------------
    float oldAmb[4], oldDif[4], oldSpec[4], oldShiny;
    glGetMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
    glGetMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, &oldShiny);

    glPushMatrix();

    //-----------------------------------------------
    //  1.  Build the string to display <-- parameter
    //-----------------------------------------------
    int infoLn = (int) strlen(infoStr);

    //-----------------------------------------------
    //  2.  Determine the string's length (in pixels)
    //-----------------------------------------------
    int textWidth = 0;
	switch(fontSize)
	{
		case 0:
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
			}
			break;

		case 1:
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
			}
			break;

		case 2:
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
			}
			break;

		default:
			break;
	}

	//  add a few pixels of padding
    textWidth += 2*TEXT_PADDING;

    //-----------------------------------------------
    //  4.  Draw the string
    //-----------------------------------------------
    glColor4fv(TEXT_COLOR);
    int x = xPos;
	switch(fontSize)
	{
		case 0:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(SMALL_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
			}
			break;

		case 1:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(MEDIUM_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
			}
			break;

		case 2:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(LARGE_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
			}
			break;

		default:
			break;
	}


    //-----------------------------------------------
    //  5.  Restore old material properties
    //-----------------------------------------------
	glMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, oldShiny);

    //-----------------------------------------------
    //  6.  Restore reference frame
    //-----------------------------------------------
    glPopMatrix();
}



void drawMessages(int numMessages, char** message)
{
	//	I compute once the dimensions for all the rendering of my state info
	//	One other place to rant about that desperately lame gcc compiler.  It's
	//	positively disgusting that the code below is rejected.
	int LEFT_MARGIN = STATE_PANE_WIDTH / 12;
	int V_PAD = STATE_PANE_HEIGHT / 12;

	for (int k=0; k<numMessages; k++)
	{
		displayTextualInfo(message[k], LEFT_MARGIN, 3*STATE_PANE_HEIGHT/4 - k*V_PAD, 1);
	}

	//	display info about number of live threads
	char infoStr[256];
	sprintf(infoStr, "Live Threads: %d", numLiveThreads);
	displayTextualInfo(infoStr, LEFT_MARGIN, 7*STATE_PANE_HEIGHT/8, 2);
}

//---------------------------------------------------------------------------
#if 0
#pragma mark -
#pragma mark Callback Functions
#endif
//---------------------------------------------------------------------------

//	This callback function is called when the window is resized
//	(generally by the user of the application).
//	It is also called when the window is created, why I placed there the
//	code to set up the virtual camera for this application.
//
void myResize(int w, int h)
{
	if ((w != WINDOW_WIDTH) || (h != WINDOW_HEIGHT))
	{
		glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	else
	{
		glutPostRedisplay();
	}
}

void displayGridPane(void)
{
	//	This is OpenGL/glut magic.  Don't touch
	glutSetWindow(gSubwindow[GRID_PANE]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, GRID_PANE_HEIGHT, 0);
	glScalef(1.f, -1.f, 1.f);
	
	drawTravelers();
	
	drawGrid();

	//	This is OpenGL/glut magic.  Don't touch
	glutSwapBuffers();
	
	glutSetWindow(gMainWindow);
}

void displayStatePane(void)
{
	//	This is OpenGL/glut magic.  Don't touch
	glutSetWindow(gSubwindow[STATE_PANE]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateMessages();
	
	//	This is OpenGL/glut magic.  Don't touch
	glutSwapBuffers();
	
	glutSetWindow(gMainWindow);
}

void myDisplay(void)
{
    glutSetWindow(gMainWindow);

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

	displayGridPane();
	displayStatePane();

    glutSetWindow(gMainWindow);
}

//	This function is called when a mouse event occurs just in the tiny
//	space between the two subwindows.
//
void myMouse(int button, int state, int x, int y)
{
	glutSetWindow(gMainWindow);
	glutPostRedisplay();
}

//	This function is called when a mouse event occurs in the grid pane
//
void myGridPaneMouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				//	do something
			}
			else if (state == GLUT_UP)
			{
				//	exit(0);
			}
			break;

		default:
			break;
	}

	glutSetWindow(gMainWindow);
	glutPostRedisplay();
}

//	This function is called when a mouse event occurs in the state pane
void myStatePaneMouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				//	do something
			}
			else if (state == GLUT_UP)
			{
				//	exit(0);
			}
			break;

		default:
			break;
	}

	glutSetWindow(gMainWindow);
	glutPostRedisplay();
}


//	This callback function is called when a keyboard event occurs
//
void myKeyboard(unsigned char c, int x, int y)
{
	handleKeyboardEvent(c, x, y);
	glutSetWindow(gMainWindow);
	glutPostRedisplay();
}



void myTimerFunc(int value)
{
	//	value not used.  Warning suppression
	(void) value;

	glutTimerFunc(25, myTimerFunc, 0);

    myDisplay();
}

//---------------------------------------------------------------------------
#if 0
#pragma mark -
#pragma mark Initialization Functions
#endif
//---------------------------------------------------------------------------


void initializeFrontEnd(int argc, char** argv)
{
	//	shutting off warning
	(void) SMALL_FONT_HEIGHT;
	(void) LARGE_FONT_HEIGHT;
	
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	gMainWindow = glutCreateWindow("Partitioned Travelers -- CSC 412 - Spring 2019");
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	//	set up the callbacks for the main window
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myResize);
	glutMouseFunc(myMouse);
    glutTimerFunc(25, myTimerFunc, 0);

	//	create the two panes as glut subwindows
	gSubwindow[GRID_PANE] = glutCreateSubWindow(gMainWindow,
												0, 0,							//	origin
												GRID_PANE_WIDTH, GRID_PANE_HEIGHT);
    glViewport(0, 0, GRID_PANE_WIDTH, GRID_PANE_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0.0f, GRID_PANE_WIDTH, 0.0f, GRID_PANE_HEIGHT, -1, 1);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myGridPaneMouse);
	glutDisplayFunc(displayGridPane);


	glutSetWindow(gMainWindow);
	gSubwindow[STATE_PANE] = glutCreateSubWindow(gMainWindow,
												GRID_PANE_WIDTH + H_PADDING, 0,	//	origin
												STATE_PANE_WIDTH, STATE_PANE_HEIGHT);
    glViewport(0, 0, STATE_PANE_WIDTH, STATE_PANE_WIDTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0.0f, STATE_PANE_WIDTH, 0.0f, STATE_PANE_HEIGHT, -1, 1);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myGridPaneMouse);
	glutDisplayFunc(displayStatePane);
}

float** createTravelerColors(unsigned int numTravelers)
{
	float** travelerColor = new float*[numTravelers];

	float hueStep = 360.f / numTravelers;

	for (unsigned int k=0; k<numTravelers; k++)
	{
		travelerColor[k] = new float[4];

		//	compute a hue for the door
		float hue = k*hueStep;
		//	convert the hue to an RGB color
		int hueRegion = (int) (hue / 60);
		switch (hueRegion)
		{
				//  hue in [0, 60] -- red-green, dominant red
			case 0:
				travelerColor[k][0] = 1.f;					//  red is max
				travelerColor[k][1] = hue / 60.f;			//  green calculated
				travelerColor[k][2] = 0.f;					//  blue is zero
				break;

				//  hue in [60, 120] -- red-green, dominant green
			case 1:
				travelerColor[k][0] = (120.f - hue) / 60.f;	//  red is calculated
				travelerColor[k][1] = 1.f;					//  green max
				travelerColor[k][2] = 0.f;					//  blue is zero
				break;

				//  hue in [120, 180] -- green-blue, dominant green
			case 2:
				travelerColor[k][0] = 0.f;					//  red is zero
				travelerColor[k][1] = 1.f;					//  green max
				travelerColor[k][2] = (hue - 120.f) / 60.f;	//  blue is calculated
				break;

				//  hue in [180, 240] -- green-blue, dominant blue
			case 3:
				travelerColor[k][0] = 0.f;					//  red is zero
				travelerColor[k][1] = (240.f - hue) / 60;	//  green calculated
				travelerColor[k][2] = 1.f;					//  blue is max
				break;

				//  hue in [240, 300] -- blue-red, dominant blue
			case 4:
				travelerColor[k][0] = (hue - 240.f) / 60;	//  red is calculated
				travelerColor[k][1] = 0;						//  green is zero
				travelerColor[k][2] = 1.f;					//  blue is max
				break;

				//  hue in [300, 360] -- blue-red, dominant red
			case 5:
				travelerColor[k][0] = 1.f;					//  red is max
				travelerColor[k][1] = 0;						//  green is zero
				travelerColor[k][2] = (360.f - hue) / 60;	//  blue is calculated
				break;

			default:
				break;

		}
		travelerColor[k][3] = 1.f;					//  alpha --> full opacity
	}

	return travelerColor;
}
