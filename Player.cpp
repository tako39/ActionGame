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

	//�X�N���[������
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

	//�����ɉ����ĕ`��
	if (direct == DIR_RIGHT) {
		DrawGraph((int)px, (int)py, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)px, (int)py, graphic_L, FALSE);
	}
}

//�ړ�
void Player::Move(float moveY, float moveX) {
	float dummy = 0.0f;

	//�㉺�����̈ړ�
	{
		//����
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//����
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//�E��
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}

		pos.y += moveY;
	}
	//���E�����̈ړ�
	{
		//����
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX);
		//�E��
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);
		//����
		MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX);
		//�E��
		MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);

		pos.x += moveX;
	}
	//�ڒn����
	{
		//�����ƉE���ɒn�ʂ����邩�ǂ���
		if (GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + EPS) == GROUND ||
			GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS) == GROUND) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}