#include "actionlist.hpp"
void ActionList::remove(char arg){
	vector<Actionable*>::iterator it;
	for(it= actions.begin(); it<actions.end(); it++)
	{
		if((*it)->getType()==arg)
		{
			actions.erase(it);
			break;
		}
	}
}

void ActionList::add(char arg){
	this->remove(arg);
	switch(arg){
	case 'w':
	actions.push_back(new Forward());
	break;
	case 's':
	actions.push_back(new Backward());
	break;
	default:
	break;
	}
}

void ActionList::execute(){
	vector<Actionable*>::iterator it;
	for(it= actions.begin(); it<actions.end(); it++)
	{
			(*it)->doCommand();
	}
}
