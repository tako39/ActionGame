#ifndef ___Class_Display
#define ___Class_Display

#include "Task.h"
#include "Define.h"

class Player;

class Display : public Task {
private:
	int hpGreeen;	//—ÎF‚ÌHP‚Ì‰æ‘œ
	int hpOrange;	//òF‚ÌHP‚Ì‰æ‘œ
	int hpRed;		//ÔF‚ÌHP‚Ì‰æ‘œ

public:
	static int Point[ENEMY_TYPE];	//“G‚ğ“|‚µ‚½”

	Display();
	~Display();

	void Update();
	void Draw() {};
	void Draw(const Player& player);
};

#endif