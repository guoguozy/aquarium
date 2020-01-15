/**
* 场景类的定义
* 定义了视角，雾气和光照
**/

#ifndef __SCENE_3201
#define __SCENE_3201

#include <GL/glut.h>
#include <list>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Renderable.h"
#include "Camera.h"

#define OBJ_CRAB 0
#define OBJ_OCTOPUS 1
#define OBJ_STARFISH 2
#define OBJ_FISH 3
#define OBJ_PLANT 4

#define SIGN(x) (x < 0 ? (-1) : 1)

class Scene
{
private:
	GLenum error;
	// 多边形模式，线连接的or实心体
	GLenum polygonModel;
	// 需要渲染的物体列表
	std::list<Renderable *> *elements;
	std::list<Renderable *>::iterator iter;

	// light0的光照参数
	static GLfloat ambient0[4];
	static GLfloat diffuse0[4];
	static GLfloat specular0[4];
	static GLfloat position0[4];

	// light1的光照参数
	static GLfloat ambient1[4];
	static GLfloat diffuse1[4];
	static GLfloat specular1[4];
	static GLfloat position1[4];
	static GLfloat direction1[4];

	static GLfloat spotAngle;

public:
	Camera camera;
	int objects[5];		  // 五种物体的计数器
	bool perspectiveMode; // 视角，从侧面或从顶部看
	bool showMenu;		  // 显示菜单
	bool light0On;		  // 开启/关闭光照0
	bool light1On;
	bool fogMode;   // 开启关闭雾气效果
	bool lightMode; // 开关光照功能

	static int width;  // 窗体宽度
	static int height; //窗体高度

public:
	Scene();
	virtual ~Scene();

	bool render(void);			  // 渲染一帧
	void add(Renderable *object); // 添加一个物体

private:
	void clear(void);
	void printGL(GLfloat x, GLfloat y, GLfloat z, const char *str, int count);
	void printGL(GLfloat x, GLfloat y, GLfloat z, const char *str);
	void printMenu(void); // 显示菜单
	void drawHUD(void);   // HUD显示信息
	void distort(void);
	void eval(int i, int j, GLfloat *ix, GLfloat *iy);
};

#endif
