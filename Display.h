#ifndef ___Class_Display
#define ___Class_Display

#include "Task.h"
#include "Define.h"

class Player;

class Display : public Task {
private:
	int hpGreeen;	//ÎFĚHPĚć
	int hpOrange;	//ňFĚHPĚć
	int hpRed;		//ÔFĚHPĚć

public:
	static int Point[ENEMY_TYPE];	//Gđ|ľ˝

	Display();
	~Display();

	void Update();
	void Draw() {};
	void Draw(const Player& player);
};

#endif