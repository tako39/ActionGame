#include "Enemy.h"
#include "Game.h"
#include "Define.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "SceneMgr.h"
#include "Map.h"
#include <math.h>

Enemy::Enemy() {
	damageSound = LoadSoundMem("sound/damage_enemy.mp3");
}

Enemy::~Enemy() {

}

void Enemy::EnemyDraw(const Player& player) {

	if ((int)player.GetPos().x < SCREEN_HALF_W) {
		screenPos.x = (int)pos.x;
	}
	else if ((int)player.GetPos().x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		screenPos.x = SCREEN_HALF_W + (int)pos.x - (int)player.GetPos().x;
	}
	else {
		screenPos.x = (int)pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if ((int)player.GetPos().y < SCREEN_HALF_H) {
		screenPos.y = (int)pos.y;
	}
	else if ((int)player.GetPos().y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		screenPos.y = SCREEN_HALF_H + (int)pos.y - (int)player.GetPos().y;
	}
	else {
		screenPos.y = (int)pos.y - (STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	//向きに応じて描画
	if (direct == DIR_RIGHT) {
		DrawGraph((int)screenPos.x, (int)screenPos.y, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)screenPos.x, (int)screenPos.y, graphic_L, FALSE);
	}

	HpDraw();	//hpの描画
}

void Enemy::HpDraw() {
	int maxHp;	//最大hp
	if (enemyType == ENEMY_ZAKO) {
		maxHp = HP_ZAKO;
	}
	else if (enemyType == ENEMY_TALL) {
		maxHp = HP_TALL;
	}
	else if (enemyType == ENEMY_BIG) {
		maxHp = HP_BIG;
	}
	else if (enemyType == ENEMY_BOSS) {
		maxHp = HP_BOSS;
	}

	SetFontSize(10);
	DrawFormatString((int)screenPos.x, (int)screenPos.y - 10, GetColor(255, 255, 255), "%d/%d", hitPoint, maxHp);
}

//位置の決定
VECTOR Enemy::randomPos(int h, int w) {
	int posY, posX;
	while (1) {
		posY = GetRand(STAGE_HEIGHT[SceneMgr::nowStage] - 1);
		posX = GetRand(STAGE_WIDTH[SceneMgr::nowStage] - 1);

		//敵がマップからはみ出さないようにする
		if (posX <= 3 || posY <= 1) continue;
		if ((posX >= STAGE_WIDTH[SceneMgr::nowStage]  - w) ||
			(posY >= STAGE_HEIGHT[SceneMgr::nowStage] - h)) {
			continue;
		}

		bool canPut = true;		//敵を配置できるか

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				//敵がマップからはみ出るなら
				if (Map::GetMap(posY + CHIP_SIZE * y, posX + CHIP_SIZE * x) != BACK) {
					canPut = false;
					break;
				}
			}
		}

		if (canPut) break;	//敵が配置できるときループを抜ける
	}
	return VGet((float)posX * CHIP_SIZE, (float)posY * CHIP_SIZE, 0.0f);
}

//向きの決定
int Enemy::randomDir() {
	int r = GetRand(1);

	if (r == 0) return DIR_LEFT;
	else return DIR_RIGHT;
}

//スピードの決定
float Enemy::randomSpeed() {
	float speed;
	int r = GetRand(2);
	
	switch (r) {
	case 0:
		speed = 1.0f;
		break;
	case 1:
		speed = 2.0f;
		break;
	case 2:
		speed = 3.0f;
		break;
	}
	return speed;
}

// 当たり判定
void Enemy::Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	//パンチが当たっているか
	if (CollisionPunch(player)) return;

	//弾が当たっているか
	if (CollisionBullet(bulletMgr)) return;

	//爆弾が爆発したときに巻き込まれたか
	if (CollisionBomb(bombMgr)) return;
}

//当たり判定（パンチ）
bool Enemy::CollisionPunch(const Player& player) {
	if (Player::isFirstPunch &&
		(fabs(pos.x + size.x / 2 - (player.GetPunchPos().x + PUNCH_WIDTH  / 2)) < size.x / 2 + PUNCH_WIDTH  / 2) &&
		(fabs(pos.y + size.y / 2 - (player.GetPunchPos().y + PUNCH_HEIGHT / 2)) < size.y / 2 + PUNCH_HEIGHT / 2)) {
		Damaged(DAMAGE_PUNCH);	//ダメージを受ける
		PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//ダメージ音
		Player::isFirstPunch = false;
		return true;
	}
	return false;
}

//当たり判定（弾）
bool Enemy::CollisionBullet(BulletMgr& bulletMgr) {
	for (int bulletNum = 0; bulletNum < BULLET_NUM; bulletNum++) {
		if (bulletMgr.IsExist(bulletNum)) {		//弾が存在するとき
			VECTOR bulletPos = bulletMgr.GetBulletPos(bulletNum);
			if ((fabs(pos.x + size.x / 2 - (bulletPos.x + BULLET_WIDTH  / 2)) < size.x + BULLET_WIDTH  / 2) &&
				(fabs(pos.y + size.y / 2 - (bulletPos.y + BULLET_HEIGHT / 2)) < size.y + BULLET_HEIGHT / 2)) {
				Damaged(DAMAGE_BULLET);		//ダメージを受ける
				bulletMgr.DeleteBullet(bulletNum);	//弾の消滅
				PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//ダメージ音
				return true;
			}
		}
	}
	return false;
}

//当たり判定（爆弾）
bool Enemy::CollisionBomb(BombMgr& bombMgr) {
	for (int bombNum = 0; bombNum < BOMB_NUM; bombNum++) {
		if (bombMgr.IsExplosion(bombNum)) {		//爆発したとき
			VECTOR bombPos = bombMgr.GetBombPos(bombNum);
			//爆弾の周囲２マス分の距離にいるなら当たる
			if ((fabs(pos.x + size.x / 2 - (bombPos.x + BOMB_WIDTH  / 2)) < size.x / 2 + BOMB_WIDTH  / 2 + BOMB_RANGE) &&
				(fabs(pos.y + size.y / 2 - (bombPos.y + BOMB_HEIGHT / 2)) < size.y / 2 + BOMB_HEIGHT / 2 + BOMB_RANGE)) {
				Damaged(DAMAGE_BOMB);	//ダメージを受ける
				PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//ダメージ音
				return true;
			}
		}
	}
	return false;
}