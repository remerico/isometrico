#include "Game/State.h"


State* StateStack::push(State *state) {
	std::cout << "push state\n";
	states.push(state);
	return state;
}

void StateStack::pop() {
	if (!states.empty()) {
		std::cout << "pop state\n";
		State *s = states.top();
		states.pop();
		//SAFE_DELETE(s);
	}
}

State* StateStack::setState(State *state) {
	pop();
	return push(state);
}

State* StateStack::getCurrentState() {
	return (!states.empty()) ? states.top() : NULL;		
}

void StateStack::clear() {
	while (!states.empty()) {
		pop();
	}
}