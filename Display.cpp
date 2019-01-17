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

//HP�̕`��
void Display::DrawHp(VECTOR hpPos, int hitPoint, int maxHp) {
	int hp = hitPoint;	//���݂�HP
	int hpGraphic;		//HP�̉摜

	if (hp > maxHp / 2) {		//��������͗�
		hpGraphic = hpGreeen;
	}
	else if (hp > maxHp / 4) {	//�����ȉ��͞�
		hpGraphic = hpOrange;
	}
	else {						//4����1�ȉ��͐�
		hpGraphic = hpRed;
	}

	SetFontSize(20);
	DrawFormatString((int)hpPos.x - 30, 0, GetColor(255, 0, 255), "HP:");
	
	int hpRate = (int)(((float)hitPoint / maxHp) * 100);	//�ő�HP�ɂ����錻�݂�HP�̊���

	for (int i = 0; i < hpRate; i++) {						//�����������`��
		DrawGraph((int)hpPos.x + 4 * i, (int)hpPos.y, hpGraphic, TRUE);
	}
}