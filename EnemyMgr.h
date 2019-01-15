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
	Enemy *enemy[MAX_ENEMY];	//“G
	VECTOR enemyPos[MAX_ENEMY];	//“G‚ÌˆÊ’u

public:
	EnemyMgr();
	EnemyMgr(int type, int enemyNum);	//type‚Ì“G‚ðnum•C¶¬‚·‚é
	~EnemyMgr();

	void Update() {};
	void Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);
	void Draw() {};
	void Draw(const Player& player);

	void SetPosAll(VECTOR sPos);	//‘S‚Ä‚Ì“G‚ðsPos‚ÉÝ’u‚·‚é

	void AddEnemy(int type, int addNum, VECTOR sPos);	//sPos‚Étype‚Ì“G‚ðaddNum•C‘‚â‚·

	bool IsExist(int num) const {	//‘¶Ý‚·‚é‚©‚Ç‚¤‚©
		if (enemy[num] != NULL) return true;
		else return false;
	}
	VECTOR GetEnemyPos(int num) const {	//enemy[num]‚ÌˆÊ’u‚ðŽæ“¾
		return enemy[num]->GetPos();
	}
	int GetEnemyType(int num) const {	//enemy[num]‚ÌŽí—Þ‚ðŽæ“¾
		return enemy[num]->GetType();
	}
	int GetEnemyHp(int num) const {		//enemy[num]‚ÌHP‚ðŽæ“¾
		return enemy[num]->GetHitPoint();
	}

	bool IsNoEnemy() {	//“G‚ª‘S‚Ä“|‚³‚ê‚½‚©
		for (int num = 0; num < MAX_ENEMY; num++) {
			if (enemy[num] != NULL) {
				return false;
			}
		}
		return true;
	}
};

#endif