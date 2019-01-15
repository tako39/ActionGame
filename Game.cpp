#include "Game.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"
#include "EnemyMgr.h"
#include "BulletMgr.h"
#include "BombMgr.h"
#include "Display.h"
#include "Manual.h"
#include "SceneMgr.h"
#include "Enemy_Boss.h"
#include "BossStage.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
	SceneMgr::nowStage = 1;	//ステージ1から始める
	enemyPhase = 0;
	mPush = false;
	player = new Player();
	map = new Map();
	enemyMgr = new EnemyMgr();
	bulletMgr = new BulletMgr();
	bombMgr = new BombMgr();
	display = new Display();
	manual = new Manual();
}

Game::~Game() {
	delete player;
	delete map;
	delete enemyMgr;
	delete bulletMgr;
	delete bombMgr;
	delete display;
	delete manual;
	delete bossStage;
}

//更新
void Game::Update() {
	if (!player->GetExist()) {	//プレイヤーが倒されたら
		mSceneChanger->ChangeScene(eScene_GameOver);	//シーンをゲームオーバーに変更
	}
	if (GetKey(KEY_INPUT_ESCAPE) != 0) {	//Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);	//シーンをメニューに変更
	}
	if (GetKey(KEY_INPUT_M) == 1) {	//mが押された状態ならManualを表示
		mPush = !mPush;
	}
	if (mPush) {	//Manual表示中は何も出来ない
		manual->Update();
		return;
	}
	if (SceneMgr::nowStage == 2) {	//ボスステージの時
		if (bossStage->FrameCheck()) {	//最初の3秒間は何もできない
			return;	
		}
	}

	player->Update(*bulletMgr, *bombMgr);	//プレイヤーの更新
	player->HitEnemy(*enemyMgr);			//プレイヤーの敵との接触

	map->Update();	//マップの更新	

	bulletMgr->Update(*player);		//弾の更新
	bombMgr->Update();				//爆弾の更新
	enemyMgr->Update(*player, *bulletMgr, *bombMgr);	//敵の更新	
	
	//ボスステージのみの更新
	if (SceneMgr::nowStage == 2) {
		if (enemyMgr->IsExist(0)) {	//ボスが生きているなら
			bossStage->Update(*player, *bulletMgr, *bombMgr, enemyMgr->GetEnemyPos(0));	//ボスの仲間の更新
		}
	}
	
	bombMgr->DeleteBombAll();	//爆発した爆弾の処理

	display->Update();		//HPバーの更新
	ChangeEnemyPhase();		//敵の生成段階の変更
}

void Game::ChangeEnemyPhase() {
	if (!enemyMgr->IsNoEnemy()) return;	//敵がまだ存在するなら

	if (enemyPhase == 0) {
		enemyMgr = new EnemyMgr(ENEMY_ZAKO, 12);
		enemyPhase++;
	}
	else if (enemyPhase == 1) {
		enemyMgr = new EnemyMgr(ENEMY_TALL, 10);
		enemyPhase++;
	}
	else if (enemyPhase == 2) {
		enemyMgr = new EnemyMgr(ENEMY_BIG, 8);
		enemyPhase++;
	}
	else if (enemyPhase == 3) {
		bossStage = new BossStage();
		enemyMgr = new EnemyMgr(ENEMY_BOSS, 1);
		player->ResetPosition();
		enemyPhase++;
	}
	else if (enemyPhase == 4) {
		mSceneChanger->ChangeScene(eScene_GameClear);	//シーンをクリア画面に変更
	}
}

//描画
void Game::Draw() {
	if (SceneMgr::nowStage == 2) {	//ボスステージの時
		if (bossStage->StageStart()) {	//最初の3秒間のみ描画
			return;
		}
	}
	map->Draw(*player);
	player->Draw();
	bulletMgr->Draw(*player);
	enemyMgr->Draw(*player);
	if (SceneMgr::nowStage == 2) {	//ボスステージのみ
		bossStage->Draw(*player);	//ボスの仲間の描画
	}
	bombMgr->Draw(*player);
	display->Draw(*player);
	if (mPush) manual->Draw();
}
