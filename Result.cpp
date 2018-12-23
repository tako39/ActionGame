#include "Result.h"
#include "Keyboard.h"

Result::Result(ISceneChanger* changer) : BaseScene(changer) {

}

Result::~Result() {

}

void Result::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //スペースキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);  //シーンをメニュー画面に変更
	}
}

void Result::Draw() {

}