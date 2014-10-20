#include "sideBySide.h"

namespace side_by_side {
class Observer;
class Subject {
	list<Observer*> observers;
public:
	void attach(Observer* obs) { observers.push_back(obs); }
	void notify();
};
class Observer {		// If the observers are varying...
protected:
	Subject* subject;
public:	virtual ~Observer() {}
public:
	virtual void update() {}
	void link(Subject* _subject) {
		subject = _subject;
		cout << "  Attached an observer to subject\n";
	}
};
void Subject::notify() {
	list<Observer*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++)
		(*it)->update();
}
class Observer1 : public Observer {

public:
	void update() { cout << "  Observer1 updated\n"; }



};
class Observer2 : public Observer {

public:
	void update() { cout << "  Observer2 updated\n"; }



};
class Observer3 : public Observer {

public:
	void update() { cout << "  Observer3 updated\n"; }



};









void clientObserver() {
	Subject* subject = new Subject;
	Observer* dp[] = { new Observer1, new Observer2, new Observer3};
	for(size_t i=0; i<COUNT(dp); i++) {
		subject->attach(dp[i]);
		dp[i]->link(subject);
	}
	subject->notify();
	cout << endl;
}

}
