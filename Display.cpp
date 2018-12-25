#include "Display.h"
#include "DxLib.h"
#include "Player.h"
#include "Define.h"

int Display::Score = 0;

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
	//“_”‚Ì•`‰æ
	DrawFormatString(0, 0, GetColor(255, 0, 0),"Score: %d", Score);

	//HPƒo[‚Ì•`‰æ
	int hp = player.GetHitPoint();
	int hpGraphic;

	if (hp > MAX_HP / 2) {
		hpGraphic = hpGreeen;
	}
	else if (hp > MAX_HP / 4) {
		hpGraphic = hpOrange;
	}
	else {
		hpGraphic = hpRed;
	}

	DrawFormatString(210, 0, GetColor(255, 0, 255), "HP:", Score);
	for (int i = 0; i < hp; i++) {
		DrawGraph(240 + 4 * i, 0, hpGraphic, TRUE);
	}
}