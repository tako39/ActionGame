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
	Bullet *bullet[BULLET_NUM];

public:
	BulletMgr();
	~BulletMgr();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	bool IsExist(int num) const {	//���݂��邩�ǂ���
		if (bullet[num] != NULL) return true;
		else return false;
	}
	VECTOR GetBulletPos(int num) const {	//bullet[num]�̈ʒu���擾
		return bullet[num]->GetPos();
	}

	void DeleteBullet(int num) {
		delete bullet[num];
		bullet[num] = NULL;
	}

	void Shot(const Player& player);	//�e��L���ɂ���
};

#endif