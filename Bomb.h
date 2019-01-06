#ifndef ___Class_Bomb
#define ___Class_Bomb

#include "Object.h"

class Player;

class Bomb : public Object {
private:
	int bombSound;	//”š’e‚ª”š”­‚µ‚½‚Æ‚«‚Ì‰¹

	int setTime;			//”š’e‚ğİ’u‚µ‚½ŠÔ	
	int bombGraphic_Count1;	//”š’e‚Ì‰æ‘œ
	int bombGraphic_Count2;
	int bombGraphic_Count3;
	int bombGraphic_Red;
	int explosionGraphic;		//”š”­‰æ‘œ

public:
	Bomb(const Player& player);
	~Bomb();

	void Update();
	void Draw() {};
	void Draw(const Player& player);

	void Move(float moveY, float moveX);
	int GetSetTime() { return setTime; }
};

#endif