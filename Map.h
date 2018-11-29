#ifndef ___Class_Map
#define ___Class_Map

#include "Task.h"
#include "Define.h"
#include "Game.h"
#include "DxLib.h"
#include "Stage.h"

class Map : public Task {

private:
	int back_Graphic;   //背景の画像
	int ground_Graphic; //地面の画像

public:
	Map();
	~Map();

	void Update(); //更新
	void Draw();   //描画

	int GetMap(int y, int x) const;  //map[y][x]の値の取得
	int GetMapChip(float y, float x) const;  //位置(x, y)に該当するマップチップの値の取得

};

#endif