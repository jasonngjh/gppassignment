
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
#include <chrono>
#include <list>

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
	Image   nebula;                 // nebula image
	Player ship;						//ship image
	Player player;			
	Image wall1;
	Image wall2;
	Image wall3;
	Image wall4;
	Zombie zombie;
	Zombie zombie2;
	Zombie zombieArray[5];
	Bullet bullet; //default bullet
	Heart heart;
	Bullet bulletList[10]; //array of bullets, at most ten (intended magazine size) <<< not actually meant to hold bullets, used for multiple bullet physics
	int k;

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
	void timer_start(std::function<void(void)> func, unsigned int interval);
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
