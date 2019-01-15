#ifndef ___Class_Display
#define ___Class_Display

#include "Task.h"
#include "Define.h"
#include "DxLib.h"

class Player;
class EnemyMgr;

class Display : public Task {
private:
	int hpGreeen;	//緑色のHPの画像
	int hpOrange;	//橙色のHPの画像
	int hpRed;		//赤色のHPの画像

public:
	Display();
	~Display();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void DrawHp(VECTOR hpPos, int hitPoint, int maxHp);	//HPバーの描画
};

#endif