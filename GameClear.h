#ifndef ___Class_GameClear
#define ___Class_GameClear

#include "BaseScene.h"

class GameClear : public BaseScene {
private:
	int gameclearGraphic;	//�Q�[���N���A���
	int gameclearSound;

public:
	GameClear(ISceneChanger* changer);
	~GameClear();

	void Update();
	void Draw();
};

#endif