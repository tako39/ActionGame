#ifndef ___BossStage
#define ___BossStage

#include "Task.h"
#include "DxLib.h"

class EnemyMgr;
class Player;
class BulletMgr;
class BombMgr;

class BossStage : public Task {
private:
	EnemyMgr *bossFriendMgr;

	int bossStageGraphic;
	int bossStageSound;
	int frameCount;

public:
	BossStage();
	~BossStage();

	void Update() {};
	void Update(Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr, VECTOR bossPos);
	void Draw() {};
	void Draw(const Player& player);

	bool StageStart();		//�ŏ��̕`��p
	bool FrameCheck() {		//�ŏ��̕`�撆�ł��邩
		if (frameCount > 180) return false;
		return true;
	}
};

#endif