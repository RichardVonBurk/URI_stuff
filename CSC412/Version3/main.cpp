//main.c
//  Final Project CSC412
//
//  Created by Jean-Yves Hervé on 2018-12-05
//	This is public domain code.  By all means appropriate it and change is to your
//	heart's content.
#include <iostream>
#include <sstream>
#include <string>
//
#include <cstdio>
#include <cstdlib>
#include <ctime>
//
#include "gl_frontEnd.h"
#include <pthread.h>
#include <unistd.h>

using namespace std;

//

//==================================================================================
//	Function prototypes
//==================================================================================
void initializeApplication(void);
GridPosition getNewFreePosition(void);
Direction newDirection(Direction forbiddenDir);
TravelerSegment newTravelerSeg(const TravelerSegment& currentSeg, bool& canAdd);
void generateWalls(void);
void generatePartitions(void);
void* updateTraveler(void*);
void updateSegments(Traveler** travelerDoublePtr);

//==================================================================================
//	Application-level global variables
//==================================================================================

//	Don't rename any of these variables
//-------------------------------------
//	The state grid and its dimensions (arguments to the program)
SquareType** grid;
int unsigned numRows = 0;	//	height of the grid
int unsigned numCols = 0;	//	width
unsigned int numTravelers = 0;	//	initial number
unsigned int numTravelersDone = 0;
unsigned int numLiveThreads = 0;		//	the number of live traveler threads
vector<Traveler> travelerList;	//list of travelers
vector<SlidingPartition> partitionList;
GridPosition	exitPos;	//	location of the exit

pthread_mutex_t masterlock; //Version3 has one lock, hence masterlock, which can only be accessed one at a time

//	you get the opposite directions from dir as (NUM_DIRECTIONS - dir)
//	you get left turn from dir as (dir + 1) % NUM_DIRECTIONS
extern const int NUM_DIRECTIONS = 4;

//	robot sleep time between moves (in microseconds)
const int MIN_SLEEP_TIME = 1000;
int travelerSleepTime = 100000;

//	An array of C-string where you can store things you want displayed
//	in the state pane to display (for debugging purposes?)
//	Dont change the dimensions as this may break the front end
const int MAX_NUM_MESSAGES = 8;
const int MAX_LENGTH_MESSAGE = 32;
char** message;
time_t launchTime;


//==================================================================================
//	These are the functions that tie the simulation with the rendering.
//	Some parts are "don't touch."  Other parts need your intervention
//	to make sure that access to critical section is properly synchronized
//==================================================================================

void drawTravelers(void)
{
	//-----------------------------
	//	You may have to sychronize things here
	//-----------------------------
	for (unsigned int k=0; k<travelerList.size(); k++)
	{
		//	here I would test if the traveler thread is still live
		drawTraveler(travelerList[k]);
	}
}

//deletes traveler one segment at a time starting from the rear
void progressively_delete_traveler(Traveler* travelerPtr)
{
	//erase the head on the EXIT Square
	travelerPtr->segmentList.erase(travelerPtr->segmentList.begin());
	//start erasing the tail
	while(!travelerPtr->segmentList.empty())
	{
		//make segment location on grid a FREE Square
		grid[ travelerPtr->segmentList[travelerPtr->segmentList.size()-1].row ][ travelerPtr->segmentList[travelerPtr->segmentList.size()-1].col ] = FREE_SQUARE;
		//remove segment
		travelerPtr->segmentList.pop_back();
		usleep(travelerSleepTime);
	}
	//traveler is basically dead so we will 'kill' the thread
	numLiveThreads--;
}

