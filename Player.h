#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class Player : virtual public Object {
private:
	//初期位置
	const VECTOR firstPos[1] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

public:
	Player();
	~Player();

	void Update();
	void Draw();

	void Move(float moveY, float moveX); //移動
};

#endif