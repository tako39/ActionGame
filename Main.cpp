#include "DxLib.h"
#include "SceneMgr.h"
#include "Define.h"
#include "Keyboard.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ウィンドウモード変更と初期化と裏画面設定
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	//画面更新 & メッセージ処理 & 画面消去
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
		UpdateKey();  //キーの更新

		sceneMgr.Update();  //更新
		sceneMgr.Draw();    //描画

	}

	sceneMgr.Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}