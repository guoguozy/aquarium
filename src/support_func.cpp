/*###################################################
##  辅助函数库文件
#####################################################*/

#include "support_func.h"

/*###################################################
##  定义全局变量
#####################################################*/
// 场景
Scene *scene;
// 模式选项开关
bool wireMode = false;
bool flatShading = false;

/*###################################################
##  给场景添加动态效果，每隔一段时间渲染一次场景
##  参数：
##  返回值：
#####################################################*/
void animator(int type)
{
	glutPostRedisplay();
	glutTimerFunc(25, animator, 0);
}

/*###################################################
##  窗口缩放
##  参数：
##      w, h： 宽度，高度
##  返回值：
#####################################################*/
void resizeWindow(int w, int h)
{
	glViewport(0, 0, w, h);

	// 更新场景的宽度和高度
	scene->width = w;
	scene->height = h;

	setupViewVolume();
}

/*###################################################
##  正常按键处理函数，根据按键做出反应
##  参数：
##      key： 按键
##  返回值：
#####################################################*/
void keyboardInput(unsigned char key, int x, int y)
{
	// 根据按键做出处理
	switch (key)
	{
	case 27: // ESC，退出
		exit(0);
		break;

	case ' ': // SPACE，Toggle flat/smooth shading
		flatShading = !flatShading;
		if (flatShading)
			glShadeModel(GL_FLAT);
		else
			glShadeModel(GL_SMOOTH);
		break;

	case 'A':
	case 'a':
		scene->camera.tiltdown();
		break;

	case 'Z':
	case 'z':
		scene->camera.tiltup();
		break;

	case 'W':
	case 'w':
		wireMode = !wireMode;
		if (!wireMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDisable(GL_BLEND);
			glDisable(GL_LINE_SMOOTH);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
		}
		break;

	case 'P':
	case 'p':
		scene->perspectiveMode = !scene->perspectiveMode;
		setupViewVolume();
		break;

	case 'f':
	case 'F':
		scene->fogMode = !scene->fogMode;
		if (scene->fogMode)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
		break;

	case 'l':
	case 'L':
		scene->lightMode = !scene->lightMode;
		if (scene->lightMode)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
		break;

	case '0':
		scene->light0On = !scene->light0On;
		if (scene->light0On)
			glEnable(GL_LIGHT0);
		else
			glDisable(GL_LIGHT0);
		break;

	case '1':
		scene->light1On = !scene->light1On;
		if (scene->light1On)
			glEnable(GL_LIGHT1);
		else
			glDisable(GL_LIGHT1);
		break;
	}
}

/*###################################################
##  特殊按键处理函数，根据按键做出反应
##  参数：
##      key： 按键
##  返回值：
#####################################################*/
void keyboardInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		scene->showMenu = !scene->showMenu;
		break;

	case GLUT_KEY_F2:
		addObject(CRAB);
		break;

	case GLUT_KEY_F3:
		addObject(OCTOPUS);
		break;

	case GLUT_KEY_F4:
		addObject(STARFISH);
		break;

	case GLUT_KEY_F5:
		addObject(FISH);
		break;

	case GLUT_KEY_F6:
		addObject(PLANT);
		break;

	case GLUT_KEY_LEFT:
		scene->camera.anticlockwise();
		break;

	case GLUT_KEY_RIGHT:
		scene->camera.clockwise();
		break;

	case GLUT_KEY_UP:
		scene->camera.inc();
		break;

	case GLUT_KEY_DOWN:
		scene->camera.dec();
		break;
	}
}

/*###################################################
##  渲染场景
##  参数：
##  返回值：
#####################################################*/
void drawScene()
{
	scene->render();
}

/*###################################################
##  往场景里添加物体
##  参数：
##      type： 物体类型
##  返回值：
#####################################################*/
void addObject(int type)
{
	// 随机选择位置
	GLfloat x = Renderable::getRand(-25.0f, 50.0f);
	GLfloat z = Renderable::getRand(-25.0f, 50.0f);

	// 高度因物体而异
	GLfloat y;

	Renderable *object;

	switch (type)
	{
	case STARFISH:
		y = -0.3f;
		object = new StarFish();
		break;
	case CRAB:
		y = -0.4f;
		object = new Crab();
		break;
	case FISH:
		y = Renderable::getRand(-26.0f, 25.0f);
		object = new Fish();
		break;
	case OCTOPUS:
		y = Renderable::getRand(-27.0f, 25.0f);
		object = new Octopus();
		break;
	case PLANT:
		y = 0.0f;
		object = new Plant();
		object->ry = 0.0f;
		break;
	}

	// 更新位置
	object->move(x, y, z);
	// 加入场景
	scene->add(object);
	// 更新计数
	scene->objects[type]++;
}

/*###################################################
##  View Volume设置
##  参数：
##  返回值：
#####################################################*/
void setupViewVolume(void)
{
	// 计算比例
	GLfloat aspect = (GLfloat)scene->width / (GLfloat)scene->height;
	GLfloat iaspect = (GLfloat)scene->height / (GLfloat)scene->width;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 根据当前状态进行设置
	if (scene->perspectiveMode == true)
		gluPerspective(-45.0f, aspect, 1.0f, 250.0f);
	else
	{
		if (aspect >= 1.0f)
			glOrtho(-40.0f * aspect, 40.0f * aspect, -40.0f, 40.0f, 1.0f, 250.0f);
		else
			glOrtho(-40.0f, 40.0f, -40.0f * iaspect, 40.0f * iaspect, 1.0f, 250.0f);
	}

	glMatrixMode(GL_MODELVIEW);
}

/*###################################################
##  初始化纹理
##  参数：
##  返回值：
#####################################################*/
void getTextures(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(2, Renderable::textures);

	getSandTexture();
	getFishTexture();
}

/*###################################################
##  读取沙土纹理
##  参数：
##  返回值：
#####################################################*/
void getSandTexture(void)
{
	char filename[] = "th.jpeg";
	GLuint tex_2d = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_AUTO,
		Renderable::textures[0],
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (0 == tex_2d)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

/*###################################################
##  读取鱼纹理
##  参数：
##  返回值：
#####################################################*/
void getFishTexture(void)
{
	char filename[] = "a.jpg";
	GLuint tex_2d = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_AUTO,
		Renderable::textures[1],
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (0 == tex_2d)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

/*###################################################
##  全局初始化函数
##  参数：
##  返回值：
#####################################################*/
bool init(int argc, char *argv[])
{
	// 初始化 glut
	cout << "-- Initialising GLUT\n";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// 窗口设置
	cout << "-- Creating window\n";
	glutCreateWindow("Aquarium Scene 3D");
	glutFullScreen();

	// 初始化 opengl
	setupGL();

	return true;
}

/*###################################################
##  Opengl 初始化
##  参数：
##  返回值：
#####################################################*/
void setupGL(void)
{
	cout << "-- Setting up OpenGL state\n";

	// 蓝绿色背景
	glClearColor(0.0, 0.5, 0.55, 1.0);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// 开启深度测试
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	// 设置雾
	glDisable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP);
	GLfloat fogColor[4] = {0.0f, 0.5f, 0.55f, 1.0f};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.0075);
	glHint(GL_FOG_HINT, GL_NICEST);

	glEnable(GL_NORMALIZE);

	// 设置灯光
	glDisable(GL_LIGHTING);
	GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// 混合设置
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 面剔除
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
