#include "State_RunGame.h"


State_RunGame::State_RunGame(TileMap *tileMap) {
	this->tileMap = tileMap;
}

void State_RunGame::update() {

	game::Input *input = Game::getInstance()->getInput();
	float speed = 5;
	float movement = (GAME->getTimer()->getDeltaTime() * speed);
		
	tileMap->setOffsetX(input->horizontal * movement);
	tileMap->setOffsetY(input->vertical * movement);

	//debug << "offset: " << input->horizontal << "\n";
}

void State_RunGame::render(game::Graphics *graphics) {
	tileMap->render(graphics);	
}