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

	int damageSound;	//�_���[�W��

public:
	Enemy();
	~Enemy();

	virtual void Update() = 0;
	virtual void Update(const Player& player) {};
	virtual void Draw() = 0;
	virtual void Draw(const Player& player) {};

	void EnemyDraw(const Player& player);	//�G�̕`��
	void HpDraw();	//�̗͂̕`��

	int GetType() const { return enemyType; };	//�G�̎�ނ̎擾
	
	VECTOR randomPos(int h, int w);		//�����_���ňʒu����(h:�G�̏c��,w:�G�̉���)
	int randomDir();		//�����_���Ō��������߂�
	float randomSpeed();	//�����_���ňړ����x�����߂�

	void Move(float moveY, float moveX);	//�ړ����̏���
	void LookAhead();	//������ė����Ȃ��悤�Ɍ�����ς���

	void GroundCheck();	//�ڒn����

	void Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);	//�����蔻��
	bool CollisionPunch(const Player& player);	//�����蔻��i�p���`�j
	bool CollisionBullet(BulletMgr& bulletMgr);	//�����蔻��i�e�j
	bool CollisionBomb(BombMgr& bombMgr);		//�����蔻��i���e�j
};

#endif