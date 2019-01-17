#ifndef ___Class_ISceneChanger
#define ___Class_ISceneChanger

typedef enum {
	eScene_Menu,		//���j���[���
	eScene_Game,		//�Q�[�����
	eScene_GameOver,	//�Q�[���I�[�o�[���
	eScene_GameClear,	//�Q�[���N���A���

	eScene_None,		//����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;	//�w��V�[���ɕύX����
};

inline ISceneChanger::~ISceneChanger() {

}

#endif