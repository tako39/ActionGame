#ifndef ___Class_Object
#define ___Class_Object

#include "Task.h"
#include "DxLib.h"
#include "Define.h"

class Object : public Task {
protected:
	//Map map;  //map

	int graphic_R;  //�E�����摜
	int graphic_L;  //�������摜

	VECTOR pos;   //�ʒu
	VECTOR move;  //�ړ�

	int direct;   //����

public:
	VECTOR GetPos() const { return pos; }  //�ʒu�̎擾
};

#endif