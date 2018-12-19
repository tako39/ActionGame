#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class EnemyMgr;

class Player :  public Object {
private:
	//�����ʒu
	const VECTOR firstPos[1] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

	int punchGraphic;		//�摜
	bool isPunch;			//�p���`���Ă��邩
	int punchDir;			//����
	float degree = 0.0f;	//����
	VECTOR punchPos;		//�ʒu
	VECTOR punchMove;		//�ړ���
	VECTOR screenPos;		//�X�N���[����̈ʒu

	bool damaged;	//�_���[�W���󂯂Ă��邩
	bool flash;		//�_�ŗp
	int flashStartTime;		//�_���[�W���󂯂��̎���

public:
	Player();
	~Player();

	void Update() {};
	void Update(const EnemyMgr& enemyMgr);
	void Draw();

	VECTOR GetPunchPos() const { return punchPos; }
	bool GetIsPunch() const { return isPunch; }
	VECTOR GetScreenPos() const { return screenPos; }

	void Move(float moveY, float moveX);	//�ړ�
	void Attack();		//�U��
	void HitWall();		//�p���`���ǂɓ����������̏���
	void HitEnemy(const EnemyMgr& enemyMgr);	//�G�ɓ����������̏���
};

#endif