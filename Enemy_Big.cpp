#include "Enemy_Big.h"
#include "Define.h"
#include "Map.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include <math.h>

Big::Big() {
	SetHitPoint(HP_BIG);
	enemyType = ENEMY_BIG;
	size = VGet(CHIP_SIZE * 2, CHIP_SIZE * 2, 0.0f);
	graphic_R = LoadGraph("image/enemyBig_r.png");
	graphic_L = LoadGraph("image/enemyBig_l.png");
	isGround = false;
	pos = randomPos(2, 2);		//�����_���Ɉʒu��ݒ�
	direct = randomDir();		//�����_���Ɍ���������
	enemySpeed = randomSpeed();	//�����_���ɑ���������
}

Big::~Big() {

}

void Big::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);	//������

	if (isGround) move.x += enemySpeed * direct;	//�������̈ړ�

	ver_Speed += Gravity;	//�d�͂�������
	move.y = ver_Speed;

	Move(move.y, move.x);	//�ړ�
	LookAhead();	//������Ƃ�������ς���
}

void Big::Draw(const Player& player) {
	EnemyDraw(player);	//�G�̕`��
}