#ifndef ___Class_BulletMgr
#define ___Class_BulletMgr

#include "Task.h"
#include "Define.h"
#include "DxLib.h"
#include "Bullet.h"

class Bullet;
class Player;

class BulletMgr : public Task {
private:
	int bulletSound;	//’e‚ğ”­Ë‚µ‚½‚Æ‚«‚Ì‰¹

	Bullet *bullet[BULLET_NUM];
	int deleteTime[BULLET_NUM];	//’e‚ğÁ”ï‚µ‚½ŠÔ

public:
	BulletMgr();
	~BulletMgr();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	bool IsExist(int num) const {	//‘¶İ‚·‚é‚©‚Ç‚¤‚©
		if (bullet[num] != NULL) return true;
		else return false;
	}
	VECTOR GetBulletPos(int num) const {	//bullet[num]‚ÌˆÊ’u‚ğæ“¾
		return bullet[num]->GetPos();
	}

	void DeleteBullet(int num) {	//bullet[num]‚ğíœ
		delete bullet[num];
		bullet[num] = NULL;
		deleteTime[num] = GetNowCount();
	}

	void Shot(const Player& player);	//’e‚ğ—LŒø‚É‚·‚é
};

#endif