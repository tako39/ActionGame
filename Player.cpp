#include "Player.h"
#include "Keyboard.h"
#include "Game.h"

Player::Player() {
	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	pos = firstPos[Game::nowStage];
	direct = DIR_RIGHT; //�n�߂͉E����
	jump_Flag = false;
	ver_Speed = 0.0f;
}

Player::~Player() {

}

void Player::Update() {
	move = VGet(0.0f, 0.0f, 0.0f);  //�ړ��ʂ̏�����

	//�E�ւ̈ړ�
	if (GetKey(KEY_INPUT_RIGHT) > 0) {
		move.x += jump_Flag ? AirSpeed : Speed;
		direct = DIR_RIGHT;
	}

	//���ւ̈ړ�
	if (GetKey(KEY_INPUT_LEFT) > 0) {
		move.x -= jump_Flag ? AirSpeed : Speed;
		direct = DIR_LEFT;
	}

	//�W�����v
	if (!jump_Flag && GetKey(KEY_INPUT_SPACE) == 1) {
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	ver_Speed += Gravity;  //�d�͂�������
	move.y = ver_Speed;
	
	Move(move.y, move.x);  //�ړ�
}

void Player::Draw() {
	if (direct == DIR_RIGHT) {
		DrawGraph((int)pos.x, (int)pos.y, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)pos.x, (int)pos.y, graphic_L, FALSE);
	}
}