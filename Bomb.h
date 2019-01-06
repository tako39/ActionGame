#ifndef ___Class_Bomb
#define ___Class_Bomb

#include "Object.h"

class Player;

class Bomb : public Object {
private:
	int bombSound;	//���e�����������Ƃ��̉�

	int setTime;			//���e��ݒu��������	
	int bombGraphic_Count1;	//���e�̉摜
	int bombGraphic_Count2;
	int bombGraphic_Count3;
	int bombGraphic_Red;
	int explosionGraphic;		//�����摜

public:
	Bomb(const Player& player);
	~Bomb();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);
	int GetSetTime() { return setTime; }
};

#endif