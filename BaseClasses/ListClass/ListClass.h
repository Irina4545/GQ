#ifndef LANGGG_LISTCLASS_H
#define LANGGG_LISTCLASS_H

#include "../RootClass/RootClass.h"

//#include <list>
#include <iterator>
#include "../IntClass/IntClass.h"
#include "list_mv.h"

class ListClass : public RootClass {
private:
	//std::list<RootClass*> all_elements;
	list_mv<RootClass*> my_all_elements;
public:
	ListClass();
	int get_size();
	void push_back(RootClass* p_obj);
	void pop_back();
	void insert(RootClass* p_obj, int pos);
	void pop(int i);
	RootClass* get(int i);
	~ListClass();
};


#endif
