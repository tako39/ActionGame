#ifndef ___Class_Bomb
#define ___Class_Bomb

#include "Object.h"

class Player;

//爆弾のクラス
class Bomb : public Object {
private:
	int bombSound;				//爆弾が爆発したときの音

	int setTime;				//爆弾を設置した時間	
	int bombGraphic_Count1;		//爆発してない爆弾
	int bombGraphic_Count2;		//爆発しそうな爆弾
	int bombGraphic_Count3;		//点滅している爆弾(通常)
	int bombGraphic_Red;		//点滅している爆弾(赤)
	int explosionGraphic;		//爆発のエフェクト画像

public:
	Bomb(const Player& player);
	~Bomb();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);	//重力落下での移動
	int GetSetTime() { return setTime; }	//セットした時間の取得
};

#endif