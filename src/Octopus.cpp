/*
* FILE NAME：Octopus.cpp
* FILE FUNCTION：Implement Octopus class.
*                Draws a Octopus.
*/
#include "Renderable.h"

using namespace std;

// setup the static variables
GLfloat Octopus::material[4] = {0.0f, 0.0f, 2.0f, 1.f};
GLfloat Octopus::shininess = 50.f;

// FUNCTION NAME：Octopus
// Default Constructor of Octopus 
Octopus::Octopus()
{
	cout << "-- Creating octopus\n";

	// leg rotation angles
	legAngle = 0.0f;
	legAngleCutOff = 30.0f;
	legAngleInc = 1.0f;
}

// FUNCTION NAME：~Octopus
// Default Destructor. Does nothing.
Octopus::~Octopus()
{
	cout << "++ Destructing octopus\n";
}

// FUNCTION NAME：_draw
// draw an octopus
void Octopus::_draw(void)
{
	// select our colour
	glColor3f(1.0f, 1.0f, 0.0f);

	// set up the material properties (only front needs to be set)
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// draw octopus body (stretched along Y axis)
	// up and down
	glPushMatrix();
	glScalef(1.0f, 3.0f, 1.0f);
	glutSolidSphere(0.3f, 16, 8);
	glPopMatrix();

	legAngle += legAngleInc;
	if (legAngle < -legAngleCutOff || legAngle > legAngleCutOff) legAngleInc *= -1;

	glRotatef(legAngle, 0.0f, 1.0f, 0.0f);// rotate

	GLfloat step = 360.0f / 8;
	for (int i = 0; i < 8;  i++)// 8 legs
	{
		glPushMatrix();

		glRotatef(i * step, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.1f, 0.5f + (legAngle / legAngleCutOff) / 7.0f, 0.0f);
		Crab::drawLeg(); //call the drawleg function of crab

		glTranslatef(0.2f, 0.725f, 0.0f);
		glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
		
		Crab::drawLeg();//call the drawleg function of crab

		glPopMatrix();
	}

	// turn of colour material tracking
	glDisable(GL_COLOR_MATERIAL);
}