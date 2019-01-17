#ifndef ___Class_Bullet
#define ___Class_Bullet

#include "Object.h"
#include "DxLib.h"

class Player;

//’e‚ÌƒNƒ‰ƒX
class Bullet : public Object {
private:
	int bulletGraphic;	//’e‚Ì‰æ‘œ
	bool init;	//¶¬

	float totalMove;	//‘ˆÚ“®‹——£

public:
	Bullet(const Player& player);
	~Bullet();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	void HitWall();	//’e‚ª•Ç‚É“–‚½‚Á‚½‚Ìˆ—
};

#endif