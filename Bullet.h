#ifndef ___Class_Bullet
#define ___Class_Bullet

#include "Object.h"
#include "DxLib.h"

class Player;

class Bullet : public Object {
private:
	int bulletGraphic;	//弾の画像
	bool init;	//生成時

public:
	Bullet(const Player& player);
	~Bullet();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void HitWall();	//弾が壁に当たった時の処理
};

#endif