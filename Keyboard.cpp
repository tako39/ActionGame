#include "Keyboard.h"

static int key[KEY_NUM];

void UpdateKey() {
	//���݂̃L�[���͏�Ԃ̊i�[
	char tmpKey[KEY_NUM];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < KEY_NUM; i++) {
		//0:���͂���Ă��Ȃ�, 1:���͂��ꂽ�u��, 2:���͂���Ă����
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