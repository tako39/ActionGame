#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"
#include "DxLib.h"
#include "Map.h"

class Map;

class Enemy : public Object {
private:
	const Map &map;

public:
	Enemy(Map &cMap, VECTOR ePos);
	~Enemy();

	void Update();
	void Draw();
};

#endif