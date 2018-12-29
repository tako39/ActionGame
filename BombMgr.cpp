#include "BombMgr.h"

BombMgr::BombMgr() {
	for (int num = 0; num < BOMB_NUM; num++) {
		bomb[num] = NULL;
		deleteTime[num] = -5000;
		explosion[num] = false;
	}
}

BombMgr::~BombMgr() {
	for (int num = 0; num < BOMB_NUM; num++) {
		delete bomb[num];
	}
}

void BombMgr::Update() {
	for (int num = 0; num < BOMB_NUM; num++) {
		if (bomb[num] != NULL) {
			bomb[num]->Update();
			if (bomb[num]->GetExist() == false) {
				explosion[num] = true;	//爆発
			}
		}
	}
}

void BombMgr::Draw(const Player& player) {
	for (int num = 0; num < BOMB_NUM; num++) {
		if (bomb[num] != NULL) {
			bomb[num]->Draw(player);
		}
	}
}

void BombMgr::BombSet(const Player& player) {
	for (int num = 0; num < BOMB_NUM; num++) {
		//NULLかつ、消費した時間から1秒経ったものを使用
		if (bomb[num] == NULL && (GetNowCount() - deleteTime[num] > 1000)) {
			bomb[num] = new Bomb(player);
			break;
		}
	}
}