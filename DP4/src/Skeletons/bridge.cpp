/*
 * bridge.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
#include <map>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace skeleton {

class BridgeImplementation {	// If multiple elements need to vary independently...
public: virtual ~BridgeImplementation() { cout << "~BridgeImplementation "; }
public:
	virtual void concreteA()=0;
	virtual void concreteB()=0;
public:
	static BridgeImplementation* getImplementation(map<string,string>& domain);
};
class ImplementationX : public BridgeImplementation {
public: virtual ~ImplementationX() { cout << "~ImplementationX "; }
	void concreteA() { cout << "concrete A implementation X.\n"; }
	void concreteB() { cout << "concrete B implementation X.\n"; }
};
class ImplementationY : public BridgeImplementation {
public: virtual ~ImplementationY() { cout << "~ImplementationY "; }
	void concreteA() { cout << "concrete A implementation Y.\n"; }
	void concreteB() { cout << "concrete B implementation Y.\n"; }
};
class ImplementationZ : public BridgeImplementation {
public: virtual ~ImplementationZ() { cout << "~ImplementationZ "; }
	void concreteA() { cout << "concrete A implementation Z.\n"; }
	void concreteB() { cout << "concrete B implementation Z.\n"; }
};
// Seam point - add another implementation.

BridgeImplementation* BridgeImplementation::getImplementation(map<string,string>& domain) {
	if(		domain["implementation"] == "one")		return new ImplementationX;
	else if(domain["implementation"] == "two")		return new ImplementationY;
	else if(domain["implementation"] == "three")	return new ImplementationZ;
	// Seam point - insert another implementation.

	else {	// Throw error, or select a default.
		throw "OOPS!";
	}
}

class BridgeAbstraction {		// If multiple elements need to vary independently...
protected:
	BridgeImplementation*	imp;
public:
	explicit BridgeAbstraction(BridgeImplementation* imp) : imp(imp) {}
	virtual ~BridgeAbstraction() { delete imp; cout << "~BridgeAbstraction\n"; }
public:
	virtual void run()=0;
public:
	static BridgeAbstraction* getAbstraction(map<string,string>& domain);
};
class Abstraction1 : public BridgeAbstraction {
public:
	Abstraction1(BridgeImplementation* imp) : BridgeAbstraction(imp) {}
	~Abstraction1() { cout << "~Abstraction1 "; }
public:
	void run() { cout << "  Bridge abstraction 1 - "; imp->concreteA(); }
};
class Abstraction2 : public BridgeAbstraction {
public:
	Abstraction2(BridgeImplementation* imp) : BridgeAbstraction(imp) {}
	~Abstraction2() { cout << "~Abstraction2 "; }
public:
	void run() { cout << "  Bridge abstraction 2 - "; imp->concreteB(); }
};
class Abstraction3 : public BridgeAbstraction {
public:
	Abstraction3(BridgeImplementation* imp) : BridgeAbstraction(imp) {}
	~Abstraction3() { cout << "~Abstraction3 "; }
public:
	void run() { cout << "  Bridge abstraction 3 - "; imp->concreteA(); }
};
// Seam point - add another abstraction.

BridgeAbstraction* BridgeAbstraction::getAbstraction(map<string,string>& domain) {
	BridgeImplementation* implementation = BridgeImplementation::getImplementation(domain);

	if(		domain["abstraction"] == "first")	return new Abstraction1(implementation);
	else if(domain["abstraction"] == "second")	return new Abstraction2(implementation);
	else if(domain["abstraction"] == "third")	return new Abstraction3(implementation);
	// Seam point - insert another abstraction.

	else {	// Throw error, or select a default.
		throw "OOPS!";
	}
}

void clientBridge() {
	cout << "Bridge\n";

	BridgeImplementation* imps[] = { new ImplementationX, new ImplementationY, new ImplementationZ };
	for(size_t i=0; i<COUNT(imps); i++) {
		BridgeAbstraction* abs[] = { new Abstraction1(imps[i]), new Abstraction2(imps[i]), new Abstraction3(imps[i]) };
		for(size_t j=0; j<COUNT(abs); j++) {
			abs[j]->run();
		}
		cout << endl;
	}

	{	// Use domain and static construct methods (getA/I) to lower coupling.
	map<string,string> domain;
	string imps[] = { "one", "two", "three" };
	string abs[]  = { "first", "second", "third" };
	BridgeAbstraction* abstractions[COUNT(abs)*COUNT(imps)] = {0};
	size_t k = 0;
	for(size_t i=0; i<COUNT(abs); i++) {
		for(size_t j=0; j<COUNT(imps); j++) {
			domain["abstraction"] = abs[i];
			domain["implementation"] = imps[j];
			abstractions[k] = BridgeAbstraction::getAbstraction(domain);
			abstractions[k]->run();
			k++;
		}
	}

	//  Show Dtor instrumentation.
	cout << COUNT(abstractions) << endl;
	for(size_t k=0; k<COUNT(abstractions); k++)
		delete abstractions[k];

	}
}

}