//function gets ptr from pthread_create (main) which references a given traveler
//concept: it checks the Direction value of Traveler's segment[0] and moves in that direction
//if it can't it tries to change direction
void* updateTraveler(void* voidPtr)
{
	//boolean for the pthread while loop
	bool keepGoing = true;
	Traveler* travelerPtr = (Traveler*)(voidPtr);

	//whileloop for pthread to constantly move traveler
	while (keepGoing==true)
	{
		//lock the masterlock
		//can be unlocked at end of loop of if EXIT is next square
		pthread_mutex_lock(&masterlock);


		//20% chance traveler will psuedo-randomly change directions
		//makes movement more interesting than just something moving in straight lines
		if( (rand()%6) == 5)
		{
			travelerPtr->segmentList[0].dir = newDirection(travelerPtr->segmentList[0].dir);
		}
		
		//get traveler's head's direction
		//direction determines which tile the traveler will try to move to
		switch (travelerPtr->segmentList[0].dir)
		{
			case NORTH:
				//if edge of grid
				if (travelerPtr->segmentList[0].row == numRows-1)
				{
					travelerPtr->segmentList[0].dir = newDirection(NORTH);
				}
				//if EXIT Square
				else if (grid[travelerPtr->segmentList[0].row+1][travelerPtr->segmentList[0].col] == EXIT)
				{
					updateSegments(&travelerPtr);
					progressively_delete_traveler(travelerPtr);
					numTravelersDone++;
					keepGoing = false;
					pthread_mutex_unlock(&masterlock);			
					pthread_exit(NULL);
				}
				//else if FREE Square
				else if (	travelerPtr->segmentList[0].row < numRows-1 &&
						grid[travelerPtr->segmentList[0].row+1][travelerPtr->segmentList[0].col] == FREE_SQUARE)
				{
					grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col] = FREE_SQUARE;
					grid[travelerPtr->segmentList[0].row+1][travelerPtr->segmentList[0].col] = TRAVELER;
					travelerPtr->segmentList[0].row+=1;
					updateSegments(&travelerPtr);
				}
				//	change to new direction
				else
				{
					travelerPtr->segmentList[0].dir = newDirection(NORTH);
				}

			case SOUTH:
				//if edge of grid
				if (travelerPtr->segmentList[0].row == 0)
				{
					travelerPtr->segmentList[0].dir = newDirection(SOUTH);
				}
				//if EXIT Square
				else if (grid[travelerPtr->segmentList[0].row-1][travelerPtr->segmentList[0].col] == EXIT)
				{
					updateSegments(&travelerPtr);
					progressively_delete_traveler(travelerPtr);
					numTravelersDone++;	
					keepGoing = false;
					pthread_mutex_unlock(&masterlock);
					pthread_exit(NULL);
				}
				//else if FREE Square
				else if (	travelerPtr->segmentList[0].row > 0 &&
						grid[travelerPtr->segmentList[0].row-1][travelerPtr->segmentList[0].col] == FREE_SQUARE)
				{
					grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col] = FREE_SQUARE;
					grid[travelerPtr->segmentList[0].row-1][travelerPtr->segmentList[0].col] = TRAVELER;
					travelerPtr->segmentList[0].row-=1;
					updateSegments(&travelerPtr);
				}

			//	change to new direction
				else
				{
					travelerPtr->segmentList[0].dir = newDirection(SOUTH);
				}

			case WEST:
				//if edge of grid
				if (travelerPtr->segmentList[0].col == numCols-1)
				{
					travelerPtr->segmentList[0].dir = newDirection(WEST);
				}
				//if EXIT Square
				else if (grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col+1] == EXIT)
				{
					updateSegments(&travelerPtr);
					progressively_delete_traveler(travelerPtr);
					numTravelersDone++;
					keepGoing = false;
					pthread_mutex_unlock(&masterlock);
					pthread_exit(NULL);
				}
				//else if FREE Square
				else if (	travelerPtr->segmentList[0].col < numCols-1 &&
						grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col+1] == FREE_SQUARE)
				{
					grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col] = FREE_SQUARE;
					grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col+1] = TRAVELER;
					travelerPtr->segmentList[0].col+=1;
					updateSegments(&travelerPtr);
				}				
				//	change to new direction
				else
				{
					travelerPtr->segmentList[0].dir = newDirection(WEST);
				}

			case EAST:
				//if edge of grid
				if (travelerPtr->segmentList[0].col == 0)
				{
					travelerPtr->segmentList[0].dir = newDirection(EAST);
				}
				//if EXIT Square
				else if (grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col-1] == EXIT)
				{
					updateSegments(&travelerPtr);
					progressively_delete_traveler(travelerPtr);
					numTravelersDone++;
					keepGoing = false;
					pthread_mutex_unlock(&masterlock);
					pthread_exit(NULL);
				}
				//else if FREE Square
				else if (	travelerPtr->segmentList[0].col > 0 &&
						grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col-1] == FREE_SQUARE)
				{
					grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col] = FREE_SQUARE;
					grid[travelerPtr->segmentList[0].row][travelerPtr->segmentList[0].col-1] = TRAVELER;
					travelerPtr->segmentList[0].col-=1;
					
					updateSegments(&travelerPtr);
				}
				//	change to new direction
				else
				{
					travelerPtr->segmentList[0].dir = newDirection(EAST);
				}

			
		//we use the masterlock here because this is where the travelers access the grid to move
		//unlock masterlock once the pthread completes one loop
		pthread_mutex_unlock(&masterlock);
		}
	//wait a fraction of a sec so user can actually see the movement
	usleep(travelerSleepTime);
	}
	return voidPtr;
}

