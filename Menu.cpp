#include "Menu.h"
#include "DxLib.h"
#include "Stage.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Map.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Manual.h"
#include "Keyboard.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 0;	//�X�e�[�W0�ɂ���
	mPush = false;

	player = new Player();
	map = new Map();
	bulletMgr = new BulletMgr();
	bombMgr = new BombMgr();
	manual = new Manual();
}


Menu::~Menu() {
	delete player;
	delete map;
	delete bulletMgr;
	delete bombMgr;
	delete manual;
}

//�X�V
void Menu::Update() {
	if (GetKey(KEY_INPUT_G) != 0) {	//G�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Game);  //�V�[�����Q�[����ʂɕύX
	}
	if (GetKey(KEY_INPUT_M) == 1) {	//M�L�[����������Manual��\��
		mPush = !mPush;
	}
	if (mPush) {
		manual->Update();
		return;
	}

	player->Update(*bulletMgr, *bombMgr);
	map->Update();
	bulletMgr->Update(*player);
	bombMgr->Update();
	bombMgr->DeleteBombAll();
}

//�`��
void Menu::Draw() {
	map->Draw(*player);
	player->Draw();
	bulletMgr->Draw(*player);
	bombMgr->Draw(*player);
	if(mPush) manual->Draw();
}
