#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"
#include "Define.h"

class Player;

class Enemy : public Object {
private:
	bool isGround;  //接地判定
	VECTOR playerPos;  //プレイヤーの位置

public:
	Enemy();
	~Enemy();

	void Update() {};
	void Update(const Player& cPlayer);
	void Draw();

	void Move(float moveY, float moveX);  //移動
	void Collision(const Player& player);  //当たり判定
};

#endif