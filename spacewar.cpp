
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

	std::thread t(&Spacewar::playBGM, this);

	int i = rand() % 2;
	switch (i)
	{
		case 0: // nebula texture
			if (!nebulaTexture.initialize(graphics, GRASS_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
			break;
		case 1: //nebula texture
			if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
			break;
	}

	if (!wall1Texture.initialize(graphics, WALL1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!wall2Texture.initialize(graphics, WALL2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!wall3Texture.initialize(graphics, WALL3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!wall4Texture.initialize(graphics, WALL4_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
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
	if (!lifebarTexture.initialize(graphics, LIFEBAR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lifebar texture"));
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
	//ship
	if (!ship.initialize(this,PlayerNS::WIDTH, PlayerNS::HEIGHT, PlayerNS::TEXTURE_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	if (!bullet.initialize(this, BULLET_WIDTH, BULLET_HEIGHT, BULLET_COLS, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	if (!heart.initialize(this, 0,0,0, &heartTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Heart"));
	if (!heart2.initialize(this, 0, 0, 0, &heartTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Heart"));
	if (!lifebar.initialize(graphics, LIFEBAR_WIDTH, LIFEBAR_HEIGHT, 0, &lifebarTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Heart"));

	lifebar.setX(3);
	lifebar.setY(0);
	lifebar.setFrames(0, 4);
	wall3.setX(770);
	wall4.setY(570);
	ship.setX(GAME_WIDTH / 4);              // start above and left of planet
	ship.setY(GAME_HEIGHT / 4);
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames ship.setCurrentFrame(SHIP_START_FRAME);             // starting frame
	ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	heart2.setVisible(false);
	heart2.setActive(false);
	heart.setActive(false);
	heart.setVisible(false);
	setFrameCountTime(0);
	ship.setHealth(100);
	ship.setActive(true);
	setSpawnTime(200); //zombie spawn time set to every 20 frame time

	//ship.setVelocity(VECTOR2(PlayerNS::SPEED, -PlayerNS::SPEED)); // VECTOR2(X, Y)

	//ship.setDegrees(45.0f);     \                       // angle of ship
	//bullet.setX(GAME_WIDTH / 4);              // start above and left of planet
	//bullet.setY(GAME_HEIGHT / 4);

	setMaxZombieCount(sizeof(zombieArray)/sizeof(*zombieArray)); //matches max zombie count to size of zombie array to prevent crashing
	setZombieCount(0);
	//zombie.spawn();
	int fr = 0;
	std::async(&Spacewar::timer_start, this); //run timer thread while main loop is contiuing
	t.join();
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

		//create Bullet at player X and Y
		//add bullet to bullet array (for multiple bullets)

		if (!bullet.getActive())
			bullet.create(ship, ship.getDegrees());

	}//cant move while shooting/shooting has delay

	//bullet.update(frameTime);

	if (bullet.getActive())
	{
		bullet.update(frameTime);
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
	// wall1.update(frameTime);
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
		if (ship.collidesWith(zombieArray[i], collisionVector))
		{
			ship.setHealth(ship.getHealth() - 20);
			if (ship.getHealth() < 0)
				ship.setHealth(0);
			
			if (ship.getHealth() == 100)
				lifebar.setCurrentFrame(0);
			if (ship.getHealth() == 80)
				lifebar.setCurrentFrame(1);
			if (ship.getHealth() == 60)
				lifebar.setCurrentFrame(2);
			if (ship.getHealth() == 40)
				lifebar.setCurrentFrame(3);
			if (ship.getHealth() == 20)
			lifebar.setCurrentFrame(4);
			if (ship.getHealth() == 0)
				lifebar.setVisible(false); //GAME SUPPOSED TO END HERE
		}
	//Zombie zombie = zombieArray[i];
	// if collision between bullet and zombies
	if (bullet.collidesWith(zombieArray[i], collisionVector))
	{
		k = 1;//(rand() % 4 + 0) % 3;
		zombieArray[i].setVisible(false);
		zombieArray[i].setActive(false);
		heart2.setX(zombieArray[i].getX());
		heart2.setY(zombieArray[i].getY());
		if (!heart.getActive() == true)
		{
			heart.setX(heart2.getX());
			heart.setY(heart2.getY());
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
		//else
		//{
		//heart.setVisible(false);
		//heart.setActive(false);
		//}

		bullet.setActive(false);

		//setZombieCount(getZombieCount() - 1); //somehow makes one bullet kill two zombies lol
		//zombieArray[i].destroy(); <<crashes the thing lol
		}
	}

	if (ship.collidesWith(heart, collisionVector))
	{
		lifebar.setVisible(true);
		heart.setVisible(false);
		heart.setActive(false);
		ship.setHealth(ship.getHealth() + 20);
		if (ship.getHealth() == 100)
			lifebar.setCurrentFrame(0);
		else if (ship.getHealth() == 80)
			lifebar.setCurrentFrame(1);
		else if (ship.getHealth() == 60)
			lifebar.setCurrentFrame(2);
		else if (ship.getHealth() == 40)
			lifebar.setCurrentFrame(3);
		else if (ship.getHealth() == 20)
		{
			
			lifebar.setCurrentFrame(4);
		}
		//else if (ship.getHealth() == 0)
			//
			//lifebar.setVisible(false);  NOT SUPPOSED TO BE HERE. GAME ENDING SCREEN.
			
	}
	//player.update(frameTime);

	
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
	heart.draw();
	lifebar.draw();
	bullet.draw();
	for (int i = 0; i < getZombieCount(); i++)
	{
		zombieArray[i].draw();
	}
	//while (i < 5)
	//{
	//	zombieArray[i].draw();
	//	i++;
	//	if (i > getZombieCount())
	//	{
	//		i = 0;
	//	}
	//}
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
//=============================================================================
// play the background music
//	using thread
//=============================================================================
void Spacewar::playBGM()
{
	PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}
//=============================================================================
// start timer
//	using thread
//=============================================================================
void Spacewar::timer_start()
{
	//create timer
	clock_t timer = clock();//start timer

	bool loop = true;
	while (loop){
		setSecondsPassed((clock() - timer) / CLOCKS_PER_SEC);  //convert computer timer to real life seconds

		if ((fmod(getSecondsPassed(),getSpawnTime()))==0){ 
			// check if current amount of zombie is less than maximum allowed amount
			//if true, create new zombie
			if (getZombieCount() < getMaxZombieCount())
			{
				setZombieCount(getZombieCount() + 1);
				zombieArray[getZombieCount() - 1] = spawnZombie();

				std::async(&Zombie::spawn, zombieArray[getZombieCount() - 1]); //asychronously spawn zombies
			}
		}
	}
}