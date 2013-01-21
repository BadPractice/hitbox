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
#include "tga.h"
#include "dataobjects/rotation.hpp"
#include "dataobjects/position.hpp"
#include "interfaces/actionable.hpp"
#include "World.h"
#include "actions/forward.hpp"
#include "actionlist.hpp"
#include <math.h>
#include "drawcube.h"
#include <iostream>
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
//Position *camPosition;
ActionList pressedKeys;

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

void keyReleased(unsigned char key, int x, int y) 
{
  usleep(100);
  switch (key) {
  case 27:
    glutDestroyWindow(window); 
    exit(0);                   
    break;
  case 'w':
	pressedKeys.remove('w');
    glutPostRedisplay();
    break;
   case 's':
	pressedKeys.remove('s');
    glutPostRedisplay();
    break;
   case 'a':
	pressedKeys.remove('a');
	glutPostRedisplay();
    break;
   case 'd':
	pressedKeys.remove('d');
    glutPostRedisplay();
    break;
  default:
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
	pressedKeys.add('w');
    glutPostRedisplay();
    break;
   case 's':
	pressedKeys.add('s');
    glutPostRedisplay();
    break;
  case 'a':
	pressedKeys.add('a');
	glutPostRedisplay();
    break;
   case 'd':
	pressedKeys.add('d');
    glutPostRedisplay();
    break;
  default:
    break;
  }
}


void drawTeaPot(){
	glutSolidTeapot(1);
}

void display()
{
	float distance;
	pressedKeys.execute();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  glLoadIdentity();  

  gluLookAt(0.,0.,0.,
  -sinf(RAD(Rotation::getInstance()->getY())),sinf(RAD(Rotation::getInstance()->getX())), cosf(RAD(Rotation::getInstance()->getY())), 
            0.,1.,0.);

  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture);

	glTranslatef(Position::getInstance()->getX(),0,-Position::getInstance()->getY());
  glPushMatrix();
 // glTranslatef(-2, 0, 0);  
  glTranslatef(0, 0, 4);  
  distance =sqrt(pow(Position::getInstance()->getX()-0, 2) + pow(Position::getInstance()->getY()-4, 2));
  if(distance> 5 && distance < 10)
  {
	  drawTeaPot();
  }
  if(distance> 10)
  {
	  drawPyram();
  }
  if(distance < 5)
  {
	  drawCube();
  }
 std::cout<<sqrt(pow(Position::getInstance()->getX()-0, 2) + pow(Position::getInstance()->getY()-0, 2) )<<std::endl;
 
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
    Rotation::getInstance()->add(angle_x-(y-wh/2)/MOUSESPEED, 
		angle_y+(x - ww/2)/MOUSESPEED);//adding movement to aim
    wraped = false;
    glutWarpPointer(ww/2, wh/2); //setting curser back to middle
  } 
  else wraped =true; 
    glutPostRedisplay();        
 
}


int main(int argc, char **argv) 
{  
  World myWorld = World();
  //camPosition = new Position();
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("foo");  
  glutDisplayFunc(&display);  
  glutReshapeFunc(&resize);
  glutKeyboardFunc(&keyPressed);
  glutKeyboardUpFunc(&keyReleased);
  glutSpecialFunc(&specialKeyPressed);
  init(640, 480);
  glutTimerFunc(15, timer, 1);
 // glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutPassiveMotionFunc(mouseMotion);
  glutFullScreen();
  glutMainLoop();  
  //delete actions;
  //delete camPosition;
  return 0;
}
