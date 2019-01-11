#ifndef ___Class_Zako
#define ___Class_Zako

#include "Enemy.h"

class Zako : public Enemy {
public:
	Zako();
	~Zako();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);	//ˆÚ“®
};

#endif