#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"

class Enemy : public Object {
private:

public:
	Enemy(VECTOR ePos);
	~Enemy();

	void Update();
	void Draw();
};

#endif