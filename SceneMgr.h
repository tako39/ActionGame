#ifndef ___Class_SceneMgr
#define ___Class_SceneMgr

#include "ISceneChanger.h"
#include "BaseScene.h"

//�V�[���̕ύX�A���݂̃X�e�[�W�����L������N���X
class SceneMgr : public ISceneChanger, Task {
private:
	int selectSound;		//�I����

	BaseScene* mScene;		//�V�[���Ǘ��ϐ�
	eScene mNextScene;		//���̃V�[���Ǘ��ϐ�

public:
	static int nowStage;	//���݂̃X�e�[�W

	SceneMgr();
	~SceneMgr();

	void Update();	//�X�V
	void Draw();	//�`��

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene);
};

#endif