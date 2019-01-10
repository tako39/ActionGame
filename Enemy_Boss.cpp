#include "Enemy_Boss.h"
#include "Define.h"
#include "Map.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include <math.h>

Boss::Boss() {
	SetHitPoint(HP_BOSS);
	enemyType = ENEMY_BOSS;
	size = VGet(CHIP_SIZE * 3, CHIP_SIZE * 3, 0.0f);	//�傫����ݒ�
	graphic_R = LoadGraph("image/enemyBoss_r.png");
	graphic_L = LoadGraph("image/enemyBoss_l.png");
	isGround = false;

	//pos = randomPos(3, 3);	//�����_���Ɉʒu��ݒ�
	pos = VGet(0.0f, 0.0f, 0.0f);	//�E�[�ɔz�u

	//direct = randomDir();		//�����_���Ɍ���������
	direct = DIR_LEFT;	//������

	//enemySpeed = randomSpeed();	//�����_���ɑ���������
	enemySpeed = 2.0f;
}

Boss::~Boss() {

}

//�p�^�[���ōs��������
void Boss::Update(const Player& player) {
	//move = VGet(0.0f, 0.0f, 0.0f);	//������

	//if (isGround) move.x += enemySpeed * direct;	//�������̈ړ�

	//ver_Speed += Gravity;	//�d�͂�������
	//move.y = ver_Speed;

	//Move(move.y, move.x);	//�ړ�
}

void Boss::Draw(const Player& player) {
	EnemyDraw(player);	//�G�̕`��
}

void Boss::Move(float moveY, float moveX) {
	float dummy = 0.0f;
	//�㉺�����̈ړ�
	{
		//����
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//�E��
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE * 3 - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//����
		if (MapCollision(pos.y + CHIP_SIZE * 3 - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE * 3 - EPS, pos.x + CHIP_SIZE * 3 - EPS, moveY, dummy) == UP) {
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
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE * 3 - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}
		//����
		if (MapCollision(pos.y + CHIP_SIZE * 3 - EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE * 3 - EPS, pos.x + CHIP_SIZE * 3 - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}

		pos.x += moveX;
	}
	//�ǂɓ����������̏�����ǉ�������
	////���̈ړ��ŗ�����Ƃ��A������ς���
	{
		//float nextMove = enemySpeed * direct;
		////�i�ސ�ɒn�ʂ��Ȃ��Ȃ������ς���
		//if (Map::GetMapChip(pos.y + CHIP_SIZE * 3 + EPS + CHIP_SIZE / 4, pos.x + EPS + nextMove) != GROUND) {
		//	direct = DIR_RIGHT;	//���[������������E��
		//}
		//if (Map::GetMapChip(pos.y + CHIP_SIZE * 3 + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE * 3 - EPS + nextMove) != GROUND) {
		//	direct = DIR_LEFT;	//�E�[�����������獶��
		//}
	}
}