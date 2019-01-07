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
	const int enemyNum;			//�G�̐�
	Enemy *enemy[MAX_ENEMY];	//�G
	VECTOR enemyPos[MAX_ENEMY];	//�G�̈ʒu

public:
	EnemyMgr(int type, int num);
	~EnemyMgr();

	void Update() {};
	void Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);
	void Draw() {};
	void Draw(const Player& player);

	int GetEnemyNum() const {
		return enemyNum;
	}

	bool IsExist(int num) const {	//���݂��邩�ǂ���
		if (enemy[num] != NULL) return true;
		else return false;
	}
	VECTOR GetEnemyPos(int num) const {	//enemy[num]�̈ʒu���擾
		return enemy[num]->GetPos();
	}
	int GetEnemyType(int num) const {
		return enemy[num]->GetType();
	}
};

#endif