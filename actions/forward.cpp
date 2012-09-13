#include"forward.hpp"

char Forward::getType(){
	return 'w';
}
void Forward::doCommand(){
	Position::getInstance()->add(sinf(RAD(Rotation::getInstance()->getY())) * 0.1f, //x value
		cosf(RAD(Rotation::getInstance()->getY())) * 0.1f);					//y value
}
