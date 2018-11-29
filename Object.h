#ifndef ___Class_Object
#define ___Class_Object

#include "Task.h"
#include "DxLib.h"
#include "Define.h"

class Object : public Task {
protected:
	//Map map;  //map

	int graphic_R;  //右向き画像
	int graphic_L;  //左向き画像

	VECTOR pos;   //位置
	VECTOR move;  //移動

	int direct;   //方向

public:
	VECTOR GetPos() const { return pos; }  //位置の取得
};

#endif