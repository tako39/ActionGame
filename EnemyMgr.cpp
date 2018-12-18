#include "EnemyMgr.h"
#include "Enemy.h"
#include "Game.h"
#include "Enemy_Zako.h"

EnemyMgr::EnemyMgr() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		enemy[num] = new Zako();
	}
}

EnemyMgr::~EnemyMgr() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		delete enemy[num];
	}
}

void EnemyMgr::Update(const Player& player) {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Update();		//XV
			enemy[num]->Update(player);	//XV
			if (enemy[num]->GetExist() == false) {	//“|‚³‚ê‚½‚Æ‚«
				delete enemy[num];
				enemy[num] = NULL;
			}
		}
	}
}

void EnemyMgr::Draw(const Player& player) {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Draw();  //•`‰æ
			enemy[num]->Draw(player);
		}
	}
}