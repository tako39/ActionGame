#ifndef ___Class_Menu
#define ___Class_Menu

#include "BaseScene.h"

class Player;
class Map;
class BulletMgr;
class BombMgr;
class Manual;

//���j���[��ʃN���X
class Menu : public BaseScene {
private:
	Player *player;
	Map *map;
	BulletMgr *bulletMgr;
	BombMgr *bombMgr;
	Manual *manual;

	bool mPush;

public:
	Menu(ISceneChanger* changer);
	~Menu();

	void Update()     override;  //�X�V�������I�[�o�[���C�h�B
	void Draw()       override;  //�`�揈�����I�[�o�[���C�h�B
};

#endif