#include "position.hpp"
Position *Position::mPInstance = NULL; 

Position* Position::getInstance()
{
   if (!mPInstance)   // Only allow one instance of class to be generated.
      mPInstance = new Position;

   return mPInstance;
}

Position::Position(){
	posX=0.0;
	posY=0.0;
}
GLfloat Position::getX(){
	return posX;
}
GLfloat Position::getY(){
	return posY;
}

void Position::add(GLfloat argX, GLfloat argY){
	posX+= argX;
	posY+= argY;
}
