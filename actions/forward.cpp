#include"forward.hpp"

char Forward::getType(){
	return 'w';
}
void Forward::doCommand(){
	Position::getInstance()->add(sinf(RAD(Rotation::getInstance()->getY())) * MOVESPEED, //x value
		cosf(RAD(Rotation::getInstance()->getY())) * MOVESPEED);					//y value
}
