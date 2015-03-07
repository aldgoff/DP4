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

namespace lecture {

namespace observer_legacy {

void demo() {
	cout << endl;
}

}

namespace observer_problem {

void demo() {
	cout << endl;
}

}

namespace observer_solution {

void demo() {
	cout << endl;
}

}

}

namespace homework {

/* Consider the Dr. Seuss children's story, "The Cat in the Hat."
 * Whenever the cat in the hat does something, the things, children & fish should respond.
 * In the below procedural approach, the Subject class (the cat in the hat) has to know
 * about all the other classes. When they get changed, Subject has to be recompiled.
 * In addition, Subject is managing multiple objects, of multiple classes, with multiple
 * interfaces, which leads to long, hard to follow code.
 * Use the Observer pattern to decouple the Subject class from the others.
 */

namespace observer_problem {

class Thing {
	string name;
public:
	Thing(string name) : name(name) {}
	~Thing() { cout << "  Thing" << name << " leaves.\n"; }
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

class Subject {
	Thing*	thing1;
	Thing*	thing2;
	Fish*	fish;
	Child*	boy;
	Child*	girl;
	Mom*	mom;
	// Dependency: Subject must know about all kinds of objects.
public:
	Subject() :
		thing1(new Thing("1")),
		thing2(new Thing("2")),
		fish(new Fish),
		boy(new Child("Boy")),
		girl(new Child("Girl")),
		mom(new Mom)
{	// Dependency: ditto.
	}
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

void demoProofOfConcept() {	// Just for development.
	cout << "  Cat in the Hat says \"Hello\".\n";
	cout << "  Thing1 makes mischief.\n";
	cout << "  Thing2 makes mischief.\n";
	cout << "  Boy has fun.\n";
	cout << "  Girl has fun.\n";
	cout << endl;

	cout << "  Thing2 leaves.\n";
	cout << "  Cat in the Hat says \"let's play\".\n";
	cout << "  Thing1 makes mischief.\n";
	cout << "  Boy has fun.\n";
	cout << "  Girl has fun.\n";
	cout << endl;

	cout << "  Cat in the Hat says \"rock & roll\".\n";
	cout << "  Thing1 makes mischief.\n";
	cout << "  Boy has fun.\n";
	cout << "  Girl has fun.\n";
	cout << "  Fish complains.\n";
	cout << endl;

	cout << "  Thing1 leaves.\n";
	cout << "  Cat in the Hat says \"Goodbye\".\n";
	cout << "  Mom returns.\n";
	cout << endl;
}

void demo() {
	Subject catInTheHat;

	catInTheHat.runSim();
}

}

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
	cout << "  Observers left to notify (should be zero) = ";
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

void makeMischief() { // Deprecated prototype for notification simulation.
	cout << "  Thing1 makes mischief.\n";
	cout << "  Thing2 makes mischief.\n";
	cout << "  Boy has fun.\n";
	cout << "  Girl has fun.\n";

	cout << "  Thing2 leaves.\n";
	cout << "  Thing1 makes mischief.\n";
	cout << "  Boy has fun.\n";
	cout << "  Girl has fun.\n";

	cout << "  Thing1 makes mischief.\n";
	cout << "  Boy has fun.\n";
	cout << "  Girl has fun.\n";
	cout << "  Red fish complains.\n";
	cout << "  Blue fish complains.\n";

	cout << "  Thing1 leaves.\n";
}

/* Consider the Dr. Seuss children's story, "The Cat in the Hat."
 * Whenever the cat in the hat does something, the things, children & fish should respond.
 * In the below procedural approach, the Subject class (the cat in the hat) has to know
 * about all the other classes. When they get changed, Subject has to be recompiled.
 * In addition, Subject is managing multiple objects, of multiple classes, with multiple
 * interfaces, which leads to long, hard to follow code.
 * Use the Observer pattern to decouple the Subject class from the others.
 */

namespace ripples {

class Thing {
	string name;
public:
	Thing(string name) : name(name) {}
	~Thing() { cout << "  Thing" << name << " leaves.\n"; }
public:
	void makesMischief() { cout << "  Thing" << name << " makes mischief.\n"; }
};

class Fish {
	string color;
public:
	Fish(string color) : color(color) {}
	~Fish() { cout << "  ~Fish(" << color << ").\n"; }
public:
	void complains() { cout << "  " << color << " fish complains.\n"; }
};

class Child {
	string gender;
public:
	Child(string gender) : gender(gender) {}
	~Child() { cout << "  ~Child(" << gender << ").\n"; }
public:
	void hasFun() { cout << "  " << gender << " has fun.\n"; }
};

class Subject {
	Thing*	thing1;
	Thing*	thing2;
	Fish*	redFish;
	Fish*	blueFish;
	Child*	boy;
	Child*	girl;
	// Dependency: Subject must know about all kinds of objects.
public:
	Subject() :
		thing1(new Thing("1")), thing2(new Thing("2")),
		redFish(new Fish("Red")), blueFish(new Fish("Blue")),
		boy(new Child("Boy")), girl(new Child("Girl")) {	// Dependency: ditto.
	}
	~Subject() {
		cout << "  Cat in the hat left: ~Subject.\n";
		cout << endl;
	}
public:
	void runSim() {
		// Event 1.
		thing1->makesMischief();
		thing2->makesMischief();
		boy->hasFun();
		girl->hasFun();
		cout << endl;

		// Event 2.
		delete thing2;
		thing1->makesMischief();
		boy->hasFun();
		girl->hasFun();
		cout << endl;

		// Event 3.
		thing1->makesMischief();
		boy->hasFun();
		girl->hasFun();
		redFish->complains();
		blueFish->complains();
		delete thing1;
		cout << endl;

		// Cleanup.
		delete blueFish;
		delete redFish;
		delete girl;
		delete boy;
	}
};

void demo() {
	cout << "<< Observer ripples >>\n";

	Subject catInTheHat;

	catInTheHat.runSim();
}

}

namespace observer {

class Observer;
class Subject;

class Subject {
	list<Observer*>	observers;
public:
	~Subject();
public:
	void attach(Observer* obs) { observers.push_back(obs); }
	void detach(Observer* obs) { observers.remove(obs); }
	void notify(const string& catSays="\n");
//	void getState() {}
//	void setState() {}
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
	string color;
public:
	Fish(string color, Subject& subject) : Observer(subject), color(color) {}
	~Fish() { cout << "  ~Fish(" << color << "):"; }
public:
	void update(Subject* subject) {
		cout << "  " << color << " fish complains.\n";
	}
};
class Child : public Observer {
	string gender;
public:
	Child(string gender, Subject& subject) : Observer(subject), gender(gender) {}
	~Child() { cout << "  ~Child(" << gender << "):"; }
public:
	void update(Subject* subject) {
		cout << "  " << gender << " has fun.\n";
	}
};

void Subject::notify(const string& catSays) {
	cout << "  Cat in the Hat says " << catSays << ".\n";
	list<Observer*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++) {
		(*it)->update();
	}
	cout << endl;
}
Subject::~Subject() {
	cout << "  Observers left to notify (should be zero) = " << observers.size() << ".\n";
	cout << "  Cat in the hat left: ~Subject.\n";
	cout << endl;
}

void demo_deprecated() {
	cout << "<< Observer solution >>\n";

	Subject catInTheHat;

	Thing thing1("1", catInTheHat);
	Child boy("Boy", catInTheHat);
	Child girl("Girl", catInTheHat);
	{
		Thing thing2("2", catInTheHat);

		catInTheHat.notify();
	}
	catInTheHat.notify();

	Fish redFish("Red", catInTheHat);
	Fish blueFish("Blue", catInTheHat);
	catInTheHat.notify();
}

void demo() {
	cout << "<< Observer solution >>\n";

	Subject catInTheHat;

	// Event 1.
	Observer* thing1 = new Thing("1", catInTheHat);
	Observer* thing2 = new Thing("2", catInTheHat);
	Child boy("Boy", catInTheHat);
	Child girl("Girl", catInTheHat);
	catInTheHat.notify("Hello");

	// Event 2.
	delete thing2;
	catInTheHat.notify("let's play");

	// Event 3.
	Fish redFish("Red", catInTheHat);
	Fish blueFish("Blue", catInTheHat);
	catInTheHat.notify("rock & roll");

	// Cleanup.
	delete thing1;
}

}

#endif /* OBSERVER_H_ */
