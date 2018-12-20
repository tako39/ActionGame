#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"
#include "BulletMgr.h"
#include "Display.h"
#include "SceneMgr.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 1;	//ステージ1から始める
	player = new Player();
	map = new Map();
	enemyMgr = new EnemyMgr();
	bulletMgr = new BulletMgr();
	display = new Display();
}

Game::~Game() {
	delete player;
	delete map;
	delete enemyMgr;
	delete bulletMgr;
	delete display;
}

//更新
void Game::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	player->Update();
	player->HitEnemy(*enemyMgr);
	if (GetKey(KEY_INPUT_S) == 1) {
		bulletMgr->Shot(*player);
	}
	map->Update(*player);
	bulletMgr->Update(*player);
	enemyMgr->Update(*player, *bulletMgr);
	display->Update();
}

//描画
void Game::Draw() {
	map->Draw();
	player->Draw();
	bulletMgr->Draw(*player);
	enemyMgr->Draw(*player);
	display->Draw();
}
