// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "heart.h"

//=============================================================================
// default constructor
//=============================================================================
Heart::Heart() : Entity()
{
	spriteData.width = HeartNS::WIDTH;           // size of Ship1
	spriteData.height = HeartNS::HEIGHT;
	spriteData.x = HeartNS::X;                   // location on screen
	spriteData.y = HeartNS::Y;
	spriteData.rect.bottom = HeartNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = HeartNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay =HeartNS::SHIP_ANIMATION_DELAY;
	//s5tartFrame = PlayerNS::SHIP_START_FRAME;      // first frame of ship animation
	//endFrame = PlayerNS::SHIP_END_FRAME;      // last frame of ship animation
	currentFrame = startFrame;
	radius = 5;
	health = 125;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Heart::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * PlayerNS::ROTATION_RATE;  // rotate the ship

}
