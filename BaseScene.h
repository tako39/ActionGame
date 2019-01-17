#ifndef ___Class_BaseScene
#define ___Class_BaseScene

#include "Task.h"
#include "ISceneChanger.h"

//�V�[���̊��N���X�B
class BaseScene : public Task {
protected:
	ISceneChanger* mSceneChanger;	//�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene();

	virtual void Update() {};
	virtual void Draw() {};
};

#endif