//updates position of traveler tail starting from the last segment and goes up until right behind the head
//only gets called when head moves in updateTraveler
void updateSegments(Traveler** travelerDoublePtr)
{
	Traveler* travelerPtr = *(travelerDoublePtr);
	for(unsigned int i=travelerPtr->segmentList.size()-1; i>1; i--)
	{
		//store current segments into variable for easier reading/understanding
		TravelerSegment preceedingSeg = travelerPtr->segmentList[i-1];
		TravelerSegment currentSeg = travelerPtr->segmentList[i];

		//if segment is the end of tail make square a free square
		if(i==travelerPtr->segmentList.size()-1)
		{
			grid[currentSeg.row][currentSeg.col] = FREE_SQUARE;
		}
		//move prev to current and copy prev's dir
		//update grid value
		currentSeg.row = preceedingSeg.row;
		currentSeg.col = preceedingSeg.col;
		currentSeg.dir = preceedingSeg.dir;
		grid[currentSeg.row][currentSeg.col] = TRAVELER;
	}
}



void updateMessages(void)
{
	//	Here I hard-code a few messages that I want to see displayed
	//	in my state pane.  The number of live robot threads will
	//	always get displayed.  No need to pass a message about it.
	unsigned int numMessages = 4;
	sprintf(message[0], "We created %d travelers", numTravelers);
	sprintf(message[1], "%d travelers solved the maze", numTravelersDone);
	sprintf(message[2], "I like cheese");
	sprintf(message[3], "Simulation run time is %ld", time(NULL)-launchTime);

	//---------------------------------------------------------
	//	This is the call that makes OpenGL render information
	//	about the state of the simulation.
	//
	//	You *must* synchronize this call.
	//
	//---------------------------------------------------------
	drawMessages(numMessages, message);
}


void handleKeyboardEvent(unsigned char c, int x, int y)
{
	int ok = 0;

	switch (c)
	{
		//	'esc' to quit
		case 27:
			exit(0);
			break;

		//	slowdown
		case ',':
			slowdownTravelers();
			ok = 1;
			break;

		//	speedup
		case '.':
			speedupTravelers();
			ok = 1;
			break;

		//North
		case 'w':
			break;

		//West
		case 'a':
			break;

		//South
		case 's':
			break;
			
		//East
		case 'd':
			break;

		default:
			ok = 1;
			break;
	}
	if (!ok)
	{
		//	do something?
	}
}


//------------------------------------------------------------------------
//	You shouldn't have to touch this one.  Definitely if you don't
//	add the "producer" threads, and probably not even if you do.
//------------------------------------------------------------------------
void speedupTravelers(void)
{
	//	decrease sleep time by 20%, but don't get too small
	int newSleepTime = (8 * travelerSleepTime) / 10;
	
	if (newSleepTime > MIN_SLEEP_TIME)
	{
		travelerSleepTime = newSleepTime;
	}
}

void slowdownTravelers(void)
{
	//	increase sleep time by 20%
	travelerSleepTime = (12 * travelerSleepTime) / 10;
}




