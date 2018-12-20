#include "Menu.h"
#include "DxLib.h"
#include "Stage.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Map.h"
#include "BulletMgr.h"
#include "Keyboard.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 0;	//�X�e�[�W0�ɂ���
	player = new Player();
	map = new Map();
	bulletMgr = new BulletMgr();
}


Menu::~Menu() {
	delete player;
	delete map;
	delete bulletMgr;
}

//�X�V
void Menu::Update() {
	if (CheckHitKey(KEY_INPUT_G) != 0) {  //G�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Game);  //�V�[�����Q�[����ʂɕύX
	}
	if (CheckHitKey(KEY_INPUT_C) != 0) {  //C�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Config);  //�V�[����ݒ��ʂɕύX
	}
	player->Update();
	if (GetKey(KEY_INPUT_S) == 1) {
		bulletMgr->Shot(*player);
	}
	map->Update(*player);
	bulletMgr->Update(*player);
}

//�`��
void Menu::Draw() {
	player->Draw();
	map->Draw();
	bulletMgr->Draw(*player);
	DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "G�L�[�������ƃQ�[����ʂɐi�݂܂��B", GetColor(255, 0, 0));
	DrawString(0, 40, "C�L�[�������Ɓ@�ݒ��ʂɐi�݂܂��B", GetColor(255, 0, 0));
}
