#include "Player.h"

Player::Player(const Map& cMap) : map(cMap) {
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

	if (GetKey(KEY_INPUT_RIGHT) > 0) {
		move.x += Speed;
		direct = DIR_RIGHT;
	}
	if (GetKey(KEY_INPUT_LEFT) > 0) {
		move.x -= Speed;
		direct = DIR_LEFT;
	}

	if (!jump_Flag && GetKey(KEY_INPUT_SPACE) > 0) {
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	ver_Speed += Gravity;
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
		if (map.GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + EPS) == GROUND ||
			map.GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + CHIP_SIZE - EPS) == GROUND) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//�����蔻��
int Player::MapCollision(float Y, float X, float &moveY, float &moveX) {
	float Top_y, Bottom_y, Left_x, Right_x; //�v���C���[�̓����蔻��̈ʒu

	//�ړ���
	float nextY = Y + moveY;
	float nextX = X + moveX;

	//�ǂɓ������Ă��邩�ǂ���
	if (map.GetMapChip(nextY, nextX) == GROUND) {

		//�ǂɂ���
		Top_y = (float)((int)nextY / CHIP_SIZE)     * CHIP_SIZE;  // ��ӂ� Y ���W
		Bottom_y = (float)((int)nextY / CHIP_SIZE + 1) * CHIP_SIZE;  // ���ӂ� Y ���W
		Left_x = (float)((int)nextX / CHIP_SIZE)     * CHIP_SIZE;  // ���ӂ� X ���W
		Right_x = (float)((int)nextX / CHIP_SIZE + 1) * CHIP_SIZE;  // �E�ӂ� X ���W

		//�������Ă�����ǂ��痣��

		//��ӂɏՓ�
		if (moveY > 0.0f) {
			moveY = Top_y - Y - EPS;
			return UP;
		}
		//���ӂɏՓ�
		if (moveY < 0.0f) {
			moveY = Bottom_y - Y + EPS;
			return DOWN;
		}

		//���ӂɏՓ�
		if (moveX > 0.0f) {
			moveX = Left_x - X - EPS;
			return LEFT;
		}
		//�E�ӂɏՓ�
		if (moveX < 0.0f) {
			moveX = Right_x - X + EPS;
			return RIGHT;
		}

		return DOWN;
	}

	return NONE; //�������Ă��Ȃ�
}