//------------------------------------------------------------------------
//	You shouldn't have to change anything in the main function besides
//	initialization of the various global variables and lists
//------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//	We know that the arguments  of the program  are going
	//	to be the width (number of columns) and height (number of rows) of the
	//	grid, the number of travelers, etc.
	//	So far, I hard code-some values

	numRows = 45;
	numCols = 40;
	
	numTravelers = 10;	//version1 only has 1 traveler so no point in having input for that
	numLiveThreads = 0;
	numTravelersDone = 0;

	//	Even though we extracted the relevant information from the argument
	//	list, I still need to pass argc and argv to the front-end init
	//	function because that function passes them to glutInit, the required call
	//	to the initialization of the glut library.
	initializeFrontEnd(argc, argv);

	//	Now we can do application-level initialization
	initializeApplication();

	launchTime = time(NULL);

	//	Now we enter the main loop of the program and to a large extend
	//	"lose control" over its execution.  The callback functions that 
	//	we set up earlier will be called when the corresponding event
	//	occurs

	for(unsigned int i=0; i<travelerList.size(); i++)
	{
		pthread_create(&(travelerList[i].thread_id), NULL, updateTraveler, &(travelerList[i]));
		numLiveThreads++;		
	}

	glutMainLoop();

	for(unsigned int i=0; i<travelerList.size(); i++)
	{
		pthread_join(travelerList[i].thread_id, NULL);		
	}
	
	//	Free allocated resource before leaving (not absolutely needed, but
	//	just nicer.  Also, if you crash there, you know something is wrong
	//	in your code.
	for (unsigned int i=0; i< numRows; i++)
		free(grid[i]);
	free(grid);
	for (int k=0; k<MAX_NUM_MESSAGES; k++)
		free(message[k]);
	free(message);
	
	//	This will probably never be executed (the exit point will be in one of the
	//	call back functions).
	return 0;
}


//==================================================================================
//
//	This is a function that you have to edit and add to.
//
//==================================================================================


void initializeApplication(void)
{
	//	Allocate the grid
	grid = new SquareType*[numRows];
	for (unsigned int i=0; i<numRows; i++)
	{
		grid[i] = new SquareType[numCols];
		for (unsigned int j=0; j< numCols; j++)
			grid[i][j] = FREE_SQUARE;
		
	}

	message = (char**) malloc(MAX_NUM_MESSAGES*sizeof(char*));
	for (unsigned int k=0; k<MAX_NUM_MESSAGES; k++)
		message[k] = (char*) malloc((MAX_LENGTH_MESSAGE+1)*sizeof(char));
		
	//---------------------------------------------------------------
	//	All the code below to be replaced/removed
	//	I initialize the grid's pixels to have something to look at
	//---------------------------------------------------------------
	//	Yes, I am using the C random generator after ranting in class that the C random
	//	generator was junk.  Here I am not using it to produce "serious" data (as in a
	//	real simulation), only wall/partition location and some color
	srand((unsigned int) time(NULL));

	//	generate a random exit
	exitPos = getNewFreePosition();
	grid[exitPos.row][exitPos.col] = EXIT;

	//	Generate walls and partitions
	generateWalls();
	generatePartitions();
	
	//	Initialize traveler info structs
	//	You will probably need to replace/complete this as you add thread-related data
	float** travelerColor = createTravelerColors(numTravelers);
	for (unsigned int k=0; k<numTravelers; k++) 
	{
		GridPosition pos = getNewFreePosition();
		Direction dir = static_cast<Direction>(rand() % NUM_DIRECTIONS);
		TravelerSegment seg = {pos.row, pos.col, dir};
		

		Traveler traveler;
		traveler.index = k;

		traveler.segmentList.push_back(seg);

		//	I add 0-6 segments to my travelers
		unsigned int numAddSegments = rand() % 7;
		TravelerSegment currSeg = traveler.segmentList[0];
		bool canAddSegment = true;
		for (unsigned int s=0; s<numAddSegments && canAddSegment; s++)
		{
			TravelerSegment newSeg = newTravelerSeg(currSeg, canAddSegment);
			if (canAddSegment)
			{
				traveler.segmentList.push_back(newSeg);
				currSeg = newSeg;
			}
		}
		
		for (unsigned int c=0; c<4; c++)
		{
			traveler.rgba[c] = travelerColor[k][c];
		}

		travelerList.push_back(traveler);
	}

	//	free array of colors
	for (unsigned int k=0; k<numTravelers; k++)
		delete []travelerColor[k];
	delete []travelerColor;
}


//------------------------------------------------------
#if 0
#pragma mark -
#pragma mark Generation Helper Functions
#endif
//------------------------------------------------------

GridPosition getNewFreePosition(void)
{
	GridPosition pos;

	bool noGoodPos = true;
	while (noGoodPos)
	{
		unsigned int row = rand() % numRows;
		unsigned int col = rand() % numCols;
		if (grid[row][col] == FREE_SQUARE)
		{
			pos.row = row;
			pos.col = col;
			noGoodPos = false;
		}
	}
	return pos;
}

