#ifndef POSITION_HPP
#define POSITION_HPP

#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif

class Position{
private:
Position();
Position& operator=(Position const&){};
Position(Position const&){};  
static Position* mPInstance;
GLfloat posY;  /* angle of spin around y axis of scene, in degrees */
GLfloat posX;  /* angle of spin around x axis  of scene, in degrees */
public:
static Position* getInstance();
GLfloat getX();
GLfloat getY();
void add(GLfloat, GLfloat);// adding rotation to the already exixting
};
#endif
