// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "player.h"
#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player () : Entity()
{
    spriteData.width = PlayerNS::WIDTH;           // size of Ship1
	spriteData.height = PlayerNS::HEIGHT;
	spriteData.x = PlayerNS::X;                   // location on screen
	spriteData.y = PlayerNS::Y;
	spriteData.rect.bottom = PlayerNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = PlayerNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
	frameDelay = PlayerNS::SHIP_ANIMATION_DELAY;
	startFrame = PlayerNS::SHIP_START_FRAME;      // first frame of ship animation
	endFrame = PlayerNS::SHIP_END_FRAME;      // last frame of ship animation
    currentFrame = startFrame;
	radius = 1;
	health = 100;
    collisionType = entityNS::CIRCLE;
	movementSpeed = SHIP_SPEED;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
    Entity::update(frameTime);

    //spriteData.x += frameTime * velocity.x;     // move ship along X 
    //spriteData.y += frameTime * velocity.y;     // move ship along Y

	if (spriteData.x > GAME_WIDTH-30 - PlayerNS::WIDTH*getScale())
    {
        // position at right screen edge
		spriteData.x = GAME_WIDTH-30 - PlayerNS::WIDTH*getScale();
		if (velocity.x > 0)
        velocity.x = -velocity.x;               // reverse X direction
    } 
    else if (spriteData.x < 30)                  // else if hit left screen edge
    {
        spriteData.x = 30;                       // position at left screen edge
		if (velocity.x < 0)
        velocity.x = -velocity.x;               // reverse X direction
    }
    // if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT-30 - PlayerNS::HEIGHT*getScale())
    {
        // position at bottom screen edge
		spriteData.y = GAME_HEIGHT-30 - PlayerNS::HEIGHT*getScale();
		if (velocity.y > 0)

        velocity.y = -velocity.y;               // reverse Y direction
    }
    else if (spriteData.y < 30)                  // else if hit top screen edge
    {
        spriteData.y = 30;                       // position at top screen edge
		if (velocity.y < 0)
        velocity.y = -velocity.y;               // reverse Y direction
    }

	if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	{
		spriteData.angle = 270.0f;
		Entity::setDegrees(270.0f);

		spriteData.x += frameTime * movementSpeed;
	}
	if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	{
		spriteData.angle = 90.0f;
		Entity::setDegrees(90.0f);

		spriteData.x -= frameTime * movementSpeed;
	}
	if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	{
		spriteData.angle = 180.0f;
		Entity::setDegrees(180.0f);

		spriteData.y -= frameTime * movementSpeed;
	}

	if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	{
		spriteData.angle = 0;
		Entity::setDegrees(0);

		spriteData.y += frameTime * movementSpeed;

	}

}