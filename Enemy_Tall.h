#ifndef ___Class_Tall
#define ___Class_Tall

#include "Enemy.h"

//Enemy_Tall‚ğ¶¬‚·‚éƒNƒ‰ƒX
class Tall : public Enemy {
public:
	Tall();
	~Tall();

	void Update() {};
	void Update(const Player& player);
	void Draw() {};
	void Draw(const Player& player);
};

#endif