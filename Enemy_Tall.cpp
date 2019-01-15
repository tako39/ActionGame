#include "Enemy_Tall.h"
#include "Define.h"
#include "Map.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include "Player.h"
#include <math.h>

Tall::Tall() {
	SetHitPoint(HP_TALL);
	enemyType = ENEMY_TALL;
	size = VGet(CHIP_SIZE * 1, CHIP_SIZE * 2, 0.0f);
	graphic_R = LoadGraph("image/enemyTall_r.png");
	graphic_L = LoadGraph("image/enemyTall_l.png");
	isGround = false;
	pos = randomPos(1, 1);		//ランダムに位置を設定
	direct = randomDir();		//ランダムに向きを決定
	enemySpeed = randomSpeed();	//ランダムに速さを決定
}

Tall::~Tall() {

}

void Tall::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);	//初期化

	if (isGround) move.x += enemySpeed * direct;	//横方向の移動

	ver_Speed += Gravity;	//重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);	//移動
	LookAhead();	//落ちるとき向きを変える
}

void Tall::Draw(const Player& player) {
	EnemyDraw(player);	//敵の描画
}