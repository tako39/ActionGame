#include "Config.h"
#include "DxLib.h"
#include "Keyboard.h"

Config::Config(ISceneChanger* changer) : BaseScene(changer) {
	
}

Config::~Config() {

}

//更新
void Config::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Config::Draw() {
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}
