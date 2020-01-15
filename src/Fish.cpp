/*
*	descri:
*		implement of class Fish : public Renderable{}
*	author:
*		17341044
*/
/*
class Fish : public Renderable
{
private:
	GLfloat tailAngle;
	GLfloat tailAngleCutOff;
	GLfloat tailAngleInc;
	static GLfloat vertex[];	/// vertex array data
	static GLfloat normal[];	/// normals for each vertex
	static GLfloat texels[]; 	/// texture coords for each vertex
	static GLfloat colours[];	/// colour array data
	static GLfloat material[4];	/// material RGBA
	static GLfloat shininess;	/// 高光系数（ shininess） in phong reflection model
private:
	void drawSide(void);		/// draws a side of the fish
public:
	Fish();	/// default constructor
	virtual ~Fish();	/// default destructor

protected:
	void _draw(void);	/// draws the Fish
};
*/
#include "Renderable.h"

using namespace std;

// setup the static variables
GLfloat Fish::material[4] = {1.f, 1.f, 1.f, 1.f};
GLfloat Fish::shininess = 120.f;

Fish::Fish()
{
	cout << "-- Creating fish\n";
	// angles and cut offs for tail animation
	tailAngle = 0.0f;
	tailAngleCutOff = 20.0f;
	tailAngleInc = 1.0f;
}

Fish::~Fish()
{
	cout << "++ Destructing fish\n";
}

