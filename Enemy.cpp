#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "BulletMgr.h"
#include "Define.h"
#include "Display.h"
#include <math.h>

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

// “–‚½‚è”»’è
void Enemy::Collision(const Player& player, BulletMgr& bulletMgr) {
	//ƒpƒ“ƒ`‚ª“–‚½‚Á‚Ä‚¢‚é‚©
	if (player.GetIsPunch() &&
		(fabs(pos.x - player.GetPunchPos().x) < CHIP_SIZE) &&
		(fabs(pos.y - player.GetPunchPos().y) < CHIP_SIZE)) {
		isExist = false;
		Display::Score += POINT_ENEMY_ZAKO;
		return;
	}

	//’e‚ª“–‚½‚Á‚Ä‚¢‚é‚©
	for (int num = 0; num < BULLET_NUM; num++) {
		if (bulletMgr.IsExist(num)) {	//’e‚ª‘¶Ý‚·‚é‚Æ‚«
			VECTOR bulletPos = bulletMgr.GetBulletPos(num);
			if ((fabs(pos.x + CHIP_SIZE / 2 - (bulletPos.x + BULLET_WIDTH  / 2)) < CHIP_SIZE / 2 + BULLET_WIDTH  / 2) &&
				(fabs(pos.y + CHIP_SIZE / 2 - (bulletPos.y + BULLET_HEIGHT / 2)) < CHIP_SIZE / 2 + BULLET_HEIGHT / 2)) {
				isExist = false;
				bulletMgr.DeleteBullet(num);
				Display::Score += POINT_ENEMY_ZAKO;
				return;
			}
		}
	}
}