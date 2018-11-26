#include "Map.h"

Map::Map() {
	back_Graphic   = LoadGraph("image/back_Graphic.png");
	ground_Graphic = LoadGraph("image/ground_Graphic.png");
}

Map::~Map() {

}

void Map::Update() {

}

void Map::Draw() {
	for (int y = 0; y < STAGE_HEIGHT[Game::nowStage]; y++) {
		for (int x = 0; x < STAGE_WIDTH[Game::nowStage]; x++) {
			if (GetMap(y, x) == GROUND) {
				DrawGraph(x * CHIP_SIZE, y * CHIP_SIZE, ground_Graphic, FALSE);
			}
			else if (GetMap(y, x) == BACK) {
				DrawGraph(x * CHIP_SIZE, y * CHIP_SIZE, back_Graphic, FALSE);
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
		X < 0 || X >= STAGE_WIDTH[Game::nowStage] ) {
		return -1;
	}

	return GetMap(Y, X);
}