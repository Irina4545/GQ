#include "ListClass.h"

ListClass::ListClass() : RootClass("ListClass") {}

int ListClass::get_size() {
	return my_all_elements.size();
}

void ListClass::push_back(RootClass *p_obj) {
	my_all_elements.push_back(p_obj);
}

void ListClass::pop_back() {
	my_all_elements.pop_back();
}

void ListClass::insert(RootClass *p_obj, int pos) {
	if (pos < my_all_elements.size()) {
		my_all_elements.insert(pos, p_obj);
	}
}

void ListClass::pop(int pos) {
	if (pos < my_all_elements.size()) {
		my_all_elements.pop(pos);
	}
}

ListClass::~ListClass() {
	for (int i = 0; i < my_all_elements.size(); i++) {
		if (my_all_elements[i]->get_type_class() == "IntClass" ) {
			delete static_cast<IntClass*>(my_all_elements[i]);
		} else if (my_all_elements[i]->get_type_class() == "ListClass") {
			delete static_cast<ListClass *>(my_all_elements[i]);
		}
	}
}

RootClass* ListClass::get(int i) {
	return my_all_elements[i];
}


