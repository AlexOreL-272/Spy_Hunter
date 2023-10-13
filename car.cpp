#include "car.h"

Car::Car(int) {
	x_ = x_pos;
	y_ = y_pos;
	type_ = CAR_DEFAULT;
	is_enemy_ = false;
	damaged_ = 0;

	bullets_shot_ = new Bullet[num_of_bullets];
	/*for (int i = 0; i < num_of_bullets; i++) {
		bullets_shot_[i] = Bullet();
	}*/
}

Car::Car(int current_line, int mapped) {
	bullets_shot_ = new Bullet[num_of_bullets];
	/*for (int i = 0; i < num_of_bullets; i++) {
		bullets_shot_[i] = Bullet();
	}*/

	int type = rand() % 2;
	is_enemy_ = 1 - type;
	damaged_ = 0;
	type_ = other_cars[type];

	y_ = -(rand() % SCREEN_HEIGHT);
	int new_car_on_line = 11 - ceil((static_cast<float>(y_) - mapped) / (2 * kSize));
	Line walls[4];
	memcpy(walls, LOOP[current_line - new_car_on_line].collider_, 4 * sizeof(Line));

	int side_of_road = (rand() % 2) * 2;
	x_ = walls[side_of_road].a_x_ + rand() % (walls[side_of_road + 1].a_x_ - walls[side_of_road].a_x_);

	// printf("new car has been created! x = %d; y = %d\n", x_, y_);
}

Car::~Car() {
	// printf("\n ~~~ Bullet array: %p ~~~\n\n", bullets_shot_);
	// delete[] bullets_shot_;
}

void Car::DrawCar(SDL_Surface* screen, SDL_Surface* sprite) {
	SDL_Rect dst = { x_, y_, x_ + 21, y_ + 42 };
	SDL_BlitSurface(sprite, &type_, screen, &dst);
}

int& Car::GetX() { return x_; }

int Car::GetY() { return y_; }

SDL_Rect& Car::GetType() { return type_; }

bool Car::IsEnemy() { return is_enemy_; }

int& Car::IsDamaged() { return damaged_; }

bool& Car::IsForced() { return forced_; }

Bullet* Car::GetBullets() { return bullets_shot_; }

int Car::GetBulletsShot() { return num_of_bullets_shot_; }

int Car::CheckCollision(int offset, Segment& segm) {
	// printf("Checking collision: ");

	int walls[4];
	for (int i = 0; i < 4; i++) {
		if (segm.collider_[i].GetK() != 0) {
			walls[i] = (y_ - segm.collider_[i].GetB() - offset) / segm.collider_[i].GetK();
		}
		else {
			walls[i] = segm.collider_[i].GetB();
		}
		// printf("[%d] = %d; ", i, walls[i]);
	}
	// printf("\n");

	if (x_ < walls[0]) {
		return 0;
	}
	else if (x_ + 24 > walls[1] && x_ + 24 < walls[2]) {
		return 1;
	}
	else if (x_ < walls[2] && x_ + 24 > walls[2]) {
		return 2;
	}
	else if (x_ + 24 > walls[3]) {
		return 3;
	}

	return -1;
}

void Car::MoveDown() {
	y_ += 3;
}

bool Car::NeedsToBeRecreated() {
	return y_ > SCREEN_HEIGHT;
}

int Car::Collides(Car& other_car) {
	int d_x = abs(x_ - other_car.GetX());
	int d_y = y_ - other_car.GetY();

	if (d_y <= 42 && d_y >= 40 && d_x < 24) {
		return 3;
	}

	if (abs(y_ - other_car.GetY()) < 42 && abs(x_ - other_car.GetX()) < 24 && x_ < other_car.GetX()) {
		return -1;
	}
	else if (abs(y_ - other_car.GetY()) < 42 && abs(x_ - other_car.GetX()) < 24 && x_ > other_car.GetX()) {
		return 1;
	}
	
	return 0;
}

void Car::ApplyDamage() {
	type_ = DAMAGED;
	damaged_++;
}

bool Car::EnemyUnderPlayer(Car& player) {
	return y_ > player.GetY() + 30 && (y_ - player.GetY()) < 200 && abs(x_ - player.GetX()) < 24;
}

void Car::Shoot() {
	if (num_of_bullets_shot_ < num_of_bullets) {
		Bullet new_bullet(x_ + 8, y_ - 5);
		bullets_shot_[num_of_bullets_shot_++] = new_bullet;
	}
}

void Car::RemoveBullet() {
	// bullets_shot_[num_of_bullets_shot_].Remove();
	num_of_bullets_shot_ = max(0, num_of_bullets_shot_ - 1);
}


// :: Bullet class

Bullet::Bullet() {
	x_ = -10;
	y_ = -10;
	type_ = BULLET;
}

Bullet::Bullet(int x, int y) : x_(x), y_(y) {
	type_ = BULLET;
}

Bullet::~Bullet() = default;

bool Bullet::Move() {
	if (height_limit <= 0) {
		return false;
	}

	y_--;
	height_limit--;

	return true;
}

bool Bullet::CheckPenetration(Car& target) {
	return abs(x_ - target.GetX()) < 24 && abs(y_ - target.GetY()) < 42;
}

void Bullet::DrawBullet(SDL_Surface* screen, SDL_Surface* sprite) {
	SDL_Rect dst = { x_, y_, 13, 2 };
	SDL_BlitSurface(sprite, &type_, screen, &dst);
}

void Bullet::Remove() {
	x_ = -10;
	y_ = -10;
}