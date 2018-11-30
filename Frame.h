#ifndef ___Class_Frame
#define ___Class_Frame

class Frame {
private:
	int startTime;  //測定開始時刻
	int count;  //カウント
	float fps;  //fps

	const int N = 60;   //平均を取るサンプル数
	const int FPS = 60; //60fpsとする

public:
	Frame();
	~Frame();
	void Update();
	void Wait();
};

#endif