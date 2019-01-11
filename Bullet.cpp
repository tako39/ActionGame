#include "Bullet.h"
#include "DxLib.h"
#include "Player.h"
#include "Define.h"
#include "SceneMgr.h"
#include <math.h>

Bullet::Bullet(const Player& player) {
	bulletGraphic = LoadGraph("image/bullet.png");

	//�������擾���Ĕ��ˈʒu�����߂�
	direct = player.GetDirect();
	if (direct == DIR_RIGHT) {
		pos = VGet(player.GetPos().x + CHIP_SIZE,
				   player.GetPos().y + CHIP_SIZE / 2 - BULLET_HEIGHT / 2,
				   0.0f);
	}
	else {
		pos = VGet(player.GetPos().x - BULLET_WIDTH,
				   player.GetPos().y + CHIP_SIZE / 2 - BULLET_HEIGHT / 2,
				   0.0f);
	}
	init = true;
	totalMove = 0.0f;
}

Bullet::~Bullet() {

}

void Bullet::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);
	if (!init) {	//�������͈ړ����Ȃ�
		move.x += bulletSpeed * direct;
	}
	else {
		init = false;
	}
	HitWall();				//�ǂɓ����������̏���
	totalMove += fabs(move.x);	//�ړ������𑫂�
	if (totalMove > CHIP_SIZE * 10) {	//���ړ�������10�}�X���ɂȂ����������
		isExist = false;
	}
}

void Bullet::Draw(const Player& player) {

	if ((int)player.GetPos().x < SCREEN_HALF_W) {
		screenPos.x = (int)pos.x;
	}
	else if ((int)player.GetPos().x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		screenPos.x = SCREEN_HALF_W + (int)pos.x - (int)player.GetPos().x;
	}
	else {
		screenPos.x = (int)pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if ((int)player.GetPos().y < SCREEN_HALF_H) {
		screenPos.y = (int)pos.y;
	}
	else if ((int)player.GetPos().y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		screenPos.y = SCREEN_HALF_H + (int)pos.y - (int)player.GetPos().y;
	}
	else {
		screenPos.y = (int)pos.y - (STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	DrawGraph((int)screenPos.x, (int)screenPos.y, bulletGraphic, FALSE);
}

//�ǂɓ����������̏���
void Bullet::HitWall() {
	float dummy = 0.0f;
	bool tauch = false;  //�ǂɐG�ꂽ��

	//����
	if (MapCollision(pos.y, pos.x, dummy, move.x) > 0) {
		tauch = true;
	}
	//�E��
	if (MapCollision(pos.y, pos.x + BULLET_WIDTH, dummy, move.x) > 0) {
		tauch = true;
	}
	//����
	if (MapCollision(pos.y + BULLET_HEIGHT, pos.x, dummy, move.x) > 0) {
		tauch = true;
	}
	//�E��
	if (MapCollision(pos.y + BULLET_HEIGHT, pos.x + BULLET_WIDTH, dummy, move.x) > 0) {
		tauch = true;
	}

	pos.x += move.x;

	if (tauch) {
		isExist = false;
	}
}