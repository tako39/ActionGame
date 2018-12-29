#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class EnemyMgr;

class Player :  public Object {
private:
	//�����ʒu
	const VECTOR firstPos[2] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

	int punchGraphic_R;		//�p���`�̉摜
	int punchGraphic_L;
	bool isPunch;			//�p���`���Ă��邩
	int punchDir;			//����
	float degree = 0.0f;	//����
	VECTOR punchPos;		//�ʒu
	VECTOR punchMove;		//�ړ���
	VECTOR screenPos;		//�X�N���[����̈ʒu

	bool damaged;			//�_���[�W���󂯂Ă��邩
	int flashCount;			//�_�ŗp
	int flashStartTime;		//�_���[�W���󂯂��̎���

	int hideGraphic;		//�B��Ă���Ƃ��̉摜
	int isHide;				//�B��Ă��邩

public:
	Player();
	~Player();

	void Update();
	void Draw();

	VECTOR GetPunchPos() const { return punchPos; }		//�p���`�̈ʒu�̎擾
	bool GetIsPunch() const { return isPunch; }			//�p���`�����Ă��邩
	VECTOR GetScreenPos() const { return screenPos; }	//�X�N���[����ł̈ʒu�̎擾

	void Move(float moveY, float moveX);	//�ړ�
	void Attack();		//�U��
	void HitWall();		//�p���`���ǂɓ����������̏���
	void HitEnemy(const EnemyMgr& enemyMgr);	//�G�ɓ����������̏���
};

#endif