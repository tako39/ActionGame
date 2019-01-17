#ifndef ___Class_BulletMgr
#define ___Class_BulletMgr

#include "Task.h"
#include "Define.h"
#include "DxLib.h"
#include "Bullet.h"

class Bullet;
class Player;

//�e���Ǘ�����N���X
class BulletMgr : public Task {
private:
	int bulletSound;			//�e�𔭎˂����Ƃ��̉�

	Bullet *bullet[BULLET_NUM];	//�e
	int deleteTime[BULLET_NUM];	//�e�����������

public:
	BulletMgr();
	~BulletMgr();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);

	bool IsExist(int num) const {			//���݂��邩�ǂ���
		if (bullet[num] != NULL) return true;
		else return false;
	}
	VECTOR GetBulletPos(int num) const {	//bullet[num]�̈ʒu���擾
		return bullet[num]->GetPos();
	}

	void DeleteBullet(int num) {			//bullet[num]���폜
		delete bullet[num];
		bullet[num] = NULL;
		deleteTime[num] = GetNowCount();
	}

	void Shot(const Player& player);		//�e��L���ɂ���
};

#endif