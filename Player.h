#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class Player :  public Object {
private:
	//初期位置
	const VECTOR firstPos[1] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

	int punchGraphic;  //パンチの画像
	double degree = 0.0f;  //パンチの周期
	bool is_punch; //パンチしているか

public:
	Player();
	~Player();

	void Update();
	void Draw();

	void Move(float moveY, float moveX);  //移動
	void Attack();  //攻撃
};

#endif