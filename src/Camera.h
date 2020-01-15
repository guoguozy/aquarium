/*###################################################
##  �ļ�: camera.h
##  �ļ�������ʵ��camera��
##  ������������
#####################################################*/

#ifndef __CAMERA_3201
#define __CAMERA_3201

#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159

/*###################################################
##  ��: Camera
##  ��������Camera�࣬ʵ�־�ͷ��ع���
##  ����������
##  verticalTilt��camera��X�����б��
##  horizontalAngle��camera��Y�����б��
##  distance��camera��ԭ��ľ���
##  ������������˵����Camera.cpp��
#####################################################*/
class Camera
{
private:
	GLfloat verticalTilt;
	GLfloat horizontalAngle;
	GLfloat distance;

public:
	Camera();	//Ĭ�Ϲ��캯��
	virtual ~Camera();	//Ĭ����������

	void reset(void);
	void position(void);
	void dec(void);
	void inc(void);
	void clockwise(void);
	void anticlockwise(void);
	void tiltup(void);
	void tiltdown(void);
};

#endif
