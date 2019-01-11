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
}

//�X�V
void Game::Update() {
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

	player->Update();
	player->HitEnemy(*enemyMgr);
	//�e�𔭎�
	if (GetKey(KEY_INPUT_S) == 1) {
		bulletMgr->Shot(*player);
	}
	//���e��ݒu
	if (GetKey(KEY_INPUT_B) == 1) {
		bombMgr->BombSet(*player);
	}
	map->Update(*player);
	bulletMgr->Update(*player);
	bombMgr->Update();
	enemyMgr->Update(*player, *bulletMgr, *bombMgr);
	display->Update();

	//�G���S�ē|���ꂽ�Ƃ�
	if (enemyMgr->IsNoEnemy()) {
		if (enemyPhase == 0) {
			delete enemyMgr;
			enemyMgr = new EnemyMgr(ENEMY_ZAKO, 1);
			enemyPhase++;
		}
		else if (enemyPhase == 1) {
			delete enemyMgr;
			enemyMgr = new EnemyMgr(ENEMY_TALL, 1);
			enemyPhase++;
		}
		else if (enemyPhase == 2) {
			delete enemyMgr;
			enemyMgr = new EnemyMgr(ENEMY_BIG, 1);
			enemyPhase++;
		}
		else if (enemyPhase == 3) {
			delete enemyMgr;
			SceneMgr::nowStage++;
			player->ResetPosition();
			enemyMgr = new EnemyMgr(ENEMY_BOSS, 1);
			enemyPhase++;
		}
		else if (enemyPhase == 4) {
			mSceneChanger->ChangeScene(eScene_GameClear);	//�V�[�����N���A��ʂɕύX
		}
	}
}

//�`��
void Game::Draw() {
	map->Draw();
	player->Draw();
	bulletMgr->Draw(*player);
	enemyMgr->Draw(*player);
	bombMgr->Draw(*player);
	display->Draw(*player);
	if(mPush) manual->Draw();
}
