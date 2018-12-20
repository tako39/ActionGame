#include "Enemy_Zako.h"
#include "Player.h"
#include "Map.h"
#include "SceneMgr.h"

Zako::Zako() {
	graphic_R = LoadGraph("image/enemy_r.png");
	graphic_L = LoadGraph("image/enemy_l.png");
	isGround = false;
	pos = randomPos();			//ランダムに位置を設定
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
}

void Zako::Draw(const Player& player) {
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

//移動
void Zako::Move(float moveY, float moveX) {
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
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//右下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}
		//右上
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}

		pos.x += moveX;
	}
	//次の移動で落ちるとき、向きを変える
	{
		float nextMove = enemySpeed * direct;
		//進む先に地面がないなら向きを変える
		if (Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + EPS + nextMove) != GROUND ||
			Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS + nextMove) != GROUND) {
			direct *= -1;
		}
	}
}

//位置の決定
VECTOR Zako::randomPos() {
	int posY, posX;
	while (1) {
		posY = GetRand(STAGE_HEIGHT[SceneMgr::nowStage] - 1);
		posX = GetRand(STAGE_WIDTH[SceneMgr::nowStage] - 1);
		if (Map::GetMap(posY, posX) == BACK) {
			break;
		}
	}
	return VGet((float)posX * CHIP_SIZE, (float)posY * CHIP_SIZE, 0.0f);
}

//向きの決定
int Zako::randomDir() {
	int r = GetRand(1);
	//移動方向を決める
	if (r == 0) return DIR_LEFT;
	else return DIR_RIGHT;
}

//スピードの決定
float Zako::randomSpeed() {
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