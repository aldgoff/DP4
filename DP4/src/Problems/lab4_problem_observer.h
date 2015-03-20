/*
 * Observer.h
 *
 * Desc: Notify observers automatically.
 *
 * Category: Behavioral
 *
 *  Created on: May 3, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Observer
 *  	http://www.dofactory.com/net/observer-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter18
 *  	http://sourcemaking.com/design_patterns/observer
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <list>
using namespace std;

namespace homework {

/* Consider the Dr. Seuss children's story, "The Cat in the Hat."
 * When the cat in the hat says something, the things, children & fish respond.
 * In a procedural approach, the Subject class (the cat in the hat) has to know
 * about all the other classes. When they change, Subject has to be recompiled.
 * In addition, Subject is managing multiple objects, of multiple classes, with
 * multiple interfaces, which leads to long, hard to follow code.
 * Use the Observer pattern to decouple the Subject class from the others.
 */

namespace observer_problem {

class Thing {
	string name;
public:
	Thing(string name) : name(name) {}
	~Thing() { cout << "  ~Thing" << name << " leaves.\n"; }
public:
	void makesMischief() { cout << "  Thing" << name << " makes mischief.\n"; }
};

class Fish {
public:
	Fish() {}
	~Fish() { cout << "  ~Fish.\n"; }
public:
	void complains() { cout << "  Fish complains.\n"; }
};

class Child {
	string gender;
public:
	Child(string gender) : gender(gender) {}
	~Child() { cout << "  ~Child(" << gender << ").\n"; }
public:
	void hasFun() { cout << "  " << gender << " has fun.\n"; }
};

class Mom {
public:
	Mom() {}
	~Mom() { cout << "  ~Mom.\n"; }
public:
	void returns() { cout << "  Mom returns.\n"; }
};

class Subject {	// Has to know about all the objects that are 'listening'.
	Thing*	thing1;
	Thing*	thing2;
	Fish*	fish;
	Child*	boy;
	Child*	girl;
	Mom*	mom;
	// Seam 1 - insert new objects.
public:
	Subject() :
		thing1(new Thing("1")),
		thing2(new Thing("2")),
		fish(new Fish),
		boy(new Child("Boy")),
		girl(new Child("Girl")),
		mom(new Mom)
		// Seam 2 - insert new objects.
		{}
	~Subject() {
		cout << "  Cat in the hat left: ~Subject.\n";
		cout << endl;
	}
public:
	void runSim() {
		// Event 1.
		cout << "  Cat in the Hat says \"Hello\".\n";
		thing1->makesMischief();
		thing2->makesMischief();
		boy->hasFun();
		girl->hasFun();
		cout << endl;

		// Event 2.
		delete thing2;
		cout << "  Cat in the Hat says \"let's play\".\n";
		thing1->makesMischief();
		boy->hasFun();
		girl->hasFun();
		cout << endl;

		// Event 3.
		cout << "  Cat in the Hat says \"rock & roll\".\n";
		thing1->makesMischief();
		boy->hasFun();
		girl->hasFun();
		fish->complains();
		cout << endl;

		// Cleanup 1.
		delete thing1;
		delete fish;
		delete girl;
		delete boy;

		// Event 4.
		cout << "  Cat in the Hat says \"Goodbye\".\n";
		mom->returns();
		cout << endl;

		// Cleanup 2.
		delete mom;
	}
};

void demo() {
	Subject catInTheHat;

	catInTheHat.runSim();
}

}

}

#endif /* OBSERVER_H_ */
