#include "Player.h"
#include "Keyboard.h"
#include "Map.h"
#include "EnemyMgr.h"
#include "SceneMgr.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include <math.h>

bool Player::isFirstPunch;
float Player::xPos;

Player::Player() {
	SetHitPoint(MAX_HP);	//体力の設定
	size = VGet(CHIP_SIZE * 1.0f, CHIP_SIZE * 1.0f, 0.0f);	//大きさの設定

	jumpSound = LoadSoundMem("sound/jump.mp3");
	damageSound = LoadSoundMem("sound/damage_player.mp3");
	punchSound = LoadSoundMem("sound/punch.mp3");

	graphic_R = LoadGraph("image/player_r.png");
	graphic_L = LoadGraph("image/player_l.png");
	punchGraphic_R = LoadGraph("image/arrow_r.png");
	punchGraphic_L = LoadGraph("image/arrow_l.png");
	hideGraphic = LoadGraph("image/player_hide.png");

	pos = firstPos[SceneMgr::nowStage];	//初期位置の設定
	xPos = pos.x;			//xの位置
	direct = DIR_RIGHT;		//始めは右向きとする
	jump_Flag = false;		//ジャンプが可能な（ジャンプしていない）状態
	ver_Speed = 0.0f;		//垂直方向の移動

	degree = 0.0f;			//パンチの周期0
	isPunch = false;		//パンチしていない状態
	isFirstPunch = false;	//敵に当たっていない状態

	damaged = false;		//ダメージを受けていない状態
	flashCount = 0;			//フレームカウントの初期化

	isHide = false;			//隠れていない状態
}

Player::~Player() {

}

void Player::Update(BulletMgr& bulletMgr, BombMgr& bombMgr) {
	xPos = pos.x;	//xの位置

	if (GetHitPoint() <= 0) {	//体力が０以下の時
		SetExist(false);
	}

	//隠れることができる(隠れているときは動けない)
	if (!jump_Flag && GetKey(KEY_INPUT_F) > 0) {
		isHide = true;
		return;
	}
	else {
		isHide = false;
	}

	move = VGet(0.0f, 0.0f, 0.0f);  //移動量の初期化

	//右への移動
	if (GetKey(KEY_INPUT_RIGHT) > 0) {
		move.x += jump_Flag ? AirSpeed : Speed;	//ジャンプ中は速度を変える
		direct = DIR_RIGHT;
	}

	//左への移動
	if (GetKey(KEY_INPUT_LEFT) > 0) {
		move.x -= jump_Flag ? AirSpeed : Speed;
		direct = DIR_LEFT;
	}

	//ジャンプ
	if (!jump_Flag && GetKey(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK);	//ジャンプ音
		ver_Speed = -JumpPower;
		jump_Flag = true;
	}

	isAttack = false;	//攻撃していない状態

	//Aが押されたとき攻撃
	if (GetKey(KEY_INPUT_A) == 1) {
		isAttack = true;
		isPunch = true;
		isFirstPunch = true;
		punchDir = direct; //ボタンを押した時の向きに攻撃
	}

	if (isPunch) {	//パンチしているとき
		PlaySoundMem(punchSound, DX_PLAYTYPE_BACK);	//パンチ音を鳴らす
		PunchAttack();
	}

	//まだ攻撃していないなら、Sボタンで弾を発射
	if ((GetKey(KEY_INPUT_S) == 1) && !isAttack) {
		isAttack = true;
		bulletMgr.Shot(*this);
	}
	//まだ攻撃していないなら、Dボタンで爆弾を設置
	if ((GetKey(KEY_INPUT_D) == 1) && !isAttack) {
		isAttack = true;
		bombMgr.BombSet(*this);
	}

	ver_Speed += Gravity;	//重力を加える
	move.y = ver_Speed;

	Move(move.y, move.x);	//移動
}

