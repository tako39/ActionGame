#ifndef ___Class_Task
#define ___Class_Task

//�^�X�N�N���X�B�����̃��W���[���͂��ׂĂ���Task�N���X���p������B
class Task {
public:
	virtual ~Task() {}
	virtual void Update() = 0;   //�X�V�����͕K���p����Ŏ�������
	virtual void Draw() = 0;     //�`�揈���͕K���p����Ŏ�������
};

#endif