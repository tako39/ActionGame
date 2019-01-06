#include "GameClear.h"
#include "Keyboard.h"

GameClear::GameClear(ISceneChanger* changer) : BaseScene(changer) {

}

GameClear::~GameClear() {

}

void GameClear::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //�X�y�[�X�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);  //�V�[�������j���[��ʂɕύX
	}
}

void GameClear::Draw() {

}