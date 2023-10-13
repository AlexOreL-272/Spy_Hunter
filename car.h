#include "lineSegments.h"

class Bullet;

class Car {
private:
	int x_, y_;
	SDL_Rect type_;
	bool is_enemy_;
	int damaged_;

	Bullet* bullets_shot_;
	int num_of_bullets_shot_ = 0;

	bool forced_ = false;

public:
	Car() = default;

	Car(int);

	Car(int current_line, int mapped);

	~Car();

	void DrawCar(SDL_Surface* screen, SDL_Surface* sprite);

	int& GetX();
	int GetY();
	SDL_Rect& GetType();
	bool IsEnemy();
	int& IsDamaged();

	Bullet* GetBullets();
	int GetBulletsShot();

	bool& IsForced();

	int CheckCollision(int offset, Segment& segm);

	bool NeedsToBeRecreated();

	int Collides(Car& other_car);

	void MoveDown();

	void ApplyDamage();

	bool EnemyUnderPlayer(Car& player);

	void Shoot();

	void RemoveBullet();
};

class Bullet {
private:
	int x_, y_;
	int height_limit = 200;
	SDL_Rect type_;

public:
	Bullet();

	Bullet(int x, int y);

	~Bullet();

	bool Move();

	bool CheckPenetration(Car& target);

	void DrawBullet(SDL_Surface* screen, SDL_Surface* sprite);

	void Remove();
};