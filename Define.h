#ifndef ___Define
#define ___Define

//スクリーン
const int SCREEN_WIDTH  = 640;  // 画面の横幅
const int SCREEN_HEIGHT = 480;  // 画面の縦幅
const int CHIP_SIZE  = 32;      // 一つのチップのサイズ

//ステージ
const int STAGE_NUM = 5;  //ステージ数
const int STAGE_WIDTH[5]  = {20, 20, 20, 20, 20}; //横のチップ数
const int STAGE_HEIGHT[5] = {15, 20, 20, 20, 20}; //縦のチップ数

//マップ
const int BACK = 0;    //背景
const int GROUND = 1;  //地面

//プレイヤー
const int DIR_RIGHT =  1;  //右向き
const int DIR_LEFT  = -1;  //左向き

const float Gravity = 0.3f;    //重力
const float Speed = 5.0f;      //横移動速度
const float AirSpeed = 3.0f;   //空中での横移動速度
const float JumpPower = 9.0f;  //ジャンプ力

const float EPS = 1.0f;

//方向
const int NONE = -1;  //なし

const int UP    = 0;  //上
const int DOWN  = 1;  //下
const int LEFT  = 2;  //左
const int RIGHT = 3;  //右

//キーボード
const int KEY_NUM = 256; //入力

//その他

#endif