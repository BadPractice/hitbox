#include "rotation.hpp"
Rotation::Rotation(){
	angleX= 0;
	angleY= 0;
}
GLfloat Rotation::getX(){
	return angleX;
}
GLfloat Rotation::getY(){
	return angleY;
}

void Rotation::add(GLfloat argX, GLfloat argY){
	angleX+= argX;
	angleY+= argY;
	if (angleY > 360.0)
	{
		angleY-= 360.0;
	}
    else if (angleY < -360.0)
    {
		  angleY+= 360.0;
	}
    if (angleX > 89.0)
    {
		 angleX= 89.0;
	 }
    else if (angleX < -89.0) 
    {
		angleX= -89.0;
	}
}
