#include "Object.h"
#include "Define.h"
#include "Stage.h"
#include "Game.h"
#include "Map.h"

Object::Object() {
	//���������Ă���
	jump_Flag = false;
	ver_Speed = 0.0f;
	isExist = true;
}

Object::~Object() {

}

//�����蔻��
int Object::MapCollision(float Y, float X, float &moveY, float &moveX) {
	float Top_y, Bottom_y, Left_x, Right_x;  //�v���C���[�̓����蔻��̈ʒu

	//�ړ���
	float nextY = Y + moveY;
	float nextX = X + moveX;

	//�ǂɓ������Ă��邩�ǂ���
	if (Map::GetMapChip(nextY, nextX) == GROUND) {

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