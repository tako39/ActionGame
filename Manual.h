#ifndef ___Class_Manual
#define ___Class_Manual

#include "Task.h"

class Manual : public Task {
private:
	int manualImage;	//‰æ‘œ
	const int MANUAL_WIDTH = 520;	//‰¡•
	const int MANUAL_HEIGHT = 360;	//c•

public:
	Manual();
	~Manual();

	void Update();
	void Draw();
};

#endif