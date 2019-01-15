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
class BossStage;

//ƒQ[ƒ€‰æ–ÊƒNƒ‰ƒX
class Game : public BaseScene {
private:
	Player * player;
	Map *map;
	EnemyMgr *enemyMgr;
	BulletMgr *bulletMgr;
	BombMgr *bombMgr;
	Display *display;
	Manual *manual;
	BossStage * bossStage;

	int enemyPhase;	//“G‚Ì¶¬’iŠK
	bool mPush;	//m‚ª‰Ÿ‚³‚ê‚½ó‘Ô‚©

public:
	Game(ISceneChanger* changer);
	~Game();

	void Update();
	void Draw();

	void ChangeEnemyPhase();	//“G‚Ì’iŠK‚Ì•ÏX
};

#endif