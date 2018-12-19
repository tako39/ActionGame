#ifndef ___Class_Zako
#define ___Class_Zako

#include "Enemy.h"

class Player;

class Zako : public Enemy {
private:
	float enemySpeed;	//敵の初期移動速度
	bool isGround;		//接地判定

public:
	Zako();
	~Zako();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	VECTOR randomPos();		//ランダムで位置決め
	int randomDir();		//ランダムで向きを決める
	float randomSpeed();	//ランダムで移動速度を決める

	void Move(float moveY, float moveX);	//移動
};

#endif