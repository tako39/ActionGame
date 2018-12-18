#ifndef ___Class_EnemyMgr
#define ___Class_EnemyMgr

#include "Define.h"
#include "DxLib.h"
#include "Task.h"
#include "Player.h"

class Enemy;

class EnemyMgr : public Task {
private:
	Enemy *enemy[ENEMY_NUM];
	VECTOR enemyPos[ENEMY_NUM];  //“G‚ÌˆÊ’u

public:
	EnemyMgr();
	~EnemyMgr();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);
};

#endif