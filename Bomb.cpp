#include "Bomb.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Keyboard.h"

Bomb::Bomb(const Player& player) {
	setTime = GetNowCount();
	bombSound = LoadSoundMem("sound/bomb.mp3");
	bombGraphic_Count3 = LoadGraph("image/bomb_count3.png");
	bombGraphic_Count2 = LoadGraph("image/bomb_count2.png");
	bombGraphic_Count1 = LoadGraph("image/bomb_count1.png");
	bombGraphic_Red = LoadGraph("image/bomb_red.png");
	explosionGraphic = LoadGraph("image/explosion.png");
	pos = player.GetPos();
}

Bomb::~Bomb() {

}

void Bomb::Update() {
	//設置してから3秒経ったとき爆発
	if (GetNowCount() - setTime > 3000) {
		PlaySoundMem(bombSound, DX_PLAYTYPE_BACK);	//爆弾が爆発したときの音
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

	//カウントによって画像を変える
	if (GetNowCount() - setTime > 2800) {
		//爆発時に爆発のエフェクトを描画
		DrawGraph(scroll_x - CHIP_SIZE * 2, scroll_y - CHIP_SIZE * 2, explosionGraphic, TRUE);
	}
	else if (GetNowCount() - setTime > 1500) {
		//爆発が近いときは点滅させる
		if (GetNowCount() % 3 == 0) {
			DrawGraph(scroll_x, scroll_y, bombGraphic_Red, FALSE);
		}
		else {
			DrawGraph(scroll_x, scroll_y, bombGraphic_Count1, FALSE);
		}
	}
	else if (GetNowCount() - setTime > 1000) {
		DrawGraph(scroll_x, scroll_y, bombGraphic_Count2, FALSE);
	}
	else {
		DrawGraph(scroll_x, scroll_y, bombGraphic_Count3, FALSE);
	}
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