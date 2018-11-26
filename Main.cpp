#include "DxLib.h"
#include "SceneMgr.h"
#include "Define.h"
#include "Keyboard.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	//��ʍX�V & ���b�Z�[�W���� & ��ʏ���
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
		UpdateKey();  //�L�[�̍X�V

		sceneMgr.Update();  //�X�V
		sceneMgr.Draw();    //�`��

	}

	sceneMgr.Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}