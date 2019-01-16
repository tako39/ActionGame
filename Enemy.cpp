#include "Enemy.h"
#include "Game.h"
#include "Define.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "SceneMgr.h"
#include "Map.h"
#include <math.h>

Enemy::Enemy() {
	damageSound = LoadSoundMem("sound/damage_enemy.mp3");
}

Enemy::~Enemy() {

}

void Enemy::EnemyDraw(const Player& player) {

	if (player.GetPos().x < SCREEN_HALF_W) {
		screenPos.x = pos.x;
	}
	else if (player.GetPos().x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		screenPos.x = SCREEN_HALF_W + pos.x - player.GetPos().x;
	}
	else {
		screenPos.x = pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if (player.GetPos().y < SCREEN_HALF_H) {
		screenPos.y = pos.y;
	}
	else if (player.GetPos().y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		screenPos.y = SCREEN_HALF_H + pos.y - player.GetPos().y;
	}
	else {
		screenPos.y = pos.y - (STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	//�����ɉ����ĕ`��
	if (direct == DIR_RIGHT) {
		DrawGraph((int)screenPos.x, (int)screenPos.y, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)screenPos.x, (int)screenPos.y, graphic_L, FALSE);
	}

	HpDraw();	//hp�̕`��
}

void Enemy::HpDraw() {
	int maxHp;	//�ő�hp
	if (enemyType == ENEMY_ZAKO) {
		maxHp = HP_ZAKO;
	}
	else if (enemyType == ENEMY_TALL) {
		maxHp = HP_TALL;
	}
	else if (enemyType == ENEMY_BIG) {
		maxHp = HP_BIG;
	}
	else if (enemyType == ENEMY_BOSS) {
		maxHp = HP_BOSS;
	}

	SetFontSize(12);
	DrawFormatString((int)screenPos.x, (int)screenPos.y - 12, GetColor(50, 50, 50), "%d/%d", hitPoint, maxHp);
}

//�ʒu�̌���
VECTOR Enemy::randomPos(int h, int w) {
	int posY, posX;
	while (1) {
		posY = GetRand(STAGE_HEIGHT[SceneMgr::nowStage] - 1);
		posX = GetRand(STAGE_WIDTH[SceneMgr::nowStage] - 1);

		//�G���}�b�v����͂ݏo���Ȃ��悤�ɂ���
		if ((posX >= STAGE_WIDTH[SceneMgr::nowStage] - w) ||
			(posY >= STAGE_HEIGHT[SceneMgr::nowStage] - h)) {
			continue;
		}

		int playerY = (int)(Player::xPos / CHIP_SIZE);	//�v���C���[�̂��ʒu
		if (abs(playerY - posX) <= 2) continue;			//2�}�X�ȏ㗣��

		bool canPut = true;		//�G��z�u�ł��邩

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				//�G���}�b�v����͂ݏo��Ȃ�
				if (Map::GetMap(posY + CHIP_SIZE * y, posX + CHIP_SIZE * x) != BACK) {
					canPut = false;
					break;
				}
			}
		}

		if (canPut) break;	//�G���z�u�ł���Ƃ����[�v�𔲂���
	}
	return VGet((float)posX * CHIP_SIZE, (float)posY * CHIP_SIZE, 0.0f);
}

//�����̌���
int Enemy::randomDir() {
	int r = GetRand(1);

	if (r == 0) return DIR_LEFT;
	else return DIR_RIGHT;
}

//�X�s�[�h�̌���
float Enemy::randomSpeed() {
	float speed = 2.0f;
	float decimal = GetRand(20) / 10.0f;
	return speed + decimal;
}

