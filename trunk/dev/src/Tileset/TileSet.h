/*
 *  TileSet.h
 *  Project Villain
 *
 *  Created by Rem on 2/13/11.
 *  Copyright 2011 Individual. All rights reserved.
 *
 */

#ifndef TILESET_H
#define TILESET_H

#include "Core/Graphics.h"

#include <iostream>
#include <string>


class TileSet {
	
private:
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int tileCount;
	int firstGid;
	
	game::Surface *image;
	
public:
	
	TileSet() {
		image = NULL;
		tileWidth = 0;
		tileHeight = 0;
		spacing = 0;
		margin = 0;
	}
	
	TileSet(int tileWidth, int tileHeight, int spacing, int margin, int firstGid) {
		
		image = NULL;
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->spacing = spacing;
		this->margin = margin;
		this->firstGid = firstGid;
	}
	
	~TileSet() {
		if (image != NULL) {
			game::Graphics::freeSurface(image);
			std::cout << "Tileset deleted!\n";
		}
	}
	
	int getTileWidth() { return tileWidth; }
	int getTileHeight() { return tileHeight; }
	int getSpacing() { return spacing; }
	int getMargin() { return margin; }
	int getFirstGid() { return firstGid; }
	int getTileCount() { return tileCount; }
	
	game::Surface *getImage() { return image; }
	int getImageWidth() { return (image != NULL) ? image->w : 0; }
	int getImageHeight() { return (image != NULL) ? image->h : 0; }
	bool loadImage(std::string fileName);
	
};


#endif