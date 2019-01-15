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
	size = VGet(CHIP_SIZE * 1, CHIP_SIZE * 2, 0.0f);
	graphic_R = LoadGraph("image/enemyTall_r.png");
	graphic_L = LoadGraph("image/enemyTall_l.png");
	isGround = false;
	pos = randomPos(1, 1);		//�����_���Ɉʒu��ݒ�
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
	LookAhead();	//������Ƃ�������ς���
}

void Tall::Draw(const Player& player) {
	EnemyDraw(player);	//�G�̕`��
}