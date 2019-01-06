#ifndef ___Class_GameClear
#define ___Class_GameClear

#include "BaseScene.h"

class GameClear : public BaseScene {

public:
	GameClear(ISceneChanger* changer);
	~GameClear();

	void Update();
	void Draw();
};

#endif#pragma once
