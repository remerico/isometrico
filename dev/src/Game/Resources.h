#ifndef RESOURCES_H
#define RESOURCES_H

#include "Resources/fontlist.h"

#define RES_PATH       "data/"
#define SPRITES_PATH   RES_PATH "sprites/"
#define TILES_PATH     RES_PATH "tilemap/"
#define FONTS_PATH     RES_PATH "fonts/"


namespace game {

class Resources {

public:
	static game::Font *loadFont(std::string font, int size) {
		return Graphics::loadFont(File::combinePath(FONTS_PATH, font), size);
	}


};

} // namespace

#endif