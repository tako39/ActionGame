#include "Frame.h"
#include <math.h>
#include "DxLib.h"

Frame::Frame() {
	startTime = 0;
	count = 0;
	fps = 0.0f;
}

Frame::~Frame() {

}

void Frame::Update() {
	if (count == 0) {  //1フレーム目
		startTime = GetNowCount();
	}
	if (count == N) {  //60フレーム目
		int endTime = GetNowCount();
		fps = 1000.0f / ((float)(endTime - startTime) / N);
		count = 0;
		startTime = endTime;
	}
	count++;
}

void Frame::Wait() {
	int requiredTime = GetNowCount() - startTime;		//所要時間
	int waitTime = count * 1000 / FPS - requiredTime;  //待つ時間
	if (waitTime > 0) {
		Sleep(waitTime);  //待機する
	}
}