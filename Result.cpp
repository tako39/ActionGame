#include "Result.h"
#include "Keyboard.h"

Result::Result(ISceneChanger* changer) : BaseScene(changer) {

}

Result::~Result() {

}

void Result::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {  //�X�y�[�X�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);  //�V�[�������j���[��ʂɕύX
	}
}

void Result::Draw() {

}