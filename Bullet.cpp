// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "bullet.h"
#include "player.h"

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
<<<<<<< HEAD
	movementSpeed = BulletNS::BULLET_SPEED;
=======
>>>>>>> refs/remotes/origin/master
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = BulletNS::BULLET_ANIMATION_DELAY;
	startFrame = BulletNS::BULLET_START_FRAME;      // first frame of ship animation
	endFrame = BulletNS::BULLET_END_FRAME;      // last frame of ship animation
	currentFrame = startFrame;
	radius = BulletNS::WIDTH / 2.0;
	collisionType = entityNS::ROTATED_BOX;
	active = false;
}

//=============================================================================
// create
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
<<<<<<< HEAD
void Bullet::create(Image player, float degree)
=======
void Bullet::create(Image player)
>>>>>>> refs/remotes/origin/master
{
	Bullet::setDegrees(player.getDegrees());
	Bullet::setX(player.getCenterX());
	Bullet::setY(player.getCenterY());

<<<<<<< HEAD
	//spriteData.angle = Bullet::getDegrees(); <<this and the next line somehow makes bullet change direction when player changes direction lol
	//spriteData.angle = degree; 
=======
	spriteData.angle = Bullet::getDegrees();
>>>>>>> refs/remotes/origin/master

	spriteData.x = Bullet::getX();                   // location on screen
	spriteData.y = Bullet::getY();

	active = true;

	PlaySound(TEXT("9_mm_gunshot-mike-koenig-123.wav"), NULL, SND_ASYNC);

}

//=============================================================================
// update
<<<<<<< HEAD
// typically called once per frame, is only called when a bullet is active
=======
// typically called once per frame
>>>>>>> refs/remotes/origin/master
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime)
{
<<<<<<< HEAD
	if (active)
		visible = true;

	Entity::update(frameTime);

	if (Bullet::getDegrees() == 270) //right
	{
		spriteData.x += frameTime * movementSpeed;
	}


	if (Bullet::getDegrees() == 90) //left
		spriteData.x -= frameTime * movementSpeed;

	if (Bullet::getDegrees() == 180) //up
		spriteData.y -= frameTime * movementSpeed;

	if (Bullet::getDegrees() == 0) //down
		spriteData.y += frameTime * movementSpeed;
=======
	Entity::update(frameTime);
	//spriteData.angle += frameTime * PlayerNS::ROTATION_RATE;  // rotate the ship
	
	//spriteData.angle = Bullet::getDegrees(); //somehow, this makes bullet start at player center instead of forward of player (maybe bullet is indeed travelling BUT???)

	if (Bullet::getDegrees() == 270) //right
	{
		spriteData.x += frameTime * BULLET_SPEED;
	}
		
	
	if (Bullet::getDegrees() == 90) //left
		spriteData.x -= frameTime * BULLET_SPEED;
	
	if (Bullet::getDegrees() == 180) //up
		spriteData.y -= frameTime * BULLET_SPEED;
	
	if (Bullet::getDegrees() == 0) //down
		spriteData.y += frameTime * BULLET_SPEED;
>>>>>>> refs/remotes/origin/master

	// disappear off walls
	// if hit right screen edge
	if (spriteData.x > GAME_WIDTH - BulletNS::WIDTH*getScale())
	{
		active = false;
	}
	else if (spriteData.x <= 0)                  // else if hit left screen edge
	{
		active = false;
	}
	// if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - BulletNS::HEIGHT*getScale())
	{
		active = false;
	}
	else if (spriteData.y <= 0)                  // else if hit top screen edge
	{
		active = false;
	}

<<<<<<< HEAD
	if (!active)
		visible = false;
=======
	


>>>>>>> refs/remotes/origin/master

}
