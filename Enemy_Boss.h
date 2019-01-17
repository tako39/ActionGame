#ifndef ___Class_Boss
#define ___Class_Boss

#include "Enemy.h"
#include "Define.h"

//Enemy_Boss�𐶐�����N���X
class Boss : public Enemy {
private:
	int fallSound;		//������Ƃ��̉�
	int createSound;	//�G�𑝂₷�Ƃ��̉�

	int frameCount;	//�J�E���g

	//Action_Dash�Ŏg�p
	bool isAction_Dash;	//Action_Dash����
	int sandGprahic_r;	//�����̉摜
	int sandGraphic_l;
	int flushCount;

	//Action_Jump�Ŏg�p
	const VECTOR upPos[5] = {	//�㏸����ʒu(0~4��4��)
		VGet( 5 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(10 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(15 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(20 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
		VGet(25 * CHIP_SIZE, 10 * CHIP_SIZE, 0.0f),
	};
	bool isAction_Jump;		//Action_Jump����
	bool firstAction_Jump;		//Action_Jump�J�n����
	float diff_x, diff_y;	//pos����upPos�܂ł̍�
	bool isRise;			//�㏸����
	bool isFall;			//��������
	int fallStep;			//�����̒i�K(0~4)
	int moveDirect;			//�ړ�����

	//Action_Wait�Ŏg�p
	bool isAction_Wait;		//�s����̑ҋ@
	int waitCount;			//�ҋ@�t���[���̃J�E���g

public:
	Boss();
	~Boss();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void Action_Dash();	//�����Ĉړ�
	void Action_Jump();	//�W�����v�ňړ�
	void Action_Create();	//���Ԃ̐���
	bool Action_Wait();	//�ҋ@

	//Action_Create�Ŏg�p
	static bool isAction_Create;	//ActionCreate����
};

#endif