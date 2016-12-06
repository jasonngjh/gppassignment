// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "bullet.h"

namespace PlayerNS
{

	//jack - brought most of these forward from constants.h
	//old naming convention kept the same for compatability 

	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 200;                // 200 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	const int   SHIP_START_FRAME = 0;       // ship starts at frame 0
	const int   SHIP_END_FRAME = 3;         // ship animation frames 0,1,2,3
	const float SHIP_ANIMATION_DELAY = 0.2f; // time between frames


}

// inherits from Entity class
class Player : public Entity
{

protected:
	bool isFiring;		//state if player is shooting 

public:
	bool playerVulnerable;
	// constructor
	Player();

	// inherited member functions
	void update(float frameTime);

	bool getPlayerVulnerable(){ return playerVulnerable; }
	void setPlayerVulnerable(bool v) { playerVulnerable = v; }

	void setFiringState(bool firingState){ isFiring = firingState; }
	bool getFiringState(){ return isFiring; }

};
#endif

