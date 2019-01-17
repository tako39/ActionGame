#ifndef ___Class_Boss
#define ___Class_Boss

#include "Enemy.h"
#include "Define.h"

//Enemy_Bossを生成するクラス
class Boss : public Enemy {
private:
	int fallSound;		//落ちるときの音
	int createSound;	//敵を増やすときの音

	int frameCount;	//カウント

	//Action_Dashで使用
	bool isAction_Dash;	//Action_Dash中か
	int sandGprahic_r;	//砂煙の画像
	int sandGraphic_l;
	int flushCount;

	//Action_Jumpで使用
	const VECTOR upPos[5] = {	//上昇する位置(0~4の4つ)
		VGet( 5 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(10 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(15 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(20 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(25 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
	};
	bool isAction_Jump;		//Action_Jump中か
	bool firstAction_Jump;		//Action_Jump開始時か
	float diff_x, diff_y;	//posからupPosまでの差
	bool isRise;			//上昇中か
	bool isFall;			//落下中か
	int fallStep;			//落下の段階(0~4)
	int moveDirect;			//移動方向

	//Action_Waitで使用
	bool isAction_Wait;		//行動後の待機
	int waitCount;			//待機フレームのカウント

public:
	Boss();
	~Boss();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Action_Dash();	//走って移動
	void Action_Jump();	//ジャンプで移動
	void Action_Create();	//仲間の生成
	bool Action_Wait();	//待機

	//Action_Createで使用
	static bool isAction_Create;	//ActionCreate中か
};

#endif