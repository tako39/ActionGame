#include "Bullet.h"
#include "DxLib.h"
#include "Player.h"
#include "Define.h"
#include "Game.h"
#include "Define.h"

Bullet::Bullet(const Player& player) {
	bulletGraphic = LoadGraph("image/bullet.png");
	//向きを取得して発射位置を決める
	direct = player.GetDirect();
	if (direct == DIR_RIGHT) {
		pos = VGet(player.GetPos().x + CHIP_SIZE,
				   player.GetPos().y + CHIP_SIZE / 2 - BULLET_HEIGHT / 2,
				   0.0f);
	}
	else {
		pos = VGet(player.GetPos().x - BULLET_WIDTH,
				   player.GetPos().y + CHIP_SIZE / 2 - BULLET_HEIGHT / 2,
				   0.0f);
	}
}

Bullet::~Bullet() {

}

void Bullet::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);
	move.x += bulletSpeed * direct;
	HitWall();
}

void Bullet::Draw(const Player& player) {
	//スクロールに合わせた描画
	int bx = SCREEN_HALF_W + (int)pos.x - (int)player.GetPos().x;
	int by = SCREEN_HALF_H + (int)pos.y - (int)player.GetPos().y;

	if ((int)player.GetPos().x - SCREEN_HALF_W < 0) {
		bx = (int)pos.x;
	}

	if ((int)player.GetPos().x - SCREEN_HALF_W >= SCREEN_WIDTH) {
		bx = (int)pos.x - SCREEN_WIDTH;
	}

	if ((int)player.GetPos().y - SCREEN_HALF_H < 0) {
		by = (int)pos.y;
	}

	if ((int)player.GetPos().y >= STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		by = (int)pos.y - (STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	DrawGraph(bx, by, bulletGraphic, FALSE);
}

//壁に当たった時の処理
void Bullet::HitWall() {
	float dummy = 0.0f;
	bool tauch = false;  //壁に触れたか

	//左上
	if (MapCollision(pos.y, pos.x, dummy, move.x) > 0) {
		tauch = true;
	}
	//右上
	if (MapCollision(pos.y, pos.x + BULLET_WIDTH, dummy, move.x) > 0) {
		tauch = true;
	}
	//左下
	if (MapCollision(pos.y + BULLET_HEIGHT, pos.x, dummy, move.x) > 0) {
		tauch = true;
	}
	//右下
	if (MapCollision(pos.y + BULLET_HEIGHT, pos.x + BULLET_WIDTH, dummy, move.x) > 0) {
		tauch = true;
	}

	pos.x += move.x;

	if (tauch) {
		isExist = false;
	}
}