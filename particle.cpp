#include<stdlib.h>
#include"particle.h"
#include<math.h>



void particle::draw()
{
	const GLfloat x1 = -0.5, x2 = 0.5;
	const GLfloat y1 = -0.5, y2 = 0.5;
	const GLfloat point[4][2] = { { x1,y1 },{ x2,y1 },{ x2,y2 },{ x1,y2 } };
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(point[i]);
	}
	glEnd();
}

void particle::show_firework0() {
	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
	glTranslatef(x, y, 0);//移动位置
	glScalef(size_x, size_y, 0);//粒子大小
	draw();
	glPopMatrix();
	y = y + speed_1;
	if (y >= Max_y)
		flag = 1;//上升结束
	glColor3f(0, 0, 0);
}//烟花上升

void particle::show_firework1() {
		glPushMatrix();
		glColor3f(color[0], color[1], color[2]);
		glTranslatef(x, y, 0);//移动位置
		glRotatef(angle, 0, 0, 1);
		glScalef(size_x, size_y, 0);//粒子大小
		draw();
		glPopMatrix();
		x += speed_2*cos(angle);
		y += speed_2*sin(angle);
		speed_2 += acc_x;//受到反向的阻力
		if (speed_2 <= 0) {
			speed_2 = 0;
			flag = 2;
		}//进入消失阶段。
}

void particle::show_firework2() {
	if (life > 0) {
		glPushMatrix();
		if (life < 4)
			glColor4f(color[0], color[1], color[2], life*0.25);
		else
			glColor3f(color[0], color[1], color[2]);
		glTranslatef(x, y, 0);//移动位置
		glRotatef(angle, 0, 0, 1);
		glScalef(size_x, size_y, 0);//粒子大小
		draw();
		glPopMatrix();
		y += speed_3;//下降
		speed_3 += -0.0002;//受到重力作用
		life -= 0.2f;
	}
}//烟花消失过程


particle::particle() {}
particle::particle(float _size_x, float _size_y,
	float _life, float _angle) {
	Max_y = 0;
	size_x = _size_x;
	size_y = _size_y;
	speed_1 = 0.6;
	speed_3 = 0;
	life = _life;
	_life = 1;
	angle = _angle;
	has_tex = false;
	flag = 0;
}

void emitter::emit(particle* (init)()) {
	for (int i = 0; i < speed; i++) {
		f = init;
		p[i] = init();
		p[i]->Max_y = y;
		p[i]->x =x;
		p[i]->y =-32;//发射的起始位置
		p[i]->color[0] = *(color + 0) + rand() % 10 * 0.02;//随机小幅度更改颜色
		p[i]->color[1] = *(color + 1) + rand() % 10 * 0.02;
		p[i]->color[2] = *(color + 2) + rand() % 10 * 0.02;
		p[i]->speed_2 = rand() % 20*size*0.0001f;//指定速度
		p[i]->acc_x =-p[i]->speed_2/ (50 + rand() % 50);//指定加速度，与速度相关
	}
}

void emitter::update() {
	for (int i = 0; i < speed; i++) {
		if (*(p + i) != 0) {
			if (p[i]->flag == 0) {
				//上升阶段
				p[i]->show_firework0();
			}
			else if (p[i]->flag == 1)//第一阶段
			{
				p[i]->show_firework1();
			}
			else {
				if (p[i]->life > 0)
				{
					if (p[i]->life < 4)//如果粒子的Life<4
					{
						int q = -10 + rand() % 20;
						if (q < 0)//随机删除粒子
						{
							delete p[i];
							*(p + i) = 0;
						}
						else
							p[i]->show_firework2();
					}
					else
						p[i]->show_firework2();			
				}
				else
				{
					delete p[i];
					*(p + i) = 0;
				}
			}
		}
	}
}



emitter::emitter(int _speed, float _x,
	float _y, GLfloat *_color,int _size) {
	speed = _speed;
	x = _x;
	y = _y;
	p = new particle*[speed];
	color = _color;
	size = _size;
}