#include "DxLib.h"
#include "Manual.h"
#include "Game.h"
#include "Menu.h"
#include "Result.h"
#include "SceneMgr.h"

int SceneMgr::nowStage = 0;

SceneMgr::SceneMgr() : mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Menu(this);
}

SceneMgr::~SceneMgr() {

}

//�X�V
void SceneMgr::Update() {
	if (mNextScene != eScene_None) {  //���̃V�[�����Z�b�g����Ă�����
		delete mScene;
		switch (mNextScene) {  //�V�[���ɂ���ď����𕪊�
		case eScene_Menu:
			mScene = (BaseScene*) new Menu(this);		//���j���[���
			break;
		case eScene_Game:
			mScene = (BaseScene*) new Game(this);		//�Q�[�����
			break;
		case eScene_Manual:
			mScene = (BaseScene*) new Manual(this);		//�Q�[���������
			break;
		case eScene_Result:
			mScene = (BaseScene*) new Result(this);		//���ʕ\�����
		}
		mNextScene = eScene_None;  //���̃V�[�������N���A
	}

	mScene->Update();  //�V�[���̍X�V
}

//�`��
void SceneMgr::Draw() {
	mScene->Draw();  //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;  //���̃V�[�����Z�b�g����
}
