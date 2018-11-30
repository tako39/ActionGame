#ifndef ___Define
#define ___Define

//�X�N���[��
const int SCREEN_WIDTH  = 640;  // ��ʂ̉���
const int SCREEN_HEIGHT = 480;  // ��ʂ̏c��
const int CHIP_SIZE  = 32;      // ��̃`�b�v�̃T�C�Y

//�X�e�[�W
const int STAGE_NUM = 5;  //�X�e�[�W��
const int STAGE_WIDTH[5]  = {20, 20, 20, 20, 20}; //���̃`�b�v��
const int STAGE_HEIGHT[5] = {15, 20, 20, 20, 20}; //�c�̃`�b�v��

//�}�b�v
const int BACK = 0;    //�w�i
const int GROUND = 1;  //�n��

//�v���C���[
const int DIR_RIGHT =  1;  //�E����
const int DIR_LEFT  = -1;  //������

const float Gravity = 0.3f;    //�d��
const float Speed = 5.0f;      //���ړ����x
const float AirSpeed = 3.0f;   //�󒆂ł̉��ړ����x
const float JumpPower = 9.0f;  //�W�����v��

const float EPS = 1.0f;

//����
const int NONE = -1;  //�Ȃ�

const int UP    = 0;  //��
const int DOWN  = 1;  //��
const int LEFT  = 2;  //��
const int RIGHT = 3;  //�E

//�L�[�{�[�h
const int KEY_NUM = 256; //����

//���̑�

#endif