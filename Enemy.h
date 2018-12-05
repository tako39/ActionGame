#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"
#include "Define.h"

class Player;

class Enemy : public Object {
private:
	bool isGround;  //Ú’n”»’è

	VECTOR playerPos;

public:
	Enemy();
	~Enemy();

	void Update() {};
	void Update(const Player& cPlayer);
	void Draw();

	void Move(float moveY, float moveX); //ˆÚ“®
};

#endif