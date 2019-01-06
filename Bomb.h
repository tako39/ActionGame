#ifndef ___Class_Bomb
#define ___Class_Bomb

#include "Object.h"

class Player;

class Bomb : public Object {
private:
	int bombSound;	//爆弾が爆発したときの音

	int setTime;			//爆弾を設置した時間	
	int bombGraphic_Count1;	//爆弾の画像
	int bombGraphic_Count2;
	int bombGraphic_Count3;
	int bombGraphic_Red;
	int explosionGraphic;		//爆発画像

public:
	Bomb(const Player& player);
	~Bomb();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);
	int GetSetTime() { return setTime; }
};

#endif