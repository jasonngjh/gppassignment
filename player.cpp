// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "player.h"

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
	radius = PlayerNS::WIDTH / 2.0;
    collisionType = entityNS::CIRCLE;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
    Entity::update(frameTime);
	//spriteData.angle += frameTime * PlayerNS::ROTATION_RATE;  // rotate the ship
    spriteData.x += frameTime * velocity.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y;     // move ship along Y

    // Bounce off walls
    // if hit right screen edge
	if (spriteData.x > GAME_WIDTH - PlayerNS::WIDTH*getScale())
    {
        // position at right screen edge
		spriteData.x = GAME_WIDTH - PlayerNS::WIDTH*getScale();
        velocity.x = -velocity.x;               // reverse X direction
    } 
    else if (spriteData.x < 0)                  // else if hit left screen edge
    {
        spriteData.x = 0;                       // position at left screen edge
        velocity.x = -velocity.x;               // reverse X direction
    }
    // if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - PlayerNS::HEIGHT*getScale())
    {
        // position at bottom screen edge
		spriteData.y = GAME_HEIGHT - PlayerNS::HEIGHT*getScale();
        velocity.y = -velocity.y;               // reverse Y direction
    }
    else if (spriteData.y < 0)                  // else if hit top screen edge
    {
        spriteData.y = 0;                       // position at top screen edge
        velocity.y = -velocity.y;               // reverse Y direction
    }

	if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	{
		spriteData.angle = 270;

		spriteData.x += frameTime * velocity.x;
	}
	if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	{
		spriteData.angle = 90;

		spriteData.x -= frameTime * velocity.x;
	}
	if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	{
		spriteData.angle = 180;

		spriteData.y += frameTime * velocity.y;
	}

	if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	{
		spriteData.angle = 0;

		spriteData.y -= frameTime * velocity.y;
	}

	if (input->isKeyDown(PLAYER_FIRE_KEY))
	{

		//create Bullet at player X and Y
		//might have to code this outside of Player 

		/*bullet.setDegrees(ship.getDegrees());
		bullet.setX(ship.getCenterX());
		bullet.setY(ship.getCenterY());

		if ((bullet.getX() < GAME_WIDTH) || (bullet.getY() < GAME_HEIGHT))
		{
			bullet.setY(bullet.getY() - frameTime * BULLET_SPEED);

		}*/

		//cant move while shooting/shooting has delay
		//PlaySound(TEXT("9_mm_gunshot-mike-koenig-123.wav"), NULL, SND_ASYNC);

	}



}
