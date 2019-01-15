#ifndef ___Class_Display
#define ___Class_Display

#include "Task.h"
#include "Define.h"
#include "DxLib.h"

class Player;
class EnemyMgr;

class Display : public Task {
private:
	int hpGreeen;	//�ΐF��HP�̉摜
	int hpOrange;	//��F��HP�̉摜
	int hpRed;		//�ԐF��HP�̉摜

public:
	Display();
	~Display();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void DrawHp(VECTOR hpPos, int hitPoint, int maxHp);	//HP�o�[�̕`��
};

#endif