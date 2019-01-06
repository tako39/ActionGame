#include "Menu.h"
#include "DxLib.h"
#include "Stage.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Map.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Keyboard.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 0;	//ステージ0にする

	player = new Player();
	map = new Map();
	bulletMgr = new BulletMgr();
	bombMgr = new BombMgr();
}


Menu::~Menu() {
	delete player;
	delete map;
	delete bulletMgr;
	delete bombMgr;
}

//更新
void Menu::Update() {
	if (CheckHitKey(KEY_INPUT_G) != 0) {  //Gキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Game);  //シーンをゲーム画面に変更
	}
	if (CheckHitKey(KEY_INPUT_M) != 0) {  //Cキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Manual);  //シーンをゲーム説明画面に変更
	}
	player->Update();
	if (GetKey(KEY_INPUT_S) == 1) {
		bulletMgr->Shot(*player);
	}
	if (GetKey(KEY_INPUT_B) == 1) {
		bombMgr->BombSet(*player);
	}
	map->Update(*player);
	bulletMgr->Update(*player);
	bombMgr->Update();
	bombMgr->DeleteBombAll();
}

//描画
void Menu::Draw() {
	map->Draw();
	player->Draw();
	bulletMgr->Draw(*player);
	bombMgr->Draw(*player);
	//DrawString(0, 0, "Gキーを押すとゲーム開始、Mキーを押すとゲーム説明", GetColor(255, 0, 0));
}
