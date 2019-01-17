#ifndef ___Class_SceneMgr
#define ___Class_SceneMgr

#include "ISceneChanger.h"
#include "BaseScene.h"

//シーンの変更、現在のステージ数を記憶するクラス
class SceneMgr : public ISceneChanger, Task {
private:
	int selectSound;		//選択音

	BaseScene* mScene;		//シーン管理変数
	eScene mNextScene;		//次のシーン管理変数

public:
	static int nowStage;	//現在のステージ

	SceneMgr();
	~SceneMgr();

	void Update();	//更新
	void Draw();	//描画

	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene NextScene);
};

#endif