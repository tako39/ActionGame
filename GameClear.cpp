#include "GameClear.h"
#include "Keyboard.h"

GameClear::GameClear(ISceneChanger* changer) : BaseScene(changer) {

}

GameClear::~GameClear() {

}

void GameClear::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //スペースキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);  //シーンをメニュー画面に変更
	}
}

void GameClear::Draw() {

}