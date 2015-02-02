/*
 * bridge.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace skeleton {

class BridgeImplementation {	// If multiple elements need to vary independently...
public: virtual ~BridgeImplementation() {}
public:
	virtual void concreteA()=0;
	virtual void concreteB()=0;
};
class Implementation1 : public BridgeImplementation {
public:
	void concreteA() { cout << "concrete A implementation 1.\n"; }
	void concreteB() { cout << "concrete B implementation 1.\n"; }
};
class Implementation2 : public BridgeImplementation {
public:
	void concreteA() { cout << "concrete A implementation 2.\n"; }
	void concreteB() { cout << "concrete B implementation 2.\n"; }
};
class Implementation3 : public BridgeImplementation {
public:
	void concreteA() { cout << "concrete A implementation 3.\n"; }
	void concreteB() { cout << "concrete B implementation 3.\n"; }
};

class BridgeAbstraction {		// If multiple elements need to vary independently...
protected:
	BridgeImplementation*	imp;
public:
	explicit BridgeAbstraction(BridgeImplementation* imp) : imp(imp) {}
	virtual ~BridgeAbstraction() {}
public:
	virtual void run()=0;
};
class Abstraction1 : public BridgeAbstraction {
public:
	Abstraction1(BridgeImplementation* imp) : BridgeAbstraction(imp) {}
	void run() { cout << "  Bridge abstraction 1 - "; imp->concreteA(); }
};
class Abstraction2 : public BridgeAbstraction {
public:
	Abstraction2(BridgeImplementation* imp) : BridgeAbstraction(imp) {}
	void run() { cout << "  Bridge abstraction 2 - "; imp->concreteB(); }
};
class Abstraction3 : public BridgeAbstraction {
public:
	Abstraction3(BridgeImplementation* imp) : BridgeAbstraction(imp) {}
	void run() { cout << "  Bridge abstraction 3 - "; imp->concreteA(); }
};

void clientBridge() {
	BridgeImplementation* imps[] = { new Implementation1, new Implementation2, new Implementation3 };
	for(size_t i=0; i<COUNT(imps); i++) {
		BridgeAbstraction* abs[] = { new Abstraction1(imps[i]), new Abstraction2(imps[i]), new Abstraction3(imps[i]) };
		for(size_t j=0; j<COUNT(abs); j++) {
			abs[j]->run();
		}
		cout << endl;
	}
	cout << endl;
}

}
