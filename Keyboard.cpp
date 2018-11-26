#include "Keyboard.h"

static int key[KEY_NUM];

void UpdateKey() {
	//Œ»İ‚ÌƒL[“ü—Íó‘Ô‚ÌŠi”[
	char tmpKey[KEY_NUM];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < KEY_NUM; i++) {
		//0:“ü—Í‚³‚ê‚Ä‚¢‚È‚¢, 1:“ü—Í‚³‚ê‚½uŠÔ, 2:“ü—Í‚³‚ê‚Ä‚¢‚éŠÔ
		if (tmpKey[i] != 0) {
			if (key[i] == 0) {
				key[i] = 1;
			}
			else {
				key[i]++;
			}
		}
		else {
			key[i] = 0;
		}
	}
}

int GetKey(int keyCode) {
	return key[keyCode];
}