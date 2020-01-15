/*
* FILE NAME：Renderable.h
* FILE FUNCTION：Declare Renderable and its children classes.
*          Its children classes e.g. Fish，Starfish，Crab，Octopus，
*          Quad，Plant and so on，which can be rendered in the scene.
*/

#ifndef __RENDERABLE_3201
#define __RENDERABLE_3201

#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

#ifndef TEXTURE_IDS
#define TEXTURE_IDS
#define FLOOR_TEXTURE 1
#define FISH_TEXTURE 2
#endif

/*
* CLASS NAME：Renderable
* CLASS DECLARATION：This is an abstract class that all of the objects that
* are attached to the scene inherit from. It provides basic functionality
* for moving/rotating/scaling objects as well as defining a pure virtual
* function '_draw()' that must be difined by its children classes which
* actually does the drawing of any specific object.
*/
class Renderable
{
public:
    GLfloat x; /// x position of object
    GLfloat y; /// y position of object
    GLfloat z; /// z position of object

    GLfloat rx; /// x rotation angle of object
    GLfloat ry; /// y rotation angle of object
    GLfloat rz; /// z rotation angle of object

    GLfloat sx; /// x scale of object
    GLfloat sy; /// y scale of object
    GLfloat sz; /// z scale of object

    bool isList; /// is this a display list object?

    static unsigned int textures[2]; /// texture id array
    static GLUquadricObj *quadric;   /// quadric object for all renderables
public:
    Renderable();          /// default constructor
    virtual ~Renderable(); /// default destructor

    void build(GLuint &dlist);                    /// builds a display list of this object
    void move(GLfloat x, GLfloat y, GLfloat z);   /// moves the object
    void rotate(GLfloat x, GLfloat y, GLfloat z); /// rotates the object
    void scale(GLfloat x, GLfloat y, GLfloat z);  /// scales the object
    void draw(void);

    static GLfloat getRand(GLfloat minimum, GLfloat range); /// generates a random value in max range
protected:
    virtual void _draw(void) = 0;     /// draws the object
    virtual void _draw_dlist(void) {} /// draws the display list for object
};
#endif

/*
* CLASS NAME：StarFish
* CLASS DECLARATION：Draws a yellowish colour StarFish.
*/
#ifndef __STARFISH_3201
#define __STARFISH_3201
class StarFish : public Renderable
{
private:
    static GLfloat vertex[];    /// vertex array data
    static GLfloat normal[];    /// normals for each vertex
    static GLfloat colours[];   /// colour array data
    static GLfloat material[4]; /// material RGBA
    static GLfloat shininess;   /// 高光系数（ shininess） in phong reflection model
public:
    StarFish();          /// default constructor
    virtual ~StarFish(); /// default destructor

protected:
    void _draw(void); /// draws the StarFish
};
#endif

/*
* CLASS NAME：Fish
* CLASS DECLARATION：Draws a Fish.
*/
#ifndef __FISH_3201
#define __FISH_3201
class Fish : public Renderable
{
private:
    GLfloat tailAngle;
    GLfloat tailAngleCutOff;
    GLfloat tailAngleInc;
    static GLfloat vertex[];    /// vertex array data
    static GLfloat normal[];    /// normals for each vertex
    static GLfloat texels[];    /// texture coords for each vertex
    static GLfloat colours[];   /// colour array data
    static GLfloat material[4]; /// material RGBA
    static GLfloat shininess;   /// 高光系数（ shininess） in phong reflection model
private:
    void drawSide(void); /// draws a side of the fish
public:
    Fish();          /// default constructor
    virtual ~Fish(); /// default destructor

protected:
    void _draw(void); /// draws the Fish
};
#endif

/*
* CLASS NAME：Crab class
* CLASS DECLARATION：Draws a pinky coloured crab.
*/
#ifndef __CRAB_3201
#define __CRAB_3201
class Crab : public Renderable
{
private:
    GLuint dlist; /// display list
    static GLfloat material[4];
    static GLfloat shininess;

private:
    static void drawLeg(void);                                    /// draws one leg
    static void drawLeg(GLfloat jointAngle, GLfloat jointOffset); /// draw leg with an angle specified
    static void drawLegs(void);                                   /// draws complete set of legs
public:
    Crab();          /// default constructor
    virtual ~Crab(); /// default destructor
protected:
    void _draw(void);                     /// draws the crab
    void _draw_dlist(void);               /// draws the crab's display list
    void generate(int level, int number); /// generates the branches

    friend class Octopus; /// so the octopus can use the drawLeg method
};
#endif

/*
* CLASS NAME：Octopus
* CLASS DECLARATION：Draws a Octopus.
*/
#ifndef __OCTOPUS_3201
#define __OCTOPUS_3201
class Octopus : public Renderable
{
private:
    GLfloat legAngle;       /// angle to spin the legs at
    GLfloat legAngleCutOff; /// cut of angle for spinning
    GLfloat legAngleInc;    /// angle spin increment
    static GLfloat material[4];
    static GLfloat shininess;

public:
    Octopus();          /// default constructor
    virtual ~Octopus(); /// default destructor
protected:
    void _draw(void); /// draws the Octopus
};
#endif

/*
* CLASS NAME：Quad
* CLASS DECLARATION：Draws a yellowish colour shaded quad.
*/
#ifndef __QUAD_3201
#define __QUAD_3201
class Quad : public Renderable
{
private:
    static GLfloat material[4];
    static GLfloat shininess;

public:
    Quad();          /// default constructor
    virtual ~Quad(); /// default destructor
protected:
    void _draw(void); /// draws the quad
};
#endif

/*
* CLASS NAME：Plant
* CLASS DECLARATION：Draws a plant.
*/
#ifndef __PLANT_3201
#define __PLANT_3201
#include <list>
class Plant : public Renderable
{
private:
    GLuint dlist; /// display list
    static GLfloat material1[4];
    static GLfloat material2[4];
    static GLfloat shininess;

public:
    Plant();          /// default constructor
    virtual ~Plant(); /// default destructor
protected:
    void _draw(void);                     /// draws the plant
    void generate(int level, int number); /// generates the branches
    void _draw_dlist(void);               /// draws the display list of this object
};
#endif
