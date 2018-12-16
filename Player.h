#ifndef ___Class_Player
#define ___Class_Player

#include "Object.h"
#include "Define.h"
#include "DxLib.h"

class Player :  public Object {
private:
	//�����ʒu
	const VECTOR firstPos[1] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

	int punchGraphic;		//�摜
	bool is_punch;			//�p���`���Ă��邩
	int punchDir;			//����
	double degree = 0.0f;	//����
	VECTOR punchPos;		//�ʒu
	VECTOR punchMove;		//�ړ���

public:
	Player();
	~Player();

	void Update();
	void Draw();

	void Move(float moveY, float moveX);  //�ړ�
	void Attack();  //�U��
	void SinkToWall();  //�ǂւ̂߂荞��
};

#endif