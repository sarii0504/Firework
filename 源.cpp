#define _CRT_SECURE_NO_WARNINGS    

#include <stdlib.h>     
#include<time.h>  
#include"particle.h"    
#include"texture.h"
#define PI 3.1415926
emitter *e1;


//视区    
float whRatio;
int wHeight = 0;
int wWidth = 0;

//视点    
float center[] = { 0, 0, 0 };
float eye[] = { 0, 0, 5 };
int newx = 400, newy = 300, oldx = 0, oldy = 0;//记录鼠标位置
void mymouse(int button, int state, int x, int y);//定义鼠标点击事件函数
particle* init_particle()
{  //大小,加速度，生命周期，角度，是否永存
	float size = rand() % 15 * 0.02f;//随机粒子大小
	float angle = rand() % 361;//返回0-360随机整数
	angle = angle*PI / 180;//变化角度
	particle* p = new particle(size, size, 45 + rand() % 20, angle);//单个烟花粒子
	return p;
}
void drawScene()
{
	e1->update();

}

void updateView(int height, int width)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);//设置矩阵模式为投影         
	glLoadIdentity();   //初始化矩阵为单位矩阵            
	whRatio = (GLfloat)width / (GLfloat)height;  //设置显示比例       
	glOrtho(-30, 30, -30, 30, -100, 100); //正投影    
	glMatrixMode(GL_MODELVIEW);  //设置矩阵模式为模型      
}

void reshape(int width, int height)
{
	if (height == 0) { //如果高度为0   
		height = 1;   //让高度为1（避免出现分母为0的现象）        
	}
	wHeight = height;
	wWidth = width;
	updateView(wHeight, wWidth); //更新视角        
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
	e1 = new emitter(rand() % 500 + 200, 0, 10, color, 30 + rand() % 30);//速度，x1,x2,y1,y2
	e1->emit(init_particle);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓存   
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   //初始化矩阵为单位矩阵        
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	drawScene();//绘制场景     
	glutSwapBuffers();//交换缓冲区    
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//对glut的初始化           
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//初始化显示模式:RGB颜色模型，深度测试，双缓冲             
	glutInitWindowSize(800, 600);//设置窗口大小           
	int windowHandle = glutCreateWindow("Firework Partical System");//设置窗口标题             
	glutDisplayFunc(redraw); //注册绘制回调函数           
	glutReshapeFunc(reshape);   //注册重绘回调函数           
	glutIdleFunc(idle);//注册全局回调函数：空闲时调用         
	init();
	glutMouseFunc(mymouse);
	glutMainLoop();  // glut事件处理循环         
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
		GLfloat color[] = { rand() % 256 * 0.004,rand() % 256* 0.004 ,rand() % 256* 0.004 };//随机颜色
		e1 = new emitter(rand()%500+200, (newx - 400) / 40.0 * 3, (300 - newy) / 10.0,color,30+rand()%30);//速度，x1,x2,y1,y2
		e1->emit(init_particle);//删除原来的烟花，新建烟花对象
	}
	drawScene();//绘制画面
}