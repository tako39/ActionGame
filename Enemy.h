#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"

class Player;
class BulletMgr;
class BombMgr;

class Enemy : public Object {
protected:
	int enemyType;		//�G�̎��

	float enemySpeed;	//�G�̏����ړ����x
	bool isGround;		//�ڒn����

public:
	Enemy();
	~Enemy();

	virtual void Update() = 0;
	virtual void Update(const Player& player) {};
	virtual void Draw() = 0;
	virtual void Draw(const Player& player) {};
	virtual void Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {};

	void EnemyDraw(const Player& player);	//�G�̕`��

	int GetType() const { return enemyType; };	//�G�̎�ނ̎擾
	
	VECTOR randomPos(int h, int w);		//�����_���ňʒu����(h:�G�̏c��,w:�G�̉���)
	int randomDir();		//�����_���Ō��������߂�
	float randomSpeed();	//�����_���ňړ����x�����߂�
};

#endif