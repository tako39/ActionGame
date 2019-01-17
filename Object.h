#ifndef ___Class_Object
#define ___Class_Object

#include "Task.h"
#include "DxLib.h"

//オブジェクトに継承するクラス
class Object : public Task {
protected:
	int hitPoint;		//体力
	bool isExist;		//生存しているか

	VECTOR size;		//大きさ
	int graphic_R;		//右向き画像
	int graphic_L;		//左向き画像

	float ver_Speed;	//垂直方向の移動量
	bool jump_Flag;		//trueならジャンプ中

	VECTOR pos;			//位置
	int direct;			//方向
	VECTOR move;		//移動

	VECTOR screenPos;	//スクリーン上の位置

public:
	Object();
	~Object();

	int  GetHitPoint() const { return hitPoint; }		//HPを取得する
	void SetHitPoint(int hp) { hitPoint = hp; }			//HPをセットする
	void Damaged(int damege) { hitPoint -= damege; }	//ダメージを受ける

	bool GetExist() const { return isExist; }			//生存の確認
	void SetExist(bool exist) { isExist = exist; }		//生存の変更

	void SetPos(VECTOR sPos) { pos = sPos; }			//位置をセットする

	VECTOR GetSize() const { return size; }				//大きさの取得
	VECTOR GetPos() const { return pos; }				//位置の取得
	int GetDirect() const { return direct; }			//方向の取得

	VECTOR GetScreenPos() const { return screenPos; }	//スクリーン上での位置の取得

	int MapCollision(float Y, float X, float &moveY, float &moveX); //当たり判定
};

#endif