#ifndef ___Class_Manual
#define ___Class_Manual

#include "BaseScene.h"

//�ݒ��ʃN���X
class Manual : public BaseScene {

public:
	Manual(ISceneChanger* changer);
	~Manual();

	void Update() override;      //�X�V�������I�[�o�[���C�h�B
	void Draw() override;        //�`�揈�����I�[�o�[���C�h�B
};

#endif