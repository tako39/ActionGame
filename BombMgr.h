#ifndef ___Class_BombMgr
#define ___Class_BombMgr

#include "Task.h"
#include "Define.h"
#include "Bomb.h"

class Bomb;
class Player;

class BombMgr : public Task {
private:
	Bomb *bomb[BOMB_NUM];
	int deleteTime[BOMB_NUM];	//”š’e‚ğÁ”ï‚µ‚½ŠÔ
	bool explosion[BOMB_NUM];	//”š”­‚µ‚Ä‚¢‚é‚©

public:
	BombMgr();
	~BombMgr();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void BombSet(const Player& player);	//”š’e‚ğİ’u

	bool IsExist(int num) const {	//‘¶İ‚·‚é‚©‚Ç‚¤‚©
		if (bomb[num] != NULL) return true;
		else return false;
	}
	VECTOR GetBombPos(int num) const {	//bomb[num]‚ÌˆÊ’u‚ğæ“¾
		return bomb[num]->GetPos();
	}
	bool IsExplosion(int num) const {	//bomb[num]‚ª”š”­‚µ‚½‚©
		return explosion[num];
	}

	void DeleteBomb(int num) {	//”š’e‚Ìíœ
		delete bomb[num];
		bomb[num] = NULL;
		deleteTime[num] = GetNowCount();
		explosion[num] = false;
	}

	void DeleteBombAll() {		//”š”­‚µ‚½”š’e‚Ìˆ—
		for (int bombNum = 0; bombNum < BOMB_NUM; bombNum++) {
			if (IsExplosion(bombNum)) {
				DeleteBomb(bombNum);
			}
		}
	}
};

#endif