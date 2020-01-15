/*
*	descri:
*		implement of class StarFish : public Renderable{}
*	author:
*		17341044
* 	reference:
*		https://www.cnblogs.com/hefee/p/3822844.html
*/
/*
class StarFish : public Renderable
{
private:
	static GLfloat vertex[];	/// vertex array data
	static GLfloat normal[];	/// normals for each vertex
	static GLfloat colours[];	/// colour array data
	static GLfloat material[4];	/// material RGBA
	static GLfloat shininess;	/// 高光系数（ shininess） in phong reflection model
public:
	StarFish();				/// default constructor
	virtual ~StarFish();	/// default destructor

protected:
	void _draw(void);	/// draws the StarFish
};
*/
#include "Renderable.h"

using namespace std;

// setup the static variables
GLfloat StarFish::material[4] = {0.3f, 0.3f, 0.3f, 1.f};
GLfloat StarFish::shininess = 32.f;

/// Default Constructor. Initialises defaults.
StarFish::StarFish() : Renderable()
{
	cout << "-- Creating StarFish\n";
}

/// Default destructor.
StarFish::~StarFish()
{
	cout << "++ Destructing StarFish\n";
}

/// Draws the StarFish
void StarFish::_draw(void)
{
	// phong 反射模型 设置RGBA，高光属性等
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// set up vertex arrays
	glVertexPointer(3, GL_FLOAT, 0, vertex);
	glNormalPointer(GL_FLOAT, 0, normal);
	glColorPointer(3, GL_FLOAT, 0, colours);

	// enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// 旋转重复画出5条腿，构成完整的海星
	GLfloat step = 360.0f / 5;
	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glRotatef(i * step, 0.0f, 1.0f, 0.0f);
		glDrawArrays(GL_QUADS, 0, 4 * 5);
		glPopMatrix();
	}

	// disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	// turn off colour material tracking
	glDisable(GL_COLOR_MATERIAL);
}

/*
*	descrip:
*		海星可由5部分构成，只构造一条腿即可
*		vertex:
*			一条腿可以变换成四棱锥（并非真正意义上的）对应的点。
*			1,2,3,4对应4个面，X对应四棱锥的上平面
*		normal:
*			对应vertex的法线
*		colors:
*			对应vertex的颜色
*/

GLfloat StarFish::vertex[] =
	{
		//3					|					|					|
		0.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.6f, 1.5f, 0.0f, 0.3f, 1.5f, 0.2f, 0.0f,
		//4					|					|					|
		0.0f, 0.0f, -0.6f, 0.0f, 0.2f, 0.0f, 1.5f, 0.2f, 0.0f, 1.5f, 0.0f, -0.3f,
		//1					|					|					|
		0.0f, -0.2f, 0.0f, 1.5f, -0.2f, 0.0f, 1.5f, 0.0f, 0.3f, 0.0f, 0.0f, 0.6f,
		//2					|					|					|
		0.0f, 0.0f, -0.6f, 1.5f, 0.0f, -0.3f, 1.5f, -0.2f, 0.0f, 0.0f, -0.2f, 0.0f,
		//X					|					|					|
		1.5f, 0.2f, 0.0f, 1.5f, 0.0f, 0.3f, 1.5f, -0.2f, 0.0f, 1.5f, 0.0f, -0.3f};

GLfloat StarFish::normal[] =
	{
		//3					|					|					|
		0.f, 0.71f, -0.71f, 0.f, 1.f, 0.0f, 0.f, 1.0f, 0.f, 0.f, 0.71f, -0.71f,
		//4					|					|					|
		0.f, 1.0f, 0.f, 0.0f, 0.71f, 0.71f, 0.f, 0.71f, 0.71f, 0.0f, 1.f, 0.f,
		//1					|					|					|
		0.f, -0.71f, -0.71f, 0.f, -1.f, 0.0f, 0.f, -1.0f, 0.f, 0.f, -0.71f, -0.71f,
		//2					|					|					|
		0.f, -1.0f, 0.f, 0.0f, -0.71f, 0.71f, 0.f, -0.71f, 0.71f, 0.0f, -1.f, 0.f,
		//X					|					|					|
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f

};

GLfloat StarFish::colours[] =
	{
		//250,192,203
		//3					|					|					|
		0.99f, 0.89f, 0.95f, 0.9f, 0.4f, 0.1f, 0.9f, 0.4f, 0.1f, 0.99f, 0.89f, 0.95f,
		//4					|					|					|
		0.9f, 0.4f, 0.1f, 0.99f, 0.89f, 0.95f, 0.99f, 0.89f, 0.95f, 0.9f, 0.4f, 0.1f,
		//1					|					|					|
		0.85f, 0.5f, 0.0f, 0.99f, 0.89f, 0.95f, 0.99f, 0.89f, 0.95f, 0.85f, 0.5f, 0.0f,
		//2					|					|					|
		0.9f, 0.4f, 0.1f, 0.99f, 0.89f, 0.95f, 0.99f, 0.89f, 0.95f, 0.9f, 0.4f, 0.1f,
		//X					|					|					|
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f

};