#include "Game.h"

int Game::nowStage = 0; //���݂̃X�e�[�W

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//������
void Game::Initialize() {
	map = new Map();
	player = new Player(*map);
}

void Game::Finalize() {
	delete map;
	delete player;
}

//�X�V
void Game::Update() {
	map->Update();
	player->Update();
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Game::Draw() {
	map->Draw();
	player->Draw();
	//BaseScene::Draw();  //�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}
