
#include "spacewar.h"
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
	/*if (!zombie.initialize(this, ZombieNS::WIDTH, ZombieNS::HEIGHT, ZombieNS::ZOMBIE_COLS, &zombieTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie"));*/

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

	setFrameCountTime(0);
	setSpawnTime(200); //zombie spawn time set to every 20 frame time

	//ship.setVelocity(VECTOR2(PlayerNS::SPEED, -PlayerNS::SPEED)); // VECTOR2(X, Y)

	//ship.setDegrees(45.0f);     \                       // angle of ship
	//bullet.setX(GAME_WIDTH / 4);              // start above and left of planet
	//bullet.setY(GAME_HEIGHT / 4);

	setMaxZombieCount(sizeof(zombieArray)/sizeof(*zombieArray)); //matches max zombie count to size of zombie array to prevent crashing
	setZombieCount(0);
	//zombie.spawn();

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
   void Spacewar::update()
   {
	   
	   setFrameCountTime(getFrameCountTime() + 1);

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
		   if (!bullet.getActive())
			   bullet.create(ship, ship.getDegrees());

		   //for multiple bullets
		   //create new bullet
		   //add new bullet to array
		   //set bullet to active (maybe do in bullet.cpp)
		   //update all other functions to work with dynamic bullet array
		   //projected problem: array cannot refresh after X amount of times, maybe use a recurring array, allowing fired bullets in an array to 'refire'
	   }


	   bullet.update(frameTime);


	   if (fmod(getFrameCountTime(), getSpawnTime()) == 0) //primitive timer
	   {

		   // check if current amount of zombie is less than maximum allowed amount
		   //if true, create new zombie

		   if (getZombieCount() < getMaxZombieCount())
		   {

			   setZombieCount(getZombieCount() + 1);
			   zombieArray[getZombieCount() - 1] = spawnZombie();

			   zombieArray[getZombieCount() - 1].spawn();
			   
			   //zombieArray[getZombieCount() - 1].
		   }
		   
	   }

	   //ship.update(frameTime);
	   //zombie.update(ship, frameTime);

	   if (getZombieCount() > 0)
	   {
		   //endlessly loop update for each zombie until no more zombies

		   for (int i = 0; i < getZombieCount(); i++)
		   {
			   zombieArray[i].update(ship, frameTime);
		   }
	   }

	   //check if zombie array is empty, refresh (set to change)
	   if (getZombieCount() == 0)
	   {
		   //make array empty or find a way to remove dead zombies from array
		   //
	   }

	   wall1.update(frameTime);

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
	
	for (int i = 0; i < getZombieCount(); i++)
	{
		//Zombie zombie = zombieArray[i];
		// if collision between bullet and zombies
		if (bullet.collidesWith(zombieArray[i], collisionVector))
		{
			k = (rand() % 4 + 0) % 3;
			zombieArray[i].setVisible(false);
			zombieArray[i].setActive(false);

			if (!heart.getActive() == true)
			{
				heart.setX(zombieArray[i].getX());
				heart.setY(zombieArray[i].getY());
			}
			graphics->spriteBegin();
			if (heart.getActive() == false)
			{
				heart.draw();
			}
			
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

			bullet.setActive(false);

			//setZombieCount(getZombieCount() - 1); //somehow makes one bullet kill two zombies lol
			//zombieArray[i].destroy(); <<crashes the thing lol

		}


	}

	
	if (ship.collidesWith(heart, collisionVector))
	{
		heart.setVisible(false);
		heart.setActive(false);
	}

	
	
}

//=============================================================================
// Spawn zombies (constantly called every x seconds)
//=======================================================
Zombie Spacewar::spawnZombie()
{

	//behavior for zombie spawn
	
	Zombie new_zombie;

	new_zombie.spawn();

	if (!new_zombie.initialize(this, ZombieNS::WIDTH, ZombieNS::HEIGHT, ZombieNS::ZOMBIE_COLS, &zombieTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie"));

	return new_zombie;
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
	//zombie.draw();
	//zombie2.draw();
	bullet.draw();
	heart.draw();

	for (int i = 0; i < getZombieCount(); i++)
	{
		zombieArray[i].draw();
	}

	graphics->spriteEnd();                  // end drawing sprites

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
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
	zombieTexture.onResetDevice();
	bulletTexture.onResetDevice();
    Game::resetAll();
    return;
}
