#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"
#include "BulletMgr.h"

int Game::nowStage = 0; //現在のステージ

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//初期化
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

//更新
void Game::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	player->Update(*enemyMgr);
	if (GetKey(KEY_INPUT_S) == 1) {
		bulletMgr->Shot(*player);
	}
	map->Update(*player);
	bulletMgr->Update(*player);
	enemyMgr->Update(*player, *bulletMgr);
}

//描画
void Game::Draw() {
	map->Draw();
	player->Draw();
	bulletMgr->Draw(*player);
	enemyMgr->Draw(*player);
}
