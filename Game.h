#ifndef ___Class_Game
#define ___Class_Game

#include "BaseScene.h"

class Map;
class Player;
class Enemy;

//ゲーム画面クラス
class Game : public BaseScene {

private:
	Player * player;
	Map *map;
	Enemy * enemy;

public:
	Game::Game(ISceneChanger* changer);
	void Initialize() override;  //初期化処理をオーバーライド。
	void Finalize() override;    //終了処理をオーバーライド。
	void Update() override;      //更新処理をオーバーライド。
	void Draw() override;        //描画処理をオーバーライド。

	static int nowStage; //現在のステージ
};

#endif