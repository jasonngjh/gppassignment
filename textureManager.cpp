#include "textureManager.h"

// default constructor
TextureManager::TextureManager()
{
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;            // set true when successfully initialized
}


// destructor
TextureManager::~TextureManager()
{
	SAFE_RELEASE(texture);
}

bool TextureManager::initialize(Graphics *g, const char *f)
{
	try{
		graphics = g;                       // the graphics object
		file = f;                           // the texture file

		hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
		if (FAILED(hr))
		{
			SAFE_RELEASE(texture);
			return false;
		}
	}
	catch (...) { return false; }
	initialized = true;                    // set true when successfully initialized
	return true;
}

// called when graphics device is lost
void TextureManager::onLostDevice()
{
	if (!initialized)
		return;
	SAFE_RELEASE(texture);
}

// called when graphics device is reset
void TextureManager::onResetDevice()
{
	if (!initialized)
		return;
	graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}
