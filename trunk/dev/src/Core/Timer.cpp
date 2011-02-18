#include "Timer.h"

namespace game {

Timer::Timer() {

	prevTick  = SDL_GetTicks();
	targetFps = 60;
	delay     = 0;
	deltaTime = 0;

	numFrames = 0;
	fps = 0;
	fpsLastUpdate = 0;


}

float Timer::getDeltaTime() {
	return deltaTime;
}

void Timer::tick() {

	int currentTick = SDL_GetTicks();

	// Update frames per second
	++numFrames;
	if (currentTick - fpsLastUpdate > MILLISECOND) {
		fps = numFrames;
		fpsLastUpdate = currentTick;
		numFrames = 0;
	}

	
	// If target FPS is set, adjust delay to get closer to target framerate
	if (targetFps > 0) {
		delay += ((MILLISECOND / targetFps) - (currentTick - prevTick));
		if (delay < 0) delay = 0;
		SDL_Delay(delay);
	}

	deltaTime = (float)(currentTick - prevTick) / 16;

	prevTick = currentTick;
	
}

void Timer::setTargetFps(int fps) {
	if (fps >= 0) {
		targetFps = fps;
		delay = 1000 / fps;
	}
}

} // namespace