Direction newDirection(Direction forbiddenDir)
{
	bool noDir = true;

	Direction dir = static_cast<Direction>(rand() % NUM_DIRECTIONS);
	while (noDir)
	{
		dir = static_cast<Direction>(rand() % NUM_DIRECTIONS);
		noDir = (dir==forbiddenDir);
	}
	return dir;
}


TravelerSegment newTravelerSeg(const TravelerSegment& currentSeg, bool& canAdd)
{
	TravelerSegment newSeg;
	switch (currentSeg.dir)
	{
		case NORTH:
			if (	currentSeg.row < numRows-1 &&
					grid[currentSeg.row+1][currentSeg.col] == FREE_SQUARE)
			{
				newSeg.row = currentSeg.row+1;
				newSeg.col = currentSeg.col;
				newSeg.dir = newDirection(SOUTH);
				grid[newSeg.row][newSeg.col] = TRAVELER;
				canAdd = true;
			}
			//	no more segment
			else
				canAdd = false;
			break;

		case SOUTH:
			if (	currentSeg.row > 0 &&
					grid[currentSeg.row-1][currentSeg.col] == FREE_SQUARE)
			{
				newSeg.row = currentSeg.row-1;
				newSeg.col = currentSeg.col;
				newSeg.dir = newDirection(NORTH);
				grid[newSeg.row][newSeg.col] = TRAVELER;
				canAdd = true;
			}
			//	no more segment
			else
				canAdd = false;
			break;

		case WEST:
			if (	currentSeg.col < numCols-1 &&
					grid[currentSeg.row][currentSeg.col+1] == FREE_SQUARE)
			{
				newSeg.row = currentSeg.row;
				newSeg.col = currentSeg.col+1;
				newSeg.dir = newDirection(EAST);
				grid[newSeg.row][newSeg.col] = TRAVELER;
				canAdd = true;
			}
			//	no more segment
			else
				canAdd = false;
			break;

		case EAST:
			if (	currentSeg.col > 0 &&
					grid[currentSeg.row][currentSeg.col-1] == FREE_SQUARE)
			{
				newSeg.row = currentSeg.row;
				newSeg.col = currentSeg.col-1;
				newSeg.dir = newDirection(WEST);
				grid[newSeg.row][newSeg.col] = TRAVELER;
				canAdd = true;
			}
			//	no more segment
			else
				canAdd = false;
			break;
		
		default:
			canAdd = false;
	}
	
	return newSeg;
}

void generateWalls(void)
{
	const unsigned int NUM_WALLS = (numCols+numRows)/4;

	//	I decide that a wall length  cannot be less than 3  and not more than
	//	1/4 the grid dimension in its orientation
	const unsigned int MIN_WALL_LENGTH = 3;
	const unsigned int MAX_HORIZ_WALL_LENGTH = numCols / 3;
	const unsigned int MAX_VERT_WALL_LENGTH = numRows / 3;
	const unsigned int MAX_NUM_TRIES = 20;

	bool goodWall = true;
	
	//	Generate the vertical walls
	for (unsigned int w=0; w< NUM_WALLS; w++)
	{
		goodWall = false;
		
		//	Case of a vertical wall
		if (rand() %2)
		{
			//	I try a few times before giving up
			for (unsigned int k=0; k<MAX_NUM_TRIES && !goodWall; k++)
			{
				//	let's be hopeful
				goodWall = true;
				
				//	select a column index
				unsigned int HSP = numCols/(NUM_WALLS/2+1);
				unsigned int col = (1+ rand()%(NUM_WALLS/2-1))*HSP;
				unsigned int length = MIN_WALL_LENGTH + rand()%(MAX_VERT_WALL_LENGTH-MIN_WALL_LENGTH+1);
				
				//	now a random start row
				unsigned int startRow = rand()%(numRows-length);
				for (unsigned int row=startRow, i=0; i<length && goodWall; i++, row++)
				{
					if (grid[row][col] != FREE_SQUARE)
						goodWall = false;
				}
				
				//	if the wall first, add it to the grid
				if (goodWall)
				{
					for (unsigned int row=startRow, i=0; i<length && goodWall; i++, row++)
					{
						grid[row][col] = WALL;
					}
				}
			}
		}
		// case of a horizontal wall
		else
		{
			goodWall = false;
			
			//	I try a few times before giving up
			for (unsigned int k=0; k<MAX_NUM_TRIES && !goodWall; k++)
			{
				//	let's be hopeful
				goodWall = true;
				
				//	select a column index
				unsigned int VSP = numRows/(NUM_WALLS/2+1);
				unsigned int row = (1+ rand()%(NUM_WALLS/2-1))*VSP;
				unsigned int length = MIN_WALL_LENGTH + rand()%(MAX_HORIZ_WALL_LENGTH-MIN_WALL_LENGTH+1);
				
				//	now a random start row
				unsigned int startCol = rand()%(numCols-length);
				for (unsigned int col=startCol, i=0; i<length && goodWall; i++, col++)
				{
					if (grid[row][col] != FREE_SQUARE)
						goodWall = false;
				}
				
				//	if the wall first, add it to the grid
				if (goodWall)
				{
					for (unsigned int col=startCol, i=0; i<length && goodWall; i++, col++)
					{
						grid[row][col] = WALL;
					}
				}
			}
		}
	}
}


