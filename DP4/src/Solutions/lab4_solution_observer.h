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

namespace observer_solution {

class Observer;
class Subject;

class Subject {
	list<Observer*>	observers;
public:
	~Subject();
public:
	void attach(Observer* obs) { observers.push_back(obs); }
	void detach(Observer* obs) { observers.remove(obs); }
	void says(const string& catSays="\n");
};

class Observer {
	Subject& subject;
public:
	Observer(Subject& subject) : subject(subject) {
		subject.attach(this);
	}
	virtual ~Observer() {
		subject.detach(this);
		cout << " ~Observer.\n";
	}
public:
	virtual void update(Subject* subject=0)=0;
};
class Thing : public Observer {
	string	name;
public:
	Thing(string name, Subject& subject) : Observer(subject), name(name) {}
	~Thing() { cout << "  Thing" << name << " leaves:"; }
public:
	void update(Subject* subject) {
		cout << "  Thing" << name << " makes mischief.\n";
	}
};
class Fish : public Observer {
public:
	Fish(Subject& subject) : Observer(subject) {}
	~Fish() { cout << "  ~Fish:"; }
public:
	void update(Subject* subject) { cout << "  Fish complains.\n"; }
};
class Child : public Observer {
	string gender;
public:
	Child(string gender, Subject& subject) : Observer(subject), gender(gender) {}
	~Child() { cout << "  ~Child(" << gender << "):"; }
public:
	void update(Subject* subject) { cout << "  " << gender << " has fun.\n"; }
};
class Mom : public Observer {
public:
	Mom(Subject& subject) : Observer(subject) {}
	~Mom() { cout << "  ~Mom:"; }
public:
	void update(Subject* subject) { cout << "  Mom returns.\n"; }
};

void Subject::says(const string& catSays) {
	cout << "  Cat in the Hat says \"" << catSays << "\".\n";
	list<Observer*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++) {
		(*it)->update();
	}
	cout << endl;
}
Subject::~Subject() {
	cout << "  Observers left to process (should be zero) = ";
	cout << observers.size() << ".\n";
	cout << "  Cat in the Hat left: ~Subject.\n";
	cout << endl;
}

void demo() {
	Subject catInTheHat;

	{
	// Event 1.
	Observer* thing1 = new Thing("1", catInTheHat);
	Observer* thing2 = new Thing("2", catInTheHat);
	Child boy("Boy", catInTheHat);
	Child girl("Girl", catInTheHat);
	catInTheHat.says("Hello");

	// Event 2.
	delete thing2;
	catInTheHat.says("let's play");

	// Event 3.
	Fish fish(catInTheHat);
	catInTheHat.says("rock & roll");

	// Cleanup 1.
	delete thing1;
	}

	// Event 4.
	Mom mom(catInTheHat);
	catInTheHat.says("Goodbye");

	// Cleanup 2.
}

}

}

#endif /* OBSERVER_H_ */
