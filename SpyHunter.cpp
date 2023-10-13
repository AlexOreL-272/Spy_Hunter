#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "car.h"
#include "lineSegments.h"
#include "renderer.h"

#include <sstream>	
#include <SDL.h>
#include <string.h>

int main(int argc, char** argv) {
	srand(time(0));

	int rc, score = 0;
	double delta = 0, distance = 0;
	char* timer = new char[5];
	char* char_score = new char[15];
	bool quit = false;
	SDL_Event event;
	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Surface* road;
	SDL_Surface* car;

	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Render printer;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Anton Matsviayuk s151550");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	charset = SDL_LoadBMP("cs8x8.bmp");

	SDL_SetColorKey(charset, true, 0x000000);

	road = SDL_LoadBMP("forest.bmp");
	car = SDL_LoadBMP("cars.bmp");

	if (charset == nullptr || road == nullptr || car == nullptr) {
		printf("Could not load file %s\n", SDL_GetError());
	}
	else {
		printf("Opened everything OK\n");
	}

	char text[128];
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int hell_blau = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	int current_line = 0, speed_param = 0;
	int mapped;
	bool paused = false;
	Uint32 pause_time_start = 0, pause_time_summ = 0;
	int collision = -1;

	Car player(0);
	bool* car_created = new bool[num_of_bots];
	for (int i = 0; i < num_of_bots; i++) {
		car_created[i] = false;
	}

	Car* cars = new Car[num_of_bots];

	int halt_score_start = 0;
	int halt_score_end = 2000;

	while (!quit) {

		// handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			// printf("%d", event.type);
			switch (event.type) {
			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: {
					// printf("Escape was pressed\n");
					quit = true;
					break;
				}
				case SDLK_w:
				case SDLK_UP: {
					if (player.IsDamaged() != 0) {
						break;
					}

					// printf("UP was pressed\n");
					current_speed = min(kSpeed - 15, current_speed);
					player.GetType() = CAR_NITRO;
					score += 5;
					break;
				}
				case SDLK_a:
				case SDLK_LEFT: {
					if (player.IsDamaged() != 0) {
						break;
					}

					// printf("Left arrow\n");
					if (player.GetX() >= 7) {
						player.GetX() -= 7;
					}
					player.GetType() = CAR_R;
					break;
				}
				case SDLK_d:
				case SDLK_RIGHT: {
					if (player.IsDamaged() != 0) {
						break;
					}

					// printf("Right arrow\n");
					if (player.GetX() <= SCREEN_WIDTH - 31) {
						player.GetX() += 7;
					}
					player.GetType() = CAR_L;
					break;

				}
				case SDLK_p: {
					// paused = !paused;
					if (!paused) {
						pause_time_start = SDL_GetTicks();
						paused = true;
					}
					else {
						pause_time_summ += SDL_GetTicks() - pause_time_start;
						paused = false;
					}

					// player.GetType() = CAR_DEFAULT;
					break;
				}
				case SDLK_n: {
					if (paused) {
						break;
					}

					pause_time_start = 0;
					pause_time_summ = SDL_GetTicks();
					score = 0;
					player.GetType() = CAR_DEFAULT;
					current_line = 0;
					current_speed = kSpeed;
					speed_param = 0;
					break;
				}
				case SDLK_SPACE: {
					if (paused) {
						break;
					}

					player.Shoot();
				}
				}
				break;
			}
			case SDL_KEYUP: {
				current_speed = kSpeed;
				player.GetType() = player.IsDamaged() ? DAMAGED : CAR_DEFAULT;
				break;
			}
			case SDL_QUIT: {
				quit = true;
				break;
			}
			};
		};

		if (paused) {
			continue;
		}

		mapped = map(speed_param, 0, kSpeed, 0, kSize * 2);
		printer.DrawLoop(screen, road, mapped, LOOP, current_line, current_line + 12);		

		// printf("BS: %d\n", player.GetBulletsShot());

		for (int i = 0; i < player.GetBulletsShot(); i++) {
			if (!player.GetBullets()[i].Move()) {
				player.RemoveBullet();
			}
			player.GetBullets()[i].DrawBullet(screen, car);
		}

		for (int i = 0; i < num_of_bots; i++) {
			if (!car_created[i]) {
				cars[i] = Car(current_line, mapped);
				car_created[i] = true;
			}
		}

		int car_on_line = 11 - ceil((static_cast<float>(y_pos) - mapped) / (2 * kSize));

		int offset = (12 - car_on_line) * 2 * kSize + mapped;
		if ((collision = player.CheckCollision(offset, LOOP[(current_line + car_on_line) % LOOP_SIZE])) != -1) {
			/*Line ln = LOOP[current_line + car_on_line].collider_[collision];
			
			int x;
			if (ln.GetK() != 0) {
				x = (y_pos - ln.GetB() - offset) / ln.GetK();
			}
			else {
				x = ln.GetB();
			}
			printf("new x: %d, line %d (%d)\n", x, car_on_line, current_line + car_on_line);
			printf("Line: k = %d, b = %d\n", ln.GetK(), ln.GetB());
			printf("collision type: %d\n\n", collision);
			player.GetX() = collision % 2 ? x - 26 : x + 2;*/
		}
		else if ((halt_score_end = SDL_GetTicks()) - halt_score_start >= 2000) {
			score++;
		}

		player.DrawCar(screen, car);
		
		if (player.IsDamaged() >= 250) {
			printf("\n ~~~~ You lose! ~~~~ \n");
			printf("\n ~~~~ Your score: %d ~~~~ \n", score);
			printf("\n ~~~~ Your time: %s ~~~~ \n", timer);
			quit = true;
		}

		if (player.IsDamaged() != 0) {
			player.IsDamaged()++;
		}

		for (int i = 0; i < num_of_bots; i++) {
			cars[i].DrawCar(screen, car);
		}

		sprintf(char_score, "%d", score);	

		if (speed_param++ > current_speed) {
			current_line = (current_line + 1) % LOOP_SIZE;
			speed_param = 0;
		}

		for (int i = 0; i < num_of_bots; i++) {
			int out_of_collider;
			int bot_on_line = 11 - ceil((static_cast<float>(cars[i].GetY()) - mapped) / (2 * kSize));
			int bot_offset = (12 - bot_on_line) * 2 * kSize + mapped;

			for (int j = 0; j < player.GetBulletsShot(); j++) {
				if (player.GetBullets()[j].CheckPenetration(cars[i])) {
    				if (!cars[i].IsEnemy()) {
						halt_score_start = SDL_GetTicks();
					}
					else {
						score += 1000;
					}

					cars[i].ApplyDamage();
					player.RemoveBullet();
					break;
				}
			}

			if (!cars[i].IsForced()) {
				if ((out_of_collider = cars[i].CheckCollision(bot_offset, LOOP[(current_line + bot_on_line) % LOOP_SIZE])) != -1) {
					Line ln = LOOP[current_line + bot_on_line].collider_[out_of_collider];

					int x;
					if (ln.GetK() != 0) {
						x = (cars[i].GetY() - ln.GetB() - bot_offset) / ln.GetK();
					}
					else {
						x = ln.GetB();
					}

					cars[i].GetX() = out_of_collider % 2 ? x - 26 : x + 2;
				}
			}

			if (speed_param == kSpeed * .2 || speed_param == kSpeed * .4 || speed_param == kSpeed * .6 || speed_param == kSpeed * 0.8) {
				cars[i].MoveDown();
			}

			if (cars[i].IsEnemy() && cars[i].EnemyUnderPlayer(player)) {
				// printf("Enemy shoots!\n");
				cars[i].Shoot();
			}

			for (int j = 0; j < cars[i].GetBulletsShot(); j++) {
				if (!cars[i].GetBullets()[j].Move()) {
					cars[i].RemoveBullet();
				}

				if (cars[i].GetBullets()[j].CheckPenetration(player)) {
					player.ApplyDamage();
					cars[i].RemoveBullet();
				}

				cars[i].GetBullets()[j].DrawBullet(screen, car);
			}

			if (cars[i].IsDamaged() != 0) {
				cars[i].IsDamaged()++;
			}

			if (cars[i].NeedsToBeRecreated() || cars[i].IsDamaged() == 100) {
				car_created[i] = false;
			}

			int side_of_collision;
			if ((side_of_collision = player.Collides(cars[i])) != 0) {
				if (cars[i].IsEnemy() && side_of_collision == 3) {
					player.ApplyDamage();
					break;
				}
				else if (!cars[i].IsEnemy() && side_of_collision == 3) {
					halt_score_start = SDL_GetTicks();
					cars[i].ApplyDamage();
				}
				else {
					cars[i].GetX() = player.GetX() - side_of_collision * 26;
					cars[i].IsForced() = true;
				}
			}
		}

		sprintf(timer, "%.1lf", (double) (SDL_GetTicks() - pause_time_summ) * 0.001);
		
		printer.DrawString(screen, 20, 20, timer, charset);
		printer.DrawString(screen, 420, 20, char_score, charset);
		printer.DrawLegend(screen, charset);


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		// SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
	};

	Uint32 end = SDL_GetTicks();
	//float secondsElapsed = (end - start) / 1000.0f;
	//printf("%.2f %s\n", secondsElapsed, "seconds you've been playing :)");
	// freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(car);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	delete[] timer;
	delete[] char_score;
	delete[] cars;
	delete[] car_created;

	return 0;
};
