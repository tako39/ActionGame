#include "Enemy_Tall.h"
#include "Define.h"
#include "Map.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include "Player.h"
#include <math.h>

Tall::Tall() {
	SetHitPoint(HP_TALL);
	enemyType = ENEMY_TALL;
	size = VGet(CHIP_SIZE * 2, CHIP_SIZE * 1, 0.0f);	//�傫����ݒ�
	graphic_R = LoadGraph("image/enemyTall_r.png");
	graphic_L = LoadGraph("image/enemyTall_l.png");
	isGround = false;
	pos = randomPos(1, 1);		//�����_���Ɉʒu��ݒ�
	direct = randomDir();		//�����_���Ɍ���������
	enemySpeed = randomSpeed();	//�����_���ɑ���������
}

Tall::Tall(VECTOR setPos) {
	enemyType = ENEMY_TALL;
	graphic_R = LoadGraph("image/enemyTall_r.png");
	graphic_L = LoadGraph("image/enemyTall_l.png");
	isGround = false;
	pos = setPos;				//setPos�Ɉʒu��ݒ�
	direct = randomDir();		//�����_���Ɍ���������
	enemySpeed = randomSpeed();	//�����_���ɑ���������
}

Tall::~Tall() {

}

void Tall::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);	//������

	if (isGround) move.x += enemySpeed * direct;	//�������̈ړ�

	ver_Speed += Gravity;	//�d�͂�������
	move.y = ver_Speed;

	Move(move.y, move.x);	//�ړ�
}

void Tall::Draw(const Player& player) {
	EnemyDraw(player);	//�G�̕`��
}

void Tall::Move(float moveY, float moveX) {
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
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}

		pos.y += moveY;
	}
	//���E�����̈ړ�
	{
		//����
		if (MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//�E��
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}
		//����
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE * 2 - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}

		pos.x += moveX;
	}
	//���̈ړ��ŗ�����Ƃ��A������ς���
	{
		float nextMove = enemySpeed * direct;
		//�i�ސ�ɒn�ʂ��Ȃ��Ȃ������ς���
		if (Map::GetMapChip(pos.y + CHIP_SIZE * 2 + EPS + CHIP_SIZE / 4, pos.x + EPS + nextMove) != GROUND) {
			direct = DIR_RIGHT;	//���[������������E��
		}
		if (Map::GetMapChip(pos.y + CHIP_SIZE * 2 + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS + nextMove) != GROUND) {
			direct = DIR_LEFT;	//�E�[�����������獶��
		}
	}
}