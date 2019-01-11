#ifndef ___Class_Game
#define ___Class_Game

#include "BaseScene.h"

class Map;
class Player;
class EnemyMgr;
class BulletMgr;
class BombMgr;
class Display;
class Manual;

//ゲーム画面クラス
class Game : public BaseScene {
private:
	Player * player;
	Map *map;
	EnemyMgr *enemyMgr;
	BulletMgr *bulletMgr;
	BombMgr *bombMgr;
	Display *display;
	Manual *manual;

	int enemyPhase;	//敵の生成段階
	bool mPush;	//mが押された状態か

public:
	Game(ISceneChanger* changer);
	~Game();

	void Update() override;      //更新処理をオーバーライド。
	void Draw() override;        //描画処理をオーバーライド。
};

#endif