#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif
#include <stdlib.h> // for exit
#include <unistd.h> // for usleep
#include <stdio.h>
#include "interfaces/action.hpp"
#include "tga.h"
#include "dataobjects/rotation.hpp"
#include "dataobjects/position.hpp"
#include <vector>
#include <math.h>
using namespace std;
/* some math.h files don't define pi... */
#ifndef M_PI
#define M_PI 3.141592653
#endif

#define RAD(x) (((x)*M_PI)/180.)

#ifdef __STRICT_ANSI__
#define sinf(x) ((float)sin((x)))
#define cosf(x) ((float)cos((x)))
#define atan2f(x, y) ((float)atan2((x), (y)))
#endif 

#define MOUSESPEED 3
bool wraped =true;
int window; 
float advance = 0.0f, advanceX =0.0f;
GLuint texture;
int animating = 1;
int windowHeight, windowWidth;
int moving = 0;     /* flag that is true while mouse moves */ 
GLfloat angle_y = 0;  /* angle of spin around y axis of scene, in degrees */
GLfloat angle_x = 0;  /* angle of spin around x axis  of scene, in degrees */
Rotation *angle;
Position *camPosition;
vector<Action> actions;

void handleEvents(){
}

void reportGLError(const char * msg)
{
  GLenum errCode;
  const GLubyte *errString;
  while ((errCode = glGetError()) != GL_NO_ERROR) {
    errString = gluErrorString(errCode);
    fprintf(stderr, "OpenGL Error: %s %s\n", msg, errString);
  }
  return;
}

void resize(int width, int height)
{
	windowWidth =width;
	windowHeight = height;
  // prevent division by zero
  if (height == 0) { height=1; }

  glViewport(0, 0, width, height);  

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void specialKeyPressed(int key, int x, int y) 
{
  usleep(100);
  switch (key) {
        
  case GLUT_KEY_UP:     /* <cursor up> */
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:     /* <cursor down> */
    glutPostRedisplay();
    break;
  }
}

void keyPressed(unsigned char key, int x, int y) 
{
  usleep(100);
  switch (key) {
  case 27:
    glutDestroyWindow(window); 
    exit(0);                   
    break;
  case 'w':

	(*camPosition).add(sinf(RAD((*angle).getY())) * 0.1f, //x value
		cosf(RAD((*angle).getY())) * 0.1f);					//y value
    glutPostRedisplay();
    break;
   case 's':
	(*camPosition).add(-sinf(RAD((*angle).getY())) * 0.1f,
		-cosf(RAD((*angle).getY())) * 0.1f);
    glutPostRedisplay();
    break;
  case 'a':
	(*camPosition).add(-cosf(RAD((*angle).getY())) * 0.1f,
		sinf(RAD((*angle).getY())) * 0.1f);
    glutPostRedisplay();
    break;
   case 'd':
	(*camPosition).add(cosf(RAD((*angle).getY())) * 0.1f,
		-sinf(RAD((*angle).getY())) * 0.1f);
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

void drawCube() 
{
	glBegin(GL_QUADS);
  // front face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  // back face
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  // top face
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  // bottom face
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  // right face
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  // left face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  glEnd();
}
void drawTeaPot(){
	glutSolidTeapot(1);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  glLoadIdentity();  

  gluLookAt(0.,0.,0.,
  -sinf(RAD((*angle).getY())),sinf(RAD((*angle).getX())), cosf(RAD((*angle).getY())), 
            0.,1.,0.);

  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture);

	glTranslatef(camPosition->getX(),0,-camPosition->getY());
  glPushMatrix();
  glTranslatef(-2, 0, 0);  
  glTranslatef(0, 0, 4);  
  drawTeaPot();
  glTranslatef(0, 0, -4);  
  drawTeaPot();
  glTranslatef(0, 0, -4);  
  drawTeaPot();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 0, 0);  
  glTranslatef(0, 0, 4);  
  drawTeaPot();
  glTranslatef(0, 0, -4);  
  drawTeaPot();
  glTranslatef(0, 0, -4);  
  drawTeaPot();
  glPopMatrix();
  
  glDisable(GL_TEXTURE_2D);

  glutSwapBuffers();
}

void init(int width, int height)  
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);        
  glDepthFunc(GL_LESS);      
  glEnable(GL_DEPTH_TEST);  
  glShadeModel(GL_SMOOTH);  

  resize(width, height);
	glutSetCursor(GLUT_CURSOR_NONE);
  GLsizei w, h;
  tgaInfo *info = 0;
  int mode;

  info = tgaLoad("crate.tga");

  if (info->status != TGA_OK) {
    fprintf(stderr, "error loading texture image: %d\n", info->status);
    
    return;
  }
  if (info->width != info->height) {
    fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
            info->width, info->height);
    return;
  }

  mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
  glGenTextures(1, &texture);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  // Upload the texture bitmap. 
  w = info->width; 
  h = info->height; 

  reportGLError("before uploading texture");
  GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, 
               GL_UNSIGNED_BYTE, info->imageData);
  reportGLError("after uploading texture");

  tgaDestroy(info);

}

void timer(int value)
{
  glutPostRedisplay();
  glutTimerFunc(15, timer, 1);
}


void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:    /* spin scene around */
    if (state == GLUT_DOWN){
      moving = 1;
      
    } else if (state == GLUT_UP){
      moving = 0;
    }
    break;
    
  default:
    break;
  }
  
  glutPostRedisplay();
}


void mouseMotion(int x, int y) {
  
  if (wraped) { /* mouse button is pressed */
    int ww = glutGet(GLUT_WINDOW_WIDTH);
    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    /* calculate new modelview matrix values */
    (*angle).add(angle_x-(y-wh/2)/MOUSESPEED, 
		angle_y+(x - ww/2)/MOUSESPEED);//adding movement to aim
    wraped = false;
    glutWarpPointer(ww/2, wh/2); //setting curser back to middle
  } 
  else wraped =true; 
    glutPostRedisplay();        
 
}


int main(int argc, char **argv) 
{  
  angle= new Rotation();
  camPosition = new Position();
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("foo");  
  glutDisplayFunc(&display);  
  glutReshapeFunc(&resize);
  glutKeyboardFunc(&keyPressed);
  glutSpecialFunc(&specialKeyPressed);
  init(640, 480);
  glutTimerFunc(15, timer, 1);
 // glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutPassiveMotionFunc(mouseMotion);
  glutFullScreen();
  glutMainLoop();  
  delete angle;
  delete camPosition;
  return 0;
}
