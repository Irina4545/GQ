#ifndef INTCLASS_H
#define INTCLASS_H

#include "../RootClass/RootClass.h"

class IntClass : public RootClass {
private:
	int num;
	std::string str_num;
public:
	IntClass(std::string value);
	IntClass(int num);
	IntClass(IntClass& other_obj);
	int get_num();
	static int to_int(std::string str_num);

	std::string get_str_num();
};


std::ostream& operator<<(std::ostream&, IntClass&);

#endif
