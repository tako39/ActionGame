#ifndef ___Class_Config
#define ___Class_Config

#include "BaseScene.h"

//�ݒ��ʃN���X
class Config : public BaseScene {

public:
	Config(ISceneChanger* changer);
	~Config();
	void Update() override;      //�X�V�������I�[�o�[���C�h�B
	void Draw() override;        //�`�揈�����I�[�o�[���C�h�B

};

#endif