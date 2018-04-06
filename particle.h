#pragma once
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>  


class particle {
	bool has_tex;//��ɫ
	float x, y;//λ��
	float Max_y = 0;//��������ߵ㣬�������ȷ��
	float size_x;//��С
	float size_y;
	int flag = 0;
	float speed_1;
	float speed_2;
	float speed_3 = 0;
	float acc_x;//���ٶ�
	float life;//����
	float angle;//�Ƕ�
	GLfloat color[3];//��ɫ
	friend class emitter;
	void draw();//�������ӣ���ɫ��
	void show_firework1();//�����̻���ը״̬
	void show_firework2();//�����̻���ʧ״̬
	void show_firework0();//�����̻�����״̬
public:
	particle();
	particle(float _size_x, float _size_y,
		float _life, float _angle);
};

class emitter {
	float x, y; //������λ��
	int speed;//��������
	int size;//�̻���С
	GLfloat *color;//��ɫ
	particle **p;//��������
	particle* (*f)(); //��ʼ�����ӵĺ���ָ��
public:
	void emit(particle* (init)());
	void update();
	emitter(int _speed, float _x,
		float _y, GLfloat *_color, int _size);
};