#include "sideBySide.h"

namespace side_by_side {

class LegacyClass1 {};
class LegacyClass2 {};
class LegacyClass3 {};



class Adapter {			// If the interfaces are varying...


public:	virtual ~Adapter() {}
public:
	virtual void method1() {}
	virtual void method2() {}
	// ...
	virtual void methodN() {}

};





class Interface1 : public Adapter {
	LegacyClass1	legacyClass1;
public:
	void method1() { cout << "  Interface1::method1()\n"; }
	void method2() { cout << "  Interface1::method2()\n"; }
	// ...
	void methodN() { cout << "  Interface1::methodN()\n"; }
};
class Interface2 : public Adapter {
	LegacyClass2	legacyClass2;
public:
	void method1() { cout << "  Interface2::method1()\n"; }
	void method2() { cout << "  Interface2::method2()\n"; }
	// ...
	void methodN() { cout << "  Interface2::methodN()\n"; }
};
class Interface3 : public Adapter {
	LegacyClass3	legacyClass3;
public:
	void method1() { cout << "  Interface3::method1()\n"; }
	void method2() { cout << "  Interface3::method2()\n"; }
	// ...
	void methodN() { cout << "  Interface3::methodN()\n"; }
};









void clientAdapter() {
	Adapter* interfaces[] = { new Interface1, new Interface2, new Interface3 };
	for(size_t i=0; i<COUNT(interfaces); i++) {
		interfaces[i]->method1();
		interfaces[i]->method2();
		// ...
		interfaces[i]->methodN();
	}
	cout << endl;
}

}
