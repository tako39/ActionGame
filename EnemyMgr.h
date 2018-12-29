#ifndef ___Class_EnemyMgr
#define ___Class_EnemyMgr

#include "Define.h"
#include "DxLib.h"
#include "Task.h"
#include "Player.h"
#include "Enemy.h"

class Enemy;
class BulletMgr;
class BombMgr;

class EnemyMgr : public Task {
private:
	Enemy *enemy[ENEMY_NUM];
	VECTOR enemyPos[ENEMY_NUM];  //“G‚ÌˆÊ’u

public:
	EnemyMgr();
	~EnemyMgr();

	void Update() {};
	void Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);
	void Draw() {};
	void Draw(const Player& player);

	bool IsExist(int num) const {	//‘¶Ý‚·‚é‚©‚Ç‚¤‚©
		if (enemy[num] != NULL) return true;
		else return false;
	}
	VECTOR GetEnemyPos(int num) const {	//enemy[num]‚ÌˆÊ’u‚ðŽæ“¾
		return enemy[num]->GetPos();
	}
};

#endif