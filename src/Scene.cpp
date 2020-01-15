/**
* 场景类的定义
**/

#include "Scene.h"

using namespace std;

int Scene::width;
int Scene::height;

// 光照0的参数，环境光，漫反射和反射光和光源位置，平行光
GLfloat Scene::ambient0[4]	= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat Scene::diffuse0[4]	= {0.4f, 0.4f, 0.4f, 1.01f};
GLfloat Scene::specular0[4]	= {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat Scene::position0[4]	= {0.0f, -1.0f, 0.0f, 0.0f};

// 光照1参数，点光源，有光照方向（聚光）
GLfloat Scene::ambient1[4]	= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat Scene::diffuse1[4]	= {0.45f, 0.45f, 0.45f, 1.0f};
GLfloat Scene::specular1[4]	= {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat Scene::position1[4]	= {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat Scene::direction1[4]	= {0.0f, 0.0f, -1.0f};

// 光照1是聚光灯，设置光源最大扩展角度，与法线夹角超过的部分被遮蔽
GLfloat Scene::spotAngle	= 15.f;


Scene::Scene()
{
	cout << "-- Creating scene\n";

	error = GL_NO_ERROR;
	polygonModel = GL_FILL;
	elements = new std::list<Renderable*>; // 创建需要显示的物体列表
	showMenu = true;
	light0On = false;
	light1On = false;
	fogMode = false;
	lightMode = false;

	// 初始化所有物体的计数器
	objects[OBJ_CRAB] = 0;
	objects[OBJ_STARFISH] = 0;
	objects[OBJ_OCTOPUS] = 0;
	objects[OBJ_FISH] = 0;
	objects[OBJ_PLANT] = 0;

	// 设置光源0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	// 光源1
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
}


Scene::~Scene()
{
	cout << "++ Destructing scene\n";
	delete elements;
}


/**
* 仅渲染一帧
**/
bool Scene::render(void)
{
	GLenum error;

	// 有错误则输出
	while ((error = glGetError()) != GL_NO_ERROR)
		cout << ">> Error: " << gluErrorString(error) << endl;

	// 清除屏幕，准备渲染和输出
	clear();

	// 设置聚光灯光照
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);

	// 摆放摄像机（调整观察角度）
	camera.position();

	// 顶部光照设定
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	// 画图
	if (elements->size() > 0)
	{
		iter = elements->begin();
		while (iter != elements->end())
			(*iter++)->draw();
	}

	drawHUD();

	glutSwapBuffers();
	return true;
}


/**
*  颜色和深度缓冲区都被清空，防止影响下一次画图
**/
void Scene::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
* 添加一个待渲染的物体
**/
void Scene::add(Renderable *object)
{
	elements->push_back(object);
}


/**
* 显示HUD的信息
**/
void Scene::drawHUD(void)
{
	// 关闭深度测试，不被任何物体遮蔽显示在顶部
	glDisable(GL_DEPTH_TEST);

	// 关闭光照，HUD信息与场景无关
	GLboolean lightsOn;
	glGetBooleanv(GL_LIGHTING, &lightsOn);
	glDisable(GL_LIGHTING);

	// 修改投影角度
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(-0.1f, 10.0f, 10.0f, -0.4f, -1.0f, 10.0f);

	// 修改观察
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);

	// 显示物体数量
	printGL(0.0f, 0.0f, 0.0f, "Crabs:    ", objects[OBJ_CRAB]);
	printGL(1.5f, 0.0f, 0.0f, "Starfish: ", objects[OBJ_STARFISH]);
	printGL(3.0f, 0.0f, 0.0f, "Octopi:   ", objects[OBJ_OCTOPUS]);
	printGL(4.5f, 0.0f, 0.0f, "Fish:     ", objects[OBJ_FISH]);
	printGL(6.0f, 0.0f, 0.0f, "Plants:   ", objects[OBJ_PLANT]);

	// char(30)

	// 光照模式开启与否
	if (lightMode) printGL(0.0f, 0.3f, -1.0f, "Lighting Calculations: On     ");
	else printGL(0.0f, 0.3f, -1.0f, "Lighting Calculations: Off    ");

	// 顶部光照0开启与否
	if (light0On) printGL(0.0f, 0.6f, -1.0f, "Overhead Light: On            ");
	else printGL(0.0f, 0.6f, -1.0f, "Overhead Light: Off           ");

	// 聚光灯光照1开启与否
	if (light1On) printGL(0.0f, 0.9f, -1.0f, "Miner's Hat Light: On         ");
	else printGL(0.0f, 0.9f, -1.0f, "Miner's Hat Light: Off        ");

	// 雾气开启与否
	if (fogMode) printGL(0.0f, 1.2f, -1.0f, "Fog: On                       ");
	else printGL(0.0f, 1.2f, -1.0f, "Fog: Off                      ");

	// print the menu if needed
	if (showMenu)
		printMenu();

	// 恢复到原来状态（观察，投影角度，深度测试，光照）
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	if (lightsOn) glEnable(GL_LIGHTING);
}


// 输出字符串到字符串，调用输出函数打印在窗口
void Scene::printGL(GLfloat x, GLfloat y, GLfloat z, const char *str, int count)
{
	char buffer[30];
	for (int i = 0; i < 30; ++i)
		buffer[i] = ' ';

	sprintf(buffer,"%s %i", str, count);
	printGL(x, y, z, buffer);
}


// 输出字符串打印在窗口
void Scene::printGL(GLfloat x, GLfloat y, GLfloat z, const char *str)
{
	glRasterPos3f(x, y, z);

	for (int j = 0; j < 30; j++) {
		int c = str[j];
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
	}
}


// 主菜单提示按键
void Scene::printMenu(void)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	printGL(0.0f, 1.7f, -1.0f, "---[ Help Screen ]------------");

	glColor3f(1.0f, 1.0f, 0.0f);
	printGL(0.0f, 2.0f, -1.0f, "F1    - Toggle Help Screen      ");
	printGL(0.0f, 2.3f, -1.0f, "F2    - Add a crab              ");
	printGL(0.0f, 2.6f, -1.0f, "F3    - Add an octopus          ");
	printGL(0.0f, 2.9f, -1.0f, "F4    - Add a starfish          ");
	printGL(0.0f, 3.2f, -1.0f, "F5    - Add a fish              ");
	printGL(0.0f, 3.5f, -1.0f, "F6    - Add a plant             ");

	glColor3f(0.5f, 1.0f, 0.0f);
	printGL(0.0f, 3.8f, -1.0f, "F/f   - Toggle fog on/off       ");
	printGL(0.0f, 4.1f, -1.0f, "W/w   - Toggle wireframe on/off ");
	printGL(0.0f, 4.4f, -1.0f, "L/l   - Toggle lighting on/off  ");
	printGL(0.0f, 4.7f, -1.0f, "1/0   - Toggle light 1/0 on/off ");

	glColor3f(0.0f, 1.0f, 0.0f);
	printGL(0.0f, 5.0f, -1.0f, "A/Z   - Inc/Dec elevation angl  ");
	printGL(0.0f, 5.3f, -1.0f, "UP    - Dec distance to origin  ");
	printGL(0.0f, 5.6f, -1.0f, "DOWN  - Inc distance to origin  ");
	printGL(0.0f, 5.9f, -1.0f, "LEFT  - Rotate clockwise        ");
	printGL(0.0f, 6.2f, -1.0f, "RIGHT - Rotate anticlockwise    ");

	glColor3f(0.0f, 0.0f, 1.0f);
	printGL(0.0f, 6.5f, -1.0f, "ESC   - Exit                    ");
}