void Enemy::Move(float moveY, float moveX) {
	float dummy = 0.0f;
	//�㉺�����̈ړ�
	{
		//����
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//�E��
		if (MapCollision(pos.y + EPS, pos.x + size.x - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//����
		if (MapCollision(pos.y + size.y - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
			isGround = true;
		}
		//�E��
		if (MapCollision(pos.y + size.y - EPS, pos.x + size.x - EPS, moveY, dummy) == UP) {
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
		if (MapCollision(pos.y + EPS, pos.x + size.x - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}
		//����
		if (MapCollision(pos.y + size.y - EPS, pos.x + EPS, dummy, moveX) == RIGHT) {
			direct = DIR_RIGHT;
		}
		//�E��
		if (MapCollision(pos.y + size.y - EPS, pos.x + size.x - EPS, dummy, moveX) == LEFT) {
			direct = DIR_LEFT;
		}

		pos.x += moveX;
	}
}

void Enemy::LookAhead() {
	//���̈ړ��ŗ�����Ƃ��A������ς���
	float nextMove = enemySpeed * direct;
	//�i�ސ�ɒn�ʂ��Ȃ��Ȃ������ς���
	int leftEnd = Map::GetMapChip(pos.y + size.y - EPS + CHIP_SIZE / 4, pos.x + EPS + nextMove);
	if ((leftEnd != GROUND) && (leftEnd != CLOUD)) {
		direct = DIR_RIGHT;	//���[������������E��
	}
	int rightEnd = Map::GetMapChip(pos.y + size.y - EPS + CHIP_SIZE / 4, pos.x + size.x - EPS + nextMove);
	if ((rightEnd != GROUND) && (rightEnd != CLOUD)) {
		direct = DIR_LEFT;	//�E�[�����������獶��
	}
}

void Enemy::GroundCheck() {
	int leftGround = Map::GetMapChip(pos.y + size.y + EPS, pos.x + EPS);
	int rightGround = Map::GetMapChip(pos.y + size.y + EPS, pos.x + size.x - EPS);
	if ((leftGround  == GROUND) || (leftGround  == CLOUD) ||
		(rightGround == GROUND) || (rightGround == CLOUD)) {
		isGround = true;
	}
	else {
		isGround = false;
	}
}

// �����蔻��
void Enemy::Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {
	//�p���`���������Ă��邩
	if (CollisionPunch(player)) return;

	//�e���������Ă��邩
	if (CollisionBullet(bulletMgr)) return;

	//���e�����������Ƃ��Ɋ������܂ꂽ��
	if (CollisionBomb(bombMgr)) return;
}

//�����蔻��i�p���`�j
bool Enemy::CollisionPunch(const Player& player) {
	if (Player::isFirstPunch &&
		(fabs(pos.x + size.x / 2 - (player.GetPunchPos().x + PUNCH_WIDTH / 2)) < size.x / 2 + PUNCH_WIDTH / 2) &&
		(fabs(pos.y + size.y / 2 - (player.GetPunchPos().y + PUNCH_HEIGHT / 2)) < size.y / 2 + PUNCH_HEIGHT / 2)) {
		Damaged(DAMAGE_PUNCH);	//�_���[�W���󂯂�
		PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//�_���[�W��
		Player::isFirstPunch = false;
		return true;
	}
	return false;
}

//�����蔻��i�e�j
bool Enemy::CollisionBullet(BulletMgr& bulletMgr) {
	for (int bulletNum = 0; bulletNum < BULLET_NUM; bulletNum++) {
		if (bulletMgr.IsExist(bulletNum)) {		//�e�����݂���Ƃ�
			VECTOR bulletPos = bulletMgr.GetBulletPos(bulletNum);
			if ((fabs(pos.x + size.x / 2 - (bulletPos.x + BULLET_WIDTH / 2)) < size.x + BULLET_WIDTH / 2) &&
				(fabs(pos.y + size.y / 2 - (bulletPos.y + BULLET_HEIGHT / 2)) < size.y + BULLET_HEIGHT / 2)) {
				Damaged(DAMAGE_BULLET);		//�_���[�W���󂯂�
				bulletMgr.DeleteBullet(bulletNum);	//�e�̏���
				PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//�_���[�W��
				return true;
			}
		}
	}
	return false;
}

//�����蔻��i���e�j
bool Enemy::CollisionBomb(BombMgr& bombMgr) {
	for (int bombNum = 0; bombNum < BOMB_NUM; bombNum++) {
		if (bombMgr.IsExplosion(bombNum)) {		//���������Ƃ�
			VECTOR bombPos = bombMgr.GetBombPos(bombNum);
			//���e�̎��͂Q�}�X���̋����ɂ���Ȃ瓖����
			if ((fabs(pos.x + size.x / 2 - (bombPos.x + BOMB_WIDTH  / 2)) < size.x / 2 + BOMB_WIDTH  / 2 + BOMB_RANGE) &&
				(fabs(pos.y + size.y / 2 - (bombPos.y + BOMB_HEIGHT / 2)) < size.y / 2 + BOMB_HEIGHT / 2 + BOMB_RANGE)) {
				Damaged(DAMAGE_BOMB);	//�_���[�W���󂯂�
				PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//�_���[�W��
				return true;
			}
		}
	}
	return false;
}