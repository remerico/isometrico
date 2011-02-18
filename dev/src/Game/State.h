#ifndef STATE_H
#define STATE_H

#include "Core/Defines.h"
#include "Core/Graphics.h"

class State {

public:
	virtual void update() { }
	virtual void render(game::Graphics *graphics) { }

	virtual ~State() {  }

};

class StateStack {

private:
	std::stack<State*> states;

public:
	
	State *push(State *state);
	void pop();

	State *setState(State *state);
	State *getCurrentState();
	void clear();

};


#endif;