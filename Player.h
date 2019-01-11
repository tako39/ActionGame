#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class EnemyMgr;

class Player :  public Object {
private:
	//初期位置
	const VECTOR firstPos[STAGE_NUM] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0f),
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0f),
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0f),
	};

	int jumpSound;		//ジャンプしたときの音
	int damageSound;	//ダメージを受けたときの音
	int punchSound;		//パンチしたときの音

	int punchGraphic_R;		//パンチの画像
	int punchGraphic_L;
	bool isPunch;			//パンチしているか
	int punchDir;			//向き
	float degree = 0.0f;	//周期
	VECTOR punchPos;		//位置
	VECTOR punchMove;		//移動量

	bool damaged;			//ダメージを受けているか
	int flashCount;			//点滅用
	int flashStartTime;		//ダメージを受けたの時間

	int hideGraphic;		//隠れているときの画像
	int isHide;				//隠れているか

public:
	static bool isFirstPunch;		//最初のパンチ

	Player();
	~Player();

	void Update();
	void Draw();

	VECTOR GetPunchPos() const { return punchPos; }		//パンチの位置の取得
	bool GetIsPunch() const { return isPunch; }			//パンチをしているか

	void Move(float moveY, float moveX);	//移動
	void Attack();		//攻撃
	void HitWall();		//パンチが壁に当たった時の処理
	void HitEnemy(const EnemyMgr& enemyMgr);	//敵に当たった時の処理

	void ResetPosition();	//位置を戻す
};

#endif