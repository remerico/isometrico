#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

namespace game {

class Input {

public:
	bool left;
	bool right;
	bool up;
	bool down;

	int horizontal;
	int vertical;
	
	bool escape;
	bool quit;

	void pollInput();

};

}

#endif