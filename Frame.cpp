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
	if (count == 0) {  //1�t���[����
		startTime = GetNowCount();
	}
	if (count == N) {  //60�t���[����
		int endTime = GetNowCount();
		fps = 1000.0f / ((float)(endTime - startTime) / N);
		count = 0;
		startTime = endTime;
	}
	count++;
}

void Frame::Wait() {
	int requiredTime = GetNowCount() - startTime;		//���v����
	int waitTime = count * 1000 / FPS - requiredTime;  //�҂���
	if (waitTime > 0) {
		Sleep(waitTime);  //�ҋ@����
	}
}