/*###################################################
##  辅助函数头文件
#####################################################*/
#ifndef __SUPPORT_FUNC
#define __SUPPORT_FUNC
#include <GL/glut.h>
#include <iostream>
#include <SOIL.h>

#include "Scene.h"
#include "Renderable.h"

using namespace std;

/*###################################################
##  定义物体编号
#####################################################*/
#define CRAB 0
#define OCTOPUS 1
#define STARFISH 2
#define FISH 3
#define PLANT 4

/*###################################################
##  函数声明
#####################################################*/
// 全局初始化函数
bool init(int argc, char *argv[]);
// Opengl 初始化
void setupGL(void);
// 给场景添加动态效果
void animator(int type);
// 窗口缩放
void resizeWindow(int w, int h);
// 正常按键处理函数
void keyboardInput(unsigned char key, int x, int y);
// 特殊按键处理函数
void keyboardInput(int key, int x, int y);
// 绘制场景
void drawScene(void);
// 往场景里添加物体
void addObject(int type);
// View Volume设置
void setupViewVolume(void);
// 初始化纹理
void getTextures(void);
// 读取沙土纹理
void getSandTexture(void);
// 读取鱼纹理
void getFishTexture(void);

#endif
