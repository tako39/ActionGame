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
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //�X�y�[�X�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);  //�V�[�������j���[��ʂɕύX
	}
}

void GameOver::Draw() {
	DrawGraph(0, 0, gameoverGraphic, TRUE);
}