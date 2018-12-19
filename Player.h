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
	VECTOR screenPos;		//スクリーン上の位置

	bool damaged;	//ダメージを受けているか
	bool flash;		//点滅用
	int flashStartTime;		//ダメージを受けたの時間

public:
	Player();
	~Player();

	void Update() {};
	void Update(const EnemyMgr& enemyMgr);
	void Draw();

	VECTOR GetPunchPos() const { return punchPos; }
	bool GetIsPunch() const { return isPunch; }
	VECTOR GetScreenPos() const { return screenPos; }

	void Move(float moveY, float moveX);	//移動
	void Attack();		//攻撃
	void HitWall();		//パンチが壁に当たった時の処理
	void HitEnemy(const EnemyMgr& enemyMgr);	//敵に当たった時の処理
};

#endif