#include "Manual.h"
#include "DxLib.h"
#include "Define.h"

Manual::Manual() {
	manualImage = LoadGraph("image/manual.png");
}

Manual::~Manual() {

}

//�X�V
void Manual::Update() {
	
}

//�`��
void Manual::Draw() {
	DrawGraph((SCREEN_WIDTH - MANUAL_WIDTH) / 2, (SCREEN_HEIGHT - MANUAL_HEIGHT) / 2, manualImage, FALSE);
}
