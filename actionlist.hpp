#ifndef ACTIONLIST_HPP
#define ACTIONLIST_HPP
#include <vector>
#include "dataobjects/rotation.hpp"
#include "dataobjects/position.hpp"
#include "interfaces/actionable.hpp"
#include "actions/forward.hpp"
using namespace std;
class ActionList{
private:
	vector <Actionable*> actions;
public:
	void add(char);
	void remove(char);
	void execute();
};
#endif