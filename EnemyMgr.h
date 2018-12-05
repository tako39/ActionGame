#ifndef ___Class_EnemyMgr
#define ___Class_EnemyMgr

#include "Define.h"
#include "Task.h"
#include "Player.h"

class Enemy;

class EnemyMgr : public Task {
private:
	Enemy * enemy[ENEMY_NUM];

public:
	EnemyMgr();
	~EnemyMgr();

	void Update() {};
	void Update(const Player& cPlayer);
	void Draw();
};

#endif