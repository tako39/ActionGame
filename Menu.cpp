#include "Menu.h"
#include "DxLib.h"
#include "Stage.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Map.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Keyboard.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 0;	//�X�e�[�W0�ɂ���

	player = new Player();
	map = new Map();
	bulletMgr = new BulletMgr();
	bombMgr = new BombMgr();
}


Menu::~Menu() {
	delete player;
	delete map;
	delete bulletMgr;
	delete bombMgr;
}

//�X�V
void Menu::Update() {
	if (CheckHitKey(KEY_INPUT_G) != 0) {  //G�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Game);  //�V�[�����Q�[����ʂɕύX
	}
	if (CheckHitKey(KEY_INPUT_M) != 0) {  //C�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Manual);  //�V�[�����Q�[��������ʂɕύX
	}
	player->Update();
	if (GetKey(KEY_INPUT_S) == 1) {
		bulletMgr->Shot(*player);
	}
	if (GetKey(KEY_INPUT_B) == 1) {
		bombMgr->BombSet(*player);
	}
	map->Update(*player);
	bulletMgr->Update(*player);
	bombMgr->Update();
	bombMgr->DeleteBombAll();
}

//�`��
void Menu::Draw() {
	map->Draw();
	player->Draw();
	bulletMgr->Draw(*player);
	bombMgr->Draw(*player);
	//DrawString(0, 0, "G�L�[�������ƃQ�[���J�n�AM�L�[�������ƃQ�[������", GetColor(255, 0, 0));
}
