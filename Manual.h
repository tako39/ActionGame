#ifndef ___Class_Manual
#define ___Class_Manual

#include "Task.h"

class Manual : public Task {
private:
	int manualImage;	//‰æ‘œ
	const int manualSize_x = 520;
	const int manualSize_y = 360;

public:
	Manual();
	~Manual();

	void Update();
	void Draw();
};

#endif