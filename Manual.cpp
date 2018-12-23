#include "Manual.h"
#include "DxLib.h"
#include "Keyboard.h"

Manual::Manual(ISceneChanger* changer) : BaseScene(changer) {
	
}

Manual::~Manual() {

}

//�X�V
void Manual::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Manual::Draw() {
	//DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}
