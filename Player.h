#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "DxLib.h"
#include "Define.h"
#include "Game.h"
#include "Map.h"
#include "Print.h"
#include "Keyboard.h"

class Map;

class Player : public Object {
private:
	const Map &map;

	float ver_Speed;  //垂直方向の移動量
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

	void Move(float moveY, float moveX); //移動
	int MapCollision(float Y, float X, float &moveY, float &moveX); //当たり判定
};

#endif