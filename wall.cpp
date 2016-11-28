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
<<<<<<< HEAD
	//spriteData.x = WallNS::X;              // location on screen
	//spriteData.y = WallNS::Y;
	radius = WallNS::COLLISION_RADIUS;
	mass = WallNS::MASS;
	//startFrame = WallNS::START_FRAME;    // first frame of ship animation
	//endFrame = WallNS::END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
	edge.left =1;
	edge.top = 1;
	edge.right=WallNS::WIDTH;
	edge.bottom = WallNS::HEIGHT;
	
=======
	spriteData.x =X;              // location on screen
	spriteData.y =Y;
	spriteData.width=WIDTH;          
	spriteData.height=HEIGHT;
	//mass = WallNS::MASS;
	//edge.top = WallNS::X;
	//edge.left = WallNS::Y;
	//edge.right = WallNS::WIDTH;
	//edge.bottom = WallNS::HEIGHT;
	//spriteData.rect.top = WallNS::X;
	//spriteData.rect.right = WallNS::Y;
	//spriteData.rect.bottom =WallNS::HEIGHT;    // rectangle to select parts of an image
	//spriteData.rect.right = WallNS::WIDTH;
>>>>>>> refs/remotes/origin/wex
	//startFrame = WallNS::START_FRAME;    // first frame of ship animation
	//endFrame = WallNS::END_FRAME;      // last frame of ship animation

	//edge = rect;
	//edge = { X, Y, WIDTH, HEIGHT };
	edge.left = X;
	edge.top = Y;
	edge.right = WIDTH;
	edge.bottom = HEIGHT;
	setActive(true);
	setCurrentFrame(startFrame);
<<<<<<< HEAD
	collisionType = entityNS::BOX;
}
=======
	collisionType = entityNS::BOX;
}
>>>>>>> refs/remotes/origin/wex
