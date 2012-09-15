#include"leftward.hpp"

char Leftward::getType(){
	return 'a';
}
void Leftward::doCommand(){
	Position::getInstance()->add(-cosf(RAD(Rotation::getInstance()->getY())) * MOVESPEED,
		sinf(RAD(Rotation::getInstance()->getY())) * MOVESPEED);
}
