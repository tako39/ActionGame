#include "BulletMgr.h"

BulletMgr::BulletMgr() {
	for (int num = 0; num < BULLET_NUM; num++) {
		bullet[num] = NULL;
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
		if (bullet[num] == NULL) {
			bullet[num] = new Bullet(player);
			break;
		}
	}
}