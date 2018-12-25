#ifndef ___Class_Display
#define ___Class_Display

#include "Task.h"

class Player;

class Display : public Task {
private:
	int hpGreeen;	//緑色のHPの画像
	int hpOrange;	//橙色のHPの画像
	int hpRed;		//赤色のHPの画像

public:
	static int Score;	//ゲームのスコア

	Display();
	~Display();

	void Update();
	void Draw() {};
	void Draw(const Player& player);
};

#endif