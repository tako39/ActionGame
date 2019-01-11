#include "Manual.h"
#include "DxLib.h"
#include "Define.h"

Manual::Manual() {
	manualImage = LoadGraph("image/manual.png");
}

Manual::~Manual() {

}

//çXêV
void Manual::Update() {
	
}

//ï`âÊ
void Manual::Draw() {
	DrawGraph((SCREEN_WIDTH - manualSize_x) / 2, (SCREEN_HEIGHT - manualSize_y) / 2, manualImage, FALSE);
}
