#ifndef ___Class_Object
#define ___Class_Object

#include "Task.h"
#include "DxLib.h"

class Object : public Task {
protected:
	int hitPoint;	//�̗�
	bool isExist;	//�������Ă��邩

	int graphic_R;  //�E�����摜
	int graphic_L;  //�������摜

	float ver_Speed;  //���������̈ړ���
	bool jump_Flag;   //true�Ȃ�W�����v��

	VECTOR pos;   //�ʒu
	int direct;   //����

	VECTOR move;  //�ړ�

public:
	Object();
	~Object();

	void SetHitPoint(int hp) { hitPoint = hp; }			//HP���Z�b�g����
	int GetHitPoint() const { return hitPoint; }		//HP���擾����
	void Damaged(int damege) { hitPoint -= damege; }	//�_���[�W��^����

	bool GetExist() const { return isExist; }		//�����m�F

	VECTOR GetPos() const { return pos; }		//�ʒu�̎擾
	int GetDirect() const { return direct; }	//�����̎擾

	int MapCollision(float Y, float X, float &moveY, float &moveX); //�����蔻��
};

#endif