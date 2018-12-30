#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"

class Player;
class BulletMgr;
class BombMgr;

class Enemy : public Object {
protected:
	int enemyType;		//“G‚Ìí—Ş

	float enemySpeed;	//“G‚Ì‰ŠúˆÚ“®‘¬“x
	bool isGround;		//Ú’n”»’è

public:
	Enemy();
	~Enemy();

	virtual void Update() = 0;
	virtual void Update(const Player& player) {};
	virtual void Draw() = 0;
	virtual void Draw(const Player& player) {};
	virtual void Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr) {};

	void EnemyDraw(const Player& player);	//“G‚Ì•`‰æ

	int GetType() const { return enemyType; };	//“G‚Ìí—Ş‚Ìæ“¾
	
	VECTOR randomPos(int h, int w);		//ƒ‰ƒ“ƒ_ƒ€‚ÅˆÊ’uŒˆ‚ß(h:“G‚Ìc•,w:“G‚Ì‰¡•)
	int randomDir();		//ƒ‰ƒ“ƒ_ƒ€‚ÅŒü‚«‚ğŒˆ‚ß‚é
	float randomSpeed();	//ƒ‰ƒ“ƒ_ƒ€‚ÅˆÚ“®‘¬“x‚ğŒˆ‚ß‚é
};

#endif