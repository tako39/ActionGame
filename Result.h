#ifndef ___Class_Result
#define ___Class_Result

#include "BaseScene.h"

class Result : public BaseScene {

public:
	Result(ISceneChanger* changer);
	~Result();

	void Update();
	void Draw();
};

#endif