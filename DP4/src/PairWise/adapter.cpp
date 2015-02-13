#include "pairWise.h"

namespace pair_wise {

class LegacyClass1 {
public:
	void func1() { cout << "LC1.funn1().\n"; }
};
class LegacyClass2 {
public:
	void func1() { cout << "LC2.func1().\n"; }
};
class LegacyClass3 {
public:
	void sub() { cout << "LC3.sub().\n"; }
};

class Adapter {			// If the interfaces are varying...
public:	virtual ~Adapter() {}
public:
	virtual void method1()=0;
};

class Interface1 : public Adapter {
	LegacyClass1	legacyClass1;
public:
	void method1() { cout << "  Interface1::method1()"; legacyClass1.func1(); }
};
class Interface2 : public Adapter {
	LegacyClass2	legacyClass2;
public:
	void method1() { cout << "  Interface2::method1()"; legacyClass2.func1(); }
};
class Interface3 : public Adapter {
	LegacyClass3	legacyClass3;
public:
	void method1() { cout << "  Interface3::method1()"; legacyClass3.sub(); }
};

void clientAdapter() {
	Adapter* interfaces[] = { new Interface1, new Interface2, new Interface3 };
	for(size_t i=0; i<COUNT(interfaces); i++) {
		interfaces[i]->method1();
	}
	cout << endl;
}

}
