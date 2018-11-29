#include "Config.h"

Config::Config(ISceneChanger* changer) : BaseScene(changer) {

}

//初期化
void Config::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Config.png");    //画像のロード
}

//更新
void Config::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Config::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}