/// Draws the full fish
void Fish::_draw(void)
{
	// 鱼的整体运动速度
	GLfloat xInc = cos(ry * (3.14156) / 180) / 10.0f;
	GLfloat zInc = sin(ry * (3.14156) / 180) / 10.0f;

	// 允许鱼活动的范围，超出则相当于从对应的另一边的边界进入
	// the floor is 70.0 x 70.0
	// the fish keep inside a 65.0 x 65.0 area
	if (x < -35)
		x += 65.f;
	if (x > 35)
		x -= 65.f;
	if (z < -35)
		z += 65.f;
	if (z > 35)
		z -= 65.f;

	//刻画运动轨迹
	// increment the fish position
	x -= xInc;
	z += zInc;

	// set up the material properties (only front needs to be set)
	glMaterialfv(GL_FRONT, GL_AMBIENT, material);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	// enable texturing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, FISH_TEXTURE);

	// set up texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// set up vertex arrays
	glVertexPointer(3, GL_FLOAT, 0, vertex);
	glNormalPointer(GL_FLOAT, 0, normal);
	glTexCoordPointer(2, GL_FLOAT, 0, texels);
	glColorPointer(3, GL_FLOAT, 0, colours);

	// enable vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//画出鱼的一面
	// CounterClockWise
	glFrontFace(GL_CCW);
	drawSide();

	//画出鱼另的一面
	glScalef(1.0f, 1.0f, -1.0f);
	// ClockWise
	glFrontFace(GL_CW);
	drawSide();

	// 刻画尾巴的运动，限制角度范围为tailAngleCutOff
	GLfloat pt = sin(tailAngle * 3.14159 / 180);
	tailAngle += tailAngleInc;
	if (tailAngle < -tailAngleCutOff || tailAngle > tailAngleCutOff)
		tailAngleInc *= -1;

	//由于尾巴是相对鱼其它部分运动的，需要另行操作
	vertex[143] = vertex[152] = vertex[149] = vertex[158] = vertex[167] = pt;
	glDrawArrays(GL_TRIANGLES, 6 + (4 * 6) + (3 * 5), 3 * 4);
	glScalef(1.0f, 1.0f, -1.0f);

	//鱼尾巴的另一部分
	glFrontFace(GL_CCW);
	vertex[143] = vertex[152] = vertex[149] = vertex[158] = vertex[167] = -pt;
	glDrawArrays(GL_TRIANGLES, 6 + (4 * 6) + (3 * 5), 3 * 4);

	// disable all vertex arrays and texturing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

/// Draws a side of the fish
void Fish::drawSide(void)
{
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
	glDrawArrays(GL_QUADS, 6, 4 * 6);
	glDrawArrays(GL_TRIANGLES, 6 + 4 * 6, 3 * 5);
}

/*
*	descrip:
*		fish is divided into 3 part:
*			part1:
*				2 triangles: 1,2
*				6 quads: 3,4,5,6,7,8
*			part2:
*				5 triangles:a,b,c,d,e
*			part3:
*				4 triangles:H,I,J,K
*/

GLfloat Fish::vertex[] =
	{
		// part1:
		// 2				|					|					|
		0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.45f,
		// 1				|					|					|
		0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.45f, 0.5f, 0.5f, 0.0f,

		// 3				|					|					|
		0.5f, 0.0f, 0.45f, 0.5f, -0.5f, 0.0f, 1.5f, -1.0f, 0.0f, 1.5f, 0.0f, 0.45f,
		// 4				|					|					|
		0.5f, 0.5f, 0.0f, 0.5f, 0.0f, 0.45f, 1.5f, 0.0f, 0.45f, 1.5f, 1.0f, 0.0f,
		// 6				|					|					|
		1.5f, 0.0f, 0.45f, 1.5f, -1.0f, 0.0f, 2.5f, -1.0f, 0.0f, 2.5f, 0.0f, 0.45f,
		// 5				|					|					|
		1.5f, 1.0f, 0.0f, 1.5f, 0.0f, 0.45f, 2.5f, 0.0f, 0.45f, 2.5f, 1.0f, 0.0f,
		// 8				|					|					|
		2.5f, 0.0f, 0.45f, 2.5f, -1.0f, 0.0f, 3.5f, -0.5f, 0.0f, 3.5f, 0.0f, 0.2f,
		// 7				|					|					|
		2.5f, 1.0f, 0.0f, 2.5f, 0.0f, 0.45f, 3.5f, 0.0f, 0.2f, 3.5f, 0.5f, 0.0f,

		// part2:
		// c				|					|					|
		3.5f, 0.5f, 0.0f, 3.5f, 0.0f, 0.2f, 3.75f, 0.4f, 0.1f,
		// b				|					|					|
		3.5f, 0.0f, 0.2f, 3.75f, -0.4f, 0.1f, 3.75f, 0.4f, 0.1f,
		// a				|					|					|
		3.5f, 0.0f, 0.2f, 3.5f, -0.5f, 0.0f, 3.75f, -0.4f, 0.1f,
		// e				|					|					|
		3.5f, 0.5f, 0.0f, 3.75f, 0.4f, 0.1f, 3.75f, 0.4f, -0.1f,
		// d				|					|					|
		3.5f, -0.5f, 0.0f, 3.75f, -0.4f, -0.1f, 3.75f, -0.4f, 0.1f,

		// part3:
		// H				|					|					|
		3.75f, 0.4f, 0.1f, 3.75f, -0.4f, 0.1f, 4.3f, -0.8f, 0.0f,
		// I				|					|					|
		3.75f, 0.4f, 0.1f, 4.3f, -0.8f, 0.0f, 4.3f, 0.8f, 0.0f,
		// K				|					|					|
		3.75f, 0.4f, 0.1f, 4.3f, 0.8f, 0.0f, 3.75f, 0.4f, -0.1f,
		// J				|					|					|
		3.75f, -0.4f, -0.1f, 4.3f, -0.8f, 0.0f, 3.75f, -0.4f, 0.1f};

GLfloat Fish::normal[] =
	{
		// part1:
		// 2				|					|					|
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		// 1				|					|					|
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		// 4				|					|					|
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 3				|					|					|
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		// 6				|					|					|
		0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 5				|					|					|
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		// 8				|					|					|
		0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 7				|					|					|
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		// part2:
		// c				|					|					|
		0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.71f, 0.71f,
		// b				|					|					|
		0.0f, -0.71f, 0.71f, 0.0f, 0.0f, 1.0f, 0.0f, -0.71f, 0.71f,
		// a				|					|					|
		0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -0.71f, 0.71f,
		// e				|					|					|
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		// d				|					|					|
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		// part3:
		// H				|					|					|
		0.0f, -0.71f, 0.71f, 0.71f, -0.71f, 0.0f, 0.71f, -0.71f, 0.0f,
		// I				|					|					|
		0.0f, -0.71f, 0.71f, 0.71f, -0.71f, 0.0f, 0.71f, 0.71f, 0.0f,

		// K				|					|					|
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		// J				|					|					|
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f};

GLfloat Fish::texels[] =
	{
		// part1:
		// 2					|						|						|
		126.f / 128.f, 68.f / 128.0f, 119.f / 128.f, 47.f / 128.f, 112.f / 128.f, 68.f / 128.f,
		// 1					|						|						|
		126.f / 128.f, 68.f / 128.0f, 112.f / 128.f, 68.f / 128.f, 117.f / 128.f, 84.f / 128.f,

		// 4					|						|						|
		112.f / 128.f, 68.f / 128.f, 119.f / 128.f, 47.f / 128.f, 86.f / 128.f, 8.f / 128.f, 84.f / 128.f, 68.f / 128.f,
		// 3					|						|						|
		117.f / 128.f, 84.f / 128.f, 112.f / 128.f, 68.f / 128.f, 84.f / 128.f, 68.f / 128.f, 83.f / 128.f, 120.f / 128.f,
		// 6					|						|						|
		84.f / 128.f, 68.f / 128.f, 86.f / 128.f, 8.f / 128.f, 52.f / 128.f, 15.f / 128.f, 53.f / 128.f, 68.f / 128.f,
		// 5					|						|						|
		83.f / 128.f, 120.f / 128.f, 84.f / 128.f, 68.f / 128.f, 53.f / 128.f, 68.f / 128.f, 54.f / 128.f, 110.f / 128.f,
		// 8					|						|						|
		53.f / 128.f, 68.f / 128.f, 52.f / 128.f, 15.f / 128.f, 26.f / 128.f, 54.f / 128.f, 25.f / 128.f, 69.f / 128.f,
		// 7					|						|						|
		54.f / 128.f, 110.f / 128.f, 53.f / 128.f, 68.f / 128.f, 25.f / 128.f, 69.f / 128.f, 28.f / 128.f, 76.f / 128.f,

		// part2:
		// c					|						|						|
		28.f / 128.f, 74.f / 128.f, 25.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
		// b					|						|						|
		25.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
		// a					|						|						|
		25.f / 128.f, 69.f / 128.f, 26.f / 128.f, 54.f / 128.f, 20.f / 128.f, 69.f / 128.f,
		// e					|						|						|
		26.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
		// d					|						|						|
		26.f / 128.f, 54.f / 128.f, 20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,

		// part3:
		// H					|						|						|
		20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f,
		// I					|						|						|
		20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f,
		// K					|						|						|
		20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
		// J					|						|						|
		20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f};

GLfloat Fish::colours[] =
	{
		// part1:
		// 2				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f,
		// 1				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f,

		// 3				|					|					|
		0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f,
		// 4				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f,
		// 6				|					|					|
		0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f,
		// 5				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f,
		// 8				|					|					|
		0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f,
		// 7				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f,

		// part2:
		// c				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f,
		// b				|					|					|
		0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f,
		// a				|					|					|
		0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f,
		// e				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f,
		// d				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f,

		// part3:
		// H				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f,
		// I				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.2f, 0.8f,
		// K				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f,
		// J				|					|					|
		0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f, 0.2f};