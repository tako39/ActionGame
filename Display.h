#ifndef ___Class_Display
#define ___Class_Display

#include "Task.h"

class Player;

class Display : public Task {
private:
	int hpGreeen;	//�ΐF��HP�̉摜
	int hpOrange;	//��F��HP�̉摜
	int hpRed;		//�ԐF��HP�̉摜

public:
	static int Score;	//�Q�[���̃X�R�A

	Display();
	~Display();

	void Update();
	void Draw() {};
	void Draw(const Player& player);
};

#endif