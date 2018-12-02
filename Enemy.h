#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"

class Player;

class Enemy : virtual public Object {
private:
	const int enemySpeed = 2.0f;
	bool isGround;

	VECTOR playerPos;

public:
	Enemy(VECTOR ePos, int dir);  //�ʒu:ePos, ����:dir�Őݒu
	~Enemy();

	void Update() {};
	void Update(const Player& cPlayer);
	void Draw();

	void Move(float moveY, float moveX); //�ړ�
};

#endif