#include "Player.h"

Player::Player(const Map& cMap) : map(cMap) {
	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	pos = firstPos[Game::nowStage];
	direct = DIR_RIGHT; //始めは右向き
	jump_Flag = false;
	ver_Speed = 0.0f;
}

Player::~Player() {

}

void Player::Update() {
	move = VGet(0.0f, 0.0f, 0.0f);  //移動量の初期化

	if (GetKey(KEY_INPUT_RIGHT) > 0) {
		move.x += Speed;
		direct = DIR_RIGHT;
	}
	if (GetKey(KEY_INPUT_LEFT) > 0) {
		move.x -= Speed;
		direct = DIR_LEFT;
	}

	if (!jump_Flag && GetKey(KEY_INPUT_SPACE) > 0) {
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	ver_Speed += Gravity;
	move.y = ver_Speed;
	
	Move(move.y, move.x);  //移動
}

void Player::Draw() {
	if (direct == DIR_RIGHT) {
		DrawGraph((int)pos.x, (int)pos.y, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)pos.x, (int)pos.y, graphic_L, FALSE);
	}
}

//移動
void Player::Move(float moveY, float moveX) {
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
		if (map.GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + EPS) == GROUND ||
			map.GetMapChip(pos.y + CHIP_SIZE + EPS * 2, pos.x + CHIP_SIZE - EPS) == GROUND) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//当たり判定
int Player::MapCollision(float Y, float X, float &moveY, float &moveX) {
	float Top_y, Bottom_y, Left_x, Right_x; //プレイヤーの当たり判定の位置

	//移動先
	float nextY = Y + moveY;
	float nextX = X + moveX;

	//壁に当たっているかどうか
	if (map.GetMapChip(nextY, nextX) == GROUND) {

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