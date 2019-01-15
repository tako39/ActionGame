#include "GameOver.h"
#include "Keyboard.h"

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer) {
	gameoverGraphic = LoadGraph("image/gameover.png");
	gameoverSound = LoadSoundMem("sound/gameover.mp3");
	PlaySoundMem(gameoverSound, DX_PLAYTYPE_LOOP);
}

GameOver::~GameOver() {
	StopSoundMem(gameoverSound);
}

void GameOver::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //スペースキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);  //シーンをメニュー画面に変更
	}
}

void GameOver::Draw() {
	DrawGraph(0, 0, gameoverGraphic, TRUE);
}