#include "BossStage.h"
#include "SceneMgr.h"
#include "EnemyMgr.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Enemy_Boss.h"

BossStage::BossStage() {
	bossStageGraphic = LoadGraph("image/bossStage.png");
	bossStageSound = LoadSoundMem("sound/bossStageBgm.mp3");
	PlaySoundMem(bossStageSound, DX_PLAYTYPE_LOOP);
	SceneMgr::nowStage = 2;
	bossFriendMgr = new EnemyMgr();
	frameCount = 0;
}

BossStage::~BossStage() {
	delete bossFriendMgr;
	StopSoundMem(bossStageSound);
}

void BossStage::Update(Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr, VECTOR bossPos) {
	if (Boss::isAction_Create) {	//ボスの仲間の生成
		bossPos.y -= CHIP_SIZE * 1.0f;
		bossFriendMgr->AddEnemy(ENEMY_ZAKO, 5, bossPos);	//5匹生成
		Boss::isAction_Create = false;
	}

	player.HitEnemy(*bossFriendMgr);	//プレイヤーのボスの仲間との接触
	bossFriendMgr->Update(player, bulletMgr, bombMgr);	//ボスの仲間の更新
}

void BossStage::Draw(const Player& player) {
	bossFriendMgr->Draw(player);
}

bool BossStage::StageStart() {
	if (frameCount > 180) return false;
	frameCount++;
	DrawGraph(0, 0, bossStageGraphic, TRUE);
	return true;
}