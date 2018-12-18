#ifndef ___Class_Zako
#define ___Class_Zako

#include "Enemy.h"

class Player;

class Zako : public Enemy {
private:
	bool isGround;		//接地判定

public:
	Zako();
	~Zako();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	VECTOR randomPos();	//ランダムで位置決め
	int randomDir();	//ランダムで向きを決める
	void Move(float moveY, float moveX);	//移動
	void Collision(const Player& player);	//当たり判定
};

#endif