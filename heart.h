
#ifndef _HEART_H                 // Prevent multiple definitions if this 
#define _HEART_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace HeartNS
{

	//jack - brought most of these forward from constants.h
	//old naming convention kept the same for compatability 

	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = rand() % 740 + 30;   // location on screen
	const int Y = rand() % 540 + 30;
	const float SPEED = 200;                // 200 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	//const int   SHIP_START_FRAME = 0;       // ship starts at frame 0
	//c/onst int   SHIP_END_FRAME = 3;         // ship animation frames 0,1,2,3
	const float SHIP_ANIMATION_DELAY = 0.2f; // time between frames
	

}

// inherits from Entity class
class Heart : public Entity
{
public:
	// constructor
	Heart();

	// inherited member functions
	void update(float frameTime);

	void destroy(Heart h)
	{
		delete h;
	}
};
#endif
