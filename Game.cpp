#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include "SceneMgr.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 1;	//�X�e�[�W1����n�߂�
	enemyPhase = 0;
	player = new Player();
	map = new Map();
	enemyMgr = new EnemyMgr();
	bulletMgr = new BulletMgr();
	bombMgr = new BombMgr();
	display = new Display();
}

Game::~Game() {
	delete player;
	delete map;
	delete enemyMgr;
	delete bulletMgr;
	delete bombMgr;
	delete display;
}

//�X�V
void Game::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) {	//Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);	//�V�[�������j���[�ɕύX
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
		}
		else if (enemyPhase == 1) {
			delete enemyMgr;
			enemyMgr = new EnemyMgr(ENEMY_TALL, 1);
		}
		else if (enemyPhase == 2) {
			delete enemyMgr;
			enemyMgr = new EnemyMgr(ENEMY_BIG, 1);
		}
		else if (enemyPhase == 3) {
			delete enemyMgr;
			enemyMgr = new EnemyMgr(ENEMY_BOSS, 1);
		}
		else if (enemyPhase == 4) {
			mSceneChanger->ChangeScene(eScene_GameClear);	//�V�[�����N���A��ʂɕύX
		}
		enemyPhase++;	//���̒i�K��
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
}
