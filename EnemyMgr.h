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
	Enemy *enemy[MAX_ENEMY];	//�G
	VECTOR enemyPos[MAX_ENEMY];	//�G�̈ʒu

public:
	EnemyMgr();
	EnemyMgr(int type, int enemyNum);	//type�̓G��num�C��������
	~EnemyMgr();

	void Update() {};
	void Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);
	void Draw() {};
	void Draw(const Player& player);

	void SetPosAll(VECTOR sPos);	//�S�Ă̓G��sPos�ɐݒu����

	void AddEnemy(int type, int addNum, VECTOR sPos);	//sPos��type�̓G��addNum�C���₷

	bool IsExist(int num) const {	//���݂��邩�ǂ���
		if (enemy[num] != NULL) return true;
		else return false;
	}
	VECTOR GetEnemyPos(int num) const {	//enemy[num]�̈ʒu���擾
		return enemy[num]->GetPos();
	}
	int GetEnemyType(int num) const {	//enemy[num]�̎�ނ��擾
		return enemy[num]->GetType();
	}
	int GetEnemyHp(int num) const {		//enemy[num]��HP���擾
		return enemy[num]->GetHitPoint();
	}

	bool IsNoEnemy() {	//�G���S�ē|���ꂽ��
		for (int num = 0; num < MAX_ENEMY; num++) {
			if (enemy[num] != NULL) {
				return false;
			}
		}
		return true;
	}
};

#endif