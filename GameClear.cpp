#include "GameClear.h"
#include "Keyboard.h"

GameClear::GameClear(ISceneChanger* changer) : BaseScene(changer) {
	gameclearGraphic = LoadGraph("image/gameclear.png");
	gameclearSound = LoadSoundMem("sound/gameclear.mp3");

	PlaySoundMem(gameclearSound, DX_PLAYTYPE_LOOP);	//BGM
}

GameClear::~GameClear() {
	StopSoundMem(gameclearSound);
}

void GameClear::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //�X�y�[�X�L�[��������s���烁�j���[��ʂɕύX
		mSceneChanger->ChangeScene(eScene_Menu);
	}
}

void GameClear::Draw() {
	DrawGraph(0, 0, gameclearGraphic, TRUE);
}