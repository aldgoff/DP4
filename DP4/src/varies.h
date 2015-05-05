/*
 * varies.h
 *
 *  Created on: Sep 5, 2014
 *      Author: aldgoff
 *
 * Summary DP1 (Intro):
 * Single inheritance trees:
 *   1) If the algorithms are varying, use the Strategy pattern.
 *   2) If the interfaces are varying, use the Adapter pattern.
 *   3) If the API's are varying, use the Facade pattern.
 *   4) If some of the steps are varying, use the Template Method pattern.
 *   5) If the classes are varying, use the Factory Method pattern.
 *   6) If the options are varying, use the Decorator pattern.
 *   7) If the listeners are varying, use the Observer pattern.
 *   8) If the responders are varying, use the Chain of Responsibility pattern.
 *   9) If the behaviors are varying, use the State pattern.
 * Multiple inheritance trees:
 *   x) If the abstractions and implementations are varying use the Bridge pattern.
 *   y) If whole familes are varying, use the Abstract Factory pattern.
 *   9) If the requests and receivers are varying, use the Command pattern.
 *   A) If the uuu and vvv are varying, use the ddd pattern.
 *
 * Summary DP2 (Advanced):
 * Single inheritance trees:
 *   x) If the yyy are varying, use the ddd pattern.
 * Multiple inheritance trees:
 *   x) If the uuu and vvv are varying, use the ddd pattern.
 *
 * Unknown:
 *   If the nodes are varying, use the Composite pattern.
 * Idioms:
 *   x) If the yyy are varying, use the ddd pattern.
 *   x) If the uuu and vvv are varying, use the ddd pattern.
 */

#ifndef VARIES_H_
#define VARIES_H_

#include <list>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

#ifdef obsolete

class LegacyClass1 {};
class LegacyClass2 {};
class LegacyClass3 {};

class DesignPattern;
class WatchMe {
	list<DesignPattern*>	observers;
public:
	void attach(DesignPattern* observer) {
		observers.push_back(observer);
	}
	void notify();
};

// If it varies: abstract and encapsulate.
class DesignPattern {
protected:
	LegacyClass1	legacyClass1;	// Typical of Facade.
	LegacyClass2	legacyClass2;
	LegacyClass3	legacyClass3;
protected:
	DesignPattern*	dp;				// Typical of Decorator.
public:
	DesignPattern(DesignPattern* dp=0) : dp(dp) {}
	virtual ~DesignPattern() {}
public: // Factory Method.
	static DesignPattern* factoryMethod(int type);	// If the classes are varying, use the Factory Method pattern.
public:	// Facade.
	virtual void simpleAPI() {}						// If the API's are varying, use the Facade pattern.
public: // Strategy.
	virtual void algorithm() {}						// If the algorithms are varying, use the Strategy pattern.
public: // Template Method.
	void sameStep1() { cout << "  sameStep1()\n"; };
	void sameStep2() { cout << "  sameStep2()\n"; };
	virtual void diffStep3() { cout << "  diffStep3 - "; };
	void sameStep4() { cout << "  sameStep4()\n"; };
	void templateMethod() {							// If the steps are varying, use the Template Method pattern.
		cout << "Template Method pattern:\n";
		sameStep1();
		sameStep2();
		diffStep3();
		sameStep4();
	}
public: // Adapter.
	virtual void method1() {}						// If the interfaces are varying, use the Adapter pattern.
	virtual void method2() {}
	// ...
	virtual void methodN() {}
public: // Decorator.
	virtual double cost() {							// If the options are varying, use the Decorator pattern.
		if(dp == 0) return 10.00;
		else		return dp->cost() + 1000.00;
	}
public: // Observer.
	virtual void update() {							// If the notifiees are varying, use the Observer pattern.
		cout << "DesignPattern.observer_update().\n";
	}
};
class TypeOf1 : public DesignPattern {
public:
	TypeOf1() {
		cout << "Factory Method pattern: TypeOf1.\n";
	}
	TypeOf1(DesignPattern* dp) : DesignPattern(dp) {}
public:
	void simpleAPI() {
		cout << "Facade pattern: simpleAPI1().\n";
	}
	void algorithm() {
		cout << "Strategy pattern: algorithm1().\n";
	}
	void diffStep3() {
		DesignPattern::diffStep3();
		cout << "TypeOf1()\n";
	}
public: // Adapter.
	void method1() {
		cout << "  method1 - TypeOf1().\n";
	}
	void method2() {
		cout << "  method2 - TypeOf1().\n";
	}
	void methodN() {
		cout << "  methodN - TypeOf1().\n";
	}
public: // Decorator.
	double cost() {
		if(dp == 0) return 10.00;
		else		return dp->cost() + 100.00;
	}
public: // Observer.
	void update() { cout << "TypeOf1.observer_update().\n"; }
};
class TypeOf2 : public DesignPattern {
public:
	TypeOf2() {
		cout << "Factory Method pattern: TypeOf2.\n";
	}
	TypeOf2(DesignPattern* dp) : DesignPattern(dp) {}
public:
	void simpleAPI() {
		cout << "Facade pattern: simpleAPI2().\n";
	}
	void algorithm() {
		cout << "Strategy pattern: algorithm2().\n";
	}
	void diffStep3() {
		DesignPattern::diffStep3();
		cout << "TypeOf2()\n";
	}
public: // Adapter.
	void method1() {
		cout << "  method1 - TypeOf2().\n";
	}
	void method2() {
		cout << "  method2 - TypeOf2().\n";
	}
	void methodN() {
		cout << "  methodN - TypeOf2().\n";
	}
public: // Decorator.
	double cost() {
		if(dp == 0) return 10.00;
		else		return dp->cost() + 200.00;
	}
public: // Observer.
	void update() { cout << "TypeOf2.observer_update().\n"; };
};
class TypeOf3 : public DesignPattern {
public:
	TypeOf3() {
		cout << "Factory Method pattern: TypeOf3.\n";
	}
	TypeOf3(DesignPattern* dp) : DesignPattern(dp) {}
public:
	void simpleAPI() {
		cout << "Facade pattern: simpleAPI3().\n";
	}
	void algorithm() {
		cout << "Strategy pattern: algorithm3().\n";
	}
	void diffStep3() {
		DesignPattern::diffStep3();
		cout << "TypeOf3()\n";
	}
public: // Adapter.
	void method1() {
		cout << "  method1 - TypeOf3().\n";
	}
	void method2() {
		cout << "  method2 - TypeOf3().\n";
	}
	void methodN() {
		cout << "  methodN - TypeOf3().\n";
	}
public: // Decorator.
	double cost() {
		if(dp == 0) return 10.00;
		else		return dp->cost() + 300.00;
	}
public: // Observer.
	void update() { cout << "TypeOf3.observer_update().\n"; };
};
DesignPattern* DesignPattern::factoryMethod(int type) {
	switch(type) {
	case 1:	return new TypeOf1;
	case 2:	return new TypeOf2;
	case 3:	return new TypeOf3;
	default: return new DesignPattern;
	}
}

