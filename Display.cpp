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

//HP‚Ì•`‰æ
void Display::DrawHp(VECTOR hpPos, int hitPoint, int maxHp) {
	int hp = hitPoint;	//Œ»İ‚ÌHP
	int hpGraphic;		//HP‚Ì‰æ‘œ

	if (hp > maxHp / 2) {		//”¼•ª‚æ‚èã‚Í—Î
		hpGraphic = hpGreeen;
	}
	else if (hp > maxHp / 4) {	//”¼•ªˆÈ‰º‚Íò
		hpGraphic = hpOrange;
	}
	else {						//4•ª‚Ì1ˆÈ‰º‚ÍÔ
		hpGraphic = hpRed;
	}

	SetFontSize(20);
	DrawFormatString((int)hpPos.x - 30, 0, GetColor(255, 0, 255), "HP:");
	
	int hpRate = (int)(((float)hitPoint / maxHp) * 100);	//Å‘åHP‚É‚¨‚¯‚éŒ»İ‚ÌHP‚ÌŠ„‡

	for (int i = 0; i < hpRate; i++) {						//Š„‡•ª‚¾‚¯•`‰æ
		DrawGraph((int)hpPos.x + 4 * i, (int)hpPos.y, hpGraphic, TRUE);
	}
}