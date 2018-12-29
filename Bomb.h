#ifndef ___Class_Bomb
#define ___Class_Bomb

#include "Object.h"

class Player;

class Bomb : public Object {
private:
	int setTime;		//���e��ݒu��������
	int bombGraphic;	//���e�̉摜

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