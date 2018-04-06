#pragma once
#include <gl/glut.h>              // OpenGL32���ͷ�ļ�
#include<stdio.h>
struct TextureTga            // ����һ���ṹ��
{
	GLubyte *imageData;           // ͼ������ (���32bit)
	GLuint bpp;            // ÿһ���ص�ͼ����ɫ���
	GLuint width;            // ͼ�����
	GLuint height;            // ͼ��߶�
	GLuint texID;            // ����ID
};

// ����BMP,JPG,GIF���ļ�
bool BuildTexture(char *szPathName, GLuint &texid);

// ����TGA�ļ�
bool BuildTexture(char *filename, TextureTga *texture);