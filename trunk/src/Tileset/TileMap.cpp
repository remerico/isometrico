/*
 *  TileMap.cpp
 *
 *  Created by Rem on 2/13/11.
 *  Copyright 2011 Rem Cruz. All rights reserved.
 *
 */

#include "TileMap.h"

TileMap::~TileMap() {

	int count, i;
		
	count = tileLayers.size();
	for (i = 0; i < count; ++i) {
		TileLayer *t = tileLayers.back();
		tileLayers.pop_back();
		delete t;
	}
	
	count = tileSets.size();
	for (i = 0; i < count; ++i) {
		TileSet *t = tileSets.back();
		tileSets.pop_back();
		delete t;
	}

	std::cout << "Tilemap deleted!\n";
	
}

TileSet* TileMap::getTileSetFromGid(int gid) {

	int count = tileLayers.size();

	for (int i = 0; i < count; ++i) {
		
		TileSet *ts = tileSets.at(i);
		
		// GID is within the range of the tileset
		if ( (ts->getFirstGid() + ts->getTileCount() - 1) >= gid) {
			return ts;
		}
	
	}

	return NULL;	

}

void TileMap::render(game::Graphics *graphics) {
	
	game::Surface *screen = graphics->getScreen();

	int layerCount = tileLayers.size();
	int screenWidth = screen->w;
	int screenHeight = screen->h;

	int halfWidth = tileWidth / 2;
	int halfHeight = tileHeight / 2;
	
	int initX = tileHeight * height;
	int initY = 0;	

	int tileSetCol, tileSetRow, tileId, gid;
	int tileColCount, tileRowCount;
	TileSet *tset = NULL;	
	game::Rect srcRect;
    game::Rect destRect;

	maxOffsetX = std::max((tileWidth  * diagonalSize) - screenWidth, 0);
	maxOffsetY = std::max((tileHeight * diagonalSize) - screenHeight, 0);

	
	std::vector<std::string> lstrlist;
		
	for (int i = 0; i < 1 /*layerCount*/; ++i) {
		
		TileLayer *layer = tileLayers.at(i);
		
		for (int row = 0; row < height; ++row) {

			std::stringstream lpstr;
			
			for (int col = 0; col < width; ++col) {

				gid = layer->tileData[row][col];				
				if (gid == 0) continue;

				// Get the proper tileset surface for this GID
				tset = getTileSetFromGid(gid);
				if (tset == NULL) continue;
				
				tileId = gid - tset->getFirstGid();
				tileColCount = tset->getImageWidth() / tset->getTileWidth();
				tileRowCount = tset->getImageHeight() / tset->getTileHeight();
				
				tileSetCol = tileId % tileColCount;
				tileSetRow = (tileId / tileColCount) % tileRowCount;
				
				
				srcRect.x = tset->getMargin() + ((tset->getSpacing() + tset->getTileWidth()) * tileSetCol);
				srcRect.y = tset->getMargin() + ((tset->getSpacing() + tset->getTileHeight()) * tileSetRow);
				srcRect.w = tset->getTileWidth();
				srcRect.h = tset->getTileHeight();
				
				destRect.x = initX + (halfWidth * col) - (halfWidth * (row + 1)) - (int)offsetX;
				destRect.y = initY + (halfHeight * row) + (halfHeight * col) - (srcRect.h - tileHeight) - (int)offsetY;
				destRect.w = tset->getTileWidth();
				destRect.h = tset->getTileHeight();

				graphics->drawSurface(tset->getImage(), srcRect, destRect);

				if (destRect.inInside(game::Rect(0, 0, screenWidth, screenHeight))) lpstr << "1";
				else lpstr << "0";

				
				
			}
			
			lstrlist.push_back(lpstr.str());
			
		}
		
	}

	for(unsigned int i = 0; i < lstrlist.size(); ++i) {
		graphics->drawText(lstrlist.at(i), game::Rect(10, 50 + (i * 15), 100, 20), game::Color(255, 255, 255));
	}

}

