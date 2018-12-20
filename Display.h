#ifndef ___Class_Display
#define ___Class_Display

#include "Task.h"

class Display {
private:

public:
	static int Score;	//ゲームのスコア

	Display();
	~Display();

	void Update();
	void Draw();
};

#endif