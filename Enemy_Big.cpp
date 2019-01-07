#include "Enemy_Big.h"
#include "Define.h"
#include "Map.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include <math.h>

Big::Big() {
	enemyType = ENEMY_BIG;
	graphic_R = LoadGraph("image/enemyBig_r.png");
	graphic_L = LoadGraph("image/enemyBig_l.png");
	isGround = false;
	pos = randomPos(2, 2);		//ランダムに位置を設定
	direct = randomDir();		//ランダムに向きを決定
	enemySpeed = randomSpeed();	//ランダムに速さを決定
}

Big::~Big() {

}

void Big::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);	//初期化

	if (isGround) move.x += enemySpeed * direct;	//横方向の移動

	ver_Speed += Gravity;	//重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);	//移動
}

void Big::Draw(const Player& player) {
	EnemyDraw(player);	//敵の描画
}

void Big::Move(float moveY, float moveX) {
	float dummy = 0.0f;
	//上下成分の移動
	{
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//右上
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE * 2 - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//左下
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}
		//右下
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + CHIP_SIZE * 2 - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}

		pos.y += moveY;
	}
	//左右成分の移動
	{
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//右上
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE * 2 - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}
		//左下
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//右下
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + CHIP_SIZE * 2 - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}

		pos.x += moveX;
	}
	//次の移動で落ちるとき、向きを変える
	{
		float nextMove = enemySpeed * direct;
		//進む先に地面がないなら向きを変える
		if (Map::GetMapChip(pos.y + CHIP_SIZE * 2 + EPS + CHIP_SIZE / 4, pos.x + EPS + nextMove) != GROUND) {
			direct = DIR_RIGHT;	//左端が当たったら右に
		}
		if (Map::GetMapChip(pos.y + CHIP_SIZE * 2 + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE * 2 - EPS + nextMove) != GROUND) {
			direct = DIR_LEFT;	//右端が当たったら左に
		}
	}
}

void Big::Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	//パンチが当たっているか
	if (player.GetIsPunch() &&
		(fabs(pos.x - player.GetPunchPos().x) < CHIP_SIZE * 1.5f) &&
		(fabs(pos.y - player.GetPunchPos().y) < CHIP_SIZE * 1.5f)) {
		isExist = false;
		Display::Score += POINT_ENEMY_TALL;
		return;
	}

	//弾が当たっているか
	for (int bulletNum = 0; bulletNum < BULLET_NUM; bulletNum++) {
		if (bulletMgr.IsExist(bulletNum)) {	//弾が存在するとき
			VECTOR bulletPos = bulletMgr.GetBulletPos(bulletNum);
			if ((fabs(pos.x + CHIP_SIZE - (bulletPos.x + BULLET_WIDTH  / 2)) < CHIP_SIZE + BULLET_WIDTH  / 2) &&
				(fabs(pos.y + CHIP_SIZE - (bulletPos.y + BULLET_HEIGHT / 2)) < CHIP_SIZE + BULLET_HEIGHT / 2)) {
				isExist = false;
				bulletMgr.DeleteBullet(bulletNum);
				Display::Score += POINT_ENEMY_TALL;
				return;
			}
		}
	}

	//爆弾が爆発したときに巻き込まれたか
	for (int bombNum = 0; bombNum < BOMB_NUM; bombNum++) {
		if (bombMgr.IsExplosion(bombNum)) {	//爆発したとき
			VECTOR bombPos = bombMgr.GetBombPos(bombNum);
			//爆弾の周囲２マス分の距離にいるなら当たる
			if ((fabs(pos.x + CHIP_SIZE - (bombPos.x + CHIP_SIZE / 2)) < CHIP_SIZE * 3.5f) &&
				(fabs(pos.y + CHIP_SIZE - (bombPos.y + CHIP_SIZE / 2)) < CHIP_SIZE * 3.5f)) {
				isExist = false;
				Display::Score += POINT_ENEMY_TALL;
				return;
			}
		}
	}
}