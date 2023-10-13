#include "renderer.h"

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void Render::DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void Render::DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

// draw a single pixel
void Render::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Render::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

void Render::DrawLine(SDL_Surface* screen, Line ln, int offset, Uint32 color) {
	if (ln.GetK() == 0) {
		DrawLine(screen, max(ln.a_x_, ln.b_x_), offset, 64, 0, 1, color);
		return;
	}

	for (int i = ln.a_x_; i < ln.b_x_; i++) {
		// printf("\n\n :: %d : %d ::\n\n", ln.a_x_, ln.b_x_);
		DrawPixel(screen, i, ln.GetK() * i + ln.GetB() + offset, color);
	}

	for (int i = ln.b_x_; i < ln.a_x_; i++) {
		DrawPixel(screen, i, ln.GetK() * i + ln.GetB() + offset, color);
	}
};

// draw a rectangle of size l by k
void Render::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

// rect width = 32, height = 64
void Render::DrawPart(SDL_Surface* screen, int x, int y, SDL_Surface* sprite, const SDL_Rect& crop) {
	SDL_Rect dst = { x, y, kSize, kSize * 2 };
	SDL_BlitSurface(sprite, &crop, screen, &dst);
}

void Render::DrawSegment(SDL_Surface* screen, int x, int y, SDL_Surface* sprite, SDL_Rect type[15]) {
	SDL_Rect dst = { x, y, kSize, kSize * 2 };
	for (int i = 0; i < 15; i++) {
		DrawPart(screen, x + i * kSize, y, sprite, type[i]);
		//if (y + 64 < SCREEN_HEIGHT)
			//DrawLine(screen, x + i * kSize, y, 64, 0, 1, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	}
	//DrawLine(screen, 0, y, SCREEN_WIDTH, 1, 0, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
}

void Render::DrawLoop(SDL_Surface* screen, SDL_Surface* sprite, int y, Segment* loop, int from, int to) {
	// printf("%d :: %d ||||  ", from, to);
	if ((to + 1) % LOOP_SIZE < from) {
		// printf("if %d :: %d\n", from, to);
		for (int i = from; i < LOOP_SIZE; i++) {
			DrawSegment(screen, 0, y + (LOOP_SIZE - i + to % LOOP_SIZE) * kSize * 2, sprite, loop[i].road_segment_);
			//if (i == from) {
			//	continue;
			//}
			//DrawLine(screen, loop[i].collider_[0], y + (LOOP_SIZE - i + to % LOOP_SIZE) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
			//DrawLine(screen, loop[i].collider_[1], y + (LOOP_SIZE - i + to % LOOP_SIZE) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
			//DrawLine(screen, loop[i].collider_[2], y + (LOOP_SIZE - i + to % LOOP_SIZE) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
			//DrawLine(screen, loop[i].collider_[3], y + (LOOP_SIZE - i + to % LOOP_SIZE) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
		}
		for (int i = 0; i <= (to + 1) % LOOP_SIZE; i++) {
			DrawSegment(screen, 0, y + (to % LOOP_SIZE - i) * kSize * 2, sprite, loop[i].road_segment_);
			//DrawLine(screen, loop[i].collider_[0], y + (to % LOOP_SIZE - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
			//DrawLine(screen, loop[i].collider_[1], y + (to % LOOP_SIZE - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
			//DrawLine(screen, loop[i].collider_[2], y + (to % LOOP_SIZE - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
			//DrawLine(screen, loop[i].collider_[3], y + (to % LOOP_SIZE - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
		}
		return;
	}

	for (int i = from; i <= to + 1; i++) {
		DrawSegment(screen, 0, y + (to - i) * kSize * 2, sprite, loop[i].road_segment_);
		/*if (i == from) {
			continue;
		}
		DrawLine(screen, loop[i].collider_[0], y + (to - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
		DrawLine(screen, loop[i].collider_[1], y + (to - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
		DrawLine(screen, loop[i].collider_[2], y + (to - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
		DrawLine(screen, loop[i].collider_[3], y + (to - i) * kSize * 2, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));*/
	}
}

void Render::DrawLegend(SDL_Surface* screen, SDL_Surface* charset) {
	DrawString(screen, 330, 740, "n - new game", charset);
	DrawString(screen, 330, 750, "arrows - movement", charset);
	DrawString(screen, 330, 760, "space - shoot", charset);
	DrawString(screen, 330, 770, "esc - quit", charset);
	DrawString(screen, 330, 780, "p - pause", charset);
	DrawString(screen, 330, 790, "f- finish", charset);
}