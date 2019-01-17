#ifndef ___Class_GameOver
#define ___Class_GameOver

#include "BaseScene.h"

//ゲームオーバーの画面クラス
class GameOver : public BaseScene {
private:
	int gameoverGraphic;	//ゲームオーバー画面
	int gameoverSound;		//ゲームオーバーの音

public:
	GameOver(ISceneChanger* changer);
	~GameOver();

	void Update();
	void Draw();
};

#endif