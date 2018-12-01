#ifndef ___Class_Map
#define ___Class_Map

#include "Task.h"
#include "DxLib.h"

class Player;

class Map : public Task {
private:
	int back_Graphic;   //�w�i�̉摜
	int ground_Graphic; //�n�ʂ̉摜

	VECTOR playerPos;   //�v���C���[�̈ʒu

public:
	Map();
	~Map();

	void Update() {};
	void Update(const Player& cPlayer); //�X�V
	void Draw();   //�`��

	int GetMap(int y, int x) const;  //map[y][x]�̒l�̎擾
	int GetMapChip(float y, float x) const;  //�ʒu(x, y)�ɊY������}�b�v�`�b�v�̒l�̎擾
};

#endif