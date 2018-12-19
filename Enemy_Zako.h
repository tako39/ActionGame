#ifndef ___Class_Zako
#define ___Class_Zako

#include "Enemy.h"

class Player;

class Zako : public Enemy {
private:
	float enemySpeed;	//�G�̏����ړ����x
	bool isGround;		//�ڒn����

public:
	Zako();
	~Zako();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	VECTOR randomPos();		//�����_���ňʒu����
	int randomDir();		//�����_���Ō��������߂�
	float randomSpeed();	//�����_���ňړ����x�����߂�

	void Move(float moveY, float moveX);	//�ړ�
};

#endif