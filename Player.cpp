#include "Player.h"
#include "Keyboard.h"
#include "Map.h"
#include "EnemyMgr.h"
#include "SceneMgr.h"
#include <math.h>

Player::Player() {
	hitPoint = MAX_HP;

	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	punchGraphic = LoadGraph("image/punch.png");
	hideGraphic = LoadGraph("image/player_hide.png");

	pos = firstPos[SceneMgr::nowStage];
	direct = DIR_RIGHT;	//始めは右向きとする
	jump_Flag = false;	//ジャンプしていない状態
	ver_Speed = 0.0f;

	degree = 0.0f;
	isPunch = false;	//パンチしていない状態

	damaged = false;	//ダメージを受けていない状態
	flashCount = 0;

	isHide = false;		//隠れていない状態
}

Player::~Player() {

}

void Player::Update() {

	//隠れる(隠れているときは動けない)
	if (!jump_Flag && 0 < GetKey(KEY_INPUT_H) && GetKey(KEY_INPUT_H) <= 120) {
		isHide = true;
		return;
	}
	else {
		isHide = false;
	}

	move = VGet(0.0f, 0.0f, 0.0f);  //移動量の初期化

	//右への移動
	if (GetKey(KEY_INPUT_RIGHT) > 0) {
		move.x += jump_Flag ? AirSpeed : Speed;
		direct = DIR_RIGHT;
	}

	//左への移動
	if (GetKey(KEY_INPUT_LEFT) > 0) {
		move.x -= jump_Flag ? AirSpeed : Speed;
		direct = DIR_LEFT;
	}

	//ジャンプ
	if (!jump_Flag && GetKey(KEY_INPUT_SPACE) == 1) {
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	//Aが押されたとき攻撃
	if (GetKey(KEY_INPUT_A) == 1) {
		isPunch = true;
		punchDir = direct; //ボタンを押した時の向きに攻撃
	}

	if (isPunch) {
		Attack();
	}

	ver_Speed += Gravity;	//重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);	//移動
}

void Player::Draw() {
	//スクロール処理
	screenPos = VGet((float)SCREEN_HALF_W, (float)SCREEN_HALF_H, 0.0f);

	if ((int)pos.x < SCREEN_HALF_W) {	//画面の半分以下
		screenPos.x = pos.x;
	}
	else if ((int)pos.x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {	//画面の半分
		screenPos.x = SCREEN_HALF_W;
	}
	else {	//画面の半分以上
		screenPos.x = pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if ((int)pos.y < SCREEN_HALF_H) {
		screenPos.y = pos.y;
	}
	else if ((int)pos.y < STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_H) {
		screenPos.y = SCREEN_HALF_H;
	}
	else {
		screenPos.y = pos.y - (STAGE_HEIGHT[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HEIGHT);
	}

	int graphic;	//向きに応じた画像

	if (isHide) {	//隠れているとき
		graphic = hideGraphic;
	}
	else {
		if (direct == DIR_RIGHT) {
			graphic = graphic_R;
		}
		else {
			graphic = graphic_L;
		}
	}

	if (damaged) {
		if (flashCount % 3 == 0) DrawGraph((int)screenPos.x, (int)screenPos.y, graphic, FALSE);
		flashCount++;
		if (flashCount >= 3) flashCount = 0;
	}
	else {
		DrawGraph((int)screenPos.x, (int)screenPos.y, graphic, FALSE);
	}

	punchPos = pos;
	punchMove = VGet((float)sin(degree / 180.0f * PI) * CHIP_SIZE * 2 * punchDir, 0.0f, 0.0f);  //パンチの移動量
	HitWall();  //壁当たった時の処理

	//パンチの描画
	if (isPunch) {
		//画面上のパンチの位置
		VECTOR pPos = VGet(screenPos.x + punchMove.x, screenPos.y, 0.0f);
		DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic, TRUE);
	}
}

//移動
void Player::Move(float moveY, float moveX) {
	float dummy = 0.0f;

	//上下成分の移動
	{	
		//左上
		if (MapCollision(pos.y + EPS, pos.x + EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -0.6f;
		}
		//右上
		if (MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == DOWN) {
			ver_Speed *= -0.6f;
		}
		//左下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}
		//右下
		if (MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, moveY, dummy) == UP) {
			ver_Speed = 0.0f;
		}

		pos.y += moveY;
	}
	//左右成分の移動
	{
		//左上
		MapCollision(pos.y + EPS, pos.x + EPS, dummy, moveX);
		//右上
		MapCollision(pos.y + EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);
		//左下
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + EPS, dummy, moveX);
		//右下
		MapCollision(pos.y + CHIP_SIZE - EPS, pos.x + CHIP_SIZE - EPS, dummy, moveX);

		pos.x += moveX;
	}
	//接地判定
	{
		int ground_R = Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + EPS);
		int ground_L = Map::GetMapChip(pos.y + CHIP_SIZE + EPS + CHIP_SIZE / 4, pos.x + CHIP_SIZE - EPS);
		//左下と右下に地面があるかどうか
		if (ground_R == GROUND || (20 <= ground_R && ground_L <= 45) ||
			ground_L == GROUND || (20 <= ground_L && ground_L <= 45)) {
			jump_Flag = false;
		}
		else {
			jump_Flag = true;
		}
	}
}

//攻撃
void Player::Attack() {
	degree += 10.0f;
	if (degree >= 180.f) {
		isPunch = false;
		degree = 0.0f;
	}
}

//パンチが壁に当たった時の処理
void Player::HitWall() {
	float dummy = 0.0f;
	bool tauch = false;  //壁に触れたか

	//左上
	if (MapCollision(punchPos.y + EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//右上
	if (MapCollision(punchPos.y + EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//左下
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}
	//右下
	if (MapCollision(punchPos.y + CHIP_SIZE - EPS, punchPos.x + CHIP_SIZE - EPS, dummy, punchMove.x) > 0) {
		tauch = true;
	}

	punchPos.x += punchMove.x;

	if (tauch) {
		isPunch = false;
		degree = 0.0f;
	}
}

//敵に当たった時の処理(無敵時間)
void Player::HitEnemy(const EnemyMgr& enemyMgr) {
	if (isHide) return;	//隠れているときはダメージを受けない

	if (!damaged) {
		for (int num = 0; num < ENEMY_NUM; num++) {
			if (enemyMgr.IsExist(num)) {
				VECTOR enemyPos = enemyMgr.GetEnemyPos(num);
				if (fabs(enemyPos.x - pos.x) < CHIP_SIZE &&
					fabs(enemyPos.y - pos.y) < CHIP_SIZE) {
					damaged = true;
					flashStartTime = GetNowCount();
					hitPoint -= 10;
					return;
				}
			}
		}
	}
	else {
		//ダメージを受けてから2秒以上経った時
		if (GetNowCount() - flashStartTime > 2000) {
			damaged = false;
		}
	}
}