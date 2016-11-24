// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "wall.h"

//=============================================================================
// default constructor
//=============================================================================
Wall::Wall() : Entity()
{
	spriteData.x = WallNS::X;              // location on screen
	spriteData.y = WallNS::Y;
	spriteData.width = WallNS::WIDTH;           // size of Bullet
	spriteData.height = WallNS::HEIGHT;
	mass = WallNS::MASS;
	spriteData.rect.bottom =WallNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WallNS::WIDTH;
	//startFrame = WallNS::START_FRAME;    // first frame of ship animation
	//endFrame = WallNS::END_FRAME;      // last frame of ship animation
	setActive(true);
	setCurrentFrame(startFrame);
	collisionType = entityNS::BOX;
}

