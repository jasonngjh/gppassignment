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

	const int WIDTH = 30;                   // image width
	const int HEIGHT = 600;                  // image height
	const int COLLISION_RADIUS= 30;
	//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 200;                // 200 pixels per second
	//const float MASS = 300.0f;              // mass
	const float MASS = 1.0e14f;
	const int   TEXTURE_COLS = 10;           // texture has 2 columns
	//const int   wall_START_FRAME = 0;       // wall starts at frame 0
	//const int   wall_END_FRAME = 3;         // wall animation frames 0,1,2,3
	//const float wall_ANIMATION_DELAY = 0.2f; // time between frames

}

// inherits from Entity class
class Wall : public Entity
{
public:
	// constructor
	Wall();

	// inherited member functions
	//void update(float frameTime);
};
#endif

