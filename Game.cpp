#include "Game.h"

int Game::nowStage = 0; //現在のステージ

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//初期化
void Game::Initialize() {
	map = new Map();
	player = new Player(*map);
}

void Game::Finalize() {
	delete map;
	delete player;
}

//更新
void Game::Update() {
	map->Update();
	player->Update();
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Game::Draw() {
	map->Draw();
	player->Draw();
	//BaseScene::Draw();  //親クラスの描画メソッドを呼ぶ
	//DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
	//DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}
