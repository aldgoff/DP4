#include "sideBySide.h"

namespace side_by_side {







class BridgeImp {		// If the implementations are varying...
public: virtual ~BridgeImp() {}
public:
	virtual void concreteA()=0;
	virtual void concreteB()=0;
};
class Implement1 : public BridgeImp {
public:
	void concreteA() { cout << "concrete A implementation 1.\n"; }
	void concreteB() { cout << "concrete B implementation 1.\n"; }
};
class Implement2 : public BridgeImp {
public:
	void concreteA() { cout << "concrete A implementation 2.\n"; }
	void concreteB() { cout << "concrete B implementation 2.\n"; }
};
class Implement3 : public BridgeImp {
public:
	void concreteA() { cout << "concrete A implementation 3.\n"; }
	void concreteB() { cout << "concrete B implementation 3.\n"; }
};

class BridgeAbstract {	// If the abstractions are also varying...
protected:
	BridgeImp*	imp;
public:
	explicit BridgeAbstract(BridgeImp* imp) : imp(imp) {}
	virtual ~BridgeAbstract() {}
public:
	virtual void run()=0;
};
class Abstract1 : public BridgeAbstract {
public:
	Abstract1(BridgeImp* imp) : BridgeAbstract(imp) {}
	void run() { cout << "  Bridge abstraction 1 - ";
		imp->concreteA();
		imp->concreteB();
	}
};
class Abstract2 : public BridgeAbstract {
public:
	Abstract2(BridgeImp* imp) : BridgeAbstract(imp) {}
	void run() { cout << "  Bridge abstraction 2 - ";
		imp->concreteA();
		imp->concreteB();
	}
};


void clientBridge() {
	BridgeImp* imps[] = { new Implement1, new Implement2, new Implement3 };
	for(size_t i=0; i<COUNT(imps); i++) {
		BridgeAbstract* abs[] = {new Abstract1(imps[i]),new Abstract2(imps[i])};
		for(size_t j=0; j<COUNT(abs); j++)
			abs[j]->run();
		cout << endl;
	}
	cout << endl;
}

}
