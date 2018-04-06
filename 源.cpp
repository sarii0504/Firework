#define _CRT_SECURE_NO_WARNINGS    

#include <stdlib.h>     
#include<time.h>  
#include"particle.h"    
#include"texture.h"
#define PI 3.1415926
emitter *e1;


//����    
float whRatio;
int wHeight = 0;
int wWidth = 0;

//�ӵ�    
float center[] = { 0, 0, 0 };
float eye[] = { 0, 0, 5 };
int newx = 400, newy = 300, oldx = 0, oldy = 0;//��¼���λ��
void mymouse(int button, int state, int x, int y);//����������¼�����
particle* init_particle()
{  //��С,���ٶȣ��������ڣ��Ƕȣ��Ƿ�����
	float size = rand() % 15 * 0.02f;//������Ӵ�С
	float angle = rand() % 361;//����0-360�������
	angle = angle*PI / 180;//�仯�Ƕ�
	particle* p = new particle(size, size, 45 + rand() % 20, angle);//�����̻�����
	return p;
}
void drawScene()
{
	e1->update();

}

void updateView(int height, int width)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);//���þ���ģʽΪͶӰ         
	glLoadIdentity();   //��ʼ������Ϊ��λ����            
	whRatio = (GLfloat)width / (GLfloat)height;  //������ʾ����       
	glOrtho(-30, 30, -30, 30, -100, 100); //��ͶӰ    
	glMatrixMode(GL_MODELVIEW);  //���þ���ģʽΪģ��      
}

void reshape(int width, int height)
{
	if (height == 0) { //����߶�Ϊ0   
		height = 1;   //�ø߶�Ϊ1��������ַ�ĸΪ0������        
	}
	wHeight = height;
	wWidth = width;
	updateView(wHeight, wWidth); //�����ӽ�        
}

void idle()
{
	glutPostRedisplay();
}

void init(void)
{
	srand(unsigned(time(nullptr)));
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	GLfloat color[] = { rand() % 256 * 0.004,rand() % 256 * 0.004 ,rand() % 256 * 0.004 };
	e1 = new emitter(rand() % 500 + 200, 0, 10, color, 30 + rand() % 30);//�ٶȣ�x1,x2,y1,y2
	e1->emit(init_particle);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����Ȼ���   
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   //��ʼ������Ϊ��λ����        
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	drawScene();//���Ƴ���     
	glutSwapBuffers();//����������    
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//��glut�ĳ�ʼ��           
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//��ʼ����ʾģʽ:RGB��ɫģ�ͣ���Ȳ��ԣ�˫����             
	glutInitWindowSize(800, 600);//���ô��ڴ�С           
	int windowHandle = glutCreateWindow("Firework Partical System");//���ô��ڱ���             
	glutDisplayFunc(redraw); //ע����ƻص�����           
	glutReshapeFunc(reshape);   //ע���ػ�ص�����           
	glutIdleFunc(idle);//ע��ȫ�ֻص�����������ʱ����         
	init();
	glutMouseFunc(mymouse);
	glutMainLoop();  // glut�¼�����ѭ��         
	return 0;
}

void mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (x<800 && y<600) {
			newx = x + 3;
			newy = y + 3;
		}
	}
	if (newx != oldx || newy != oldy)
	{
		oldx = newx;
		oldy = newy;
		delete e1;
		GLfloat color[] = { rand() % 256 * 0.004,rand() % 256* 0.004 ,rand() % 256* 0.004 };//�����ɫ
		e1 = new emitter(rand()%500+200, (newx - 400) / 40.0 * 3, (300 - newy) / 10.0,color,30+rand()%30);//�ٶȣ�x1,x2,y1,y2
		e1->emit(init_particle);//ɾ��ԭ�����̻����½��̻�����
	}
	drawScene();//���ƻ���
}