#ifndef ___Class_GameClear
#define ___Class_GameClear

#include "BaseScene.h"

//�Q�[���N���A�̉�ʃN���X
class GameClear : public BaseScene {
private:
	int gameclearGraphic;	//�Q�[���N���A���
	int gameclearSound;		//�Q�[���N���A�̉�

public:
	GameClear(ISceneChanger* changer);
	~GameClear();

	void Update();
	void Draw();
};

#endif