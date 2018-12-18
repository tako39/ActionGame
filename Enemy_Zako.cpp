#include "Enemy_Zako.h"
#include "Player.h"
#include "Game.h"
#include "Map.h"
#include <math.h>

Zako::Zako() {
	graphic_R = LoadGraph("image/enemy_r.png");
	graphic_L = LoadGraph("image/enemy_l.png");
	isGround = false;
	pos = randomPos();		//�����_���Ɉʒu��ݒ�
	direct = randomDir();	//�����_���Ɍ���������
}

Zako::~Zako() {

}

void Zako::Update(const Player& player) {
	move = VGet(0.0f, 0.0f, 0.0f);	//������

	if (isGround) move.x += enemySpeed * direct;	//�������̈ړ�

	ver_Speed += Gravity;	//�d�͂�������
	move.y = ver_Speed;

	Move(move.y, move.x);	//�ړ�
	Collision(player);		//�����蔻��
}

void Zako::Draw(const Player& player) {
	//�X�N���[������
	int px = SCREEN_HALF_W + (int)pos.x - (int)player.GetPos().x;
	int py = SCREEN_HALF_H + (int)pos.y - (int)player.GetPos().y;

	if ((int)player.GetPos().x - SCREEN_HALF_W < 0) {
		px = (int)pos.x;
	}

	if ((int)player.GetPos().x - SCREEN_HALF_W >= SCREEN_WIDTH) {
		px = (int)pos.x - SCREEN_WIDTH;
	}

	if ((int)player.GetPos().y - SCREEN_HALF_H < 0) {
		py = (int)pos.y;
	}

	if ((int)player.GetPos().y >= STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		py = (int)pos.y - (STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	//�����ɉ����ĕ`��
	if (direct == DIR_RIGHT) {
		DrawGraph((int)px, (int)py, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)px, (int)py, graphic_L, FALSE);
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
}

VECTOR Zako::randomPos() {
	int posY, posX;
	while (1) {
		posY = GetRand(STAGE_HEIGHT[Game::nowStage] - 1);
		posX = GetRand(STAGE_WIDTH[Game::nowStage] - 1);
		if (Map::GetMap(posY, posX) == BACK) {
			break;
		}
	}
	return VGet(posX * CHIP_SIZE, posY * CHIP_SIZE, 0.0f);
}

int Zako::randomDir() {
	int r = GetRand(1);
	//�ړ����������߂�
	if (r == 0) return DIR_LEFT;
	else return DIR_RIGHT;
}

//�����蔻��
void Zako::Collision(const Player& player) {
	//�p���`���������Ă��邩
	if (player.GetIsPunch() &&
		fabs(pos.x - player.GetPunchPos().x) < CHIP_SIZE &&
		fabs(pos.y - player.GetPunchPos().y) < CHIP_SIZE) {
		isExist = false;
	}
}