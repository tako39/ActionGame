#ifndef ___Class_Map
#define ___Class_Map

#include "Task.h"
#include "DxLib.h"

class Player;

class Map : public Task {
private:
	int back_Graphic;		//背景の画像
	int ground_Graphic;		//地面の画像

	int image_Alpha[26];	//文字の画像

	int arrowGraphic_r;		//矢印の画像
	int arrowGraphic_l;

	VECTOR playerPos;   //プレイヤーの位置

public:
	Map();
	~Map();

	void Update() {};
	void Update(const Player& cPlayer); //更新
	void Draw();   //描画

	static int GetMap(int y, int x);  //map[y][x]の値の取得
	static int GetMapChip(float y, float x);  //位置(x, y)に該当するマップチップの値の取得
};

#endif