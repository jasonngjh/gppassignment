#include "spacewar.h"
#include "Entity.h"
#include <chrono>
#include <thread>
#include <functional>
#include "threeCsDX.h"

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
	t.join();

	srand(time(NULL));
	switch (rand()%2)
	{
		case 0: // nebula texture
			if (!nebulaTexture.initialize(graphics, GRASS_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing grass background texture"));
			break;
		case 1: //nebula texture
			if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stone background texture"));
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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	//bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hearts texture"));

	if (!bloodTexture.initialize(graphics, BLOOD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initiazing screen blood textyre"));

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
	if (!dxFont.initialize(graphics, gameNS::POINT_SIZE, true, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	if (!dxFontScore.initialize(graphics, gameNS::POINT_SIZE, true, false, gameNS::FONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	if (!blood.initialize(graphics, 0, 0, 0, &bloodTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game"));

	std::clock_t start;
	start = std::clock();

	fpsOn = true;
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
	blood.setVisible(false);

	//ship.setVelocity(VECTOR2(PlayerNS::SPEED, -PlayerNS::SPEED)); // VECTOR2(X, Y)

	//ship.setDegrees(45.0f);     \                       // angle of ship
	//bullet.setX(GAME_WIDTH / 4);              // start above and left of planet
	//bullet.setY(GAME_HEIGHT / 4);

	setMaxZombieCount(30); //matches max zombie count to size of zombie array to prevent crashing
	setZombieCount(0);
	int fr = 0;
	std::async(&Spacewar::timer_start, this); //run timer thread while main loop is contiuing
    return;
}

//=============================================================================
// Update all game items
// Calls each game item's own update functions
//=============================================================================
void Spacewar::update()
{
	setFrameCountTime(getFrameCountTime() + 1);

	ship.update(frameTime); //ship movement is done here

	//CONTROLS
	if (input->isKeyDown(PLAYER_FIRE_KEY))
	{

		//create Bullet at player X and Y
		//add bullet to bullet array (for multiple bullets)

		if (!bullet.getActive())
			bullet.create(ship, ship.getDegrees());

	}//cant move while shooting/shooting has delay

	//update for bullet
	bullet.update(frameTime);

	//update for zombies
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
			std::async(&Spacewar::displayBlood, this); //display blood when collide with zombie
			mciSendString("play player_injured.wav", NULL, 0, NULL);
			zombieArray[i].setVisible(false);
			zombieArray[i].setActive(false);
			zombieArray.erase(zombieArray.begin() + i);
			setZombieCount(getZombieCount() - 1);


			if (ship.getPlayerVulnerable() == false){
				ship.setHealth(ship.getHealth() - 20);
				ship.setPlayerVulnerable(true);

				std::async(&Spacewar::checkVulnerable,this); //run asychronous thread to check if the player is vulnerable
			}

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
		bullet.setVisible(false);
		setScore(zombie.getScore());
		k = (rand() % 4 + 0) % 3;
		zombieArray[i].setVisible(false);
		zombieArray[i].setActive(false);

		mciSendString("play zombie_death.wav", NULL, 0, NULL);
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
		
		zombieArray.erase(zombieArray.begin() + i);
		setZombieCount(getZombieCount() - 1);

		bullet.setActive(false);

		}
	}
	if (ship.collidesWith(heart, collisionVector))
	{
		setScore(heart.getScore());
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
// Create bullets (called when player presses fire button)
//=============================================================================
Bullet Spacewar::createBullet()
{
	Bullet new_bullet;
	new_bullet.create(player, player.getDegrees());

	return bullet;

}

//=============================================================================
// Spawn zombies (constantly called every x seconds)
//=============================================================================
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
// Fire Bullet
//=============================================================================


//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{	
	dxFont.setFontColor(graphicsNS::WHITE);
	dxFontScore.setFontColor(graphicsNS::WHITE);
	graphics->spriteBegin();                // begin drawing sprites
	const int BUF_SIZE = 25;
	static char buffer[BUF_SIZE];
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
	blood.draw();
	for (int i = 0; i < getZombieCount(); i++)
	{
		zombieArray[i].draw();
	}
		_snprintf_s(buffer, BUF_SIZE, "Score: %d ", (int)getScore());
		dxFontScore.print(buffer, GAME_WIDTH - 300, 1);
		_snprintf_s(buffer, BUF_SIZE, "Seconds Passed: %d ",(int)getSecondsPassed());
		dxFont.print(buffer, GAME_WIDTH - 300, GAME_HEIGHT - 25);


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
	bloodTexture.onLostDevice();
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
	bloodTexture.onResetDevice();
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
		setSecondsPassed((clock() - timer) / (double)CLOCKS_PER_SEC);  //convert computer timer to real life seconds

		if ((fmod(getSecondsPassed(), 1)) == 0)
		{
			// check if current amount of zombie is less than maximum allowed amount
			//if true, create new zombie
			Sleep(10);
			if (getZombieCount() < getMaxZombieCount())
			{
				mciSendString("play zombie_comehere.wav", NULL, 0, NULL);
				setZombieCount(getZombieCount() + 1);

				Zombie z = spawnZombie();

				zombieArray.push_back(z);

				//zombieArray[getZombieCount() - 1] = spawnZombie();
				zombieArray[getZombieCount() - 1].spawn();
				//std::async(&Zombie::spawn, zombieArray[getZombieCount() - 1]); //asychronously spawn zombies
			}
			
		}

		if ((fmod(getSecondsPassed(), 10)) == 00)
		{
			// check if current amount of zombie is less than maximum allowed amount
			//if true, create new zombie
			Sleep(10);
			if (getZombieCount() < getMaxZombieCount())
			{
				mciSendString("play zombie_comehere.wav", NULL, 0, NULL);
				setZombieCount(getZombieCount() + 1);

				Zombie z = spawnZombie();

				zombieArray.push_back(z);

				//zombieArray[getZombieCount() - 1] = spawnZombie();
				zombieArray[getZombieCount() - 1].spawn();
				//std::async(&Zombie::spawn, zombieArray[getZombieCount() - 1]); //asychronously spawn zombies
			}

		}
	}
}
//=============================================================================
// check vulnerability of the player after colliding with zombie
//	set the vulnerable to off after x seconds
//=============================================================================
void Spacewar::checkVulnerable()
{
	bool loop = true;
	while (loop){
		if (ship.getPlayerVulnerable() == true){
			for (int i = 0; i < getZombieCount(); i++){
				zombieArray[i].freeze(ship, frameTime);
				Sleep(3000);
				zombieArray[i].update(ship, frameTime);
				ship.setPlayerVulnerable(false);
				loop = false;
			}
		}
	}
}
//=============================================================================
// display blood when collide with zombie
//=============================================================================
void Spacewar::displayBlood()
{
	blood.setVisible(true);
	Sleep(3000);
	blood.setVisible(false);
}

