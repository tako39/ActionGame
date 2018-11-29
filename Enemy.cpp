#include "Enemy.h"

Enemy::Enemy(Map &cMap, VECTOR ePos) : map(cMap) {
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
		DrawGraph(pos.x, pos.y, graphic_R, FALSE);
	}
	else {
		DrawGraph(pos.x, pos.y, graphic_L, FALSE);
	}
}