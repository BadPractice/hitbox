#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif

#include "../interfaces/actionable.hpp"
class Forward : public Actionable{
	char getType();
	virtual void doCommand();
};
