#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"

int Game::nowStage = 0; //���݂̃X�e�[�W

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//������
void Game::Initialize() {
	player = new Player();
	map = new Map();
	enemyMgr = new EnemyMgr();
}

void Game::Finalize() {
	delete player;
	delete map;
	delete enemyMgr;
}

//�X�V
void Game::Update() {
	player->Update(*enemyMgr);
	map->Update(*player);
	enemyMgr->Update(*player);
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Game::Draw() {
	map->Draw();
	player->Draw();
	enemyMgr->Draw();
}
