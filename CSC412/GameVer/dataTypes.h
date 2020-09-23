//
//  dataTypes.h
//  Final
//
//  Created by Jean-Yves Hervé on 2019-05-01.

#ifndef DATAS_TYPES_H
#define DATAS_TYPES_H
#include <pthread.h>
#include <vector>

//	Travel direction data type
//	Note that if you define a variable
//	Direction dir = whatever;
typedef enum Direction {
							NORTH = 0,
							WEST,
							SOUTH,
							EAST,
							//
} Direction;


//	Grid square types for this simulation
typedef enum SquareType {
							FREE_SQUARE,
							EXIT,
							WALL,
							VERTICAL_PARTITION,
							HORIZONTAL_PARTITION,
							TRAVELER,
							//
							NUM_SQUARE_TYPES
} SquareType;


//	Data type to store the position of things on the grid
typedef struct GridPosition {
								unsigned int row;
								unsigned int col;
} GridPosition;

//	Data type to store the position and orientation of a traveler's segment
typedef struct TravelerSegment {
								unsigned int row;
								unsigned int col;
								Direction dir;
} TravelerSegment;


//	Data type for storing all information about a traveler
//	Feel free to add anything you need.
typedef struct Traveler {
	unsigned int index;
	float rgba[4];
	std::vector<TravelerSegment> segmentList;
	pthread_t thread_id;
	bool isControlled = false;
} Traveler;


//	Data type to represent a sliding partition
typedef struct SlidingPartition {
	bool isVertical;
	//	The blocks making up the partition, listed
	//		top-to-bottom for a vertical list
	//		left-to-right for a horizontal list
	std::vector<GridPosition> blockList;

} SlidingPartition;

#endif //	DATAS_TYPES_H
