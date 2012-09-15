#ifndef ACTIONABLE_HPP
#define ACTIONABLE_HPP
#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif
#define MOVESPEED 0.05f

class Actionable{
public:
	virtual char getType() =0;
	virtual void doCommand() =0;
};
#endif
