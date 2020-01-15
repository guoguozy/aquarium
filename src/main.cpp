/*###################################################
##  主函数文件
#####################################################*/

#include <GL/glut.h>
#include <iostream>

#include "support_func.h"

using namespace std;


/*###################################################
##  定义全局变量
#####################################################*/
// 场景
extern Scene *scene;	
// 模式选项开关
extern bool wireMode;	
extern bool flatShading;	


/*###################################################
##  主函数，控制整个运行过程
##  参数：
##  返回值：
#####################################################*/
int main(int argc, char *argv[])
{
	cout << "-- Program starting\n";

	srand(time(NULL));
	init(argc, argv);

	// 注册回调函数
	cout << "-- Registering callback functions\n";
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboardInput);
	glutSpecialFunc(keyboardInput);

	// 生成纹理
	cout << "-- Generating/Loading Textures\n";
	getTextures();

	// 创建场景
	scene = new Scene();
	scene->perspectiveMode = true;

	// 添加地板
	Quad *quad;
	for (GLfloat i = -9.5; i <= 9.5; i++)
	{
		for (GLfloat j = -9.5; j <= 9.5; j++)
		{
			quad = new Quad();
			quad->ry = 0.0f;	
			quad->rx = 90.0f;
			quad->x = 3.5f * i;
			quad->z = 3.5f * j;
			quad->scale(3.5f, 3.5f, 1.0f);
			scene->add(quad);
		}
	}

	// 初始化设置
	keyboardInput((unsigned char)'L', 0, 0);
	keyboardInput((unsigned char)'0', 0, 0);
	keyboardInput((unsigned char)'1', 0, 0);
	keyboardInput((unsigned char)'F', 0, 0);

	// 开启计时器
	glutTimerFunc(50, animator, 0);
	glutMainLoop();
	
	return 0;
}


