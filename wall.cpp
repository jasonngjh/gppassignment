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
	//spriteData.x = WallNS::X;              // location on screen
	//spriteData.y = WallNS::Y;
	radius = WallNS::COLLISION_RADIUS;
	mass = WallNS::MASS;
	//startFrame = WallNS::START_FRAME;    // first frame of ship animation
	//endFrame = WallNS::END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
}