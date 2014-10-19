/*
 * singleton.h
 *
 * Desc: Insure only one instance of an object exists.
 *
 * Category: Creational
 *
 *  Created on: May 10, 2014
 *      Author: aldgoff
 *
 * URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Singleton
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace too_many {

/* Consider the requirement that there be only one instance of a class.
 * This could be because it implements an interface to a limited resource.
 * For this exercise the "resource" is a global variable (it's just an exercise).
 * Replace the OnlyOneOf class, which doesn't enforce the Singleton pattern,
 * with a class that does. What do you have to implement to prevent a
 * user from instantiating more than one instance of a Singleton class?
 */

static int resource = 0;

class OnlyOneOf { // Name implies only one instance, but does not enforce it.
public:
	OnlyOneOf() {
		cout << "  Construction happens on every call to ctor.\n";
	}
public:
	int accessFiniteResource(int id=-1) { // General accessor, combined getter/setter.
		if(id < 0)
			return resource;
		else {
			resource = id;
			return resource;
		}
	}
};

void demo() {
	cout << "<< Singleton problem >>\n";

	OnlyOneOf foo;	// Class constructors allow for multiple instances.
	OnlyOneOf bar;

	foo.accessFiniteResource(1);	// Different objects access the same resource.
	bar.accessFiniteResource(2);	// Last change set resource to 2.

	if(&foo == &bar)	cout << "  foo and bar are same object, expect 2 & 2.\n";
	else				cout << "  foo and bar are different objects, expect 1 & 2.\n";

	cout << "    foo = " << foo.accessFiniteResource() << "\n";
	cout << "    bar = " << bar.accessFiniteResource() << "\n";

	cout << endl;
}

}

namespace singleton {

static int resource = 0;

class Singleton {
private:			// Private constructors prohibit outside instantiation.
	Singleton() {
		cout << "  Construction of singleton only happens once.\n";
	}
	Singleton(const Singleton&);				  // Disallow copy ctor.
	const Singleton& operator=(const Singleton&); // Disallow assignment operator.
//	~Singleton() {}								  // Prevent deletion of the single instance.
public:
	static Singleton& instance() {	// Single, global point of access.
		static Singleton* instance = new Singleton;
		return *instance;
	}
public:
	int accessFiniteResource(int id=-1) { // General accessor, combined getter/setter.
		if(id < 0)
			return resource;
		else {
			resource = id;
			return resource;
		}
	}
};

void demo() {
	cout << "<< Singleton solution >>\n";

	Singleton& foo = Singleton::instance();	// Instance method controls instantiations.
	Singleton& bar = Singleton::instance();

	foo.accessFiniteResource(1);	// Now, foo & bar are same object.
	bar.accessFiniteResource(2);	// Last change set resource to 2.

	if(&foo == &bar)	cout << "  foo and bar are same object, expect 2 & 2.\n";
	else				cout << "  foo and bar are different objects, expect 1 & 2.\n";

	cout << "    foo = " << foo.accessFiniteResource() << "\n";
	cout << "    bar = " << bar.accessFiniteResource() << "\n";

	#ifdef CompilerComplains // Not easy to integrate into a unit test.
		Singleton	sam;							// ctor stack.
		Singleton*	iam = new Singleton();			// ctor heap.
		Singleton	dup(Singleton::instance());		// cctor.
		sam = *iam;									// op=.
	#else
		cout << "  Skipping code snippets prohibited by Singleton DP.\n";
	#endif
}

}

namespace inherting_singleton {

class Singleton {};
class JustOne : public Singleton {};
class OnlyOne : public Singleton {};
class LessThanTwo : public Singleton {};

}

namespace double_checked_locking_pattern {

void demo() {
	cout << "<< Double-Checked Locking Pattern solution >>\n";
}

}

namespace polyton {

void demo() {
	cout << "<< Polyton solution >>\n";
}

}

#endif /* SINGLETON_H_ */
