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
		CHIP_SIZE * (STAGE_HEIGHT[SceneMgr::nowStage] - 3) - size.y, 0.0f);	//右端に配置
	direct = DIR_LEFT;	//左向き
	enemySpeed = 5.5f;	//移動速度

	frameCount = 0;
	flushCount = 0;

	isAction_Jump = false;
	firstAction = true;
	isRise = false;
	isFall = false;

	isAction_Create = false;

	isAction_Wait = false;
	waitCount = 0;
}

Boss::~Boss() {

}

void Boss::Update(const Player& player) {
	if (isAction_Wait) {
		if(Action_Wait()) return;	//待機中なら
	}

	frameCount++;
	if (frameCount >= fps * 60) {
		frameCount = 0;
	}

	GroundCheck();	//接地判定

	move = VGet(0.0f, 0.0f, 0.0f);	//初期化

	ver_Speed += Gravity;	//重力を加える
	move.y = ver_Speed;

	isAction_Dash = false;

	if (frameCount % (fps * 60) == 0) {	//60秒に1回Action_Create
		Action_Create();
		isAction_Wait = true;
		return;
	}
	else if (frameCount % (fps * 12) == 0) {	//12秒に1回Action_Jump
		isAction_Jump = true;
	}

	if (isAction_Jump) {
		Action_Jump();
	}
	else {
		Action_Dash();	//何もしていないならAction_Dash
	}
}

void Boss::Draw(const Player& player) {
	EnemyDraw(player);	//敵の描画

	flushCount++;
	if (flushCount >= 10) {
		flushCount = 0;
		return;
	}

	//砂煙の描画(10フレームに一回表示しない)
	if (isAction_Dash) {
		VECTOR sandPos;
		if (direct == DIR_RIGHT) {
			sandPos.x = screenPos.x - CHIP_SIZE * 2;
			sandPos.y = screenPos.y + CHIP_SIZE * 1;
			DrawGraph(sandPos.x, sandPos.y, sandGprahic_r, TRUE);
		}
		else {
			sandPos.x = screenPos.x + size.x;
			sandPos.y = screenPos.y + CHIP_SIZE * 1;
			DrawGraph(sandPos.x, sandPos.y, sandGraphic_l, TRUE);
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
	Move(move.y, move.x);	//移動
}

void Boss::Action_Jump() {
	if (firstAction) {
		if (pos.x < STAGE_WIDTH[SceneMgr::nowStage] * CHIP_SIZE / 2) {	//左側にいるなら
			moveDirect = DIR_RIGHT;
			fallStep = 0;	//0->4
		}
		else {	//右側にいるなら
			moveDirect = DIR_LEFT;
			fallStep = 4;	//4->0
		}
		firstAction = false;
	}

	if (!isRise && (pos.y >= CHIP_SIZE * 16)) {		//目的の位置までの距離を求める
		diff_x = (upPos[fallStep].x - pos.x) / 60.0f;
		diff_y = (upPos[fallStep].y - pos.y) / 60.0f;
		isRise = true;
	}
	if (isRise) {	//上昇中のとき
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

			if (moveDirect == DIR_RIGHT) fallStep++;
			else fallStep--;

			if (fallStep < 0) {
				fallStep = 0;
				isAction_Jump = false;
				firstAction = true;
			}
			if (fallStep > 4) {
				fallStep = 4;
				isAction_Jump = false;
				firstAction = true;
			}
		}
	}
}

void Boss::Action_Create() {
	PlaySoundMem(createSound, DX_PLAYTYPE_BACK);	//敵を増やしたときの音
	isAction_Create = true;
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