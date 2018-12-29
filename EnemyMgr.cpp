#include "EnemyMgr.h"
#include "Game.h"
#include "Enemy_Zako.h"
#include "BombMgr.h"

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

void EnemyMgr::Update(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Update();		//�X�V
			enemy[num]->Update(player);	//�X�V
			enemy[num]->Collision(player, bulletMgr, bombMgr);	//�����蔻��
			if (enemy[num]->GetExist() == false) {	//�|���ꂽ�Ƃ�
				delete enemy[num];
				enemy[num] = NULL;
			}
		}
	}
	bombMgr.DeleteBombAll();	//�����������e�̏���
}

void EnemyMgr::Draw(const Player& player) {
	for (int num = 0; num < ENEMY_NUM; num++) {
		if (enemy[num] != NULL) {
			enemy[num]->Draw();  //�`��
			enemy[num]->Draw(player);
		}
	}
}