#ifndef RENDERER_H
#define RENDERER_H

#include "util.h"

class Render {
private:

public:
	Render() = default;
	~Render() = default;

	void DrawString(SDL_Surface*, int, int, const char*, SDL_Surface*);
	void DrawSurface(SDL_Surface*, SDL_Surface*, int, int);
	void DrawPixel(SDL_Surface*, int, int, Uint32);
	void DrawLine(SDL_Surface*, int, int, int, int, int, Uint32);
	void DrawLine(SDL_Surface*, Line, int, Uint32);
	void DrawRectangle(SDL_Surface*, int, int, int, int, Uint32, Uint32);
	void DrawPart(SDL_Surface*, int, int, SDL_Surface*, const SDL_Rect&);
	void DrawSegment(SDL_Surface*, int, int, SDL_Surface*, SDL_Rect[15]);
	void DrawLoop(SDL_Surface*, SDL_Surface*, int, Segment*, int, int);
	void DrawCar(SDL_Surface*, SDL_Surface*, SDL_Rect&, int, int);
	void DrawLegend(SDL_Surface*, SDL_Surface*);
};

#endif RENDERER_H