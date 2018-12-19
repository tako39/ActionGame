#ifndef ___Define
#define ___Define

//�X�N���[��
const int SCREEN_WIDTH  = 640;	// ��ʂ̉���
const int SCREEN_HEIGHT = 480;	// ��ʂ̏c��
const int CHIP_SIZE  = 32;		// ��̃`�b�v�̃T�C�Y

const int SCREEN_HALF_W = 320;	//�����̔���
const int SCREEN_HALF_H = 240;	//�c���̔���


//�X�e�[�W
const int STAGE_NUM = 5;	//�X�e�[�W��
const int STAGE_WIDTH[5]  = {40, 0, 0, 0, 0};	//���̃`�b�v��
const int STAGE_HEIGHT[5] = {20, 0, 0, 0, 0};	//�c�̃`�b�v��


//�}�b�v
const int BACK = 0;		//�w�i
const int GROUND = 1;	//�n��


//�v���C���[
const int DIR_RIGHT =  1;	//�E����
const int DIR_LEFT  = -1;	//������

const float Gravity = 0.5f;		//�d��
const float Speed = 5.0f;		//���ړ����x
const float AirSpeed = 3.0f;	//�󒆂ł̉��ړ����x
const float JumpPower = 12.0f;	//�W�����v��

const float EPS = 1.0f;		//�n�ʂƂ̓����蔻���EPS�������ɂ���


//�e
const int BULLET_WIDTH	= 16;	//�e�̉���
const int BULLET_HEIGHT = 8;	//�e�̏c��
const int BULLET_NUM = 5;		//�e�̐�

const float bulletSpeed = 10.0f;	//�e�̑��x

//�G
const int ENEMY_NUM = 5;	//�ő�̓G�̐�

//����
const int NONE = -1;	//�Ȃ�

const int UP    = 0;	//��
const int DOWN	= 1;	//��
const int LEFT  = 2;	//��
const int RIGHT = 3;	//�E


//�L�[�{�[�h
const int KEY_NUM = 256;	//����


//���̑�
const float PI = 3.14f;		//�~����

#endif