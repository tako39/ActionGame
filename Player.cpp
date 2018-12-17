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
	direct = DIR_RIGHT; //�n�߂͉E����
	jump_Flag = false;
	ver_Speed = 0.0f;

	degree = 0.0f;
	isPunch = false;
}

Player::~Player() {

}

void Player::Update(const EnemyMgr& enemymgr) {
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

	//A�������ꂽ�Ƃ��U��
	if (GetKey(KEY_INPUT_A) == 1) {
		isPunch = true;
		punchDir = direct; //�{�^�������������̌����ɍU��
	}
	
	if (isPunch) {
		Attack();
	}
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

	punchPos = pos;
	punchMove = VGet((float)sin(degree / 180.0f * PI) * CHIP_SIZE * 2 * punchDir, 0.0f, 0.0f);  //�p���`�̈ړ���
	SinkToWall();  //�ǂɂ߂荞�񂾎��̏���

	//�p���`�̕`��
	if (isPunch) {
		//��ʏ�̃p���`�̈ʒu
		VECTOR pPos = VGet((float)px + punchMove.x, (float)py, 0.0f);
		DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic, TRUE);
	}
}

//�ړ�
void Player::Move(float moveY, float moveX) {
	float dummy = 0.0f;

	//�㉺�����̈ړ�
	{	
		//����
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//�E��
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//����
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}

		pos.y += moveY;
	}
	//���E�����̈ړ�
	{
		//����
		MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX);
		//�E��
		MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);
		//����
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX);
		//�E��
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);

		pos.x += moveX;
	}
	//�ڒn����
	{
		//�����ƉE���ɒn�ʂ����邩�ǂ���
		if (Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + EPS) == GROUND ||
			Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS) == GROUND) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//�U��
void Player::Attack() {
	degree += 10.0f;
	if (degree >= 180.f) {
		isPunch = false;
		degree = 0.0f;
	}
}

//�ǂɂ߂荞�񂾎��̏���
void Player::SinkToWall() {
	float dummy = 0.0f;
	bool tauch = false;  //�ǂɐG�ꂽ��

	//����
	if (MapCollision(punchPos.y + EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//�E��
	if (MapCollision(punchPos.y + EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//����
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//�E��
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}

	punchPos.x += punchMove.x;

	if (tauch) {
		isPunch = false;
		degree = 0.0f;
	}
}