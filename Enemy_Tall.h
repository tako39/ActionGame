#ifndef ___Class_Tall
#define ___Class_Tall

#include "Enemy.h"

class Tall : public Enemy {
public:
	Tall();
	Tall(VECTOR setPos);
	~Tall();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);
};

#endif