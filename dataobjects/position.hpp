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
GLfloat posY;  /* angle of spin around y axis of scene, in degrees */
GLfloat posX;  /* angle of spin around x axis  of scene, in degrees */
public:
Position();
GLfloat getX();
GLfloat getY();
void add(GLfloat, GLfloat);// adding rotation to the already exixting
};
