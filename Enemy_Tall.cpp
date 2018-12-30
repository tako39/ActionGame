#include "Enemy_Tall.h"
#include "Define.h"
#include "Map.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include "Player.h"
#include <math.h>

Tall::Tall() {
	enemyType = ENEMY_TALL;
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
		if (Map::GetMapChip(pos.y + CHIP_SIZE * 2 + EPS + CHIP_SIZE / 4, pos.x + EPS + nextMove) != GROUND ||
			Map::GetMapChip(pos.y + CHIP_SIZE * 2 + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS + nextMove) != GROUND) {
			direct *= -1;
		}
	}
}

// �����蔻��
void Tall::Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	//�p���`���������Ă��邩
	if (player.GetIsPunch() &&
		(fabs(pos.x - player.GetPunchPos().x) < CHIP_SIZE) &&
		(fabs(pos.y - player.GetPunchPos().y) < CHIP_SIZE * 1.5f)) {
		isExist = false;
		Display::Score += POINT_ENEMY_TALL;
		return;
	}

	//�e���������Ă��邩
	for (int bulletNum = 0; bulletNum < BULLET_NUM; bulletNum++) {
		if (bulletMgr.IsExist(bulletNum)) {	//�e�����݂���Ƃ�
			VECTOR bulletPos = bulletMgr.GetBulletPos(bulletNum);
			if ((fabs(pos.x + CHIP_SIZE / 2 - (bulletPos.x + BULLET_WIDTH / 2)) < CHIP_SIZE / 2 + BULLET_WIDTH / 2) &&
				(fabs(pos.y + CHIP_SIZE - (bulletPos.y + BULLET_HEIGHT / 2)) < CHIP_SIZE + BULLET_HEIGHT / 2)) {
				isExist = false;
				bulletMgr.DeleteBullet(bulletNum);
				Display::Score += POINT_ENEMY_TALL;
				return;
			}
		}
	}

	//���e�����������Ƃ��Ɋ������܂ꂽ��
	for (int bombNum = 0; bombNum < BOMB_NUM; bombNum++) {
		if (bombMgr.IsExplosion(bombNum)) {	//���������Ƃ�
			VECTOR bombPos = bombMgr.GetBombPos(bombNum);
			//���e�̎��͂Q�}�X���̋����ɂ���Ȃ瓖����
			if ((fabs(pos.x + CHIP_SIZE / 2 - (bombPos.x + CHIP_SIZE / 2)) < CHIP_SIZE * 2) &&
				(fabs(pos.y + CHIP_SIZE - (bombPos.y + CHIP_SIZE / 2)) < CHIP_SIZE * 2.5f)) {
				isExist = false;
				Display::Score += POINT_ENEMY_TALL;
				return;
			}
		}
	}
}