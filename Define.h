#ifndef ___Define
#define ___Define

//スクリーン
const int SCREEN_WIDTH  = 640;	// 画面の横幅
const int SCREEN_HEIGHT = 480;	// 画面の縦幅
const int CHIP_SIZE  = 32;		// 一つのチップのサイズ

const int SCREEN_HALF_W = 320;	//横幅の半分
const int SCREEN_HALF_H = 240;	//縦幅の半分


//ステージ
const int STAGE_NUM = 5;	//ステージ数
const int STAGE_WIDTH[5]  = {40, 0, 0, 0, 0};	//横のチップ数
const int STAGE_HEIGHT[5] = {20, 0, 0, 0, 0};	//縦のチップ数


//マップ
const int BACK = 0;		//背景
const int GROUND = 1;	//地面


//プレイヤー
const int DIR_RIGHT =  1;	//右向き
const int DIR_LEFT  = -1;	//左向き

const float Gravity = 0.5f;		//重力
const float Speed = 5.0f;		//横移動速度
const float AirSpeed = 3.0f;	//空中での横移動速度
const float JumpPower = 12.0f;	//ジャンプ力

const float EPS = 1.0f;		//地面との当たり判定はEPS分内側にある


//弾
const int BULLET_WIDTH	= 16;	//弾の横幅
const int BULLET_HEIGHT = 8;	//弾の縦幅
const int BULLET_NUM = 5;		//弾の数

const float bulletSpeed = 10.0f;	//弾の速度

//敵
const int ENEMY_NUM = 5;	//最大の敵の数

//方向
const int NONE = -1;	//なし

const int UP    = 0;	//上
const int DOWN	= 1;	//下
const int LEFT  = 2;	//左
const int RIGHT = 3;	//右


//キーボード
const int KEY_NUM = 256;	//入力


//その他
const float PI = 3.14f;		//円周率

#endif