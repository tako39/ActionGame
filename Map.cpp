#include "Map.h"
#include "Define.h"
#include "Stage.h"
#include "Player.h"
#include "SceneMgr.h"
#include <iostream>
#include <string>

Map::Map() {
	back_Graphic   = LoadGraph("image/back_Graphic.png");
	ground_Graphic = LoadGraph("image/ground_Graphic.png");
	cloud_Graphic  = LoadGraph("image/cloud.png");

	for (int i = 0; i <= 25; i++) {
		std::string s = "image/image_";
		s += (char)('A' + i);
		s += ".png";
		image_Alpha[i] = LoadGraph(s.c_str());
	}
}

Map::~Map() {

}

//�X�V
void Map::Update() {
	
}

//�`��
void Map::Draw(const Player& player) {
	////�X�N���[������(����Ɖ���)
	int scroll_x, scroll_y;

	if ((int)player.GetPos().x < SCREEN_HALF_W) {
		scroll_x = 0;
	}
	else if ((int)player.GetPos().x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		scroll_x = (int)player.GetPos().x - SCREEN_HALF_W;
	}
	else {
		scroll_x = STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH;
	}

	if ((int)player.GetPos().y < SCREEN_HALF_H) {
		scroll_y = 0;
	}
	else if ((int)player.GetPos().y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		scroll_y = (int)player.GetPos().y - SCREEN_HALF_H;
	}
	else {
		scroll_y = STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT;
	}

	//�}�b�v�̕`��
	for (int y = 0; y < STAGE_HEIGHT[SceneMgr::nowStage]; y++) {
		for (int x = 0; x < STAGE_WIDTH[SceneMgr::nowStage]; x++) {

			int chip_x = x * CHIP_SIZE - scroll_x;  //�`�b�v��x���W
			int chip_y = y * CHIP_SIZE - scroll_y;  //�`�b�v��y���W

			int chip = GetMap(y, x);

			if (chip == GROUND) {
				DrawGraph(chip_x, chip_y, ground_Graphic, TRUE);
			}
			if (chip == BACK) {
				DrawGraph(chip_x, chip_y, back_Graphic, TRUE);
			}
			if (chip == CLOUD) {
				DrawGraph(chip_x, chip_y, cloud_Graphic, TRUE);
			}

			if (20 <= chip && chip <= 45) {
				DrawGraph(chip_x, chip_y, image_Alpha[chip - 20], TRUE);
			}
		}
	}
}

//map[y][x]�̒l�̎擾
int Map::GetMap(int y, int x) {
	return map_stage[SceneMgr::nowStage][y][x];
}

//�ʒu(x, y)�ɊY������}�b�v�`�b�v�̒l�̎擾
int Map::GetMapChip(float y, float x) {
	int Y = (int)y / CHIP_SIZE;
	int X = (int)x / CHIP_SIZE;

	//�X�e�[�W�O
	if (Y < 0 || Y >= STAGE_HEIGHT[SceneMgr::nowStage] ||
		X < 0 || X >= STAGE_WIDTH[SceneMgr::nowStage]) {
		return -1;
	}

	return GetMap(Y, X);
}