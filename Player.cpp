#include "Player.h"
#include "Keyboard.h"
#include "Game.h"
#include "Map.h"
#include <math.h>

Player::Player() {
	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	punchGraphic = LoadGraph("image/punch.png");

	pos = firstPos[Game::nowStage];
	direct = DIR_RIGHT; //始めは右向き
	jump_Flag = false;
	ver_Speed = 0.0f;

	degree = 0.0f;
	isPunch = false;
}

Player::~Player() {

}

void Player::Update(const EnemyMgr& enemymgr) {
	move = VGet(0.0f, 0.0f, 0.0f);  //移動量の初期化

	//右への移動
	if (GetKey(KEY_INPUT_RIGHT) > 0) {
		move.x += jump_Flag ? AirSpeed : Speed;
		direct = DIR_RIGHT;
	}

	//左への移動
	if (GetKey(KEY_INPUT_LEFT) > 0) {
		move.x -= jump_Flag ? AirSpeed : Speed;
		direct = DIR_LEFT;
	}

	//ジャンプ
	if (!jump_Flag && GetKey(KEY_INPUT_SPACE) == 1) {
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	ver_Speed += Gravity;  //重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);  //移動

	//Aが押されたとき攻撃
	if (GetKey(KEY_INPUT_A) == 1) {
		isPunch = true;
		punchDir = direct; //ボタンを押した時の向きに攻撃
	}
	
	if (isPunch) {
		Attack();
	}
}

void Player::Draw() {

	//スクロール処理
	int px = SCREEN_HALF_W;
	int py = SCREEN_HALF_H;

	if ((int)pos.x - SCREEN_HALF_W < 0) {
		px = (int)pos.x;
	}

	if ((int)pos.x - SCREEN_HALF_W >= SCREEN_WIDTH) {
		px = (int)pos.x - SCREEN_WIDTH;
	}

	if ((int)pos.y - SCREEN_HALF_H < 0) {
		py = (int)pos.y;
	}

	if ((int)pos.y >= STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		py = (int)pos.y - (STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	//向きに応じて描画
	if (direct == DIR_RIGHT) {
		DrawGraph((int)px, (int)py, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)px, (int)py, graphic_L, FALSE);
	}

	punchPos = pos;
	punchMove = VGet((float)sin(degree / 180.0f * PI) * CHIP_SIZE * 2 * punchDir, 0.0f, 0.0f);  //パンチの移動量
	SinkToWall();  //壁にめり込んだ時の処理

	//パンチの描画
	if (isPunch) {
		//画面上のパンチの位置
		VECTOR pPos = VGet((float)px + punchMove.x, (float)py, 0.0f);
		DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic, TRUE);
	}
}

//移動
void Player::Move(float moveY, float moveX) {
	float dummy = 0.0f;

	//上下成分の移動
	{	
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//右上
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
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
	//左右成分の移動
	{
		//左上
		MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX);
		//右上
		MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);
		//左下
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX);
		//右下
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);

		pos.x += moveX;
	}
	//接地判定
	{
		//左下と右下に地面があるかどうか
		if (Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + EPS) == GROUND ||
			Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS) == GROUND) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//攻撃
void Player::Attack() {
	degree += 10.0f;
	if (degree >= 180.f) {
		isPunch = false;
		degree = 0.0f;
	}
}

//壁にめり込んだ時の処理
void Player::SinkToWall() {
	float dummy = 0.0f;
	bool tauch = false;  //壁に触れたか

	//左上
	if (MapCollision(punchPos.y + EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//右上
	if (MapCollision(punchPos.y + EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//左下
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//右下
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}

	punchPos.x += punchMove.x;

	if (tauch) {
		isPunch = false;
		degree = 0.0f;
	}
}