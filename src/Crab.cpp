/*###################################################
##  文件: crab.cpp
##  文件描述：绘制一只小红蟹
##  参数描述：无
#####################################################*/
#include "Renderable.h"

using namespace std;

//设置静态变量
GLfloat Crab::material[4] = {0.5f, 0.5f, 0.5f, 1.f};
GLfloat Crab::shininess = 50.f;

/*###################################################
##  函数: Crab() : Renderable()
##  函数描述：默认构造函数，为螃蟹构建显示列表
##  参数描述：无
#####################################################*/
Crab::Crab() : Renderable()
{
	cout << "-- Creating crab\n";
	sy = sx = sz = 2.f; //让螃蟹大小为之前的两倍
	build(dlist);
}

/*###################################################
##  函数: ~Crab()
##  函数描述：默认析构函数
##  参数描述：无
#####################################################*/
Crab::~Crab()
{
	cout << "++ Destructing crab\n";
}

/*###################################################
##  函数: _draw()
##  函数描述：画图函数，画出小红蟹
##  参数描述：无
#####################################################*/
void Crab::_draw(void)
{
	//小红蟹的颜色
	glColor3f(1.0f, 0.45f, 0.45f);

	//画出螃蟹的身子
	glPushMatrix();
	glScalef(1.0f, 0.5f, 1.0f);
	gluSphere(quadric, 0.3f, 16, 16);
	glPopMatrix();

	//画出螃蟹全部的腿
	glPushMatrix();
	drawLegs();
	glScalef(-1.f, 1.f, 1.f);
	glFrontFace(GL_CW);
	drawLegs();
	glFrontFace(GL_CCW);
	glPopMatrix();

	//将颜色设置为黑色
	glColor3f(0.0f, 0.0f, 0.0f);

	//螃蟹的左眼
	glTranslatef(-0.06f, 0.0f, 0.3f);
	glutSolidSphere(0.05f, 12, 8);

	//螃蟹的右眼
	glTranslatef(0.12f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 12, 8);
}

/*###################################################
##  函数: _draw_dlist()
##  函数描述：绘制螃蟹对象的显示列表
##  参数描述：无
#####################################################*/
void Crab::_draw_dlist(void)
{
	//设置材质属性（只需设置前视图）
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glCallList(this->dlist);

	//跟踪色料
	glDisable(GL_COLOR_MATERIAL);
}

/*###################################################
##  函数: _drawLeg(GLfloat，GLfloat)
##  函数描述：根据螃蟹腿两个关节骨骼间的角度画出腿
##  参数描述：
##  jointAngle：用于旋转的角度参数
##  jointOffset：用于平移的距离参数
#####################################################*/
void Crab::drawLeg(GLfloat jointAngle, GLfloat jointOffset)
{
	//画出腿的第一个关节
	glPushMatrix();
	glTranslatef(-0.38f, 0.0f, 0.0f);
	glScalef(3.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();

	//画出腿的第二个关节
	glPushMatrix();
	glTranslatef(-0.53f, jointOffset, 0.0f);
	glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);
	glScalef(4.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();
}

/*###################################################
##  函数: drawLeg()
##  函数描述：绘制螃蟹的一条腿
##  参数描述：无
#####################################################*/
void Crab::drawLeg()
{
	drawLeg(-45.0f, 0.075f);
}

/*###################################################
##  函数: drawLegs()
##  函数描述：绘制螃蟹的全部侧腿
##  参数描述：无
#####################################################*/
void Crab::drawLegs()
{
	//设置腿部的颜色（较深的粉红色）
	glColor3f(1.0f, 0.55f, 0.55f);

	//画出三条侧腿
	for (GLfloat i = -15.0f; i <= 15.0f; i += 15.0f)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -0.025f);
		glRotatef(i, 0.0f, 1.0f, 0.0f);
		drawLeg();
		glPopMatrix();
	}

	//画第四条腿（直的和弯曲的向下的腿）
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.00f);
	glRotatef(-65.0f, -0.2f, 1.0f, 0.0f);
	drawLeg(0.0f, 0.0f);
	glPopMatrix();

	//设置前腿的颜色（浅粉色）
	glColor3f(1.0f, 0.65f, 0.65f);

	//绘制前足（前臂）
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(55.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg();
	glPopMatrix();

	//绘制前足（前臂）上的钳子
	glPushMatrix();
	glTranslatef(0.24f, 0.0f, 0.725f);
	glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg(-60.0f, 0.1f);
	glPopMatrix();
}
