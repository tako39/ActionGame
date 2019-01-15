#include "GameClear.h"
#include "Keyboard.h"

GameClear::GameClear(ISceneChanger* changer) : BaseScene(changer) {
	gameclearGraphic = LoadGraph("image/gameclear.png");
	gameclearSound = LoadSoundMem("sound/gameclear.mp3");
	PlaySoundMem(gameclearSound, DX_PLAYTYPE_LOOP);
}

GameClear::~GameClear() {
	StopSoundMem(gameclearSound);
}

void GameClear::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //スペースキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);  //シーンをメニュー画面に変更
	}
}

void GameClear::Draw() {
	DrawGraph(0, 0, gameclearGraphic, TRUE);
}