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

//�����蔻��
int Object::MapCollision(float Y, float X, float &moveY, float &moveX) {
	float Top_y, Bottom_y, Left_x, Right_x;  //�v���C���[�̓����蔻��̈ʒu

	//�ړ���
	float nextY = Y + moveY;
	float nextX = X + moveX;

	//�ǂɓ������Ă��邩�ǂ���
	if (GetMapChip(nextY, nextX) == GROUND) {

		//�ǂɂ���
		Top_y = (float)((int)nextY / CHIP_SIZE)     * CHIP_SIZE;     // ��ӂ� Y ���W
		Bottom_y = (float)((int)nextY / CHIP_SIZE + 1) * CHIP_SIZE;  // ���ӂ� Y ���W
		Left_x = (float)((int)nextX / CHIP_SIZE)     * CHIP_SIZE;    // ���ӂ� X ���W
		Right_x = (float)((int)nextX / CHIP_SIZE + 1) * CHIP_SIZE;   // �E�ӂ� X ���W

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

	}

	return NONE; //�������Ă��Ȃ�
}