void generatePartitions(void)
{
	const unsigned int NUM_PARTS = (numCols+numRows)/4;

	//	I decide that a partition length  cannot be less than 3  and not more than
	//	1/4 the grid dimension in its orientation
	const unsigned int MIN_PART_LENGTH = 3;
	const unsigned int MAX_HORIZ_PART_LENGTH = numCols / 3;
	const unsigned int MAX_VERT_PART_LENGTH = numRows / 3;
	const unsigned int MAX_NUM_TRIES = 20;

	bool goodPart = true;

	for (unsigned int w=0; w< NUM_PARTS; w++)
	{
		goodPart = false;
		
		//	Case of a vertical partition
		if (rand() %2)
		{
			//	I try a few times before giving up
			for (unsigned int k=0; k<MAX_NUM_TRIES && !goodPart; k++)
			{
				//	let's be hopeful
				goodPart = true;
				
				//	select a column index
				unsigned int HSP = numCols/(NUM_PARTS/2+1);
				unsigned int col = (1+ rand()%(NUM_PARTS/2-2))*HSP + HSP/2;
				unsigned int length = MIN_PART_LENGTH + rand()%(MAX_VERT_PART_LENGTH-MIN_PART_LENGTH+1);
				
				//	now a random start row
				unsigned int startRow = rand()%(numRows-length);
				for (unsigned int row=startRow, i=0; i<length && goodPart; i++, row++)
				{
					if (grid[row][col] != FREE_SQUARE)
						goodPart = false;
				}
				
				//	if the partition is possible,
				if (goodPart)
				{
					//	add it to the grid and to the partition list
					SlidingPartition part;
					part.isVertical = true;
					for (unsigned int row=startRow, i=0; i<length && goodPart; i++, row++)
					{
						grid[row][col] = VERTICAL_PARTITION;
						GridPosition pos = {row, col};
						part.blockList.push_back(pos);
					}
				}
			}
		}
		// case of a horizontal partition
		else
		{
			goodPart = false;
			
			//	I try a few times before giving up
			for (unsigned int k=0; k<MAX_NUM_TRIES && !goodPart; k++)
			{
				//	let's be hopeful
				goodPart = true;
				
				//	select a column index
				unsigned int VSP = numRows/(NUM_PARTS/2+1);
				unsigned int row = (1+ rand()%(NUM_PARTS/2-2))*VSP + VSP/2;
				unsigned int length = MIN_PART_LENGTH + rand()%(MAX_HORIZ_PART_LENGTH-MIN_PART_LENGTH+1);
				
				//	now a random start row
				unsigned int startCol = rand()%(numCols-length);
				for (unsigned int col=startCol, i=0; i<length && goodPart; i++, col++)
				{
					if (grid[row][col] != FREE_SQUARE)
						goodPart = false;
				}
				
				//	if the wall first, add it to the grid and build SlidingPartition object
				if (goodPart)
				{
					SlidingPartition part;
					part.isVertical = false;
					for (unsigned int col=startCol, i=0; i<length && goodPart; i++, col++)
					{
						grid[row][col] = HORIZONTAL_PARTITION;
						GridPosition pos = {row, col};
						part.blockList.push_back(pos);
					}
				}
			}
		}
	}
}

