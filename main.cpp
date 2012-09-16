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
#include "actions/forward.hpp"
#include "actionlist.hpp"
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
GLuint texture[5];
int animating = 1;
int windowHeight, windowWidth;
int moving = 0;     /* flag that is true while mouse moves */ 
GLfloat angle_y = 0;  /* angle of spin around y axis of scene, in degrees */
GLfloat angle_x = 0;  /* angle of spin around x axis  of scene, in degrees */
//Position *camPosition;
ActionList pressedKeys;

typedef struct vert
{
	float u, v, x, y, z;
	int w;
} VERTEX;

typedef struct tri
{
	VERTEX vt[3];
} TRIANGLE;

typedef struct sect
{
	int ntr;
	TRIANGLE* tri;
} SECTOR;

SECTOR scene;

void load_scene()
{
	float u, v, x, y, z;
	int w;
	int tris;
	FILE *input;
	char line[255];
	input = fopen("worlddata.txt", "rt");

	fgets(line, 255, input);

	sscanf(line, "Total number of Triangles: %d\n", &tris);

	scene.tri=new TRIANGLE[tris];
	scene.ntr=tris;

	for(int i=0;i<tris;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			do
			{
				fgets(line, 255, input);
			}
			while((line[0]=='/')||(line[0]=='\n'));
			

			sscanf(line, "%f %f %d %f %f %f", &u, &v, &w, &x, &y, &z);

			scene.tri[i].vt[j].u = u;
			scene.tri[i].vt[j].v = v;
			scene.tri[i].vt[j].w = w;
			scene.tri[i].vt[j].x = x;
			scene.tri[i].vt[j].y = y;
			scene.tri[i].vt[j].z = z;
		}
	}

	fclose(input);
	return;
}

void create_scene()
{
	GLfloat u, v, x, y, z;
	int w;

	glBegin(GL_TRIANGLES);
	glColor3f(0.4, 0.3, 0.6);
	for(int i = 0; i < scene.ntr;i++)
	{
		u = scene.tri[i].vt[0].u;
		v = scene.tri[i].vt[0].v;
		w = scene.tri[i].vt[0].w;
		x = scene.tri[i].vt[0].x;
		y = scene.tri[i].vt[0].y;
		z = scene.tri[i].vt[0].z;

		glBindTexture(GL_TEXTURE_2D, texture[w]);

		glTexCoord2f(u, w);
		glVertex3f(x, y, z);

		u = scene.tri[i].vt[1].u;
		v = scene.tri[i].vt[1].v;
		w = scene.tri[i].vt[1].w;
		x = scene.tri[i].vt[1].x;
		y = scene.tri[i].vt[1].y;
		z = scene.tri[i].vt[1].z;

		glTexCoord2f(u, w);
		glVertex3f(x, y, z);

		u = scene.tri[i].vt[2].u;
		v = scene.tri[i].vt[2].v;
		w = scene.tri[i].vt[2].w;
		x = scene.tri[i].vt[2].x;
		y = scene.tri[i].vt[2].y;
		z = scene.tri[i].vt[2].z;

		glTexCoord2f(u, w);
		glVertex3f(x, y, z);
	}
	glEnd();
}

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
	pressedKeys.execute();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  glLoadIdentity();
  gluLookAt(0.,0.,0.,
  -sinf(RAD(Rotation::getInstance()->getY())),sinf(RAD(Rotation::getInstance()->getX())), cosf(RAD(Rotation::getInstance()->getY())), 
            0.,1.,0.);
  
  create_scene();
  
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[1]);

	glTranslatef(Position::getInstance()->getX(),0,-Position::getInstance()->getY());
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

  for(int i = 0; i < 5 ;i++){

  tgaInfo *info = 0;
  int mode;

  switch(i){
	  case 0:
		  info = tgaLoad("brick.tga");
		  break;
	  case 1:
		  info = tgaLoad("crate.tga");
		  break;

	  case 2:
		  info = tgaLoad("marble.tga");
		  break;
	  case 3:
		  info = tgaLoad("pillar.tga");
		  break;
	  case 4:
		  info = tgaLoad("wood.tga");
		  break;
	  default:
		  break;
	  }

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
  glGenTextures(1, &texture[i]);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glBindTexture(GL_TEXTURE_2D, texture[i]);
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
  load_scene();
  glutMainLoop();  
  //delete actions;
  //delete camPosition;
  return 0;
}
