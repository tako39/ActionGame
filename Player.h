#ifndef ___Class_Player
#define ___Class_Player

#include "Task.h"
#include "DxLib.h"
#include "Define.h"
#include "Game.h"
#include "Map.h"
#include "Print.h"
#include "Keyboard.h"

class Map;

class Player : public Task {
private:
	const Map& map;  //mapのコピー

	int player_Graphic_R;  //右向きの画像
	int player_Graphic_L;  //左向きの画像
	
	VECTOR pos;   //位置
	VECTOR move;  //移動用
	
	float ver_Speed;  //垂直方向の移動量
	int direct;  //向き情報(1 : 右, -1 : 左)

	bool jump_Flag; //trueならジャンプ中

	//初期位置
	const VECTOR firstPos[1] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

public:
	Player(const Map& cMap);
	~Player();

	void Update();
	void Draw();

	VECTOR GetPos() const { return pos; }  //位置の取得

	void Move(float moveY, float moveX); //移動
	int MapCollision(float Y, float X, float &moveY, float &moveX); //当たり判定
};

#endif