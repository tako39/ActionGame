#include "EnemyMgr.h"
#include "Enemy_Zako.h"
#include "Enemy_Tall.h"
#include "Enemy_Big.h"
#include "Game.h"
#include "BombMgr.h"
#include <typeinfo>

EnemyMgr::EnemyMgr() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		enemy[num] = new Big();
	}
}

EnemyMgr::~EnemyMgr() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		delete enemy[num];
	}
}

void EnemyMgr::Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Update();		//XV
			enemy[num]->Update(player);	//XV
			enemy[num]->Collision(player, bulletMgr, bombMgr);	//“–‚½‚è”»’è
			if (enemy[num]->GetExist() == false) {	//“|‚³‚ê‚½‚Æ‚«
				if (enemy[num]->GetType() == ENEMY_ZAKO) {
					delete enemy[num];
					enemy[num] = NULL;
				}
				else if (enemy[num]->GetType() == ENEMY_TALL) {
					VECTOR tallPos = enemy[num]->GetPos();
					delete enemy[num];
					enemy[num] = new Zako(tallPos);
				}
				else if (enemy[num]->GetType() == ENEMY_BIG) {
					VECTOR bigPos = enemy[num]->GetPos();
					delete enemy[num];
					enemy[num] = new Tall(bigPos);
				}
			}
		}
	}
	bombMgr.DeleteBombAll();	//”š”­‚µ‚½”š’e‚Ìˆ—
}

void EnemyMgr::Draw(const Player& player) {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Draw();  //•`‰æ
			enemy[num]->Draw(player);
		}
	}
}