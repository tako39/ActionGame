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
			if (bullet[num]->GetExist() == false) {	//���݂��Ȃ��Ȃ����
				DeleteBullet(num);
			}
			else {
				bullet[num]->Update(player);		//����ȊO�͍X�V
			}
		}
	}
}

void BulletMgr::Draw(const Player& player) {
	for (int num = 0; num < BULLET_NUM; num++) {
		if (bullet[num] != NULL) {
			bullet[num]->Draw(player);				//�`��
		}
	}
}

//�ˌ�
void BulletMgr::Shot(const Player& player) {
	for (int num = 0; num < BULLET_NUM; num++) {
		//NULL����������Ԃ���2�b�o�������̂��g�p
		if (bullet[num] == NULL && GetNowCount() - deleteTime[num] > 2000) {
			PlaySoundMem(bulletSound, DX_PLAYTYPE_BACK);	//�e�̔��ˉ���炷
			bullet[num] = new Bullet(player);				//�e�𐶐�����
			break;
		}
	}
}