#ifndef ___Class_Tall
#define ___Class_Tall

#include "Enemy.h"

class Tall : public Enemy {
public:
	Tall();
	~Tall();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);
};

#endif