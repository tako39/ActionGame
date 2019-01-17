#ifndef ___BossStage
#define ___BossStage

#include "Task.h"
#include "DxLib.h"

class EnemyMgr;
class Player;
class BulletMgr;
class BombMgr;

//ボスステージのクラス
class BossStage : public Task {
private:
	EnemyMgr *bossFriendMgr;	//ボスが生成する仲間

	int bossStageGraphic;		//ボスステージの開始画像
	int bossStageSound;			//ボスステージの音楽
	int frameCount;				//フレームのカウント

public:
	BossStage();
	~BossStage();

	void Update() {};
	void Update(Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr, VECTOR bossPos);
	void Draw() {};
	void Draw(const Player& player);

	bool StageStart();			//ボスステージ導入部分の描画用
	bool FrameCheck() {			//ボスステージ導入部分の描画中であるか
		if (frameCount > 180) return false;
		return true;
	}
};

#endif