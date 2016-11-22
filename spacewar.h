
#ifndef _SPACEWAR_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"

//=============================================================================
// Create game class
//=============================================================================
class Spacewar : public Game
{
private:
    // variables
	// game items
	TextureManager nebulaTexture;   // nebula texture
	TextureManager planetTexture;   // planet texture
	TextureManager shipTexture;		//ship texture
	TextureManager bulletTexture;
	TextureManager wall1Texture;		//wall Texture
	TextureManager wall2Texture;		//wall Texture
	TextureManager wall3Texture;		//wall Texture
	TextureManager wall4Texture;		//wall Texture
	Image   planet;                 // planet image
	Image   nebula;                 // background image
	Image ship;						//player character image
	Image bullet;					//bullet image
	Image wall1;
	Image wall2;
	Image wall3;
	Image wall4;

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
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
