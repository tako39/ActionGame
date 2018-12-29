#include "Player.h"
#include "Keyboard.h"
#include "Map.h"
#include "EnemyMgr.h"
#include "SceneMgr.h"
#include <math.h>

Player::Player() {
	hitPoint = MAX_HP;

	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	punchGraphic = LoadGraph("image/punch.png");
	hideGraphic = LoadGraph("image/player_hide.png");

	pos = firstPos[SceneMgr::nowStage];
	direct = DIR_RIGHT;	//�n�߂͉E�����Ƃ���
	jump_Flag = false;	//�W�����v���Ă��Ȃ����
	ver_Speed = 0.0f;

	degree = 0.0f;
	isPunch = false;	//�p���`���Ă��Ȃ����

	damaged = false;	//�_���[�W���󂯂Ă��Ȃ����
	flashCount = 0;

	isHide = false;		//�B��Ă��Ȃ����
}

Player::~Player() {

}

void Player::Update() {

	//�B���(�B��Ă���Ƃ��͓����Ȃ�)
	if (!jump_Flag && 0 < GetKey(KEY_INPUT_H) && GetKey(KEY_INPUT_H) <= 120) {
		isHide = true;
		return;
	}
	else {
		isHide = false;
	}

	move = VGet(0.0f, 0.0f, 0.0f);  //�ړ��ʂ̏�����

	//�E�ւ̈ړ�
	if (GetKey(KEY_INPUT_RIGHT) > 0) {
		move.x += jump_Flag ? AirSpeed : Speed;
		direct = DIR_RIGHT;
	}

	//���ւ̈ړ�
	if (GetKey(KEY_INPUT_LEFT) > 0) {
		move.x -= jump_Flag ? AirSpeed : Speed;
		direct = DIR_LEFT;
	}

	//�W�����v
	if (!jump_Flag && GetKey(KEY_INPUT_SPACE) == 1) {
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	//A�������ꂽ�Ƃ��U��
	if (GetKey(KEY_INPUT_A) == 1) {
		isPunch = true;
		punchDir = direct; //�{�^�������������̌����ɍU��
	}

	if (isPunch) {
		Attack();
	}

	ver_Speed += Gravity;	//�d�͂�������
	move.y = ver_Speed;

	Move(move.y, move.x);	//�ړ�
}

void Player::Draw() {
	//�X�N���[������
	screenPos = VGet((float)SCREEN_HALF_W, (float)SCREEN_HALF_H, 0.0f);

	if ((int)pos.x < SCREEN_HALF_W) {	//��ʂ̔����ȉ�
		screenPos.x = pos.x;
	}
	else if ((int)pos.x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {	//��ʂ̔���
		screenPos.x = SCREEN_HALF_W;
	}
	else {	//��ʂ̔����ȏ�
		screenPos.x = pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if ((int)pos.y < SCREEN_HALF_H) {
		screenPos.y = pos.y;
	}
	else if ((int)pos.y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		screenPos.y = SCREEN_HALF_H;
	}
	else {
		screenPos.y = pos.y - (STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	int graphic;	//�����ɉ������摜

	if (isHide) {	//�B��Ă���Ƃ�
		graphic = hideGraphic;
	}
	else {
		if (direct == DIR_RIGHT) {
			graphic = graphic_R;
		}
		else {
			graphic = graphic_L;
		}
	}

	if (damaged) {
		if (flashCount % 3 == 0) DrawGraph((int)screenPos.x, (int)screenPos.y, graphic, FALSE);
		flashCount++;
		if (flashCount >= 3) flashCount = 0;
	}
	else {
		DrawGraph((int)screenPos.x, (int)screenPos.y, graphic, FALSE);
	}

	punchPos = pos;
	punchMove = VGet((float)sin(degree / 180.0f * PI) * CHIP_SIZE * 2 * punchDir, 0.0f, 0.0f);  //�p���`�̈ړ���
	HitWall();  //�Ǔ����������̏���

	//�p���`�̕`��
	if (isPunch) {
		//��ʏ�̃p���`�̈ʒu
		VECTOR pPos = VGet(screenPos.x + punchMove.x, screenPos.y, 0.0f);
		DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic, TRUE);
	}
}

//�ړ�
void Player::Move(float moveY, float moveX) {
	float dummy = 0.0f;

	//�㉺�����̈ړ�
	{	
		//����
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -0.6f;
		}
		//�E��
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -0.6f;
		}
		//����
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//�E��
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}

		pos.y += moveY;
	}
	//���E�����̈ړ�
	{
		//����
		MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX);
		//�E��
		MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);
		//����
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX);
		//�E��
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);

		pos.x += moveX;
	}
	//�ڒn����
	{
		int ground_R = Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + EPS);
		int ground_L = Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS);
		//�����ƉE���ɒn�ʂ����邩�ǂ���
		if (ground_R == GROUND || (20 <= ground_R && ground_L <= 45) ||
			ground_L == GROUND || (20 <= ground_L && ground_L <= 45)) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//�U��
void Player::Attack() {
	degree += 10.0f;
	if (degree >= 180.f) {
		isPunch = false;
		degree = 0.0f;
	}
}

//�p���`���ǂɓ����������̏���
void Player::HitWall() {
	float dummy = 0.0f;
	bool tauch = false;  //�ǂɐG�ꂽ��

	//����
	if (MapCollision(punchPos.y + EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//�E��
	if (MapCollision(punchPos.y + EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//����
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//�E��
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}

	punchPos.x += punchMove.x;

	if (tauch) {
		isPunch = false;
		degree = 0.0f;
	}
}

//�G�ɓ����������̏���(���G����)
void Player::HitEnemy(const EnemyMgr& enemyMgr) {
	if (isHide) return;	//�B��Ă���Ƃ��̓_���[�W���󂯂Ȃ�

	if (!damaged) {
		for (int num = 0; num < ENEMY_NUM; num++) {
			if (enemyMgr.IsExist(num)) {
				VECTOR enemyPos = enemyMgr.GetEnemyPos(num);
				if (fabs(enemyPos.x - pos.x) < CHIP_SIZE &&
					fabs(enemyPos.y - pos.y) < CHIP_SIZE) {
					damaged = true;
					flashStartTime = GetNowCount();
					hitPoint -= 10;
					return;
				}
			}
		}
	}
	else {
		//�_���[�W���󂯂Ă���2�b�ȏ�o������
		if (GetNowCount() - flashStartTime > 2000) {
			damaged = false;
		}
	}
}