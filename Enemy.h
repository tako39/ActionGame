#ifndef ___Class_Enemy
#define ___Class_Enemy

#include "Object.h"

class Player;
class BulletMgr;
class BombMgr;

class Enemy : public Object {
protected:
	int enemyType;		//敵の種類
	float enemySpeed;	//敵の初期移動速度
	bool isGround;		//接地判定

	int damageSound;	//ダメージ音

public:
	Enemy();
	~Enemy();

	virtual void Update() = 0;
	virtual void Update(const Player& player) {};
	virtual void Draw() = 0;
	virtual void Draw(const Player& player) {};

	void EnemyDraw(const Player& player);	//敵の描画
	void HpDraw();	//体力の描画

	int GetType() const { return enemyType; };	//敵の種類の取得
	
	VECTOR randomPos(int h, int w);		//ランダムで位置決め(h:敵の縦幅,w:敵の横幅)
	int randomDir();		//ランダムで向きを決める
	float randomSpeed();	//ランダムで移動速度を決める

	void Move(float moveY, float moveX);	//移動時の処理
	void LookAhead();	//先を見て落ちないように向きを変える

	void GroundCheck();	//接地判定

	void Collision(const Player& player, BulletMgr& bulletMgr, BombMgr& bombMgr);	//当たり判定
	bool CollisionPunch(const Player& player);	//当たり判定（パンチ）
	bool CollisionBullet(BulletMgr& bulletMgr);	//当たり判定（弾）
	bool CollisionBomb(BombMgr& bombMgr);		//当たり判定（爆弾）
};

#endif