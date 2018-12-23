#include "Manual.h"
#include "DxLib.h"
#include "Keyboard.h"

Manual::Manual(ISceneChanger* changer) : BaseScene(changer) {
	
}

Manual::~Manual() {

}

//更新
void Manual::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Manual::Draw() {
	//DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
	//DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}
