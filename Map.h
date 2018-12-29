#ifndef ___Class_Map
#define ___Class_Map

#include "Task.h"
#include "DxLib.h"

class Player;

class Map : public Task {
private:
	int back_Graphic;		//�w�i�̉摜
	int ground_Graphic;		//�n�ʂ̉摜

	int image_Alpha[26];	//�����̉摜

	int arrowGraphic_r;		//���̉摜
	int arrowGraphic_l;

	VECTOR playerPos;   //�v���C���[�̈ʒu

public:
	Map();
	~Map();

	void Update() {};
	void Update(const Player& cPlayer); //�X�V
	void Draw();   //�`��

	static int GetMap(int y, int x);  //map[y][x]�̒l�̎擾
	static int GetMapChip(float y, float x);  //�ʒu(x, y)�ɊY������}�b�v�`�b�v�̒l�̎擾
};

#endif