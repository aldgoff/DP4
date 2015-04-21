/*
 * decorator.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
#include <vector>
using namespace std;

namespace skeleton {

namespace original {

class Decorator {		// If the options are varying...
};

class Option1 : public Decorator {
public:
	Option1(Decorator* decorator) { cout << "  Option1\n"; }
};
class Option2 : public Decorator {
public:
	Option2(Decorator* decorator) { cout << "  Option2\n"; }
};
class Option3 : public Decorator {
public:
	Option3(Decorator* decorator) { cout << "  Option3\n"; }
};

void clientDecorator() {
	Decorator *decorator = new Decorator;
	decorator = new Option1(decorator);
	decorator = new Option2(decorator);
	decorator = new Option3(decorator);
	cout << endl;
}

}

//namespace component {

class Component {
public:
	Component() {}
	virtual ~Component() { cout << "~Component\n"; }
public:
	virtual void run() {
		cout << "  Component\n";
	}
};
class Decoratee : public Component {
public:
	Decoratee() {}
	virtual ~Decoratee() { cout << "~Decoratee "; }
public:
	virtual void run() {
		cout << "  Decoratee\n";
	}
};
class Decorator : public Component {
protected:
	Component* component;
public:
	Decorator(Component* component) : component(component) {}
	virtual ~Decorator() { cout << "~Decorator\n"; delete component; }
public:
	virtual void run() {
		cout << "  Decorator\n";
	}
public:
	static Component* addOption(const string& option, Component* component);
};
class Option1 : public Decorator {
public:
	Option1(Component* component) : Decorator(component) {}
	~Option1() { cout << "~Option1 "; }
public:
	virtual void run() {
		component->run();
		cout << "    Add option1\n";
	}
};
class Option2 : public Decorator {
public:
	Option2(Component* component) : Decorator(component) {}
	~Option2() { cout << "~Option2 "; }
public:
	virtual void run() {
		component->run();
		cout << "    Add option2\n";
	}
};
class Option3 : public Decorator {
public:
	Option3(Component* component) : Decorator(component) {}
	~Option3() { cout << "~Option3 "; }
public:
	virtual void run() {
		component->run();
		cout << "    Add option3\n";
	}
};
// Seam point - add another option.

/* Decision logic has to exist somewhere.
 * If its in client code, then client is coupled to the derived classes.
 * Potentially better to have it in a class static method,
 * but then Decorator class can become coupled to the client code.
 * Abstract an interface (here string) to decouple client code & derived classes.
 * Decision logic on client side produces one of the optionX strings.
 */
Component* Decorator::addOption(const string& option, Component* component) {
	if(		option == "option1")	return new Option1(component);
	else if(option == "option2")	return new Option2(component);
	else if(option == "option3")	return new Option3(component);
	// Seam point - add another option.

	else {
		cout << "  Unknown option: " << option << ".\n";
		return component;
	}
}

void clientDecorator() {
	// Simulate translation of decision logic to list of options.
	vector<string> domain;
	bool fizzbin = true;
	string sam = "iam";
	if(fizzbin)		domain.push_back("option1");
	if(sam=="iam")	domain.push_back("option2");
	if(1<2)			domain.push_back("option3");
	// Seam point - add another option.

	Component* component = new Decoratee;

	for(size_t i=0; i<domain.size(); i++) {
		component = Decorator::addOption(domain[i], component);
	}

	component->run();

	delete component;	// Dtor instrumentation.

	cout << endl;
}

//}

}