void WatchMe::notify() {
	list<DesignPattern*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++) {
		(*it)->update();
	}
}

namespace side_by_side {

}

// Classes: use Factory Method pattern.
class FactoryMethod {
public:	virtual ~FactoryMethod() {}
public:
	static FactoryMethod* makeObject(int type);
	virtual const char* compute() { return "type"; }
};
class Type1 : public FactoryMethod {
	const char* compute() { return "Type1"; }
};
class Type2 : public FactoryMethod {
	const char* compute() { return "Type2"; }
};
class Type3 : public FactoryMethod {
	const char* compute() { return "Type3"; }
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
	FactoryMethod* classes[] = { FactoryMethod::makeObject(1), FactoryMethod::makeObject(2), FactoryMethod::makeObject(3)};
	for(size_t i=0; i<COUNT(classes); i++)
		classes[i]->compute();
}


// API: use Facade pattern.
class Facade {
protected:
	LegacyClass1	legacyClass1;
	LegacyClass2	legacyClass2;
	LegacyClass3	legacyClass3;
};
class API1 : public Facade {
public:
	void simpleAPI() {}
};
class API2 : public Facade {
public:
	void simpleAPI() {}
};
class API3 : public Facade {
public:
	void simpleAPI() {}
};

void clientFacade() {
	API1 facade1;	facade1.simpleAPI();
	API1 facade2;	facade2.simpleAPI();
	API1 facade3;	facade3.simpleAPI();
}


// Algorithms: use Strategy pattern.
class Strategy {
public:	virtual ~Strategy() {}
public:
	virtual void compute() {}
};
class Algorithm1 : public Strategy {};
class Algorithm2 : public Strategy {};
class Algorithm3 : public Strategy {};

void clientStrategy() {
	Strategy* algorithms[] = { new Algorithm1, new Algorithm2, new Algorithm3};
	for(size_t i=0; i<COUNT(algorithms); i++)
		algorithms[i]->compute();
}


// Steps: use Template Method pattern.
class TemplateMethod {
public:	virtual ~TemplateMethod() {};
public:
	void sameStep1(){};
	void sameStep2(){};
	virtual void diffStep3(){};
	void sameStep4(){};
	void compute() {
		sameStep1();
		sameStep2();
		diffStep3();
		sameStep4();
	}
};
class Step3_thisWay : public TemplateMethod {};
class Step3_thatWay : public TemplateMethod {};
class Step3_yourWay : public TemplateMethod {};

void clientTemplateMethod() {
	TemplateMethod* steps[] = { new Step3_thisWay, new Step3_thatWay, new Step3_yourWay };
	for(size_t i=0; i<COUNT(steps); i++)
		steps[i]->compute();
}


