#include "Map.h"
#include "Define.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"

Map::Map() {
	back_Graphic   = LoadGraph("image/back_Graphic.png");
	ground_Graphic = LoadGraph("image/ground_Graphic.png");
}

Map::~Map() {

}

//更新
void Map::Update(const Player& player) {
	playerPos = player.GetPos();
}

//描画
void Map::Draw() {

	//スクロール処理(上限と下限)
	int scroll_x = (int)playerPos.x - SCREEN_HALF_W;
	int scroll_y = (int)playerPos.y - SCREEN_HALF_H;

	if (scroll_x < 0) {
		scroll_x = 0;
	}

	if (scroll_x >= SCREEN_WIDTH) {
		scroll_x = SCREEN_WIDTH;
	}

	if (scroll_y < 0) {
		scroll_y = 0;
	}

	if (scroll_y >= STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT) {
		scroll_y = STAGE_HEIGHT[Game::nowStage] * CHIP_SIZE - SCREEN_HEIGHT;
	}

	//マップの描画
	for (int y = 0; y < STAGE_HEIGHT[Game::nowStage]; y++) {
		for (int x = 0; x < STAGE_WIDTH[Game::nowStage]; x++) {

			int chip_x = x * CHIP_SIZE - scroll_x;  //チップのx座標
			int chip_y = y * CHIP_SIZE - scroll_y;  //チップのy座標

			if (GetMap(y, x) == GROUND) {
				DrawGraph(chip_x, chip_y, ground_Graphic, TRUE);
			}
			else if (GetMap(y, x) == BACK) {
				DrawGraph(chip_x, chip_y, back_Graphic, TRUE);
			}
		}
	}
}

//map[y][x]の値の取得
int Map::GetMap(int y, int x) const {
	return map_stage[Game::nowStage][y][x];
}

//位置(x, y)に該当するマップチップの値の取得
int Map::GetMapChip(float y, float x) const {
	int Y = (int)y / CHIP_SIZE;
	int X = (int)x / CHIP_SIZE;

	//ステージ外
	if (Y < 0 || Y >= STAGE_HEIGHT[Game::nowStage] ||
		X < 0 || X >= STAGE_WIDTH[Game::nowStage]) {
		return -1;
	}

	return GetMap(Y, X);
}