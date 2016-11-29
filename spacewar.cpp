
#include "spaceWar.h"
#include "Entity.h"
#include <chrono>
#include <thread>
#include <functional>

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	if (!wall1Texture.initialize(graphics, WALL1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!wall2Texture.initialize(graphics, WALL2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!wall3Texture.initialize(graphics, WALL3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!wall4Texture.initialize(graphics, WALL4_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	//zombie texture
	if (!zombieTexture.initialize(graphics, ENEMY_ZOMBIE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialiing zombie texture"));

	//ship texture
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));
	//bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
	// place planet in center of screen
	//planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	//planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	// wall
	if (!wall1.initialize(graphics, 0,0, 0, &wall1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	if (!wall2.initialize(graphics, 0,0, 0, &wall2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	if (!wall3.initialize(graphics,0,0,0, &wall3Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	if (!wall4.initialize(graphics, 0,0,0, &wall4Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	////ship
	if (!ship.initialize(this,PlayerNS::WIDTH, PlayerNS::HEIGHT, PlayerNS::TEXTURE_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	//zombie
	if (!zombie.initialize(this, ZombieNS::WIDTH, ZombieNS::HEIGHT, ZombieNS::ZOMBIE_COLS, &zombieTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie"));

	if (!bullet.initialize(this, BULLET_WIDTH, BULLET_HEIGHT, BULLET_COLS, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	if (!heart.initialize(this, 0,0,0, &heartTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));

	wall3.setX(770);
	wall4.setY(570);
	ship.setX(GAME_WIDTH / 4);              // start above and left of planet
	ship.setY(GAME_HEIGHT / 4);
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames ship.setCurrentFrame(SHIP_START_FRAME);             // starting frame
	ship.setFrameDelay(SHIP_ANIMATION_DELAY);

	//ship.setVelocity(VECTOR2(PlayerNS::SPEED, -PlayerNS::SPEED)); // VECTOR2(X, Y)

	//ship.setDegrees(45.0f);     \                       // angle of ship
	//bullet.setX(GAME_WIDTH / 4);              // start above and left of planet
	//bullet.setY(GAME_HEIGHT / 4);

	zombie.spawn();
	zombie2.spawn();

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
   void Spacewar::update()
   {
	   ship.update(frameTime);
	   // rotate ship
	   //ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE);
	   // make ship smaller
	   //ship.setScale(ship.getScale() - frameTime * SCALE_RATE);
	   // move ship right
	   /*ship.setX(ship.getX() + frameTime * SHIP_SPEED);
	   if (ship.getX() > GAME_WIDTH)               // if off screen right
	   {
	   ship.setX((float)-ship.getWidth());     // position off screen left
	   ship.setScale(SHIP_SCALE);              // set to starting size
	   }*/

	   //CONTROLS

	   //maybe put if key on, ship stop moving


	   if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	   {
		   ship.setDegrees(270.0f);

		   ship.setX(ship.getX() + frameTime * SHIP_SPEED);
		   if (ship.getX() > GAME_WIDTH)               // if off screen right
			   ship.setX((float)-ship.getWidth());  // position off screen left
	   }
	   if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	   {

		   ship.setDegrees(90);

		   ship.setX(ship.getX() - frameTime * SHIP_SPEED);
		   if (ship.getX() < -ship.getWidth())         // if off screen left
			   ship.setX((float)GAME_WIDTH);      // position off screen right
	   }
	   if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	   {
		   ship.setDegrees(180);

		   ship.setY(ship.getY() - frameTime * SHIP_SPEED);
		   if (ship.getY() < -ship.getHeight())        // if off screen top
			   ship.setY((float)GAME_HEIGHT);     // position off screen bottom
	   }

	   if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	   {
		   ship.setDegrees(0);

		   ship.setY(ship.getY() + frameTime * SHIP_SPEED);
		   if (ship.getY() > GAME_HEIGHT)              // if off screen bottom
			   ship.setY((float)-ship.getHeight());    // position off screen top
	   }

	   if (input->isKeyDown(PLAYER_FIRE_KEY))
	   {

		   //create Bullet at player X and Y
		   //add bullet to bullet array (for multiple bullets)

		   if (!bullet.getActive())
			   bullet.create(ship, ship.getDegrees());

	   }//cant move while shooting/shooting has delay

	   bullet.update(frameTime);

	   if (bullet.getActive())
	   {

		   //bullet.setDegrees(ship.getDegrees());
		   bullet.update(frameTime);
	   }

	   /*if (bullet.getDegrees() == 270) //right
		   bullet.setX(bullet.getX() + frameTime * BULLET_SPEED);
		   else
		   if (bullet.getDegrees() == 90) //left
		   bullet.setX(bullet.getX() - frameTime * BULLET_SPEED);
		   else
		   if (bullet.getDegrees() == 180) //up
		   bullet.setY(bullet.getY() - frameTime * BULLET_SPEED);
		   else
		   if (bullet.getDegrees() == 0) //down
		   bullet.setY(bullet.getY() + frameTime * BULLET_SPEED);*/
	   /*if (zombie.getX() > ship.getX())
   =======

   if (zombie.getX() > ship.getX())
   >>>>>>> refs/remotes/origin/wex
   zombie.setX(zombie.getX() - frameTime * ZOMBIE_SPEED);

   if (zombie.getX() < ship.getX())
   zombie.setX(zombie.getX() + frameTime * ZOMBIE_SPEED);

   if (zombie.getY() > ship.getY())
   zombie.setY(zombie.getY() - frameTime * ZOMBIE_SPEED);

   if (zombie.getY() < ship.getY())
   zombie.setY(zombie.getY() + frameTime * ZOMBIE_SPEED);*/

	   //ship.update(frameTime);
	   zombie.update(ship, frameTime);
	   zombie2.update(ship, frameTime);
	   wall1.update(frameTime);
	   /*if (rand() % 4 + 0==1)
	   {
		   heart.setActive(true);
		   heart.setVisible(true);
	   }
	   else{
		   heart.setActive(false);
		   heart.setVisible(false);
	   }
	   heart.update(frameTime);*/
	//code to check
	//if bullet active
	//PEW PEW!

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	
	VECTOR2 collisionVector;
	
	// if collision between ship and planet
	if (bullet.collidesWith(zombie, collisionVector))
	{
		// bounce off planet
		k = (rand() % 4 + 0) % 3;
		zombie.setVisible(false);
		zombie.setActive(false);
		//bullet.setActive(false);
		//ship1.damage(PLANET);
		if (!heart.getActive() == true)
		{
			heart.setX(zombie.getX());
			heart.setY(zombie.getY());
		}
		zombie.setX(rand() % GAME_WIDTH - 30 + 30);
		zombie.setY(rand() % GAME_HEIGHT - 30 + 30);
		graphics->spriteBegin();
		if (heart.getActive() == false)
		{
			heart.draw();
		}
		zombie.draw();
		graphics->spriteEnd();
		if (k == 1)
		{
			heart.setVisible(true);
			heart.setActive(true);
		}
		else 
		{
			heart.setVisible(false);
			heart.setActive(false);
		}
		zombie.setVisible(true);
		zombie.setActive(true);
	}
	if (ship.collidesWith(heart, collisionVector))
	{
		heart.setVisible(false);
		heart.setActive(false);
	}

	
	
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{	
	graphics->spriteBegin();                // begin drawing sprites

	nebula.draw();                          // add the orion nebula to the scene
	//planet.draw();                          // add the planet to the scene
	ship.draw();
	wall1.draw();
	wall2.draw();
	wall3.draw();
	wall4.draw();
	zombie.draw();
	zombie2.draw();
	bullet.draw();
	heart.draw();
	graphics->spriteEnd();                  // end drawing sprites

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	zombieTexture.onLostDevice();
	bulletTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	zombieTexture.onResetDevice();
	bulletTexture.onResetDevice();
    Game::resetAll();
    return;
}
