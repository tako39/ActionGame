#ifndef ___Class_Game
#define ___Class_Game

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Map.h"
#include "Player.h"
#include "Keyboard.h"
#include "DxLib.h"

class Map;
class Player;

//�Q�[����ʃN���X
class Game : public BaseScene {

private:
	Map *map;
	Player *player;

public:
	Game::Game(ISceneChanger* changer);
	void Initialize() override;  //�������������I�[�o�[���C�h�B
	void Finalize() override;    //�I���������I�[�o�[���C�h�B
	void Update() override;      //�X�V�������I�[�o�[���C�h�B
	void Draw() override;        //�`�揈�����I�[�o�[���C�h�B

	static int nowStage; //���݂̃X�e�[�W
};

#endif