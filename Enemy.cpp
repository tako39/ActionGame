#include "Enemy.h"
#include "Game.h"
#include "Define.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include <math.h>

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

// �����蔻��
void Enemy::Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	//�p���`���������Ă��邩
	if (player.GetIsPunch() &&
		(fabs(pos.x - player.GetPunchPos().x) < CHIP_SIZE) &&
		(fabs(pos.y - player.GetPunchPos().y) < CHIP_SIZE)) {
		isExist = false;
		Display::Score += POINT_ENEMY_ZAKO;
		return;
	}

	//�e���������Ă��邩
	for (int bulletNum = 0; bulletNum < BULLET_NUM; bulletNum++) {
		if (bulletMgr.IsExist(bulletNum)) {	//�e�����݂���Ƃ�
			VECTOR bulletPos = bulletMgr.GetBulletPos(bulletNum);
			if ((fabs(pos.x + CHIP_SIZE / 2 - (bulletPos.x + BULLET_WIDTH  / 2)) < CHIP_SIZE / 2 + BULLET_WIDTH  / 2) &&
				(fabs(pos.y + CHIP_SIZE / 2 - (bulletPos.y + BULLET_HEIGHT / 2)) < CHIP_SIZE / 2 + BULLET_HEIGHT / 2)) {
				isExist = false;
				bulletMgr.DeleteBullet(bulletNum);
				Display::Score += POINT_ENEMY_ZAKO;
				return;
			}
		}
	}

	//���e�����������Ƃ��Ɋ������܂ꂽ��
	for (int bombNum = 0; bombNum < BOMB_NUM; bombNum++) {
		if (bombMgr.IsExplosion(bombNum)) {	//���������Ƃ�
			VECTOR bombPos = bombMgr.GetBombPos(bombNum);
			//���e�̎��͂Q�}�X���̋����ɂ���Ȃ瓖����
			if ((fabs(pos.x + CHIP_SIZE / 2 - (bombPos.x + CHIP_SIZE / 2)) < CHIP_SIZE * 2) &&
				(fabs(pos.y + CHIP_SIZE / 2 - (bombPos.y + CHIP_SIZE / 2)) < CHIP_SIZE * 2)) {
				isExist = false;
				Display::Score += POINT_ENEMY_ZAKO;
				return;
			}
		}
	}
}