#ifndef ___Class_Player
#define ___Class_Player

#include "Task.h"
#include "DxLib.h"
#include "Define.h"
#include "Game.h"
#include "Map.h"
#include "Print.h"
#include "Keyboard.h"

class Map;

class Player : public Task {
private:
	const Map& map;  //map�̃R�s�[

	int player_Graphic_R;  //�E�����̉摜
	int player_Graphic_L;  //�������̉摜
	
	VECTOR pos;   //�ʒu
	VECTOR move;  //�ړ��p
	
	float ver_Speed;  //���������̈ړ���
	int direct;  //�������(1 : �E, -1 : ��)

	bool jump_Flag; //true�Ȃ�W�����v��

	//�����ʒu
	const VECTOR firstPos[1] =
	{
		VGet(1 * CHIP_SIZE, 1 * CHIP_SIZE, 0.0),
	};

public:
	Player(const Map& cMap);
	~Player();

	void Update();
	void Draw();

	VECTOR GetPos() const { return pos; }  //�ʒu�̎擾

	void Move(float moveY, float moveX); //�ړ�
	int MapCollision(float Y, float X, float &moveY, float &moveX); //�����蔻��
};

#endif