// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 wall.h v1.0

#ifndef _WALL_H                 // Prevent multiple definitions if this 
#define _WALL_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace WallNS
{

	//jack - brought most of these forward from constants.h
	//old naming convention kept the same for compatability 

	const float MASS = 1.0e14f;
	const int   TEXTURE_COLS = 2; // texture has 2 columns
	
	
}

// inherits from Entity class
class Wall : public Entity
{
public:
	// constructor
	
	int WIDTH=getWidth();                   // image width
	int HEIGHT=getHeight();                  // image height
	int X=getX();						//location
	int Y=getY();
	
	Wall();


	// inherited member functions
	//void update(float frameTime);
};
#endif
