#include "Bomb.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Keyboard.h"

Bomb::Bomb(const Player& player) {
	setTime = GetNowCount();
	bombGraphic = LoadGraph("image/bomb.png");
	pos = player.GetPos();
}

Bomb::~Bomb() {

}

void Bomb::Update() {
	//設置してから3秒経ったとき爆発
	if (GetNowCount() - setTime > 3000) {
		isExist = false;
	}
	
	ver_Speed += Gravity;	//重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);	//移動
}

void Bomb::Draw(const Player& player) {
	//スクロールに合わせた描画
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

	DrawGraph(scroll_x, scroll_y, bombGraphic, FALSE);
}

//移動
void Bomb::Move(float moveY, float moveX) {
	float dummy = 0.0f;

	//上下成分の移動
	{
		//左下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//右下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}

		pos.y += moveY;
	}
}