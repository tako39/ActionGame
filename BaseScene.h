#ifndef ___Class_BaseScene
#define ___Class_BaseScene

#include "Task.h"
#include "ISceneChanger.h"

//シーンの基底クラス。
class BaseScene : public Task {
protected:
	ISceneChanger* mSceneChanger;	//クラス所有元にシーン切り替えを伝えるインターフェイス

public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene();

	virtual void Update() {};
	virtual void Draw() {};
};

#endif