#ifndef ___Class_Frame
#define ___Class_Frame

//FPS�𒲐�����N���X
class Frame {
private:
	int startTime;	//����J�n����
	int count;		//�J�E���g
	float fps;		//fps

	const int N = 60;	//���ς����T���v����
	const int FPS = 60;	//60fps�Ƃ���

public:
	Frame();
	~Frame();

	void Update();
	void Wait();	//FPS�̒����̂��߂̑ҋ@
};

#endif