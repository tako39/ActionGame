#include "DxLib.h"
#include "SceneMgr.h"
#include "Define.h"
#include "Keyboard.h"
#include "Frame.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr sceneMgr;
	Frame frame;

	sceneMgr.Initialize();

	//��ʍX�V & ���b�Z�[�W���� & ��ʏ���
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
		frame.Update();  //�t���[���̍X�V

		UpdateKey();  //�L�[�̍X�V

		sceneMgr.Update();  //�V�[���̍X�V
		sceneMgr.Draw();    //�V�[���̕`��


		frame.Wait();  //�ҋ@
	}

	sceneMgr.Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}