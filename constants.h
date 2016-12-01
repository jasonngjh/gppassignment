
#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Surviive";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  800;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;
const UCHAR SHIP_LEFT_KEY = VK_LEFT;
const UCHAR SHIP_UP_KEY = VK_UP;
const UCHAR SHIP_DOWN_KEY = VK_DOWN;
const UCHAR PLAYER_FIRE_KEY = VK_SPACE;

// graphic images (names kept the same as of gameEngine)
const char NEBULA_IMAGE[] = "pictures\\lol.png";  // ORIGINAL PHOTO
const char GRASS_IMAGE[] = "pictures\\background2.png"; //picture of grass
const char PLANET_IMAGE[] = "pictures\\planet.png"; // picture of planet
const char SHIP_IMAGE[] = "pictures\\player.png";   // player
const char ENEMY_ZOMBIE_IMAGE[] = "pictures\\zombie.png"; //enemy zombie
const char WALL1_IMAGE[] = "pictures\\wall1.png";//Left wall
const char WALL2_IMAGE[] = "pictures\\wall2.png";//Top wall
const char WALL3_IMAGE[] = "pictures\\wall1.png";//Right wall
const char WALL4_IMAGE[] = "pictures\\wall2.png";//Bottomwall
const char BULLET_IMAGE[] = "pictures\\bullet.png";//bullet
const char HEART_IMAGE[] = "pictures\\pixelheart.png";//lifeup

const int  SHIP_START_FRAME = 0;         // starting frame of ship animation
const int  SHIP_END_FRAME = 3;           // last frame of ship animation
const float SHIP_ANIMATION_DELAY = 0.2f; // time between frames of ship animation original is 0.2f
const int  ZOMBIE_START_FRAME = 0;         // starting frame of ship animation
const int  ZOMBIE_END_FRAME = 3;           // last frame of ship animation
const float ZOMBIE_ANIMATION_DELAY = 0.15f;

const int  BULLET_START_FRAME = 0;         // starting frame of ship animation
const int  BULLET_END_FRAME = 1;           // last frame of ship animation
const float BULLET_ANIMATION_DELAY = 0.05f;
const int BULLET_SPEED = 5000;


//MAYBE WE CAN MAKE IF HEALTH IS LOW, PLAYER BLINKS FASTER

const int  SHIP_COLS = 2;                // ship texture has 2 columns
const int  SHIP_WIDTH = 32;              // width of ship image
const int  SHIP_HEIGHT = 32;             // height of ship image
const float ROTATION_RATE = 180.0f;             // degrees per second
//const float SCALE_RATE = 0.2f;                  // % change per second
const float SHIP_SPEED = 200.0f;                // pixels per second
const float SHIP_SCALE = 1.5f;         
const float ZOMBIE_SPEED = SHIP_SPEED / 2;
//left wall 
//const int WALL1_WIDTH = 30;
//const int WALL1_HEIGHT = GAME_HEIGHT;
//const int WALL1_x = GAME_WIDTH/2;
//const int WALL1_y = GAME_HEIGHT/2;
//top wall
//const int WALL2_WIDTH = 800;
//const int WALL2_HEIGHT = 30;
//const int wall2_x = 1;
//const int wall2_y = 1;
//const float WALL2_ROTATION_RATE=90.0f;

//zombie height and width
const int ZOMBIE_COLS = 2;
const int ZOMBIE_HEIGHT = 32;
const int ZOMBIE_WIDTH = 32;

//bullet
const int BULLET_COLS = 2;
const int BULLET_HEIGHT = 12;
const int BULLET_WIDTH = 3;


#endif
