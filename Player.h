#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class EnemyMgr;
class BulletMgr;
class BombMgr;

//�v���C���[�̃N���X
class Player :  public Object {
private:
	//�X�e�[�W���Ƃ̏����ʒu
	const VECTOR firstPos[STAGE_NUM] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0f),
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0f),
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0f),
	};

	int jumpSound;		//�W�����v�����Ƃ��̉�
	int damageSound;	//�_���[�W���󂯂��Ƃ��̉�
	int punchSound;		//�p���`�����Ƃ��̉�

	int punchGraphic_R;		//�p���`�̉摜�E
	int punchGraphic_L;		//�p���`�̉摜��
	bool isPunch;			//�p���`���Ă��邩
	int punchDir;			//����
	float degree = 0.0f;	//����
	VECTOR punchPos;		//�ʒu
	VECTOR punchMove;		//�ړ���

	bool damaged;			//�_���[�W���󂯂Ă��邩
	int flashCount;			//�_�ŗp
	int flashStartTime;		//�_���[�W���󂯂��u�Ԃ̎���

	int hideGraphic;		//�B��Ă���Ƃ��̉摜
	int isHide;				//�B��Ă��邩

	bool isAttack;			//���ɍU��������(�p���`�A�e�A���e�̂����ꂩ)

public:
	static bool isFirstPunch;		//�ŏ��̃p���`(�G�Ɉ�x�����������ǂ���)
	static float xPos;				//�v���C���\��pos.x(�G�̐����Ŏg�p)

	Player();
	~Player();

	void Update() {};
	void Update(BulletMgr& bulletMgr, BombMgr& bombMgr);
	void Draw();

	VECTOR GetPunchPos() const { return punchPos; }		//�p���`�̈ʒu�̎擾
	bool GetIsPunch() const { return isPunch; }			//�p���`�����Ă��邩

	void Move(float moveY, float moveX);		//�ړ�
	void PunchAttack();							//�p���`�U���̎����̕ύX
	void HitWall();								//�p���`���ǂɓ����������̏���
	void HitEnemy(const EnemyMgr& enemyMgr);	//�G�ɓ����������̏���

	void ResetPosition();	//�����ʒu�ɖ߂�
};

#endif