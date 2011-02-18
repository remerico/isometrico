/*
 *  TileLayer.h
 *  Project Villain
 *
 *  Created by Rem on 2/13/11.
 *  Copyright 2011 Individual. All rights reserved.
 *
 */


#ifndef TILELAYER_H
#define TILELAYER_H


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

#include "Core/Defines.h"

struct TileLayer {

	TileLayer(int width, int height) {
		tileWidth = width;
		tileHeight = height;
	}

	int tileWidth;
	int tileHeight;
	
	std::string tileName;
	vector2int tileData;
	
};

#endif