void Player::Draw() {
	//スクロール処理
	screenPos = VGet((float)SCREEN_HALF_W, (float)SCREEN_HALF_H, 0.0f);

	//実際の位置によって描画位置を変える
	if ((int)pos.x < SCREEN_HALF_W) {	//横
		screenPos.x = pos.x;
	}
	else if ((int)pos.x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_HALF_W) {
		screenPos.x = SCREEN_HALF_W;
	}
	else {
		screenPos.x = pos.x - (STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE - SCREEN_WIDTH);
	}

	if ((int)pos.y < SCREEN_HALF_H) {	//縦
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
	else {			//隠れていないとき
		if (direct == DIR_RIGHT) {
			graphic = graphic_R;
		}
		else {
			graphic = graphic_L;
		}
	}

	if (damaged) {	//ダメージを受けているとき点滅させる
		if (flashCount % 3 == 0) DrawGraph((int)screenPos.x, (int)screenPos.y, graphic, FALSE);
		flashCount++;
		if (flashCount >= 3) flashCount = 0;
	}
	else {
		DrawGraph((int)screenPos.x, (int)screenPos.y, graphic, FALSE);
	}

	punchPos = pos;	//パンチの位置
	punchMove = VGet((float)sin(degree / 180.0f * PI) * CHIP_SIZE * 2 * punchDir, 0.0f, 0.0f);  //パンチの移動量
	HitWall();		//壁当たった時の処理

	//パンチの描画
	if (isPunch) {
		VECTOR pPos = VGet(screenPos.x + punchMove.x, screenPos.y, 0.0f);	//画面上のパンチの位置
		if (direct == DIR_RIGHT) {
			DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic_R, TRUE);
		}
		else {
			DrawGraph((int)pPos.x, (int)pPos.y, punchGraphic_L, TRUE);
		}
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
		//左下と右下に地面があるなら
		if (ground_R == GROUND || ground_R == CLOUD || (20 <= ground_R && ground_R <= 45) ||
			ground_L == GROUND || ground_R == CLOUD || (20 <= ground_L && ground_L <= 45)) {
			jump_Flag = false;	//ジャンプできる
		}
		else {
			jump_Flag = true;	//ジャンプできない
		}
	}
}

//パンチ攻撃の周期の変更
void Player::PunchAttack() {
	degree += 10.0f;		//周期を増やす
	if (degree >= 180.f) {	//パンチ終了
		isPunch = false;
		degree = 0.0f;
	}
}

//パンチが壁に当たった時の処理
void Player::HitWall() {
	float dummy = 0.0f;		//ダミー
	bool tauch = false;		//壁に触れたか

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

	if (tauch) {	//壁に当たったならパンチを戻す
		isPunch = false;
		degree = 0.0f;
	}
}

//敵に当たった時の処理(無敵時間あり)
void Player::HitEnemy(const EnemyMgr& enemyMgr) {
	if (damaged) {
		if (GetNowCount() - flashStartTime > 2000) {	//ダメージを受けてから2秒以上経ったとき
			damaged = false;							//ダメージを受けていない状態にする
		}
	}

	if (isHide) return;		//隠れているときはダメージを受けない

	if (!damaged) {
		for (int num = 0; num < MAX_ENEMY; num++) {
			if (enemyMgr.IsExist(num)) {
				VECTOR enemyPos = enemyMgr.GetEnemyPos(num);	//敵の位置
				int enemySizeX, enemySizeY;						//敵の大きさ
				int type = enemyMgr.GetEnemyType(num);			//敵の種類

				if (type == ENEMY_ZAKO) {
					enemySizeX = CHIP_SIZE;
					enemySizeY = CHIP_SIZE;
				}
				else if (type == ENEMY_TALL) {
					enemySizeX = CHIP_SIZE;
					enemySizeY = CHIP_SIZE * 2;
				}
				else if(type == ENEMY_BIG) {
					enemySizeX = CHIP_SIZE * 2;
					enemySizeY = CHIP_SIZE * 2;
				}
				else if (type == ENEMY_BOSS) {
					enemySizeX = CHIP_SIZE * 3;
					enemySizeY = CHIP_SIZE * 3;
				}

				//当たり判定の計算、処理
				if ((fabs(pos.x + size.x / 2 - (enemyPos.x + enemySizeX / 2)) < size.x / 2 + enemySizeX / 2) &&
					(fabs(pos.y + size.y / 2 - (enemyPos.y + enemySizeY / 2)) < size.y / 2 + enemySizeY / 2)) {
					PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);	//ダメージを受けたときの音
					damaged = true;						//ダメージを受けている状態にする
					Damaged(10);						//10ダメージ受ける
					flashStartTime = GetNowCount();		//ダメージを受けた時間の記憶
					return;
				}
			}
		}
	}
}

//位置を初期位置に戻す
void Player::ResetPosition() {
	pos = firstPos[SceneMgr::nowStage];
}