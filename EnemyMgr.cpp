#include "EnemyMgr.h"
#include "DxLib.h"
#include "Enemy.h"

EnemyMgr::EnemyMgr() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		enemy[num] = new Enemy();
		enemy[num]->SetPos(VGet(15.0f * CHIP_SIZE, 1.0f, 0.0f));
		enemy[num]->SetDirect(DIR_LEFT);
	}
}

EnemyMgr::~EnemyMgr() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		delete enemy[num];
	}
}

void EnemyMgr::Update(const Player& cPlayer) {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Update(cPlayer);
		}
	}
}

void EnemyMgr::Draw() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Draw();
		}
	}
}