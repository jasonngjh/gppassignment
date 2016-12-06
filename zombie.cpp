#include "zombie.h"
#include "player.h"
#include <stdlib.h>

//=============================================================================
// default constructor
//=============================================================================
Zombie::Zombie() : Entity()
{
	spriteData.width = ZombieNS::WIDTH;
	spriteData.height = ZombieNS::HEIGHT;
	spriteData.x = ZombieNS::X;
	spriteData.y = ZombieNS::Y;
	spriteData.rect.bottom = ZombieNS::HEIGHT;
	spriteData.rect.right = ZombieNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = ZombieNS::ZOMBIE_ANIMATION_DELAY;
	startFrame = ZombieNS::ZOMBIE_START_FRAME;      // first frame of ship animation
	endFrame = ZombieNS::ZOMBIE_END_FRAME;      // last frame of ship animation
	currentFrame = startFrame;
	radius = ZombieNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	score = ZombieNS::score;
}

//=============================================================================
// spawn
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Zombie::spawn()
{
	int randomX, randomY;
	randomX = rand() % GAME_WIDTH + 1;
	randomY = rand() % GAME_HEIGHT + 1;

	Zombie::setX(randomX);
	Zombie::setY(randomY);

	Zombie::setActive(true);

	Zombie::setFrames(ZOMBIE_START_FRAME, ZOMBIE_END_FRAME);   // animation frames ship.setCurrentFrame(SHIP_START_FRAME);             // starting frame
	Zombie::setFrameDelay(ZOMBIE_ANIMATION_DELAY);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Zombie::update(Image player,float frameTime){
	Entity::update(frameTime);

	if (spriteData.x > player.getX())
		spriteData.x = Zombie::getX() - frameTime * ZOMBIE_SPEED;

	if (spriteData.x < player.getX())
		spriteData.x = Zombie::getX() + frameTime * ZOMBIE_SPEED;

	if (spriteData.y > player.getY())
		spriteData.y = Zombie::getY() - frameTime * ZOMBIE_SPEED;

	if (spriteData.y < player.getY())
		spriteData.y = Zombie::getY() + frameTime * ZOMBIE_SPEED;

	/*double x = player.getCenterX() - Zombie::getCenterX();
	double y = player.getCenterY() - Zombie::getCenterY();
	spriteData.angle = atan2(x,y);*/

}
void Zombie::destroy()
{
	delete this;
}