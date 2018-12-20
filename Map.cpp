#include "Map.h"
#include "Define.h"
#include "Stage.h"
#include "Player.h"
#include "SceneMgr.h"

Map::Map() {
	back_Graphic   = LoadGraph("image/back_Graphic.png");
	ground_Graphic = LoadGraph("image/ground_Graphic.png");
}

Map::~Map() {

}

//�X�V
void Map::Update(const Player& player) {
	playerPos = player.GetPos();
}

//�`��
void Map::Draw() {
	////�X�N���[������(����Ɖ���)
	int scroll_x, scroll_y;

	if ((int)playerPos.x < SCREEN_HALF_W) {
		scroll_x = 0;
	}
	else if ((int)playerPos.x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		scroll_x = (int)playerPos.x - SCREEN_HALF_W;
	}
	else {
		scroll_x = STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH;
	}

	if ((int)playerPos.y < SCREEN_HALF_H) {
		scroll_y = 0;
	}
	else if ((int)playerPos.y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		scroll_y = (int)playerPos.y - SCREEN_HALF_H;
	}
	else {
		scroll_y = STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT;
	}

	//�}�b�v�̕`��
	for (int y = 0; y < STAGE_HEIGHT[SceneMgr::nowStage]; y++) {
		for (int x = 0; x < STAGE_WIDTH[SceneMgr::nowStage]; x++) {

			int chip_x = x * CHIP_SIZE - scroll_x;  //�`�b�v��x���W
			int chip_y = y * CHIP_SIZE - scroll_y;  //�`�b�v��y���W

			if (GetMap(y, x) == GROUND) {
				DrawGraph(chip_x, chip_y, ground_Graphic, TRUE);
			}
			else if (GetMap(y, x) == BACK) {
				DrawGraph(chip_x, chip_y, back_Graphic, TRUE);
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