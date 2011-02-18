#ifndef STATE_RUNGAME_H
#define STATE_RUNGAME_H

#include <iostream>
#include "Game/Game.h"
#include "Game/State.h"
#include "Tileset/TileMap.h"


class State_RunGame : public State {

private:	

public:
	TileMap *tileMap;

	~State_RunGame() { 
		std::cout << "State_RunGame deleted\n"; 
		SAFE_DELETE(tileMap); 
	}

	State_RunGame(TileMap *tileMap);

	void update();
	void render(game::Graphics *graphics);
		
};

#endif