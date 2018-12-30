#include "Enemy.h"
#include "Game.h"
#include "Define.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Map.h"
#include <math.h>

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

void Enemy::EnemyDraw(const Player& player) {
	//スクロール処理
	int scroll_x, scroll_y;

	if ((int)player.GetPos().x < SCREEN_HALF_W) {
		scroll_x = (int)pos.x;
	}
	else if ((int)player.GetPos().x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		scroll_x = SCREEN_HALF_W + (int)pos.x - (int)player.GetPos().x;
	}
	else {
		scroll_x = (int)pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if ((int)player.GetPos().y < SCREEN_HALF_H) {
		scroll_y = (int)pos.y;
	}
	else if ((int)player.GetPos().y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		scroll_y = SCREEN_HALF_H + (int)pos.y - (int)player.GetPos().y;
	}
	else {
		scroll_y = (int)pos.y - (STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	//向きに応じて描画
	if (direct == DIR_RIGHT) {
		DrawGraph((int)scroll_x, (int)scroll_y, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)scroll_x, (int)scroll_y, graphic_L, FALSE);
	}
}

//位置の決定
VECTOR Enemy::randomPos(int h, int w) {
	int posY, posX;
	while (1) {
		posY = GetRand(STAGE_HEIGHT[SceneMgr::nowStage] - 1);
		posX = GetRand(STAGE_WIDTH[SceneMgr::nowStage] - 1);

		bool canPut = true;

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				if (Map::GetMap(posY + CHIP_SIZE * y, posX + CHIP_SIZE * x) != BACK) {
					canPut = false;
					break;
				}
			}
		}

		if (canPut) break;
	}
	return VGet((float)posX * CHIP_SIZE, (float)posY * CHIP_SIZE, 0.0f);
}

//向きの決定
int Enemy::randomDir() {
	int r = GetRand(1);
	//移動方向を決める
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