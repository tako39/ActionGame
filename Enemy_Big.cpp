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
	LookAhead();	//落ちるとき向きを変える
}

void Big::Draw(const Player& player) {
	EnemyDraw(player);	//敵の描画
}