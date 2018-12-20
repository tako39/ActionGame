#include "Display.h"
#include "DxLib.h"

int Display::Score = 0;

Display::Display() {

}

Display::~Display() {

}

void Display::Update() {

}

void Display::Draw() {
	DrawFormatString(0, 0, GetColor(255, 0, 0),"Score: %d", Score);
}