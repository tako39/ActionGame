#ifndef ___Class_Big
#define ___Class_Big

#include "Enemy.h"

class Big : public Enemy {
public:
	Big();
	~Big();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);
};

#endif