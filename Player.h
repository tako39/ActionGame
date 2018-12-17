#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class EnemyMgr;

class Player :  public Object {
private:
	//初期位置
	const VECTOR firstPos[1] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

	int punchGraphic;		//画像
	bool isPunch;			//パンチしているか
	int punchDir;			//向き
	float degree = 0.0f;	//周期
	VECTOR punchPos;		//位置
	VECTOR punchMove;		//移動量

public:
	Player();
	~Player();

	void Update() {};
	void Update(const EnemyMgr& enemymgr);
	void Draw();

	VECTOR GetPunchPos() const { return punchPos; };
	bool GetIsPunch() const { return isPunch; };

	void Move(float moveY, float moveX);  //移動
	void Attack();  //攻撃
	void SinkToWall();  //壁へのめり込み
};

#endif