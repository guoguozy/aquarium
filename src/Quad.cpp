/**
* Renderable中四边形基类的定义，用于生成水族馆的地板
**/
#include "Renderable.h"

using namespace std;

// 地板材质颜色和粗糙程度的静态变量
GLfloat Quad::material[4] = {1.f, 1.f, 1.f, 1.f};
GLfloat Quad::shininess = 120.f;


// 构造函数
Quad::Quad() : Renderable()
{}


// 析构函数
Quad::~Quad()
{}

// 四边形描绘，先设定材质属性和纹理，然后画四边形
void Quad::_draw(void)
{
	// 设置材质属性（只需要前面，背面在底部看不到，参数material和shininess为static，已初始化
	glMaterialfv(GL_FRONT, GL_AMBIENT, material); // 环境颜色
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material); // 散射颜色
	glMaterialfv(GL_FRONT, GL_SPECULAR, material); // 环境和散射颜色
	glMaterialf(GL_FRONT, GL_SHININESS, shininess); // 镜面反射颜色

	// 开启纹理
	glEnable(GL_TEXTURE_2D);
	// 绑定自定义纹理
	glBindTexture(GL_TEXTURE_2D, FLOOR_TEXTURE);

	// 纹理参数，REPEAT对越界的纹理采用重复填充，消除板块之间的缝隙
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 加载不同大小纹理，自动选择放大缩小最优的纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor3f(0.9f, 0.6f, 0.0f);
	// 设定顶点顺序逆时针为正面
	glFrontFace(GL_CCW);
	glBegin(GL_QUADS);
		glNormal3f(0.f, 0.f, 1.f);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(-0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(0.5f,  -0.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
