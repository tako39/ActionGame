#include "Keyboard.h"

static int key[KEY_NUM];

void UpdateKey() {
	//���݂̃L�[���͏�Ԃ̊i�[
	char tmpKey[KEY_NUM];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < KEY_NUM; i++) {
		//0:���͂���Ă��Ȃ�, 1:���͂��ꂽ�u��, 2�ȏ�:���͂���Ă����
		if (tmpKey[i] != 0) {
			if (key[i] == 0) {
				key[i] = 1;
			}
			else {
				key[i]++;

				//�I�[�o�[�t���[���l��
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