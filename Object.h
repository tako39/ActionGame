#ifndef ___Class_Object
#define ___Class_Object

#include "Task.h"
#include "DxLib.h"

//�I�u�W�F�N�g�Ɍp������N���X
class Object : public Task {
protected:
	int hitPoint;		//�̗�
	bool isExist;		//�������Ă��邩

	VECTOR size;		//�傫��
	int graphic_R;		//�E�����摜
	int graphic_L;		//�������摜

	float ver_Speed;	//���������̈ړ���
	bool jump_Flag;		//true�Ȃ�W�����v��

	VECTOR pos;			//�ʒu
	int direct;			//����
	VECTOR move;		//�ړ�

	VECTOR screenPos;	//�X�N���[����̈ʒu

public:
	Object();
	~Object();

	int  GetHitPoint() const { return hitPoint; }		//HP���擾����
	void SetHitPoint(int hp) { hitPoint = hp; }			//HP���Z�b�g����
	void Damaged(int damege) { hitPoint -= damege; }	//�_���[�W���󂯂�

	bool GetExist() const { return isExist; }			//�����̊m�F
	void SetExist(bool exist) { isExist = exist; }		//�����̕ύX

	void SetPos(VECTOR sPos) { pos = sPos; }			//�ʒu���Z�b�g����

	VECTOR GetSize() const { return size; }				//�傫���̎擾
	VECTOR GetPos() const { return pos; }				//�ʒu�̎擾
	int GetDirect() const { return direct; }			//�����̎擾

	VECTOR GetScreenPos() const { return screenPos; }	//�X�N���[����ł̈ʒu�̎擾

	int MapCollision(float Y, float X, float &moveY, float &moveX); //�����蔻��
};

#endif