#ifndef TIMER_H
#define TIMER_H

#include "Defines.h"
#include "SDL.h"

#define MILLISECOND 1000

namespace game {

class Timer {

private:
	int prevTick;
	int targetFps;
	int delay;
	float deltaTime;

	// FPS variables
	int fps;
	int numFrames;
	int fpsLastUpdate;
	
	
public:
	Timer();

	void tick();

	float getDeltaTime();
	int getFps() { return fps; }

	void setTargetFps(int fps);

};

}

#endif