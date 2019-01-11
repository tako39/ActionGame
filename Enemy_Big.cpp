#include "Enemy_Big.h"
#include "Define.h"
#include "Map.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include <math.h>

Big::Big() {
	SetHitPoint(HP_BIG);
	enemyType = ENEMY_BIG;
	size = VGet(CHIP_SIZE * 2, CHIP_SIZE * 2, 0.0f);
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