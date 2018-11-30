#include "Keyboard.h"

static int key[KEY_NUM];

void UpdateKey() {
	//現在のキー入力状態の格納
	char tmpKey[KEY_NUM];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < KEY_NUM; i++) {
		//0:入力されていない, 1:入力された瞬間, 2以上:入力されている間
		if (tmpKey[i] != 0) {
			if (key[i] == 0) {
				key[i] = 1;
			}
			else {
				key[i]++;

				//オーバーフローを考慮
				if (key[i] >= CHAR_MAX - 1) {
					key[i] = 2;
				}
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