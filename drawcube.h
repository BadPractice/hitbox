void drawCube() 
{
	glBegin(GL_QUADS);
  // front face
   glVertex3f(-1.0f, -1.0f,  1.0f);
   glVertex3f( 1.0f, -1.0f,  1.0f);
   glVertex3f( 1.0f,  1.0f,  1.0f);
  glVertex3f(-1.0f,  1.0f,  1.0f);
  // back face
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glVertex3f(-1.0f,  1.0f, -1.0f);
   glVertex3f( 1.0f,  1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f, -1.0f);
  // top face
   glVertex3f(-1.0f,  1.0f, -1.0f);
   glVertex3f(-1.0f,  1.0f,  1.0f);
   glVertex3f( 1.0f,  1.0f,  1.0f);
   glVertex3f( 1.0f,  1.0f, -1.0f);
  // bottom face
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f,  1.0f);
   glVertex3f(-1.0f, -1.0f,  1.0f);
  // right face
   glVertex3f( 1.0f, -1.0f, -1.0f);
   glVertex3f( 1.0f,  1.0f, -1.0f);
   glVertex3f( 1.0f,  1.0f,  1.0f);
   glVertex3f( 1.0f, -1.0f,  1.0f);
  // left face
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glVertex3f(-1.0f, -1.0f,  1.0f);
   glVertex3f(-1.0f,  1.0f,  1.0f);
   glVertex3f(-1.0f,  1.0f, -1.0f);
  glEnd();
}

void drawPyram() 
{
	glBegin(GL_TRIANGLES);
  // front face
   glVertex3f(-1.0f, -1.0f,  1.0f);
   glVertex3f( 1.0f, -1.0f,  1.0f);
   glVertex3f( 0.0f,  1.0f,  0.0f);
  // back face
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f, -1.0f);
   glVertex3f( 0.0f,  1.0f, 0.0f);
  // right face
   glVertex3f( 1.0f, -1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f,  1.0f);
   glVertex3f( 0.0f,  1.0f, 0.0f);
  // left face
   glVertex3f( -1.0f, -1.0f, -1.0f);
   glVertex3f( -1.0f, -1.0f,  1.0f);
   glVertex3f( 0.0f,  1.0f, 0.0f);
 // glEnd();
  
  glBegin(GL_QUADS);
  // bottom face
   glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f( 1.0f, -1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f,  1.0f);
   glVertex3f(-1.0f, -1.0f,  1.0f);
   
  
  glEnd();
}
