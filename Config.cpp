#include "Config.h"
#include "DxLib.h"
#include "Keyboard.h"

Config::Config(ISceneChanger* changer) : BaseScene(changer) {
	
}

Config::~Config() {

}

//�X�V
void Config::Update() {
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Config::Draw() {
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}
