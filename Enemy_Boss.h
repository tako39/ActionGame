#ifndef ___Class_Boss
#define ___Class_Boss

#include "Enemy.h"

class Boss : public Enemy {
public:
	Boss();
	~Boss();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);
};

#endif