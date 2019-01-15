#include "Enemy_Zako.h"
#include "Player.h"
#include "Map.h"
#include "SceneMgr.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include <math.h>

Zako::Zako() {
	SetHitPoint(HP_ZAKO);
	enemyType = ENEMY_ZAKO;
	size = VGet(CHIP_SIZE * 1, CHIP_SIZE * 1, 0.0f);
	graphic_R = LoadGraph("image/enemyZako_r.png");
	graphic_L = LoadGraph("image/enemyZako_l.png");
	isGround = false;
	pos = randomPos(1, 1);		//�����_���Ɉʒu��ݒ�
	direct = randomDir();		//�����_���Ɍ���������
	enemySpeed = randomSpeed();	//�����_���ɑ���������
}

Zako::~Zako() {

}

void Zako::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);	//������

	if (isGround) move.x += enemySpeed * direct;	//�������̈ړ�

	ver_Speed += Gravity;	//�d�͂�������
	move.y = ver_Speed;

	Move(move.y, move.x);	//�ړ�
	LookAhead();	//������Ƃ�������ς���
}

void Zako::Draw(const Player& player) {
	EnemyDraw(player);	//�G�̕`��
}