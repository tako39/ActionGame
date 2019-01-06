#include "GameOver.h"
#include "Keyboard.h"

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer) {

}

GameOver::~GameOver() {

}

void GameOver::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //スペースキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);  //シーンをメニュー画面に変更
	}
}

void GameOver::Draw() {

}