#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(ISceneChanger* changer) {
	mSceneChanger = changer;
}

BaseScene::~BaseScene() {
	
}
