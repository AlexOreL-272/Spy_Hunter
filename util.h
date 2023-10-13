#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include <cmath>
#include <cstdio>
#include <cstring>

constexpr int SCREEN_WIDTH = 480;
constexpr int SCREEN_HEIGHT = 832;
constexpr int LOOP_SIZE = 254;

#include "SDL2-2.0.10/include/SDL.h"
#include "SDL2-2.0.10/include/SDL_main.h"

constexpr int kSize = 32;
constexpr int kSpeed = 80;
static int current_speed = kSpeed;

constexpr int x_pos = SCREEN_WIDTH / 2;
constexpr int y_pos = SCREEN_HEIGHT * 2 / 3;

constexpr int num_of_bots = 4;
constexpr int num_of_bullets = 20;

// (0 - kSpeed) -> (0 - kSize * 2);
static int map(int cur, int old_st, int old_end, int new_st, int new_end) {
	return static_cast<int>(cur * abs(new_end - new_st) / abs(old_end - old_st));
}

static int min(int left, int right) {
	return left < right ? left : right;
}

static int max(int left, int right) {
	return left > right ? left : right;
}

typedef struct line {
private:
	int k, b;

public:
	int a_x_, a_y_, b_x_, b_y_;

	line() = default;

	line (int a_x, int a_y, int b_x, int b_y):
		a_x_(a_x), a_y_(a_y), b_x_(b_x), b_y_(b_y) {
		k = (a_x - b_x == 0) ? 0 : (a_y - b_y) / (a_x - b_x);
		b = k != 0 ? a_y - k * a_x : a_x;
		
		// k = 0;
		// b = (a_x + b_x) / 2;
	}

	int& GetB() { return b; }
	int& GetK() { return k; }
} Line;

// { Line(112, 0, 96, 64), Line(368, 0, 384, 64), Line(112, 0, 96, 64), Line(368, 0, 384, 64) };
// 64 + 4 * 368

typedef struct segm {
	SDL_Rect road_segment_[15];
	Line collider_[4];

	segm(SDL_Rect road_segment[15], Line collider[4]) {
		memcpy(road_segment_, road_segment, 15 * sizeof(SDL_Rect));
		memcpy(collider_, collider, 4 * sizeof(Line));
	}

} Segment;



#endif // !_UTIL_H_