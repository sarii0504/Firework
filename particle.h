#pragma once
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>  


class particle {
	bool has_tex;//颜色
	float x, y;//位置
	float Max_y = 0;//上升的最高点，由鼠标点击确定
	float size_x;//大小
	float size_y;
	int flag = 0;
	float speed_1;
	float speed_2;
	float speed_3 = 0;
	float acc_x;//加速度
	float life;//生命
	float angle;//角度
	GLfloat color[3];//颜色
	friend class emitter;
	void draw();//绘制粒子（颜色）
	void show_firework1();//绘制烟花爆炸状态
	void show_firework2();//绘制烟花消失状态
	void show_firework0();//绘制烟花上升状态
public:
	particle();
	particle(float _size_x, float _size_y,
		float _life, float _angle);
};

class emitter {
	float x, y; //发射器位置
	int speed;//发射速率
	int size;//烟花大小
	GLfloat *color;//颜色
	particle **p;//发射粒子
	particle* (*f)(); //初始化粒子的函数指针
public:
	void emit(particle* (init)());
	void update();
	emitter(int _speed, float _x,
		float _y, GLfloat *_color, int _size);
};