#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"
#include "Define.h"

class Player;

class Enemy : public Object {
private:
	bool isGround;  //�ڒn����
	VECTOR playerPos;  //�v���C���[�̈ʒu

public:
	Enemy();
	~Enemy();

	void Update() {};
	void Update(const Player& cPlayer);
	void Draw();

	void Move(float moveY, float moveX);  //�ړ�
	void Collision(const Player& player);  //�����蔻��
};

#endif