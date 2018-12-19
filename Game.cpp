#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"
#include "BulletMgr.h"

int Game::nowStage = 0; //���݂̃X�e�[�W

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//������
void Game::Initialize() {
	player = new Player();
	map = new Map();
	enemyMgr = new EnemyMgr();
	bulletMgr = new BulletMgr();
}

void Game::Finalize() {
	delete player;
	delete map;
	delete enemyMgr;
	delete bulletMgr;
}

//�X�V
void Game::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	player->Update(*enemyMgr);
	if (GetKey(KEY_INPUT_S) == 1) {
		bulletMgr->Shot(*player);
	}
	map->Update(*player);
	bulletMgr->Update(*player);
	enemyMgr->Update(*player, *bulletMgr);
}

//�`��
void Game::Draw() {
	map->Draw();
	player->Draw();
	bulletMgr->Draw(*player);
	enemyMgr->Draw(*player);
}