// Interfaces: use Adapter pattern.
class Adapter {
public:	virtual ~Adapter() {}
public:
	virtual void method1() {}
	virtual void method2() {}
	// ...
	virtual void methodN() {}
};
class Interface1 : public Adapter {
	LegacyClass1	legacyClass1;
};
class Interface2 : public Adapter {
	LegacyClass2	legacyClass2;
};
class Interface3 : public Adapter {
	LegacyClass3	legacyClass3;
};

void clientAdapter() {
	Adapter* interfaces[] = { new Interface1, new Interface2, new Interface3 };
	for(size_t i=0; i<COUNT(interfaces); i++) {
		interfaces[i]->method1();
		interfaces[i]->method2();
		// ...
		interfaces[i]->methodN();
	}
}


// Options: use Decorator pattern.
class Build {};
class Decorator : public Build {};
class Option1 : public Decorator {
public:
	Option1(Build* build) {}
};
class Option2 : public Decorator {
public:
	Option2(Build* build) {}
};
class Option3 : public Decorator {
public:
	Option3(Build* build ){}
};

void clientDecorator() {
	Build *build = new Build;
	build = new Option1(build);
	build = new Option2(build);
	build = new Option3(build);
}


// Observers: use the Observer pattern.
class Subject {
public: virtual ~Subject() {}
public:
	virtual void notify() {};
};
class Observer : public Subject {
	list<Observer*> observers;
public:
	virtual void attach(Observer* obs) {}
	virtual void detach(Observer* obs) {}
	void notify() {}
};
class Observer1 : public Observer {};
class Observer2 : public Observer {};
class Observer3 : public Observer {};

void clientObserver() {
	Observer subject;
	Observer* observers[] = { new Observer1, new Observer2, new Observer3 };
	for(size_t i=0; i<COUNT(observers); i++)
		observers[i]->attach(&subject);
	subject.notify();
}


// Requests: use the Command pattern;
class Command {
public: virtual ~Command() {}
public:
	virtual void ask() {}
};
class Request1 : public Command {};
class Request2 : public Command {};
class Request3 : public Command {};

void clientCommand() {
	Command* requests[] = { new Request1, new Request2, new Request3 };
	for(size_t i=0; i<COUNT(requests); i++)
		requests[i]->ask();
}


namespace problem {
	void demo() {
		cout << "<< Design Pattern problem >>\n";

		cout << endl;
}
}

namespace solution {
	void demo() {
		cout << "<< Design Pattern solution >>\n";

//		DesignPattern* dps[] = { new TypeOf1, new TypeOf2, new TypeOf3 };
		DesignPattern* dps[] = { DesignPattern::factoryMethod(1), DesignPattern::factoryMethod(2), DesignPattern::factoryMethod(3)};
		cout << endl;

		WatchMe subject;

		for(size_t i=0; i<COUNT(dps); i++) {	// Client wants to use polymorphically.
			dps[i]->simpleAPI();
			dps[i]->algorithm();
			dps[i]->templateMethod();
			cout << "Adapter pattern:\n";
				dps[i]->method1();
				dps[i]->method2();
				cout << "  ...\n";
				dps[i]->methodN();
			DesignPattern* base = new DesignPattern(dps[i]);
			DesignPattern* decorator = 0;
			switch(i) {
			case 0:  decorator = new TypeOf1(base); break;
			case 1:  decorator = new TypeOf2(base); break;
			case 2:  decorator = new TypeOf3(base); break;
			default: decorator = new DesignPattern(base);
			break;
			}
			cout << "Decorator pattern: $" << decorator->cost() << ".\n";
			subject.attach(dps[i]);

			cout << endl;
		}
		subject.notify();

		cout << endl;
	}
}

#endif

#ifdef obsolete

vector<Strategy*> ops;
ops.push_back(new Algorithm1);
ops.push_back(new Algorithm2);
ops.push_back(new Algorithm3);

for(size_t i=0; i<ops.size(); i++) {
	ops[i]->compute();
}

vector<TemplateMethod*> flow;
flow.push_back(new Step3_thisWay);
flow.push_back(new Step3_thatWay);
flow.push_back(new Step3_yourWay);

for(size_t i=0; i<flow.size(); i++) {
	flow[i]->compute();
}

vector<FactoryMethod*> objects;
objects.push_back(FactoryMethod::makeObject(1));
objects.push_back(FactoryMethod::makeObject(2));
objects.push_back(FactoryMethod::makeObject(3));

for(size_t i=0; i<objects.size(); i++) {
	objects[i]->action();
}

vector<Adapter*> classes;
classes.push_back(new Interface1);
classes.push_back(new Interface2);
classes.push_back(new Interface3);

for(size_t i=0; i<classes.size(); i++) {
	classes[i]->method1();
	classes[i]->method2();
	// ...
	classes[i]->methodN();
}

#endif

#endif /* VARIES_H_ */
