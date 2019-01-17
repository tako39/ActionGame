#include "Menu.h"
#include "DxLib.h"
#include "Stage.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Map.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Manual.h"
#include "Keyboard.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 0;	//ステージを0にする
	mPush = false;			//Mキーは押されていない状態

	player = new Player();
	map = new Map();
	bulletMgr = new BulletMgr();
	bombMgr = new BombMgr();
	manual = new Manual();
}


Menu::~Menu() {
	delete player;
	delete map;
	delete bulletMgr;
	delete bombMgr;
	delete manual;
}

//更新
void Menu::Update() {
	if (GetKey(KEY_INPUT_G) != 0) {	//Gキーが押されていたらシーンをゲーム画面に変更
		mSceneChanger->ChangeScene(eScene_Game);
	}
	if (GetKey(KEY_INPUT_M) == 1) {	//Mキーを押されていたらManual状態を変更
		mPush = !mPush;
	}
	if (mPush) {					//Mキーが押されている状態のときのみManualを表示
		manual->Update();
		return;
	}

	player->Update(*bulletMgr, *bombMgr);
	map->Update();
	bulletMgr->Update(*player);
	bombMgr->Update();
	bombMgr->DeleteBombAll();
}

//描画
void Menu::Draw() {
	map->Draw(*player);
	player->Draw();
	bulletMgr->Draw(*player);
	bombMgr->Draw(*player);
	if(mPush) manual->Draw();
}
