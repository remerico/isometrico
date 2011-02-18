#include "Graphics.h"

namespace game {

Graphics::Graphics(int width, int height, int bpp, bool fullscreen) {

	Uint32 flags = 0;

	// Init SDL video subsystem
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {		
		debug << "Couldn't initialize SDL: " << SDL_GetError() << "\n";
		exit(1);
	}

	// Request double-buffered OpenGL
    //SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	flags = SDL_SWSURFACE | SDL_DOUBLEBUF;
    if (fullscreen) flags |= SDL_FULLSCREEN;

    // Create window
    screen = SDL_SetVideoMode (width, height, bpp, flags);

    if (screen == NULL) {		
		debug << "Couldn't set video mode:" << SDL_GetError() << "\n";
		SDL_Quit();
		exit(2);
	}

	currentFont = NULL;
	TTF_Init();

}

Graphics::~Graphics() {
	SDL_FreeSurface(screen);
	SDL_Quit();
}

Surface* Graphics::loadSurface(const std::string& fileName) {
	
	Surface *image;

	// Load the image
	Surface* loadedImage = IMG_Load(fileName.c_str());
	
    // If the image loaded
    if(loadedImage != NULL)
    {
        // Create an optimized surface
        image = SDL_DisplayFormat(loadedImage);
		
        // Free loaded surface
        SDL_FreeSurface(loadedImage);
		
        //If the surface was optimized
        if (image != NULL) {
            // Color key surface
            SDL_SetColorKey(image, SDL_SRCCOLORKEY, image->format->colorkey);
        }
	
		std::cout << "Image loaded: " << fileName << "\n";

		return image;
    }

	else {
		std::cout << "Error loading " << fileName << "\n";
		return NULL;
	}

}

void Graphics::drawSurface(Surface *surface, Rect& srcRect, Rect& destRect) {
	if (srcRect.inInside(screen->clip_rect)) SDL_BlitSurface(surface, &srcRect, screen, &destRect);
}

void Graphics::clearScreen() {
	SDL_FillRect(screen, NULL, 0x000000);
}

void Graphics::drawText(std::string text, Rect position, Color color) {

	if (currentFont == NULL) {
		//debug << "Current font is null\n";
		return;
	}

	SDL_Surface *message;
	
	if (message = TTF_RenderText_Solid(currentFont, text.c_str(), color)) {
		SDL_BlitSurface(message, NULL, screen, &position);
	}
	else {
		//debug << "Text render error\n";
	}
	
	SDL_FreeSurface(message);
	
}


Font* Graphics::loadFont(const std::string& fileName, int size) {
	Font *font = TTF_OpenFont(fileName.c_str(), size);

	if (font != NULL) debug << "Font loaded: " << fileName << "\n";
	else debug << "Font " << fileName << " failed to font.\n";
	
	return font;
}

void Graphics::closeFont(Font *font) {
	TTF_CloseFont(font);
}

void Graphics::setFont(Font *font) {
	currentFont = font;
}

} // namespace