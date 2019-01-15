#include "Enemy_Zako.h"
#include "Player.h"
#include "Map.h"
#include "SceneMgr.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include <math.h>

Zako::Zako() {
	SetHitPoint(HP_ZAKO);
	enemyType = ENEMY_ZAKO;
	size = VGet(CHIP_SIZE * 1, CHIP_SIZE * 1, 0.0f);
	graphic_R = LoadGraph("image/enemyZako_r.png");
	graphic_L = LoadGraph("image/enemyZako_l.png");
	isGround = false;
	pos = randomPos(1, 1);		//ランダムに位置を設定
	direct = randomDir();		//ランダムに向きを決定
	enemySpeed = randomSpeed();	//ランダムに速さを決定
}

Zako::~Zako() {

}

void Zako::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);	//初期化

	if (isGround) move.x += enemySpeed * direct;	//横方向の移動

	ver_Speed += Gravity;	//重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);	//移動
	LookAhead();	//落ちるとき向きを変える
}

void Zako::Draw(const Player& player) {
	EnemyDraw(player);	//敵の描画
}