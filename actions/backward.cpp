#include"backward.hpp"

char Backward::getType(){
	return 's';
}
void Backward::doCommand(){
	Position::getInstance()->add(-sinf(RAD(Rotation::getInstance()->getY())) * MOVESPEED,
		-cosf(RAD(Rotation::getInstance()->getY())) * MOVESPEED);
}
