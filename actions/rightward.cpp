#include"rightward.hpp"

char Rightward::getType(){
	return 'd';
}
void Rightward::doCommand(){
	Position::getInstance()->add(cosf(RAD(Rotation::getInstance()->getY())) * MOVESPEED,
		-sinf(RAD(Rotation::getInstance()->getY())) * MOVESPEED);
}
