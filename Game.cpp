#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include "Manual.h"
#include "SceneMgr.h"
#include "Enemy_Boss.h"
#include "BossStage.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 1;	//�X�e�[�W1����n�߂�
	enemyPhase = 0;
	mPush = false;
	player = new Player();
	map = new Map();
	enemyMgr = new EnemyMgr();
	bulletMgr = new BulletMgr();
	bombMgr = new BombMgr();
	display = new Display();
	manual = new Manual();
}

Game::~Game() {
	delete player;
	delete map;
	delete enemyMgr;
	delete bulletMgr;
	delete bombMgr;
	delete display;
	delete manual;
	delete bossStage;
}

//�X�V
void Game::Update() {
	if (!player->GetExist()) {	//�v���C���[���|���ꂽ��
		mSceneChanger->ChangeScene(eScene_GameOver);	//�V�[�����Q�[���I�[�o�[�ɕύX
	}
	if (GetKey(KEY_INPUT_ESCAPE) != 0) {	//Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);	//�V�[�������j���[�ɕύX
	}
	if (GetKey(KEY_INPUT_M) == 1) {	//m�������ꂽ��ԂȂ�Manual��\��
		mPush = !mPush;
	}
	if (mPush) {	//Manual�\�����͉����o���Ȃ�
		manual->Update();
		return;
	}
	if (SceneMgr::nowStage == 2) {	//�{�X�X�e�[�W�̎�
		if (bossStage->FrameCheck()) {	//�ŏ���3�b�Ԃ͉����ł��Ȃ�
			return;	
		}
	}

	player->Update(*bulletMgr, *bombMgr);	//�v���C���[�̍X�V
	player->HitEnemy(*enemyMgr);			//�v���C���[�̓G�Ƃ̐ڐG

	map->Update();	//�}�b�v�̍X�V	

	bulletMgr->Update(*player);		//�e�̍X�V
	bombMgr->Update();				//���e�̍X�V
	enemyMgr->Update(*player, *bulletMgr, *bombMgr);	//�G�̍X�V	
	
	//�{�X�X�e�[�W�݂̂̍X�V
	if (SceneMgr::nowStage == 2) {
		if (enemyMgr->IsExist(0)) {	//�{�X�������Ă���Ȃ�
			bossStage->Update(*player, *bulletMgr, *bombMgr, enemyMgr->GetEnemyPos(0));	//�{�X�̒��Ԃ̍X�V
		}
	}
	
	bombMgr->DeleteBombAll();	//�����������e�̏���

	display->Update();		//HP�o�[�̍X�V
	ChangeEnemyPhase();		//�G�̐����i�K�̕ύX
}

void Game::ChangeEnemyPhase() {
	if (!enemyMgr->IsNoEnemy()) return;	//�G���܂����݂���Ȃ�

	if (enemyPhase == 0) {
		enemyMgr = new EnemyMgr(ENEMY_ZAKO, 12);
		enemyPhase++;
	}
	else if (enemyPhase == 1) {
		enemyMgr = new EnemyMgr(ENEMY_TALL, 10);
		enemyPhase++;
	}
	else if (enemyPhase == 2) {
		enemyMgr = new EnemyMgr(ENEMY_BIG, 8);
		enemyPhase++;
	}
	else if (enemyPhase == 3) {
		bossStage = new BossStage();
		enemyMgr = new EnemyMgr(ENEMY_BOSS, 1);
		player->ResetPosition();
		enemyPhase++;
	}
	else if (enemyPhase == 4) {
		mSceneChanger->ChangeScene(eScene_GameClear);	//�V�[�����N���A��ʂɕύX
	}
}

//�`��
void Game::Draw() {
	if (SceneMgr::nowStage == 2) {	//�{�X�X�e�[�W�̎�
		if (bossStage->StageStart()) {	//�ŏ���3�b�Ԃ̂ݕ`��
			return;
		}
	}
	map->Draw(*player);
	player->Draw();
	bulletMgr->Draw(*player);
	enemyMgr->Draw(*player);
	if (SceneMgr::nowStage == 2) {	//�{�X�X�e�[�W�̂�
		bossStage->Draw(*player);	//�{�X�̒��Ԃ̕`��
	}
	bombMgr->Draw(*player);
	display->Draw(*player);
	if (mPush) manual->Draw();
}
