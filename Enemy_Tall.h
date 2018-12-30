#ifndef ___Class_Tall
#define ___Class_Tall

#include "Enemy.h"

class Player;

class Tall : public Enemy {
public:
	Tall();
	~Tall();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);
	void Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);	//“–‚½‚è”»’è
};

#endif