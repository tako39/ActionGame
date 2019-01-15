#include "Display.h"
#include "Player.h"
#include "EnemyMgr.h"

Display::Display() {
	hpGreeen = LoadGraph("image/hp_green.png");
	hpOrange = LoadGraph("image/hp_orange.png");
	hpRed = LoadGraph("image/hp_red.png");
}

Display::~Display() {

}

void Display::Update() {

}

void Display::Draw(const Player& player) {
	DrawHp(VGet(240.0f, 0.0f, 0.0f), player.GetHitPoint(), MAX_HP);
}

void Display::DrawHp(VECTOR hpPos, int hitPoint, int maxHp) {
	int hp = hitPoint;
	int hpGraphic;

	if (hp > maxHp / 2) {
		hpGraphic = hpGreeen;
	}
	else if (hp > maxHp / 4) {
		hpGraphic = hpOrange;
	}
	else {
		hpGraphic = hpRed;
	}

	SetFontSize(20);
	DrawFormatString((int)hpPos.x - 30, 0, GetColor(255, 0, 255), "HP:");
	int hpRate = ((float)hitPoint / maxHp) * 100;
	for (int i = 0; i < hpRate; i++) {
		DrawGraph((int)hpPos.x + 4 * i, (int)hpPos.y, hpGraphic, TRUE);
	}
}