/*###################################################
##  文件: camera.h
##  文件描述：实现camera类
##  参数描述：无
#####################################################*/

#ifndef __CAMERA_3201
#define __CAMERA_3201

#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159

/*###################################################
##  类: Camera
##  类描述：Camera类，实现镜头相关功能
##  参数描述：
##  verticalTilt：camera在X轴的倾斜角
##  horizontalAngle：camera在Y轴的倾斜角
##  distance：camera到原点的距离
##  其他函数功能说明在Camera.cpp中
#####################################################*/
class Camera
{
private:
	GLfloat verticalTilt;
	GLfloat horizontalAngle;
	GLfloat distance;

public:
	Camera();	//默认构造函数
	virtual ~Camera();	//默认析构函数

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
