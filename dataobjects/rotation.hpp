#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif

class Rotation{
private:
Rotation();
Rotation& operator=(Rotation const&){};
Rotation(Rotation const&){};  
static Rotation* mPInstance;

GLfloat angleY;  /* angle of spin around y axis of scene, in degrees */
GLfloat angleX;  /* angle of spin around x axis  of scene, in degrees */
public:
static Rotation* getInstance();
GLfloat getX();
GLfloat getY();
void add(GLfloat, GLfloat);// adding rotation to the already exixting
};
