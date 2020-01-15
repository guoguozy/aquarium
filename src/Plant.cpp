/*###################################################
##  �ļ�: plant.cpp
##  �ļ�����������ˮ�����Ҫ��ֲ��
##  ������������
#####################################################*/
#include "Renderable.h"

using namespace std;

//���þ�̬����
GLfloat Plant::material1[4] = {0.1f, 0.3f, 0.15f, 1.f};
GLfloat Plant::material2[4] = {0.6f, 1.f, 0.8f, 1.f};
GLfloat Plant::shininess = 100.f;

/*###################################################
##  ����: Plant() : Renderable()
##  ����������Ĭ�Ϲ��캯��
##  ������������
#####################################################*/
Plant::Plant() : Renderable()
{
	cout << "-- Creating Plant\n";
	build(dlist);
}

/*###################################################
##  ����: ~Plant()
##  ����������Ĭ����������
##  ������������
#####################################################*/
Plant::~Plant()
{
	cout << "++ Destructing Plant\n";
}

/*###################################################
##  ����: _draw()
##  �������������ú�������ֲ��
##  ������������
#####################################################*/
void Plant::_draw(void)
{
	//��һ��ʼ���Ǿ�����һ��������һ����֧��ֲ�����������ǲ���õ�û�з�֧��ֲ��
	generate(0, Renderable::getRand(1, 6));
}

/*###################################################
##  ����: generate()
##  �������������ڻ���ֲ���ĺ���
##  ����������
##  level���ݹ����
##  number�����εݹ�����ֲ��������
#####################################################*/
void Plant::generate(int level, int number)
{
	//���˵����ݹ����ٵݹ�
	if (level == 5) return;

	//ÿ����֧����������һ����֧��3/4
	GLfloat height = 3.0f / (0.75 * (level + 1.f));
	GLfloat bottom = 0.75f / pow(2, level);
	GLfloat top = 0.75f / pow(2, (GLfloat)level + 1.f);

	for (int i = 0; i < number; i++)
	{

		GLfloat horzAngle = Renderable::getRand(0, 180);
		GLfloat vertAngle = Renderable::getRand(0, 180);
		int numChildren = Renderable::getRand(0, 6);

		glPushMatrix();
		glRotatef(horzAngle, 0.0f, 1.0f, 0.0f);
		glRotatef(vertAngle, 1.0f, 0.0f, 0.0f);

		//���
		glFrontFace(GL_CW);
		gluDisk(quadric, 0.0f, bottom, 8 - level, 1);
		glFrontFace(GL_CCW);

		//������֧
		gluCylinder(quadric, bottom, top, height, 8 - level, 1);

		//�ⶥ
		glTranslatef(0.0f, 0.0f, height);
		gluDisk(quadric, 0.0f, top, 8 - level, 1);

		//�����ǶȻ�ԭ��λ�ú��ٴε������ɺ���������֧
		glRotatef(-vertAngle, 1.0f, 0.0f, 0.0f);
		generate(level + 1, numChildren);
		glPopMatrix();
	}
}


/*###################################################
##  ����: _draw_dlist()
##  �������������ڻ���ֲ���������ʾ�б�
##  ������������
#####################################################*/
void Plant::_draw_dlist(void)
{
	//���ò������ԣ�ֻ������ǰ��ͼ��
	glMaterialfv(GL_FRONT, GL_AMBIENT, material1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material2);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColor4fv(material1);

	glCallList(this->dlist);
}
