#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "BulletMgr.h"
#include "Define.h"
#include <math.h>

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

// “–‚½‚è”»’è
void Enemy::Collision(const Player& player, BulletMgr& bulletMgr) {
	//ƒpƒ“ƒ`‚ª“–‚½‚Á‚Ä‚¢‚é‚©
	if (player.GetIsPunch() &&
		fabs(pos.x - player.GetPunchPos().x) < CHIP_SIZE &&
		fabs(pos.y - player.GetPunchPos().y) < CHIP_SIZE) {
		isExist = false;
		return;
	}

	//’e‚ª“–‚½‚Á‚Ä‚¢‚é‚©
	for (int num = 0; num < BULLET_NUM; num++) {
		if (bulletMgr.IsExist(num)) {	//’e‚ª‘¶Ý‚·‚é‚Æ‚«
			VECTOR bulletPos = bulletMgr.GetBulletPos(num);
			if (fabs(pos.x - bulletPos.x) < CHIP_SIZE / 2 + BULLET_WIDTH  / 2 &&
				fabs(pos.y - bulletPos.y) < CHIP_SIZE / 2 + BULLET_HEIGHT / 2) {
				isExist = false;
				bulletMgr.DeleteBullet(num);
				return;
			}
		}
	}
}