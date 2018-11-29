#ifndef ___Class_Object
#define ___Class_Object

#include "Task.h"
#include "DxLib.h"
#include "Define.h"

class Object : public Task {
protected:
	//Map map;  //map

	int graphic_R;  //‰EŒü‚«‰æ‘œ
	int graphic_L;  //¶Œü‚«‰æ‘œ

	VECTOR pos;   //ˆÊ’u
	VECTOR move;  //ˆÚ“®

	int direct;   //•ûŒü

public:
	VECTOR GetPos() const { return pos; }  //ˆÊ’u‚Ìæ“¾
};

#endif