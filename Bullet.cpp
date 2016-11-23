// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
{
	spriteData.width = BulletNS::WIDTH;           // size of Ship1
	spriteData.height = BulletNS::HEIGHT;
	spriteData.x = BulletNS::X;                   // location on screen
	spriteData.y = BulletNS::Y;
	spriteData.rect.bottom = BulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = BulletNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = BulletNS::BULLET_ANIMATION_DELAY;
	startFrame = BulletNS::BULLET_START_FRAME;      // first frame of ship animation
	endFrame = BulletNS::BULLET_END_FRAME;      // last frame of ship animation
	currentFrame = startFrame;
	radius = BulletNS::WIDTH / 2.0;
	collisionType = entityNS::BOX;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * PlayerNS::ROTATION_RATE;  // rotate the ship
	spriteData.x += frameTime * BULLET_SPEED;     // move ship along X 
	spriteData.y += frameTime * BULLET_SPEED;     // move ship along Y

	if (spriteData.angle == 270) //right
		spriteData.x += frameTime * BULLET_SPEED;
	else
	if (spriteData.angle == 90) //left
		spriteData.x -= frameTime * BULLET_SPEED;
	else
	if (spriteData.angle == 180) //up
		spriteData.y += frameTime * BULLET_SPEED;
	else
	if (spriteData.angle == 0) //down
		spriteData.y -= frameTime * BULLET_SPEED;

	// disappear off walls
	// if hit right screen edge
	if (spriteData.x > GAME_WIDTH - BulletNS::WIDTH*getScale())
	{
		//disappear
	}
	else if (spriteData.x < 0)                  // else if hit left screen edge
	{
		//disappear
	}
	// if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - BulletNS::HEIGHT*getScale())
	{
		//disappear
	}
	else if (spriteData.y < 0)                  // else if hit top screen edge
	{
		//disappear
	}

	



}
