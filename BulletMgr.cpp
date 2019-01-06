#include "BulletMgr.h"

BulletMgr::BulletMgr() {
	bulletSound = LoadSoundMem("sound/bullet.mp3");

	for (int num = 0; num < BULLET_NUM; num++) {
		bullet[num] = NULL;
		deleteTime[num] = -1000;
	}
}

BulletMgr::~BulletMgr() {
	for (int num = 0; num < BULLET_NUM; num++) {
		delete bullet[num];
	}
}

void BulletMgr::Update(const Player& player) {
	for (int num = 0; num < BULLET_NUM; num++) {
		if (bullet[num] != NULL) {
			bullet[num]->Update(player);	//更新
			if (bullet[num]->GetExist() == false) {	//存在しないなら消す
				DeleteBullet(num);
			}
		}
	}
}

void BulletMgr::Draw(const Player& player) {
	for (int num = 0; num < BULLET_NUM; num++) {
		if (bullet[num] != NULL) {
			bullet[num]->Draw(player);
		}
	}
}

//射撃
void BulletMgr::Shot(const Player& player) {
	for (int num = 0; num < BULLET_NUM; num++) {
		//NULLかつ消費した時間から2秒経ったものを使用
		if (bullet[num] == NULL && GetNowCount() - deleteTime[num] > 2000) {
			PlaySoundMem(bulletSound, DX_PLAYTYPE_BACK);	//弾を発射した時の音
			bullet[num] = new Bullet(player);
			break;
		}
	}
}