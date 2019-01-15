#include "EnemyMgr.h"
#include "Enemy_Zako.h"
#include "Enemy_Tall.h"
#include "Enemy_Big.h"
#include "Enemy_Boss.h"
#include "Game.h"
#include "BombMgr.h"
#include "Display.h"

EnemyMgr::EnemyMgr() {
	for (int num = 0; num < MAX_ENEMY; num++) {
		enemy[num] = NULL;
	}
}

EnemyMgr::EnemyMgr(int type, int enemyNum) {
	for (int num = 0; num < MAX_ENEMY; num++) {
		enemy[num] = NULL;
	}

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

//�S�Ă̓G�̈ʒu��sPos�ɂ���
void EnemyMgr::SetPosAll(VECTOR sPos) {
	for (int num = 0; num < MAX_ENEMY; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->SetPos(sPos);
		}
	}
}

//sPos��type�̓G��addNum�C���₷
void EnemyMgr::AddEnemy(int type, int addNum, VECTOR sPos) {
	int enemyCount = 0;
	for (int num = 0; num < MAX_ENEMY; num++) {
		if (enemy[num] != NULL) continue;

		if (type == ENEMY_ZAKO) {
			enemy[num] = new Zako();
		}
		else if (type == ENEMY_TALL) {
			enemy[num] = new Tall();
		}
		else if (type == ENEMY_BIG) {
			enemy[num] = new Big();
		}
		else if (type == ENEMY_BOSS) {
			enemy[num] = new Boss();
		}
		enemy[num]->SetPos(sPos);

		enemyCount++;
		if (enemyCount >= addNum) break;
	}
}

EnemyMgr::~EnemyMgr() {
	for (int num = 0; num < MAX_ENEMY; num++) {
		delete enemy[num];
	}
}

void EnemyMgr::Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	for (int num = 0; num < MAX_ENEMY; num++) {
		if (enemy[num] != NULL) {
			int type = enemy[num]->GetType();

			enemy[num]->Update();		//�X�V
			enemy[num]->Update(player);	//�X�V
			enemy[num]->Collision(player, bulletMgr, bombMgr);	//�����蔻��

			if (enemy[num]->GetHitPoint() <= 0) {	//�|���ꂽ�Ƃ�
				enemy[num]->SetExist(false);

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
}

void EnemyMgr::Draw(const Player& player) {
	for (int num = 0; num < MAX_ENEMY; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Draw();  //�`��
			enemy[num]->Draw(player);
		}
	}
}