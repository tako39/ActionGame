#ifndef ___Class_Bullet
#define ___Class_Bullet

#include "Object.h"
#include "DxLib.h"

class Player;

//�e�̃N���X
class Bullet : public Object {
private:
	int bulletGraphic;	//�e�̉摜
	bool init;	//������

	float totalMove;	//���ړ�����

public:
	Bullet(const Player& player);
	~Bullet();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void HitWall();	//�e���ǂɓ����������̏���
};

#endif