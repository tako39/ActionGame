#include "Object.h"
#include "Define.h"
#include "Stage.h"
#include "Game.h"

//map[y][x]�̒l�̎擾
int Object::GetMap(int y, int x) const {
	return map_stage[Game::nowStage][y][x];
}

//�ʒu(x, y)�ɊY������}�b�v�`�b�v�̒l�̎擾
int Object::GetMapChip(float y, float x) const {
	int Y = (int)y / CHIP_SIZE;
	int X = (int)x / CHIP_SIZE;

	//�X�e�[�W�O
	if (Y < 0 || Y >= STAGE_HEIGHT[Game::nowStage] ||
		X < 0 || X >= STAGE_WIDTH[Game::nowStage]) {
		return -1;
	}

	return GetMap(Y, X);
}

//�ړ�
void Object::Move(float moveY, float moveX) {
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
		if (GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + EPS) == GROUND ||
			GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + CHIP_SIZE - EPS) == GROUND) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//�����蔻��
int Object::MapCollision(float Y, float X, float &moveY, float &moveX) {
	float Top_y, Bottom_y, Left_x, Right_x; //�v���C���[�̓����蔻��̈ʒu

											//�ړ���
	float nextY = Y + moveY;
	float nextX = X + moveX;

	//�ǂɓ������Ă��邩�ǂ���
	if (GetMapChip(nextY, nextX) == GROUND) {

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