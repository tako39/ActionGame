#include "BombMgr.h"

BombMgr::BombMgr() {
	putSound = LoadSoundMem("sound/put.mp3");

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
		//NULLかつ、消費した時間から2秒経ったものを使用
		if (bomb[num] == NULL && (GetNowCount() - deleteTime[num] > 2000)) {
			PlaySoundMem(putSound, DX_PLAYTYPE_BACK);	//爆弾を置いたときの音
			bomb[num] = new Bomb(player);
			break;
		}
	}
}