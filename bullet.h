#ifndef _BULLET_H              // Prevent multiple definitions if this 
#define _BULLET_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "player.h"

namespace BulletNS
{

	//jack - brought most of these forward from constants.h
	//old naming convention kept the same for compatability 
	const int  BULLET_START_FRAME = 0;         // starting frame of ship animation
	const int  BULLET_END_FRAME = 1;           // last frame of ship animation
	const int X = 0;
	const int Y = 0;
	const float BULLET_ANIMATION_DELAY = 0.05f;
	const int BULLET_SPEED = 500;
	const bool isActive = true; //when created a bullet is active

	//bullet
	const int BULLET_COLS = 2;
	const int HEIGHT = 12;
	const int WIDTH = 3;
}

// inherits from Entity class
class Bullet : public Entity
{
public:
	// constructor
	Bullet();

	// inherited member functions
	void update(float frameTime);

	void create(Image player, float degree);
	void create(Image player);

		
};
#endif

