#ifndef ___Class_GameClear
#define ___Class_GameClear

#include "BaseScene.h"

//ゲームクリアの画面クラス
class GameClear : public BaseScene {
private:
	int gameclearGraphic;	//ゲームクリア画面
	int gameclearSound;		//ゲームクリアの音

public:
	GameClear(ISceneChanger* changer);
	~GameClear();

	void Update();
	void Draw();
};

#endif