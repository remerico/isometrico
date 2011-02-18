/*
 *  Game.h
 *
 *  Created by Rem on 2/13/11.
 *  Copyright 2011 Rem Cruz. All rights reserved.
 *
 */
#ifndef GAME_H
#define GAME_H


#include "Core/Defines.h"
#include "Core/Graphics.h"
#include "Core/Input.h"
#include "Core/Timer.h"
#include "Core/File.h"
#include "Game/State.h"
#include "Game/Resources.h"
#include "Tileset/TMXLoader.h"

#include "Game/State.h"

class Game {

public:

	Game();
	~Game();

	void mainLoop();
	void cleanup();

	void update();
	void render();

	static Game *getInstance() { return instance; }

	game::Input      *getInput() { return input; }
	game::Timer      *getTimer() { return timer; }
	StateStack *getStates() { return states; }
	
private:

	static Game *instance;

	game::Graphics   *graphics;
	game::Input      *input;
	game::Timer      *timer;
	StateStack *states;
	
	bool running;

	game::Font *textFont;

	void pollEvents();

};

#define GAME Game::getInstance()

#endif