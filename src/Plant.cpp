/*###################################################
##  文件: plant.cpp
##  文件描述：绘制水族馆需要的植被
##  参数描述：无
#####################################################*/
#include "Renderable.h"

using namespace std;

//设置静态变量
GLfloat Plant::material1[4] = {0.1f, 0.3f, 0.15f, 1.f};
GLfloat Plant::material2[4] = {0.6f, 1.f, 0.8f, 1.f};
GLfloat Plant::shininess = 100.f;

/*###################################################
##  函数: Plant() : Renderable()
##  函数描述：默认构造函数
##  参数描述：无
#####################################################*/
Plant::Plant() : Renderable()
{
	cout << "-- Creating Plant\n";
	build(dlist);
}

/*###################################################
##  函数: ~Plant()
##  函数描述：默认析构函数
##  参数描述：无
#####################################################*/
Plant::~Plant()
{
	cout << "++ Destructing Plant\n";
}

/*###################################################
##  函数: _draw()
##  函数描述：调用函数绘制植被
##  参数描述：无
#####################################################*/
void Plant::_draw(void)
{
	//在一开始我们就生成一个至少有一个分支的植被，这样我们不会得到没有分支的植被
	generate(0, Renderable::getRand(1, 6));
}

/*###################################################
##  函数: generate()
##  函数描述：用于绘制植被的函数
##  参数描述：
##  level：递归层数
##  number：单次递归生成植被的数量
#####################################################*/
void Plant::generate(int level, int number)
{
	//到了第五层递归则不再递归
	if (level == 5) return;

	//每个分支数量都是上一个分支的3/4
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

		//封底
		glFrontFace(GL_CW);
		gluDisk(quadric, 0.0f, bottom, 8 - level, 1);
		glFrontFace(GL_CCW);

		//画出分支
		gluCylinder(quadric, bottom, top, height, 8 - level, 1);

		//封顶
		glTranslatef(0.0f, 0.0f, height);
		gluDisk(quadric, 0.0f, top, 8 - level, 1);

		//调整角度回原来位置后再次调用生成函数产生分支
		glRotatef(-vertAngle, 1.0f, 0.0f, 0.0f);
		generate(level + 1, numChildren);
		glPopMatrix();
	}
}


/*###################################################
##  函数: _draw_dlist()
##  函数描述：用于绘制植被对象的显示列表
##  参数描述：无
#####################################################*/
void Plant::_draw_dlist(void)
{
	//设置材质属性（只需设置前视图）
	glMaterialfv(GL_FRONT, GL_AMBIENT, material1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material2);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColor4fv(material1);

	glCallList(this->dlist);
}
