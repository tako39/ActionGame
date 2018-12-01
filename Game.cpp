#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Keyboard.h"

int Game::nowStage = 0; //���݂̃X�e�[�W

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//������
void Game::Initialize() {
	player = new Player();
	map = new Map();
}

void Game::Finalize() {
	delete player;
	delete map;
}

//�X�V
void Game::Update() {
	player->Update();
	map->Update(*player);
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Game::Draw() {
	player->Draw();
	map->Draw();
	//BaseScene::Draw();  //�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}
