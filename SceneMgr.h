#ifndef ___Class_SceneMgr
#define ___Class_SceneMgr

#include "ISceneChanger.h"
#include "BaseScene.h"

class SceneMgr : public ISceneChanger, Task {

private:
	BaseScene* mScene;    //シーン管理変数
	eScene mNextScene;    //次のシーン管理変数

public:
	static int nowStage;	//現在のステージ

	SceneMgr();
	~SceneMgr();

	void Update()     override;  //更新
	void Draw()       override;  //描画

	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene NextScene) override;

};

#endif