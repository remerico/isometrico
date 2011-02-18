#include "Input.h"

namespace game {

void Input::pollInput() {

	SDL_Event event;
	bool isDown;

	// Check for events
	while ( SDL_PollEvent (&event) ) {
		switch (event.type) {

			case SDL_MOUSEMOTION:
				break;

			case SDL_MOUSEBUTTONDOWN:
				break;

			case SDL_KEYUP:
			case SDL_KEYDOWN:
				isDown = (event.type == SDL_KEYDOWN) ? true : false;

				switch (event.key.keysym.sym) {
					case SDLK_LEFT:    left   = isDown;  break;
					case SDLK_RIGHT:   right  = isDown;  break;
					case SDLK_UP:      up     = isDown;  break;
					case SDLK_DOWN:    down   = isDown;  break;
					case SDLK_ESCAPE:  escape = isDown;  break;
				}
				break;
				
			case SDL_QUIT:
				quit = true;
				break;

			default:
				break;
		}
	}

	horizontal = (left == right) ? 0 : right ? 1 : left ? -1 : 0;
	vertical = (up == down) ? 0 : down ? 1 : up ? -1 : 0;

}

} // namespace