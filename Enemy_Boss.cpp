#include "Enemy_Boss.h"
#include "Map.h"
#include "Player.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include "SceneMgr.h"
#include <math.h>

bool Boss::isAction_Create;	//ActionCreate中か

Boss::Boss() {
	SetHitPoint(HP_BOSS);
	enemyType = ENEMY_BOSS;
	size = VGet(CHIP_SIZE * 3, CHIP_SIZE * 3, 0.0f);
	graphic_R = LoadGraph("image/enemyBoss_r.png");
	graphic_L = LoadGraph("image/enemyBoss_l.png");
	sandGprahic_r = LoadGraph("image/sandcloud_r.png");
	sandGraphic_l = LoadGraph("image/sandcloud_l.png");
	fallSound = LoadSoundMem("sound/fall.mp3");
	createSound = LoadSoundMem("sound/create.mp3");
	isGround = false;

	pos = VGet(CHIP_SIZE * (STAGE_WIDTH[SceneMgr::nowStage] - 5) - size.x,
		CHIP_SIZE * (STAGE_HEIGHT[SceneMgr::nowStage] - 3) - size.y, 0.0f);		//右端に配置
	direct = DIR_LEFT;			//左向き
	enemySpeed = 5.5f;			//移動速度

	frameCount = 0;				//フレームカウントの初期化
	flushCount = 0;				//点滅用カウントの初期化

	isAction_Jump = false;		//Action_Jump中ではない
	firstAction_Jump = true;	//最初のAction_Jumpである
	isRise = false;				//上昇中ではない
	isFall = false;				//下降中ではない

	isAction_Create = false;	//Action_Create中ではない

	isAction_Wait = false;		//待機中ではない
	waitCount = 0;				//待機カウントの初期化
}

Boss::~Boss() {

}

void Boss::Update(const Player& player) {
	if (isAction_Wait) {			//待機中なら
		if(Action_Wait()) return;
	}

	frameCount++;
	if (frameCount >= fps * 45) {	//45秒経ったら初期化
		frameCount = 0;
	}

	GroundCheck();					//接地判定

	move = VGet(0.0f, 0.0f, 0.0f);	//初期化

	ver_Speed += Gravity;			//重力を加える
	move.y = ver_Speed;

	isAction_Dash = false;

	if (frameCount % (fps * 60) == 0) {			//45秒に1回Action_Create
		Action_Create();
		isAction_Wait = true;
		return;
	}
	else if (frameCount % (fps * 12) == 0) {	//15秒に1回Action_Jump
		isAction_Jump = true;
	}

	if (isAction_Jump) {
		Action_Jump();
	}
	else {
		Action_Dash();							//それ以外はAction_Dash
	}
}

void Boss::Draw(const Player& player) {
	EnemyDraw(player);	//敵の描画

	flushCount++;
	if (flushCount >= 10) {
		flushCount = 0;
		return;
	}

	//砂煙の描画(10フレームに1回表示しない)
	if (isAction_Dash) {
		VECTOR sandPos;
		if (direct == DIR_RIGHT) {
			sandPos.x = screenPos.x - CHIP_SIZE * 2;
			sandPos.y = screenPos.y + CHIP_SIZE * 1;
			DrawGraph((int)sandPos.x, (int)sandPos.y, sandGprahic_r, TRUE);
		}
		else {
			sandPos.x = screenPos.x + size.x;
			sandPos.y = screenPos.y + CHIP_SIZE * 1;
			DrawGraph((int)sandPos.x, (int)sandPos.y, sandGraphic_l, TRUE);
		}
	}
}

void Boss::Action_Dash() {
	isAction_Dash = true;

	//折り返す
	if (pos.x <= CHIP_SIZE * 3) {
		direct = DIR_RIGHT;
	}
	if (pos.x >= CHIP_SIZE * (STAGE_WIDTH[SceneMgr::nowStage] - 3) - size.x) {
		direct = DIR_LEFT;
	}

	if (isGround) move.x += enemySpeed * direct;	//横方向の移動
	Move(move.y, move.x);							//移動
}

void Boss::Action_Jump() {
	if (firstAction_Jump) {
		if (pos.x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE / 2) {	//左側にいるなら
			moveDirect = DIR_RIGHT;
			fallStep = 0;												//0->4
		}
		else {															//右側にいるなら
			moveDirect = DIR_LEFT;
			fallStep = 4;												//4->0
		}
		firstAction_Jump = false;
	}

	if (!isRise && (pos.y >= CHIP_SIZE * 16)) {		//目的の位置までの距離を求める
		diff_x = (upPos[fallStep].x - pos.x) / 60.0f;
		diff_y = (upPos[fallStep].y - pos.y) / 60.0f;
		isRise = true;
	}
	if (isRise) {		//上昇中のとき
		//大体目的の位置に達したら落ちる
		if ((fabs(upPos[fallStep].x - pos.x) <= EPS) &&
			(fabs(upPos[fallStep].y - pos.y) <= EPS)) {
			isFall = true;
		}

		if (!isFall) {	//目的の位置まで移動
			move.x = diff_x;
			move.y = diff_y;
		}
		Move(move.y, move.x);

		if (pos.y >= CHIP_SIZE * 16) {	//地面についたとき
			PlaySoundMem(fallSound, DX_PLAYTYPE_BACK);	//落ちたときの音
			isRise = false;
			isFall = false;

			if (moveDirect == DIR_RIGHT) fallStep++;	//0->4
			else fallStep--;							//4->0

			//Action_Jumpの終了
			if (fallStep < 0) {
				fallStep = 0;
				isAction_Jump = false;
				firstAction_Jump = true;
			}
			if (fallStep > 4) {
				fallStep = 4;
				isAction_Jump = false;
				firstAction_Jump = true;
			}
		}
	}
}

void Boss::Action_Create() {
	PlaySoundMem(createSound, DX_PLAYTYPE_BACK);	//敵の生成音を鳴らす
	isAction_Create = true;		//仲間を生成する
}

bool Boss::Action_Wait() {
	waitCount++;
	if (waitCount > fps * 1) {	//１秒待つ
		waitCount = 0;
		isAction_Wait = false;
		return false;
	}
	return true;
}