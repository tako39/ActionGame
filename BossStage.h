#ifndef ___BossStage
#define ___BossStage

#include "Task.h"
#include "DxLib.h"

class EnemyMgr;
class Player;
class BulletMgr;
class BombMgr;

//�{�X�X�e�[�W�̃N���X
class BossStage : public Task {
private:
	EnemyMgr *bossFriendMgr;	//�{�X���������钇��

	int bossStageGraphic;		//�{�X�X�e�[�W�̊J�n�摜
	int bossStageSound;			//�{�X�X�e�[�W�̉��y
	int frameCount;				//�t���[���̃J�E���g

public:
	BossStage();
	~BossStage();

	void Update() {};
	void Update(Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr, VECTOR bossPos);
	void Draw() {};
	void Draw(const Player& player);

	bool StageStart();			//�{�X�X�e�[�W���������̕`��p
	bool FrameCheck() {			//�{�X�X�e�[�W���������̕`�撆�ł��邩
		if (frameCount > 180) return false;
		return true;
	}
};

#endif