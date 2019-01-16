#include "Player.h"
#include "Keyboard.h"
#include "Map.h"
#include "EnemyMgr.h"
#include "SceneMgr.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include <math.h>

bool Player::isFirstPunch;
float Player::xPos;

Player::Player() {
	SetHitPoint(MAX_HP);
	size = VGet(CHIP_SIZE * 1.0f, CHIP_SIZE * 1.0f, 0.0f);	//�傫��

	jumpSound = LoadSoundMem("sound/jump.mp3");
	damageSound = LoadSoundMem("sound/damage_player.mp3");
	punchSound = LoadSoundMem("sound/punch.mp3");

	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	punchGraphic_R = LoadGraph("image/arrow_r.png");
	punchGraphic_L = LoadGraph("image/arrow_l.png");
	hideGraphic = LoadGraph("image/player_hide.png");

	pos = firstPos[SceneMgr::nowStage];	//�����ʒu�̐ݒ�
	xPos = pos.x;
	direct = DIR_RIGHT;	//�n�߂͉E�����Ƃ���
	jump_Flag = false;	//�W�����v���Ă��Ȃ����
	ver_Speed = 0.0f;

	degree = 0.0f;		//�p���`���Ă��Ȃ����
	isPunch = false;
	isFirstPunch = false;

	damaged = false;	//�_���[�W���󂯂Ă��Ȃ����
	flashCount = 0;

	isHide = false;		//�B��Ă��Ȃ����
}

Player::~Player() {

}

void Player::Update(BulletMgr& bulletMgr, BombMgr& bombMgr) {
	xPos = pos.x;

	if (GetHitPoint() <= 0) {	//�̗͂��O�ȉ��̎�
		SetExist(false);
	}

	//�B��邱�Ƃ��ł���(�B��Ă���Ƃ��͓����Ȃ�)
	if (!jump_Flag && GetKey(KEY_INPUT_F) > 0) {
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
		PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK);	//�W�����v��
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	isAttack = false;	//�U�����Ă��Ȃ����

	//A�������ꂽ�Ƃ��U��
	if (GetKey(KEY_INPUT_A) == 1) {
		isAttack = true;
		isPunch = true;
		isFirstPunch = true;
		punchDir = direct; //�{�^�������������̌����ɍU��
	}

	if (isPunch) {
		PlaySoundMem(punchSound, DX_PLAYTYPE_BACK);	//�p���`�����Ƃ��̉�
		Attack();
	}

	//�܂��U�����Ă��Ȃ��Ȃ�AS�{�^���Œe�𔭎�
	if ((GetKey(KEY_INPUT_S) == 1) && !isAttack) {
		isAttack = true;
		bulletMgr.Shot(*this);
	}
	//�܂��U�����Ă��Ȃ��Ȃ�AD�{�^���Ŕ��e��ݒu
	if ((GetKey(KEY_INPUT_D) == 1) && !isAttack) {
		isAttack = true;
		bombMgr.BombSet(*this);
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
		if (direct == DIR_RIGHT) {
			DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic_R, TRUE);
		}
		else {
			DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic_L, TRUE);
		}
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
		if (ground_R == GROUND || ground_R == CLOUD || (20 <= ground_R && ground_R <= 45) ||
			ground_L == GROUND || ground_R == CLOUD || (20 <= ground_L && ground_L <= 45)) {
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

//�G�ɓ����������̏���(���G���Ԃ���)
void Player::HitEnemy(const EnemyMgr& enemyMgr) {
	if (damaged) {
		//�_���[�W���󂯂Ă���2�b�ȏ�o������
		if (GetNowCount() - flashStartTime > 2000) {
			damaged = false;
		}
	}

	if (isHide) return;	//�B��Ă���Ƃ��̓_���[�W���󂯂Ȃ�

	if (!damaged) {
		for (int num = 0; num < MAX_ENEMY; num++) {
			if (enemyMgr.IsExist(num)) {
				VECTOR enemyPos = enemyMgr.GetEnemyPos(num);	//�G�̈ʒu
				int enemySizeX, enemySizeY;						//�G�̑傫��
				int type = enemyMgr.GetEnemyType(num);			//�G�̎��

				if (type == ENEMY_ZAKO) {
					enemySizeX = CHIP_SIZE;
					enemySizeY = CHIP_SIZE;
				}
				else if (type == ENEMY_TALL) {
					enemySizeX = CHIP_SIZE;
					enemySizeY = CHIP_SIZE * 2;
				}
				else if(type == ENEMY_BIG) {
					enemySizeX = CHIP_SIZE * 2;
					enemySizeY = CHIP_SIZE * 2;
				}
				else if (type == ENEMY_BOSS) {
					enemySizeX = CHIP_SIZE * 3;
					enemySizeY = CHIP_SIZE * 3;
				}

				//�����蔻��̌v�Z�A����
				if ((fabs(pos.x + size.x / 2 - (enemyPos.x + enemySizeX / 2)) < size.x / 2 + enemySizeX / 2) &&
					(fabs(pos.y + size.y / 2 - (enemyPos.y + enemySizeY / 2)) < size.y / 2 + enemySizeY / 2)) {
					PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//�_���[�W���󂯂��Ƃ��̉�
					damaged = true;
					flashStartTime = GetNowCount();	//�_���[�W���󂯂����Ԃ̋L��
					Damaged(10);	//10�_���[�W�󂯂�
					return;
				}
			}
		}
	}
}

//�ʒu�������ʒu�ɖ߂�
void Player::ResetPosition() {
	pos = firstPos[SceneMgr::nowStage];
}