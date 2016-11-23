#include "zombie.h"
#include "player.h"

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
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Zombie::update(float frameTime){
	Entity::update(frameTime);

}

void Zombie::movement(){
	int zombieX = spriteData.x;

}