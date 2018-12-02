#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Keyboard.h"
#include "Enemy.h"

int Game::nowStage = 0; //���݂̃X�e�[�W

Game::Game(ISceneChanger* changer) : BaseScene(changer) {

}

//������
void Game::Initialize() {
	player = new Player();
	map = new Map();
	enemy = new Enemy(VGet(10.0f * CHIP_SIZE, 1.0f, 0.0f), DIR_LEFT);
}

void Game::Finalize() {
	delete player;
	delete map;
	delete enemy;
}

//�X�V
void Game::Update() {
	player->Update();
	map->Update(*player);
	enemy->Update(*player);
	if (GetKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Game::Draw() {
	player->Draw();
	map->Draw();
	enemy->Draw();
	//BaseScene::Draw();  //�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}
