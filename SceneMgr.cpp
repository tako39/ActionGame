#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "SceneMgr.h"

int SceneMgr::nowStage = 0;

SceneMgr::SceneMgr() : mNextScene(eScene_None) //次のシーン管理変数
{
	mScene = (BaseScene*) new Menu(this);
}

SceneMgr::~SceneMgr() {

}

//更新
void SceneMgr::Update() {
	if (mNextScene != eScene_None) {  //次のシーンがセットされていたら
		delete mScene;
		switch (mNextScene) {  //シーンによって処理を分岐
		case eScene_Menu:
			mScene = (BaseScene*) new Menu(this);    //メニュー画面
			break;
		case eScene_Game:
			mScene = (BaseScene*) new Game(this);    //ゲーム画面
			break;
		case eScene_Config:
			mScene = (BaseScene*) new Config(this);  //設定画面
			break;
		}
		mNextScene = eScene_None;  //次のシーン情報をクリア
		//mScene->Initialize();  //シーンを初期化
	}

	mScene->Update();  //シーンの更新
}

//描画
void SceneMgr::Draw() {
	mScene->Draw();  //シーンの描画
}

// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;  //次のシーンをセットする
}
