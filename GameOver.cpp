#include "GameOver.h"
#include "Keyboard.h"

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer) {

}

GameOver::~GameOver() {

}

void GameOver::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //�X�y�[�X�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);  //�V�[�������j���[��ʂɕύX
	}
}

void GameOver::Draw() {

}