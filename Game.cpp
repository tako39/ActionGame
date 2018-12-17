#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"

int Game::nowStage = 0; //現在のステージ

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//初期化
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

//更新
void Game::Update() {
	player->Update(*enemyMgr);
	map->Update(*player);
	enemyMgr->Update(*player);
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Game::Draw() {
	map->Draw();
	player->Draw();
	enemyMgr->Draw();
}
