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

	int enemyPhase;	//�G�̐����i�K
	bool mPush;	//m�������ꂽ��Ԃ�

public:
	Game(ISceneChanger* changer);
	~Game();

	void Update() override;      //�X�V�������I�[�o�[���C�h�B
	void Draw() override;        //�`�揈�����I�[�o�[���C�h�B
};

#endif