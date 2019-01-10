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
	const int enemyNum;			//敵の数
	Enemy *enemy[MAX_ENEMY];	//敵
	VECTOR enemyPos[MAX_ENEMY];	//敵の位置

public:
	EnemyMgr();
	EnemyMgr(int type, int num);	//typeの敵をnum匹生成する
	~EnemyMgr();

	void Update() {};
	void Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);
	void Draw() {};
	void Draw(const Player& player);

	int GetEnemyNum() const {
		return enemyNum;
	}

	bool IsExist(int num) const {	//存在するかどうか
		if (enemy[num] != NULL) return true;
		else return false;
	}
	VECTOR GetEnemyPos(int num) const {	//enemy[num]の位置を取得
		return enemy[num]->GetPos();
	}
	int GetEnemyType(int num) const {	//enemy[num]の種類を取得
		return enemy[num]->GetType();
	}

	bool IsNoEnemy() {	//敵が全て倒されたか
		for (int num = 0; num < enemyNum; num++) {
			if (enemy[num] != NULL) {
				return false;
			}
		}
		return true;
	}
};

#endif