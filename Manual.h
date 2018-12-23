#ifndef ___Class_Manual
#define ___Class_Manual

#include "BaseScene.h"

//設定画面クラス
class Manual : public BaseScene {

public:
	Manual(ISceneChanger* changer);
	~Manual();

	void Update() override;      //更新処理をオーバーライド。
	void Draw() override;        //描画処理をオーバーライド。
};

#endif