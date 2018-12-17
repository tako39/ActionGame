#include "EnemyMgr.h"
#include "Enemy.h"
#include "Game.h"

EnemyMgr::EnemyMgr() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		enemy[num] = new Enemy();
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
			enemy[num]->Update(player);		//�X�V
			enemy[num]->Collision(player);	//�����蔻��
			if (enemy[num]->GetExist() == false) {	//�|���ꂽ�Ƃ�
				delete enemy[num];
				enemy[num] = NULL;
			}
		}
	}
}

void EnemyMgr::Draw() {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Draw();  //�`��
		}
	}
}