#ifndef ___Class_BombMgr
#define ___Class_BombMgr

#include "Task.h"
#include "Define.h"
#include "DxLib.h"
#include "Bomb.h"

class Bomb;
class Player;

//���e�̊Ǘ��N���X
class BombMgr : public Task {
private:
	int putSound;				//���e��u�����Ƃ��̉�

	Bomb *bomb[BOMB_NUM];		//���e
	int deleteTime[BOMB_NUM];	//���e���������ꂽ����
	bool explosion[BOMB_NUM];	//�������Ă��邩

public:
	BombMgr();
	~BombMgr();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void BombSet(const Player& player);	//���e�̐ݒu

	bool IsExist(int num) const {		//���݂��邩�ǂ���
		if (bomb[num] != NULL) return true;
		else return false;
	}
	VECTOR GetBombPos(int num) const {	//bomb[num]�̈ʒu���擾
		return bomb[num]->GetPos();
	}
	bool IsExplosion(int num) const {	//bomb[num]������������
		return explosion[num];
	}

	void DeleteBomb(int num) {			//���e�̏���
		delete bomb[num];
		bomb[num] = NULL;
		deleteTime[num] = GetNowCount();
		explosion[num] = false;
	}

	void DeleteBombAll() {				//�����������e�̏���
		for (int bombNum = 0; bombNum < BOMB_NUM; bombNum++) {
			if (IsExplosion(bombNum)) {	//���������Ȃ�폜
				DeleteBomb(bombNum);
			}
		}
	}
};

#endif