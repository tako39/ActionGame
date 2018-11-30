#include "Enemy.h"
#include "Define.h"

Enemy::Enemy(VECTOR ePos) {
	pos = ePos;
	graphic_R = LoadGraph("");
	graphic_L = LoadGraph("");
	direct = LEFT;
}

Enemy::~Enemy() {

}

void Enemy::Update() {
	move = VGet(0.0f, 0.0f, 0.0f);

}

void Enemy::Draw() {
	if (direct == RIGHT) {
		DrawGraph((int)pos.x, (int)pos.y, graphic_R, FALSE);
	}
	else {
		DrawGraph((int)pos.x, (int)pos.y, graphic_L, FALSE);
	}
}