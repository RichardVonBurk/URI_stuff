//
//  gl_frontEnd.h
//  GL threads
//
//  Created by Jean-Yves Hervé on 2018-12-08
//

#ifndef GL_FRONT_END_H
#define GL_FRONT_END_H

#include "dataTypes.h"

//------------------------------------------------------------------------------
//	Find out whether we are on Linux or macOS (sorry, Windows people)
//	and load the OpenGL & glut headers.
//	For the macOS, lets us choose which glut to use
//------------------------------------------------------------------------------
#if (defined(__dest_os) && (__dest_os == __mac_os )) || \
	defined(__APPLE_CPP__) || defined(__APPLE_CC__)
	//	Either use the Apple-provided---but deprecated---glut
	//	or the third-party freeglut install
	#if 0
		#include <GLUT/GLUT.h>
	#else
		#include <GL/freeglut.h>
		#include <GL/gl.h>
	#endif
#elif defined(linux)
	#include <GL/glut.h>
#else
	#error unknown OS
#endif


//-----------------------------------------------------------------------------
//	Function prototypes
//-----------------------------------------------------------------------------

//	I don't want to impose how you store the information about your robots,
//	boxes and doors, so the two functions below will have to be called once for
//	each pair robot/box and once for each door.

//	This draws a colored multi-segment traveler
void drawTraveler(const Traveler& traveler);

//	This function assigns a color to the door based on its number
void drawDoor(int doorNumber, int doorRow, int doorCol);

//	Defined in main.c
void speedupTravelers(void);
void slowdownTravelers(void);
void drawTravelers(void);
void updateMessages(void);


void drawGrid(void);
void drawMessages(int numMessages, char** message);
void handleKeyboardEvent(unsigned char c, int x, int y);

void initializeFrontEnd(int argc, char** argv);
float** createTravelerColors(unsigned int numTravelers);

#endif // GL_FRONT_END_H

