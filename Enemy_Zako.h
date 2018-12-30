#ifndef ___Class_Zako
#define ___Class_Zako

#include "Enemy.h"

class Player;

class Zako : public Enemy {
public:
	Zako();
	Zako(VECTOR setPos);
	~Zako();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);	//移動
	void Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);	//当たり判定
};

#endif