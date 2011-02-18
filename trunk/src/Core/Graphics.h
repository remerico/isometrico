#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Defines.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

namespace game {

typedef SDL_Surface  Surface;
typedef TTF_Font     Font;

struct Rect : SDL_Rect {
	Rect() { }
	Rect(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	bool inInside(const SDL_Rect& rect) {
		return (this->x < (rect.x + rect.w) && (this->x + this->w) > rect.x &&
			    this->y < (rect.y + rect.h) && (this->y + this->h) > rect.y);
	}
};

struct Color : SDL_Color {
	Color() { }
	Color(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	static inline Color white() { return Color(255, 255, 255); }
};


class Graphics {

private:
	Surface *screen;
	Font *currentFont;

protected:

public:
	Graphics(int width, int height, int bpp, bool fullscreen);
	~Graphics();

	Surface *getScreen() { return screen; }

	void drawSurface(Surface *surface, Rect& srcRect, Rect& destRect);
	void drawText(std::string text, Rect position, Color color = Color());

	static Surface *loadSurface(const std::string& fileName);
	static void freeSurface(Surface *surface) { if (surface != NULL) SDL_FreeSurface(surface); }

	void clearScreen();
	void renderScreen() { SDL_Flip(screen); }

	static Font *loadFont(const std::string& fileName, int size);	
	static void closeFont(Font *font);
	void setFont(Font *font);

};

}

#endif