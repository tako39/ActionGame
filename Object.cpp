#include "Object.h"
#include "Define.h"
#include "Stage.h"
#include "Game.h"

//map[y][x]の値の取得
int Object::GetMap(int y, int x) const {
	return map_stage[Game::nowStage][y][x];
}

//位置(x, y)に該当するマップチップの値の取得
int Object::GetMapChip(float y, float x) const {
	int Y = (int)y / CHIP_SIZE;
	int X = (int)x / CHIP_SIZE;

	//ステージ外
	if (Y < 0 || Y >= STAGE_HEIGHT[Game::nowStage] ||
		X < 0 || X >= STAGE_WIDTH[Game::nowStage]) {
		return -1;
	}

	return GetMap(Y, X);
}

//当たり判定
int Object::MapCollision(float Y, float X, float &moveY, float &moveX) {
	float Top_y, Bottom_y, Left_x, Right_x;  //プレイヤーの当たり判定の位置

	//移動先
	float nextY = Y + moveY;
	float nextX = X + moveX;

	//壁に当たっているかどうか
	if (GetMapChip(nextY, nextX) == GROUND) {

		//壁について
		Top_y = (float)((int)nextY / CHIP_SIZE)     * CHIP_SIZE;     // 上辺の Y 座標
		Bottom_y = (float)((int)nextY / CHIP_SIZE + 1) * CHIP_SIZE;  // 下辺の Y 座標
		Left_x = (float)((int)nextX / CHIP_SIZE)     * CHIP_SIZE;    // 左辺の X 座標
		Right_x = (float)((int)nextX / CHIP_SIZE + 1) * CHIP_SIZE;   // 右辺の X 座標

		//当たっていたら壁から離す

		//上辺に衝突
		if (moveY > 0.0f) {
			moveY = Top_y - Y - EPS;
			return UP;
		}
		//下辺に衝突
		if (moveY < 0.0f) {
			moveY = Bottom_y - Y + EPS;
			return DOWN;
		}

		//左辺に衝突
		if (moveX > 0.0f) {
			moveX = Left_x - X - EPS;
			return LEFT;
		}
		//右辺に衝突
		if (moveX < 0.0f) {
			moveX = Right_x - X + EPS;
			return RIGHT;
		}

	}

	return NONE; //当たっていない
}