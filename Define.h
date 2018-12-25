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
const int STAGE_WIDTH[5]  = {20, 40, 0, 0, 0};	//�X�e�[�W�̉��̃`�b�v��
const int STAGE_HEIGHT[5] = {15, 20, 0, 0, 0};	//�X�e�[�W�̏c�̃`�b�v��


//�}�b�v
const int BACK = 0;		//�w�i
const int GROUND = 1;	//�n��

const int A = 20;
const int B = 21;
const int C = 22;
const int D = 23;
const int E = 24;
const int F = 25;
const int G = 26;
const int H = 27;
const int I = 28;
const int J = 29;
const int K = 30;
const int L = 31;
const int M = 32;
const int N = 33;
const int O = 34;
const int P = 35;
const int Q = 36;
const int R = 37;
const int S = 38;
const int T = 39;
const int U = 40;
const int V = 41;
const int W = 42;
const int X = 43;
const int Y = 44;
const int Z = 45;

//�v���C���[
const int MAX_HP = 100;	//�ő�g�o

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

const float bulletSpeed = 8.0f;	//�e�̑��x

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

//�_��
const int POINT_ENEMY_ZAKO = 10;	//Zako�œ�����|�C���g

//���̑�
const float PI = 3.14f;		//�~����

#endif