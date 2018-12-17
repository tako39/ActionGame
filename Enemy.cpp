#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "DxLib.h"
#include "Map.h"
#include <math.h>

Enemy::Enemy() {
	graphic_R = LoadGraph("image/enemy_r.png");
	graphic_L = LoadGraph("image/enemy_l.png");
	jump_Flag = false;
	ver_Speed = 0.0f;
	isGround = false;
	pos = randomPos();		//ランダムに位置を設定
	direct = randomDir();	//ランダムに向きを決定
}

Enemy::~Enemy() {

}

void Enemy::Update(const Player& player) {
	playerPos = player.GetPos();
	move = VGet(0.0f, 0.0f, 0.0f);  //初期化
	
	if(isGround) move.x += enemySpeed * direct;  //横方向の移動
	
	ver_Speed += Gravity;  //重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);  //移動
}

void Enemy::Draw() {

	//スクロール処理
	int px = SCREEN_HALF_W + (int)pos.x - (int)playerPos.x;
	int py = SCREEN_HALF_H + (int)pos.y - (int)playerPos.y;

	if ((int)playerPos.x - SCREEN_HALF_W < 0) {
		px = (int)pos.x;
	}

	if ((int)playerPos.x - SCREEN_HALF_W >= SCREEN_WIDTH) {
		px = (int)pos.x - SCREEN_WIDTH;
	}

	if ((int)playerPos.y - SCREEN_HALF_H < 0) {
		py = (int)pos.y;
	}

	if ((int)playerPos.y >= STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		py = (int)pos.y - (STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	//向きに応じて描画
	if (direct == DIR_RIGHT) {
		DrawGraph((int)px, (int)py, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)px, (int)py, graphic_L, FALSE);
	}
}

//移動
void Enemy::Move(float moveY, float moveX) {
	float dummy = 0.0f;
	//上下成分の移動
	{
		//左下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}
		//右下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//右上
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}

		pos.y += moveY;
	}
	//左右成分の移動
	{
		//左下
		if(MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct  =DIR_RIGHT;
		}
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//右下
		if(MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}
		//右上
		if(MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}

		pos.x += moveX;
	}
}

VECTOR Enemy::randomPos() {
	int posY, posX;
	while (1) {
		posY = GetRand(STAGE_HEIGHT[Game::nowStage] - 1);
		posX = GetRand(STAGE_WIDTH[Game::nowStage] - 1);
		if (Map::GetMap(posY, posX) == BACK) {
			break;
		}
	}
	return VGet(posX * CHIP_SIZE, posY * CHIP_SIZE, 0.0f);
}

int Enemy::randomDir() {
	int r = GetRand(1);
	//移動方向を決める
	if (r == 0) return DIR_LEFT;
	else return DIR_RIGHT;
}

//当たり判定
void Enemy::Collision(const Player& player) {
	//パンチが当たっているか
	if (player.GetIsPunch() &&
		fabs(pos.x - player.GetPunchPos().x) < CHIP_SIZE &&
		fabs(pos.y - player.GetPunchPos().y) < CHIP_SIZE) {
		isExist = false;
	}
}