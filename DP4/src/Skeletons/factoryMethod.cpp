/*
 * factoryMethod.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace skeleton {

class FactoryMethod {	// If the classes are varying...
public:	virtual ~FactoryMethod() {}
public:
	virtual void compute() {}
public:
	static FactoryMethod* makeObject(int type);
};

class Type1 : public FactoryMethod {
public:
	void compute() { cout << "  Type1\n"; }
};
class Type2 : public FactoryMethod {
public:
	void compute() { cout << "  Type2\n"; }
};
class Type3 : public FactoryMethod {
public:
	void compute() { cout << "  Type3\n"; }
};

FactoryMethod* FactoryMethod::makeObject(int type) {
	switch(type) {
	case 1:	return new Type1;
	case 2:	return new Type2;
	case 3:	return new Type3;
	default: return new FactoryMethod;
	}
}

void clientFactoryMethod() {
	cout << "Factory Method\n";
	FactoryMethod* classes[] = { FactoryMethod::makeObject(1), FactoryMethod::makeObject(2), FactoryMethod::makeObject(3)};
	for(size_t i=0; i<COUNT(classes); i++) {
		classes[i]->compute();
	}
	cout << endl;
}

}
