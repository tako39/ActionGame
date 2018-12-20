#include "Enemy_Zako.h"
#include "Player.h"
#include "Map.h"
#include "SceneMgr.h"

Zako::Zako() {
	graphic_R = LoadGraph("image/enemy_r.png");
	graphic_L = LoadGraph("image/enemy_l.png");
	isGround = false;
	pos = randomPos();			//�����_���Ɉʒu��ݒ�
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
}

void Zako::Draw(const Player& player) {
	//�X�N���[������
	int scroll_x, scroll_y;

	if ((int)player.GetPos().x < SCREEN_HALF_W) {
		scroll_x = (int)pos.x;
	}
	else if ((int)player.GetPos().x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		scroll_x = SCREEN_HALF_W + (int)pos.x - (int)player.GetPos().x;
	}
	else {
		scroll_x = (int)pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if ((int)player.GetPos().y < SCREEN_HALF_H) {
		scroll_y = (int)pos.y;
	}
	else if ((int)player.GetPos().y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		scroll_y = SCREEN_HALF_H + (int)pos.y - (int)player.GetPos().y;
	}
	else {
		scroll_y = (int)pos.y - (STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	//�����ɉ����ĕ`��
	if (direct == DIR_RIGHT) {
		DrawGraph((int)scroll_x, (int)scroll_y, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)scroll_x, (int)scroll_y, graphic_L, FALSE);
	}
}

//�ړ�
void Zako::Move(float moveY, float moveX) {
	float dummy = 0.0f;
	//�㉺�����̈ړ�
	{
		//����
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
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
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//����
		if (MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}
		//�E��
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}

		pos.x += moveX;
	}
	//���̈ړ��ŗ�����Ƃ��A������ς���
	{
		float nextMove = enemySpeed * direct;
		//�i�ސ�ɒn�ʂ��Ȃ��Ȃ������ς���
		if (Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + EPS + nextMove) != GROUND ||
			Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS + nextMove) != GROUND) {
			direct *= -1;
		}
	}
}

//�ʒu�̌���
VECTOR Zako::randomPos() {
	int posY, posX;
	while (1) {
		posY = GetRand(STAGE_HEIGHT[SceneMgr::nowStage] - 1);
		posX = GetRand(STAGE_WIDTH[SceneMgr::nowStage] - 1);
		if (Map::GetMap(posY, posX) == BACK) {
			break;
		}
	}
	return VGet((float)posX * CHIP_SIZE, (float)posY * CHIP_SIZE, 0.0f);
}

//�����̌���
int Zako::randomDir() {
	int r = GetRand(1);
	//�ړ����������߂�
	if (r == 0) return DIR_LEFT;
	else return DIR_RIGHT;
}

//�X�s�[�h�̌���
float Zako::randomSpeed() {
	float speed;
	
	int r = GetRand(2);
	switch (r) {
	case 0:
		speed = 1.0f;
		break;
	case 1:
		speed = 2.0f;
		break;
	case 2:
		speed = 3.0f;
		break;
	}
	return speed;
}