
#ifndef _SPACEWAR_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bullet.h"
#include "zombie.h"
#include "heart.h"
#include <windows.h>
#include <conio.h>
#include <functional>
#include <ctime>
#include <list>
#include <future>


//=============================================================================
// Create game class
//=============================================================================
class Spacewar : public Game
{
private:
    // variables
	// game items
	TextureManager nebulaTexture;   // nebula texture
	TextureManager shipTexture;		//ship texture
	TextureManager wall1Texture;		//wall Texture
	TextureManager wall2Texture;		//wall Texture
	TextureManager wall3Texture;		//wall Texture
	TextureManager wall4Texture;		//wall Texture
	TextureManager zombieTexture;
	TextureManager bulletTexture;
	TextureManager heartTexture;
	TextureManager lifebarTexture;
	TextureManager bloodTexture;
	Image   nebula;                 // nebula image
	Player ship;						//ship image
	Player player;			
	Image wall1;
	Image wall2;
	Image wall3;
	Image wall4;
	Zombie zombie;
	Zombie zombie2;
	Image lifebar;
	Image blood;

	std::vector<Zombie> zombieArray;
	int maxZombieCount; //amt of zombies allowed to exist (should be equal to zombieArray's size)
	int zombieCount; //amt of zombies currently alive (should be less or equal to maxZombieCount)
	

	Bullet bullet; //default bullet
	Heart heart;
	Heart heart2;
	Bullet bulletList[10];//array of bullets, at most ten (intended magazine size) <<< not actually meant to hold bullets, used for multiple bullet physics
	
	int k;
	float zombieSpawnTime;
	float frameCountTime;
	float score;
	int rng;

public:
	double secondsPassed;
    // Constructor
    Spacewar();

	

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
	void timer_start();
	Zombie spawnZombie();
	Bullet createBullet();
    void render();      // "
    void releaseAll();
    void resetAll();
	void checkFrameTime(int value);
	int fr;
	void setBackgroundRNG(int value);
	void checkVulnerable();
	void playBGM();
	void displayBlood();

	float getSpawnTime() { return zombieSpawnTime; }
	void setSpawnTime(float time) { zombieSpawnTime = time; }

	float getFrameCountTime() { return frameCountTime; }
	void setFrameCountTime(float time) { frameCountTime = time; }

	int getZombieCount() { return zombieCount; }
	void setZombieCount(int amt) { zombieCount = amt; }

	float getScore(){ return score; }
	void setScore(int sc){ score += sc; }
	int getMaxZombieCount() { return maxZombieCount; }
	void setMaxZombieCount(int amt) { maxZombieCount = amt; }

	double getSecondsPassed() { return secondsPassed; }
	void setSecondsPassed(double seconds) { secondsPassed = seconds; }



};

#endif
