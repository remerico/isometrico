/*
 *  TileMap.h
 *
 *  Created by Rem on 2/13/11.
 *  Copyright 2011. All rights reserved.
 *
 */
#ifndef TILEMAP_H
#define TILEMAP_H


#include "Core/Defines.h"
#include "TileSet.h"
#include "TileLayer.h"


class TileMap {

	// TMXLoader can access TileMap's private parts
	friend class TMXLoader;

private:
	int width;
	int height;
	int tileWidth;
	int tileHeight;

	float offsetX;
	float offsetY;

	int maxOffsetX;
	int maxOffsetY;

	int diagonalSize;

	std::string filePath;

public:
	std::vector<TileLayer*> tileLayers;
	std::vector<TileSet*> tileSets;

	TileMap() : offsetX(0), offsetY(0), maxOffsetX(0), maxOffsetY(0) { }	
	~TileMap();

	TileSet *getTileSetFromGid(int gid);
	void render(game::Graphics *graphics);

	inline void setOffsetX(float x) {
		offsetX += x;
		if (offsetX > maxOffsetX) offsetX = (float)maxOffsetX;
		else if (offsetX < 0) offsetX = 0;
	}

	inline void setOffsetY(float y) {
		offsetY += y;
		if (offsetY > maxOffsetY) offsetY = (float)maxOffsetY;
		else if (offsetY < 0) offsetY = 0;
	}

		
};

#endif