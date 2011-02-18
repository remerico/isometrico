/*
 *  TileSet.cpp
 *  Project Villain
 *
 *  Created by Rem on 2/13/11.
 *  Copyright 2011 Individual. All rights reserved.
 *
 */

#include "TileSet.h"


bool TileSet::loadImage(std::string fileName) {

	tileCount = 0;
	game::Graphics::freeSurface(image);

	image = game::Graphics::loadSurface(fileName.c_str());

	if (image != NULL) {
		// Get number of tiles based on image size and tile size
		tileCount = (image->w / tileWidth) * (image->h / tileHeight);

		return true;
	}

	else return false;
	
}