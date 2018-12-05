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

	VECTOR pos;   //�ʒu
	int direct;   //����

	VECTOR move;  //�ړ�

public:
	VECTOR GetPos() const { return pos; }  //�ʒu�̎擾

	void SetPos(const VECTOR& sPos) {  //�ʒu�̃Z�b�g
		pos = sPos;
	}
	void SetDirect(const int& sDir) {  //�����̃Z�b�g
		direct = sDir;
	}

	int GetMap(int y, int x) const;  //map[y][x]�̒l�̎擾
	int GetMapChip(float y, float x) const;  //�ʒu(x, y)�ɊY������}�b�v�`�b�v�̒l�̎擾

	int MapCollision(float Y, float X, float &moveY, float &moveX); //�����蔻��
};

#endif