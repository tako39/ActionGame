#ifndef ___Class_Zako
#define ___Class_Zako

#include "Enemy.h"

class Player;

class Zako : public Enemy {
private:
	bool isGround;		//�ڒn����

public:
	Zako();
	~Zako();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	VECTOR randomPos();	//�����_���ňʒu����
	int randomDir();	//�����_���Ō��������߂�
	void Move(float moveY, float moveX);	//�ړ�
	void Collision(const Player& player);	//�����蔻��
};

#endif