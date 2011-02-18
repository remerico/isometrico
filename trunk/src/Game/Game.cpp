#include "Game.h"
#include "States/State_RunGame.h"

Game* Game::instance = NULL;

Game::Game() {

	if (instance != NULL) return;
	else instance = this;

	graphics = new game::Graphics(480, 360, 32, false);	
	input    = new game::Input();
	timer    = new game::Timer();
	states   = new StateStack();

	running = false;

	textFont = game::Resources::loadFont(FONTS_DEFAULT, 12);

	states->push(new State_RunGame(TMXLoader::loadMap("data/tilemap/isotest.tmx")));

}

Game::~Game() {
	instance = NULL;
	game::Graphics::closeFont(textFont);
}

void Game::cleanup() {
	states->clear();
	delete graphics;
	delete input;
}


void Game::mainLoop() {
	    
	running = true;

    while (running) {
		update();
        render();

		timer->tick();
	}

	cleanup();
	
}


void Game::update() {
	pollEvents();
	states->getCurrentState()->update();
}

void Game::render() {
	graphics->clearScreen();	

	//states->getCurrentState()->render(graphics);

	// Draw FPS
	std::stringstream fpstr;
	fpstr << "FPS: " << Game::getInstance()->getTimer()->getFps() ;//<< "  " << Timer::getDeltaTime();
	graphics->setFont(textFont);
	graphics->drawText(fpstr.str(), game::Rect(10, 10, 20, 20), game::Color::white());

	std::stringstream istr;
	istr << input->left << " " << input->right;
	graphics->drawText(istr.str(), game::Rect(10, 30, 20, 20), game::Color::white());
	
	graphics->renderScreen();
}


void Game::pollEvents() {
	input->pollInput();
	if (input->quit || input->escape) running = false;
}