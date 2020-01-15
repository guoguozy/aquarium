/*###################################################
##  �ļ�: crab.cpp
##  �ļ�����������һֻС��з
##  ������������
#####################################################*/
#include "Renderable.h"

using namespace std;

//���þ�̬����
GLfloat Crab::material[4] = {0.5f, 0.5f, 0.5f, 1.f};
GLfloat Crab::shininess = 50.f;

/*###################################################
##  ����: Crab() : Renderable()
##  ����������Ĭ�Ϲ��캯����Ϊ�з������ʾ�б�
##  ������������
#####################################################*/
Crab::Crab() : Renderable()
{
	cout << "-- Creating crab\n";
	sy = sx = sz = 2.f; //���з��СΪ֮ǰ������
	build(dlist);
}

/*###################################################
##  ����: ~Crab()
##  ����������Ĭ����������
##  ������������
#####################################################*/
Crab::~Crab()
{
	cout << "++ Destructing crab\n";
}

/*###################################################
##  ����: _draw()
##  ������������ͼ����������С��з
##  ������������
#####################################################*/
void Crab::_draw(void)
{
	//С��з����ɫ
	glColor3f(1.0f, 0.45f, 0.45f);

	//�����з������
	glPushMatrix();
	glScalef(1.0f, 0.5f, 1.0f);
	gluSphere(quadric, 0.3f, 16, 16);
	glPopMatrix();

	//�����зȫ������
	glPushMatrix();
	drawLegs();
	glScalef(-1.f, 1.f, 1.f);
	glFrontFace(GL_CW);
	drawLegs();
	glFrontFace(GL_CCW);
	glPopMatrix();

	//����ɫ����Ϊ��ɫ
	glColor3f(0.0f, 0.0f, 0.0f);

	//�з������
	glTranslatef(-0.06f, 0.0f, 0.3f);
	glutSolidSphere(0.05f, 12, 8);

	//�з������
	glTranslatef(0.12f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 12, 8);
}

/*###################################################
##  ����: _draw_dlist()
##  ���������������з�������ʾ�б�
##  ������������
#####################################################*/
void Crab::_draw_dlist(void)
{
	//���ò������ԣ�ֻ������ǰ��ͼ��
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glCallList(this->dlist);

	//����ɫ��
	glDisable(GL_COLOR_MATERIAL);
}

/*###################################################
##  ����: _drawLeg(GLfloat��GLfloat)
##  ���������������з�������ؽڹ�����ĽǶȻ�����
##  ����������
##  jointAngle��������ת�ĽǶȲ���
##  jointOffset������ƽ�Ƶľ������
#####################################################*/
void Crab::drawLeg(GLfloat jointAngle, GLfloat jointOffset)
{
	//�����ȵĵ�һ���ؽ�
	glPushMatrix();
	glTranslatef(-0.38f, 0.0f, 0.0f);
	glScalef(3.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();

	//�����ȵĵڶ����ؽ�
	glPushMatrix();
	glTranslatef(-0.53f, jointOffset, 0.0f);
	glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);
	glScalef(4.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();
}

/*###################################################
##  ����: drawLeg()
##  ���������������з��һ����
##  ������������
#####################################################*/
void Crab::drawLeg()
{
	drawLeg(-45.0f, 0.075f);
}

/*###################################################
##  ����: drawLegs()
##  ���������������з��ȫ������
##  ������������
#####################################################*/
void Crab::drawLegs()
{
	//�����Ȳ�����ɫ������ķۺ�ɫ��
	glColor3f(1.0f, 0.55f, 0.55f);

	//������������
	for (GLfloat i = -15.0f; i <= 15.0f; i += 15.0f)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -0.025f);
		glRotatef(i, 0.0f, 1.0f, 0.0f);
		drawLeg();
		glPopMatrix();
	}

	//���������ȣ�ֱ�ĺ����������µ��ȣ�
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.00f);
	glRotatef(-65.0f, -0.2f, 1.0f, 0.0f);
	drawLeg(0.0f, 0.0f);
	glPopMatrix();

	//����ǰ�ȵ���ɫ��ǳ��ɫ��
	glColor3f(1.0f, 0.65f, 0.65f);

	//����ǰ�㣨ǰ�ۣ�
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(55.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg();
	glPopMatrix();

	//����ǰ�㣨ǰ�ۣ��ϵ�ǯ��
	glPushMatrix();
	glTranslatef(0.24f, 0.0f, 0.725f);
	glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg(-60.0f, 0.1f);
	glPopMatrix();
}
