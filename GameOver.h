#ifndef ___Class_GameOver
#define ___Class_GameOver

#include "BaseScene.h"

//�Q�[���I�[�o�[�̉�ʃN���X
class GameOver : public BaseScene {
private:
	int gameoverGraphic;	//�Q�[���I�[�o�[���
	int gameoverSound;		//�Q�[���I�[�o�[�̉�

public:
	GameOver(ISceneChanger* changer);
	~GameOver();

	void Update();
	void Draw();
};

#endif