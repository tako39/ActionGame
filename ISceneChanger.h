#ifndef ___Class_ISceneChanger
#define ___Class_ISceneChanger

typedef enum {
	eScene_Menu,		//メニュー画面
	eScene_Game,		//ゲーム画面
	eScene_GameOver,	//ゲームオーバー画面
	eScene_GameClear,	//ゲームクリア画面

	eScene_None,		//無し
} eScene;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;	//指定シーンに変更する
};

inline ISceneChanger::~ISceneChanger() {

}

#endif