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

	PlaySoundMem(bossStageSound, DX_PLAYTYPE_LOOP);	//BGM

	bossFriendMgr = new EnemyMgr();

	SceneMgr::nowStage = 2;		//�X�e�[�W��2�ɂ���
	frameCount = 0;				//�t���[���J�E���g�̏�����
}

BossStage::~BossStage() {
	delete bossFriendMgr;
	StopSoundMem(bossStageSound);
}

void BossStage::Update(Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr, VECTOR bossPos) {
	if (Boss::isAction_Create) {							//�{�X�����Ԃ𐶐�����Ƃ�
		bossPos.y -= CHIP_SIZE * 1.0f;						//�{�X�̓���ɐ���
		bossFriendMgr->AddEnemy(ENEMY_ZAKO, 5, bossPos);	//5�C����
		Boss::isAction_Create = false;
	}

	player.HitEnemy(*bossFriendMgr);					//�v���C���[�̃{�X�̒��ԂƂ̐ڐG
	bossFriendMgr->Update(player, bulletMgr, bombMgr);	//�{�X�̒��Ԃ̍X�V
}

void BossStage::Draw(const Player& player) {
	bossFriendMgr->Draw(player);						//�{�X�̒��Ԃ̕`��
}

//�{�X�X�e�[�W�̓���
bool BossStage::StageStart() {
	if (frameCount > 180) return false;		//�J�n3�b�Ԃ����`�悷��
	frameCount++;
	DrawGraph(0, 0, bossStageGraphic, TRUE);
	return true;
}