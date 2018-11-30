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

//移動
void Object::Move(float moveY, float moveX) {
	float dummy = 0.0f;

	//上下成分の移動
	{
		//左下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//右下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}
		//右上
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -1.0f;
		}

		pos.y += moveY;
	}
	//左右成分の移動
	{
		//左下
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX);
		//右下
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);
		//左上
		MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX);
		//右上
		MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);

		pos.x += moveX;
	}
	//接地判定
	{
		//左下と右下に地面があるかどうか
		if (GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + EPS) == GROUND ||
			GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + CHIP_SIZE - EPS) == GROUND) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//当たり判定
int Object::MapCollision(float Y, float X, float &moveY, float &moveX) {
	float Top_y, Bottom_y, Left_x, Right_x; //プレイヤーの当たり判定の位置

											//移動先
	float nextY = Y + moveY;
	float nextX = X + moveX;

	//壁に当たっているかどうか
	if (GetMapChip(nextY, nextX) == GROUND) {

		//壁について
		Top_y = (float)((int)nextY / CHIP_SIZE)     * CHIP_SIZE;  // 上辺の Y 座標
		Bottom_y = (float)((int)nextY / CHIP_SIZE + 1) * CHIP_SIZE;  // 下辺の Y 座標
		Left_x = (float)((int)nextX / CHIP_SIZE)     * CHIP_SIZE;  // 左辺の X 座標
		Right_x = (float)((int)nextX / CHIP_SIZE + 1) * CHIP_SIZE;  // 右辺の X 座標

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

		return DOWN;
	}

	return NONE; //当たっていない
}