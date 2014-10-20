/*
 * forest.h
 *
 * Compare, contrast, and summarize all the design patterns.
 *
 *  Created on: Apr 12, 2014
 *      Author: aldgoff
 */

#ifndef FOREST_H_
#define FOREST_H_

using namespace std;

namespace forest {

// Abstract what varies.
class Base {};
class Derived1 : public Base {};
class Derived2 : public Base {};
class Derived3 : public Base {};

class Abstract {};
class Concrete1 : public Abstract {};
class Concrete2 : public Abstract {};
class Concrete3 : public Abstract {};

class Interface {};
class Implementation1 : public Interface{};
class Implementation2 : public Interface{};
class Implementation3 : public Interface{};

// Design patterns.
class Facade {
	void simplerInterface1() {}
	void simplerInterface2() {}
	void simplerInterface3() {}
};

namespace adapter {
class API {
public:
	virtual void draw() {}
	virtual void calc() {}
	// ...
	virtual void diff() {}
public:
	virtual ~API() {}
};
class DiffAPI {
public:
	virtual void display() {}
	virtual void compute() {}
	// ...
	virtual void subtract() {}
public:
	virtual ~DiffAPI() {}
};
class Adapter : public API { // Adapt interfaces so classes can work together polymorphically.
	DiffAPI sam;
public:
	void draw() { sam.display(); }
	void calc() { sam.compute(); }
	// ...
	void diff() { sam.subtract(); }
};
}

class Strategy {
public:
	Base*		base;
	Abstract*	abstract;
	Interface*	interface;
public:
	Strategy(Base* base, Abstract* abstract, Interface* interface)
		: base(base), abstract(abstract), interface(interface) {}
};
class Algorithm1 : public Strategy {
public:
	Algorithm1() : Strategy(new Derived1, new Concrete2, new Implementation3) {}
};
class Algorithm2 : public Strategy {
public:
	Algorithm2() : Strategy(new Derived2, new Concrete2, new Implementation1) {}
};
class Algorithm3 : public Strategy {
public:
	Algorithm3() : Strategy(new Derived3, new Concrete2, new Implementation3) {}
};

class Bridge {
protected:
	Base*		base;
	Abstract*	abstract;
	Interface*	interface;
public:
	Bridge(Base* base, Abstract* abstract, Interface* interface)
		: base(base), abstract(abstract), interface(interface) {}
	virtual ~Bridge(){}
	virtual void method()=0;
};
class Build1 : public Bridge {
public:
	Build1(Base* base, Abstract* abstract, Interface* interface)
		: Bridge(base, abstract, interface) {} // May differ, but have these in common.
	void method() { /* Differences */ }
};
class Build2 : public Bridge {
public:
	Build2(Base* base, Abstract* abstract, Interface* interface)
		: Bridge(base, abstract, interface) {} // May differ, but have these in common.
	void method() { /* Differences */ }
};
class Build3 : public Bridge {
public:
	Build3(Base* base, Abstract* abstract, Interface* interface)
		: Bridge(base, abstract, interface) {} // May differ, but have these in common.
	void method() { /* Differences */ }
};


class AbstractFactory {
public:
	enum Constructs {
		Construct1ID,
		Construct2ID,
		Construct3ID,
	};
public:
	static AbstractFactory* newConstruct(Constructs constructsID);
	virtual ~AbstractFactory() {}
	virtual Base* createBase()=0;
	virtual Abstract* createAbstract()=0;
	virtual Interface* createInterface()=0;
};
class Construct1 : public AbstractFactory {
public:
	Base*		createBase()	  { return new Derived1; }
	Abstract*	createAbstract()  { return new Concrete1; }
	Interface*	createInterface() { return new Implementation1; }
};
class Construct2 : public AbstractFactory {
public:
	Base*		createBase()	  { return new Derived2; }
	Abstract*	createAbstract()  { return new Concrete2; }
	Interface*	createInterface() { return new Implementation2; }
};
class Construct3 : public AbstractFactory {
public:
	Base*		createBase()	  { return new Derived3; }
	Abstract*	createAbstract()  { return new Concrete3; }
	Interface*	createInterface() { return new Implementation3; }
};

AbstractFactory* AbstractFactory::newConstruct(Constructs constructsID) {
	switch(constructsID) {
	case Construct1ID:
		return new Construct1;
	case Construct2ID:
		return new Construct2;
	case Construct3ID:
		return new Construct3;
	};
	throw "oops";
}

class Client {
private:
	Base*		base;
	Abstract*	abstract;
	Interface*	interface;
public:
	Client(AbstractFactory::Constructs constructID) {
		AbstractFactory* construct = AbstractFactory::newConstruct(constructID);
		base = construct->createBase();
		abstract = construct->createAbstract();
		interface = construct->createInterface();
	}
	void run() { /* Use the private members. */ }
};

class Foundation {
};
class Block1 : public Foundation {
};
class Block2 : public Foundation {
};
class Block3 : public Foundation {
};


class Thing {
};
class Basic : public Thing {
};
class ThingDecorator : public Thing {
};
class Dec1 : public ThingDecorator {
};
class Dec2 : public ThingDecorator {
};
class Dec3 : public ThingDecorator {
};

class Observer;
class Subject {
	list<Observer*>	observers;
public:
	~Subject();
public:
	void attach(Observer* obs) { observers.push_back(obs); }
	void detach(Observer* obs) { observers.remove(obs); }
	void notify();
};
class Observer {
	Subject& subject;
public:
	Observer(Subject& subject) : subject(subject) {
		subject.attach(this);
	}
	virtual ~Observer() {
		subject.detach(this);
	}
public:
	virtual void update(Subject* subject=0)=0;
};
class Notifie_1 : public Observer {
public:
	Notifie_1(Subject& subject) : Observer(subject) {}
public:
	void update(Subject* subject) {/*...*/}
};
class Notifie_2 : public Observer {
public:
	Notifie_2(Subject& subject) : Observer(subject) {}
public:
	void update(Subject* subject) {/*...*/}
};
class Notifie_3 : public Observer {
public:
	Notifie_3(Subject& subject) : Observer(subject) {}
public:
	void update(Subject* subject) {/*...*/}
};

class TemplateMethod {
public:
	virtual ~TemplateMethod() {}
public:
	void run() {
		step1();
		step2();
		algorithm();
		step3();
		//...
		stepN();
	}
protected:
	virtual void step1() {}
	virtual void step2() {}
	virtual void step3() {}
	//...
	virtual void stepN() {}
private:
	void algorithm() {
		algor1();
		while(algor2()) {
			algor3();
			algor4();
			//...
		}
		algorX();
	}
protected:
	virtual void algor1() {}
	virtual bool algor2() { return false; }
	virtual void algor3() {}
	virtual void algor4() {}
	//...
	virtual void algorX() {}
};
class DetailDiffs1 : public TemplateMethod {
	void step1() {}
	void step2() {}
	void step3() {}
	//...
	void stepN() {}
	void algor1() {}
	bool algor2() { return false; }
	void algor3() {}
	void algor4() {}
	//...
	void algorX() {}
};
class DetailDiffs2 : public TemplateMethod {
	void step1() {}
	void step2() {}
	void step3() {}
	//...
	void stepN() {}
	void algor1() {}
	bool algor2() { return false; }
	void algor3() {}
	void algor4() {}
	//...
	void algorX() {}
};
class DetailDiffs3 : public TemplateMethod {
	void step1() {}
	void step2() {}
	void step3() {}
	//...
	void stepN() {}
	void algor1() {}
	bool algor2() { return false; }
	void algor3() {}
	void algor4() {}
	//...
	void algorX() {}
};


namespace obsolete {

class BoardInterface1 {};
class BoardInterface2 {};
class DataInterface1 {};
class ParaData : public DataInterface1 {};
class ConditionBoard : public BoardInterface1, public BoardInterface2 {};
class StatisticsBoard : public BoardInterface1, public BoardInterface2 {};

}

}

#endif /* FOREST_H_ */
