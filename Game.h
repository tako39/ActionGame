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

//�Q�[����ʃN���X
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

	int enemyPhase;	//�G�̐����i�K
	bool mPush;	//m�������ꂽ��Ԃ�

public:
	Game(ISceneChanger* changer);
	~Game();

	void Update();
	void Draw();

	void ChangeEnemyPhase();	//�G�̒i�K�̕ύX
};

#endif