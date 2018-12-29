#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class EnemyMgr;

class Player :  public Object {
private:
	//初期位置
	const VECTOR firstPos[2] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

	int punchGraphic_R;		//パンチの画像
	int punchGraphic_L;
	bool isPunch;			//パンチしているか
	int punchDir;			//向き
	float degree = 0.0f;	//周期
	VECTOR punchPos;		//位置
	VECTOR punchMove;		//移動量
	VECTOR screenPos;		//スクリーン上の位置

	bool damaged;			//ダメージを受けているか
	int flashCount;			//点滅用
	int flashStartTime;		//ダメージを受けたの時間

	int hideGraphic;		//隠れているときの画像
	int isHide;				//隠れているか

public:
	Player();
	~Player();

	void Update();
	void Draw();

	VECTOR GetPunchPos() const { return punchPos; }		//パンチの位置の取得
	bool GetIsPunch() const { return isPunch; }			//パンチをしているか
	VECTOR GetScreenPos() const { return screenPos; }	//スクリーン上での位置の取得

	void Move(float moveY, float moveX);	//移動
	void Attack();		//攻撃
	void HitWall();		//パンチが壁に当たった時の処理
	void HitEnemy(const EnemyMgr& enemyMgr);	//敵に当たった時の処理
};

#endif