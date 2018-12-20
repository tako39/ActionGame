#ifndef ___Class_Object
#define ___Class_Object

#include "Task.h"
#include "DxLib.h"

class Object : public Task {
protected:
	int graphic_R;  //�E�����摜
	int graphic_L;  //�������摜

	float ver_Speed;  //���������̈ړ���
	bool jump_Flag;   //true�Ȃ�W�����v��

	bool isExist;  //�������Ă��邩

	VECTOR pos;   //�ʒu
	int direct;   //����

	VECTOR move;  //�ړ�

public:
	Object();
	~Object();

	bool GetExist() const { return isExist; }	//�����m�F

	VECTOR GetPos() const { return pos; }  //�ʒu�̎擾

	int GetDirect() const { return direct; }	//�����̎擾

	int MapCollision(float Y, float X, float &moveY, float &moveX); //�����蔻��
};

#endif