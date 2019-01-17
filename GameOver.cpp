#include "GameOver.h"
#include "Keyboard.h"

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer) {
	gameoverGraphic = LoadGraph("image/gameover.png");
	gameoverSound = LoadSoundMem("sound/gameover.mp3");

	PlaySoundMem(gameoverSound, DX_PLAYTYPE_LOOP);	//BGM
}

GameOver::~GameOver() {
	StopSoundMem(gameoverSound);
}

void GameOver::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //�X�y�[�X�L�[�������ꂽ�烁�j���[��ʂɕύX
		mSceneChanger->ChangeScene(eScene_Menu);
	}
}

void GameOver::Draw() {
	DrawGraph(0, 0, gameoverGraphic, TRUE);
}