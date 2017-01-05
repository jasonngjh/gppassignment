#ifndef _ZOMBIE_H                 // Prevent multiple definitions if this 
#define _ZOMBIE_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace ZombieNS{
	//zombie height and width
	const int ZOMBIE_COLS = 2;
	const int HEIGHT = 32;
	const int WIDTH = 32;
	const int  ZOMBIE_START_FRAME = 0;         // starting frame of ship animation
	const int  ZOMBIE_END_FRAME = 3;           // last frame of ship animation
	const float ZOMBIE_ANIMATION_DELAY = 0.15f;
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int score = 100;
	
}

class Zombie : public Entity{



public:
	//constructor
	Zombie();

	float ZOMBIE_SPEED = ZOMBIE_SPEED;

	// inherited member functions
	void spawn();
	void update(Image player, float frameTime);
	void destroy();

	void setZombieSpeed(float speed){
		ZOMBIE_SPEED = speed;
	}

	float getZombieSpeed(){
		return ZOMBIE_SPEED;
	}
};
#endif