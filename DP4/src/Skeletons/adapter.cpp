/*
 * adapter.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace skeleton {

class LegacyClassA {
public:
	void func1(...) { cout << "Func 1.\n"; }
	void func2(...) { cout << "Func 2.\n"; }
	// ...
	void funcX(...) { cout << "Func X.\n"; }
};
class LegacyClassB {
public:
	void routine1(...) { cout << "Routine 1.\n"; }
	void routine2(...) { cout << "Routine 2.\n"; }
	// ...
	void routineY(...) { cout << "Routine Y.\n"; }
};
class LegacyClassC {
public:
	void sub1(...) { cout << "Sub 1.\n"; }
	void sub2(...) { cout << "Sub 2.\n"; }
	// ...
	void subZ(...) { cout << "Sub Z.\n"; }
};

class Adapter {			// If the interfaces are varying...
public:	virtual ~Adapter() {}
public:
	virtual void method1() {}
	virtual void method2() {}
	// ...
	virtual void methodN() {}
};

class Interface1 : public Adapter {
	LegacyClassA	legacyClassA;
public:
	void method1() { cout << "  Interface1::method1() - "; legacyClassA.func1(); }
	void method2() { cout << "  Interface1::method2() - "; legacyClassA.func2(); }
	// ...
	void methodN() { cout << "  Interface1::methodN() - "; legacyClassA.funcX(); }
};
class Interface2 : public Adapter {
	LegacyClassB	legacyClassB;
public:
	void method1() { cout << "  Interface2::method1() - "; legacyClassB.routine1(); }
	void method2() { cout << "  Interface2::method2() - "; legacyClassB.routine2(); }
	// ...
	void methodN() { cout << "  Interface2::methodN() - "; legacyClassB.routineY(); }
};
class Interface3 : public Adapter {
	LegacyClassC	legacyClassC;
public:
	void method1() { cout << "  Interface3::method1() - "; legacyClassC.sub1(); }
	void method2() { cout << "  Interface3::method2() - "; legacyClassC.sub2(); }
	// ...
	void methodN() { cout << "  Interface3::methodN() - "; legacyClassC.subZ(); }
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
