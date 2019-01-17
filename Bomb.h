#ifndef ___Class_Bomb
#define ___Class_Bomb

#include "Object.h"

class Player;

//���e�̃N���X
class Bomb : public Object {
private:
	int bombSound;				//���e�����������Ƃ��̉�

	int setTime;				//���e��ݒu��������	
	int bombGraphic_Count1;		//�������ĂȂ����e
	int bombGraphic_Count2;		//�����������Ȕ��e
	int bombGraphic_Count3;		//�_�ł��Ă��锚�e(�ʏ�)
	int bombGraphic_Red;		//�_�ł��Ă��锚�e(��)
	int explosionGraphic;		//�����̃G�t�F�N�g�摜

public:
	Bomb(const Player& player);
	~Bomb();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);	//�d�͗����ł̈ړ�
	int GetSetTime() { return setTime; }	//�Z�b�g�������Ԃ̎擾
};

#endif