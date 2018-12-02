#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Keyboard.h"
#include "Enemy.h"

int Game::nowStage = 0; //現在のステージ

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//初期化
void Game::Initialize() {
	player = new Player();
	map = new Map();
	enemy = new Enemy(VGet(10.0f * CHIP_SIZE, 1.0f, 0.0f), DIR_LEFT);
}

void Game::Finalize() {
	delete player;
	delete map;
	delete enemy;
}

//更新
void Game::Update() {
	player->Update();
	map->Update(*player);
	enemy->Update(*player);
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Game::Draw() {
	player->Draw();
	map->Draw();
	enemy->Draw();
	//BaseScene::Draw();  //親クラスの描画メソッドを呼ぶ
	//DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
	//DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}
