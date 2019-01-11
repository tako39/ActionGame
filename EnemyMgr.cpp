#include "EnemyMgr.h"
#include "Enemy_Zako.h"
#include "Enemy_Tall.h"
#include "Enemy_Big.h"
#include "Enemy_Boss.h"
#include "Game.h"
#include "BombMgr.h"
#include "Display.h"

EnemyMgr::EnemyMgr() : enemyNum(MAX_ENEMY) {
	for (int num = 0; num < MAX_ENEMY; num++) {
		enemy[num] = NULL;
	}
}

EnemyMgr::EnemyMgr(int type, int num) : enemyNum(num) {
	if (type == ENEMY_ZAKO) {
		for (int num = 0; num < enemyNum; num++) {
			enemy[num] = new Zako();
		}
	}
	else if (type == ENEMY_TALL) {
		for (int num = 0; num < enemyNum; num++) {
			enemy[num] = new Tall();
		}
	}
	else if (type == ENEMY_BIG) {
		for (int num = 0; num < enemyNum; num++) {
			enemy[num] = new Big();
		}
	}
	else if (type == ENEMY_BOSS) {
		for (int num = 0; num < enemyNum; num++) {
			enemy[num] = new Boss();
		}
	}
}

EnemyMgr::~EnemyMgr() {
	for (int num = 0; num < enemyNum; num++) {
		delete enemy[num];
	}
}

void EnemyMgr::Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	for (int num = 0; num < enemyNum; num++) {
		if (enemy[num] != NULL) {
			int type = enemy[num]->GetType();

			enemy[num]->Update();		//XV
			enemy[num]->Update(player);	//XV
			enemy[num]->Collision(player, bulletMgr, bombMgr);	//“–‚½‚è”»’è

			if (enemy[num]->GetHitPoint() <= 0) {	//“|‚³‚ê‚½‚Æ‚«
				enemy[num]->SetExist(false);
				Display::Point[type]++;	//“|‚µ‚½”‚ğ‘‚â‚·

				if (type == ENEMY_ZAKO) {
					enemy[num] = NULL;
				}
				else if (type == ENEMY_TALL) {
					VECTOR tallPos = enemy[num]->GetPos();
					enemy[num] = new Zako();
					enemy[num]->SetPos(tallPos);
				}
				else if (type == ENEMY_BIG) {
					VECTOR bigPos = enemy[num]->GetPos();
					enemy[num] = new Tall();
					enemy[num]->SetPos(bigPos);
				}
				else if (type == ENEMY_BOSS) {
					enemy[num] = NULL;
				}
			}
		}
	}
	bombMgr.DeleteBombAll();	//”š”­‚µ‚½”š’e‚Ìˆ—
}

void EnemyMgr::Draw(const Player& player) {
	for (int num = 0; num < enemyNum; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Draw();  //•`‰æ
			enemy[num]->Draw(player);
		}
	}
}