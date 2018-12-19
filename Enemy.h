#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"

class Player;
class BulletMgr;

class Enemy : public Object {
public:
	Enemy();
	~Enemy();

	virtual void Update() = 0;
	virtual void Update(const Player& player) {};
	virtual void Draw() = 0;
	virtual void Draw(const Player& player) {};

	void Collision(const Player& player, BulletMgr& bulletMgr);	//“–‚½‚è”»’è
};

#endif