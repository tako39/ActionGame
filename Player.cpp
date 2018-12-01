#include "Player.h"
#include "Keyboard.h"
#include "Game.h"

Player::Player() {
	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	pos = firstPos[Game::nowStage];
	direct = DIR_RIGHT; //始めは右向き
	jump_Flag = false;
	ver_Speed = 0.0f;
}

Player::~Player() {

}

void Player::Update() {
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
}

void Player::Draw() {

	int px = SCREEN_HALF_W;  //プレイヤーの位置
	int py = SCREEN_HALF_H;  //プレイヤーの位置

	if ((int)pos.x - SCREEN_HALF_W < 0) {
		px = (int)pos.x;
	}

	if ((int)pos.x - SCREEN_HALF_W >= SCREEN_WIDTH) {
		px = (int)pos.x - SCREEN_WIDTH;
	}

	if ((int)pos.y - SCREEN_HALF_H < 0) {
		py = (int)pos.y;
	}

	if ((int)pos.y - SCREEN_HALF_H >= STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT) {
		py = (int)pos.y - (STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	if (direct == DIR_RIGHT) {
		DrawGraph(px, py, graphic_R, FALSE);
	}
	else {
		DrawGraph(px, py, graphic_L, FALSE);
	}
}