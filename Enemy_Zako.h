#ifndef ___Class_Zako
#define ___Class_Zako

#include "Enemy.h"

//Enemy_Zako�𐶐�����N���X
class Zako : public Enemy {
public:
	Zako();
	~Zako();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);
};

#endif