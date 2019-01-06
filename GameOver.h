#ifndef ___Class_GameOver
#define ___Class_GameOver

#include "BaseScene.h"

class GameOver : public BaseScene {

public:
	GameOver(ISceneChanger* changer);
	~GameOver();

	void Update();
	void Draw();
};

#endif