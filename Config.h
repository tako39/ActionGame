#ifndef ___Class_Config
#define ___Class_Config

#include "BaseScene.h"

//設定画面クラス
class Config : public BaseScene {

public:
	Config(ISceneChanger* changer);
	~Config();
	void Update() override;      //更新処理をオーバーライド。
	void Draw() override;        //描画処理をオーバーライド。

};

#endif