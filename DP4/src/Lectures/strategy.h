/*
 * strategy.h
 *
 *  Created on: Feb 13, 2015
 *      Author: adgoff
 *
 * Desc: Define a family of interchangeable algorithms which can vary independently from the clients.
 *
 * Varies: If the algorithms are varying...
 *
 * Category: Behavioral
 *
 * URLs:
 *   http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Strategy
 *   http://www.dofactory.com/net/strategy-design-pattern
 *   http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter9
 *   http://sourcemaking.com/design_patterns/strategy
 */


#ifndef LECTURES_STRATEGY_H_
#define LECTURES_STRATEGY_H_

namespace lectures {

namespace strategy_common {

enum Domain {		// The domain (x)
	ONE,
	TWO,
	THREE,
	// Seam point 1 - insert another alternative.
};

}

namespace strategy_legacy {

using namespace strategy_common;

void run1() {				// The range (y).
	cout << "  run 1.\n";
}
void run2() {
	cout << "  run 2.\n";
}
void run3() {
	cout << "  run 3.\n";
}
// Seam point 2 - add another alternative.

void clientCode(Domain alt) {	// Client code maps from domain to range.
	switch(alt) {
	case ONE:
		run1();
		break;
	case TWO:
		run2();
		break;
	case THREE:
		run3();
		break;
	// Seam point 3 - insert another alternative.
	default:
	throw "OOPS";		// Requires error handling.
	break;
	}
}

void demo() {
	Domain alts[] = { ONE, TWO, THREE };
	for(size_t i=0; i<sizeof(alts)/sizeof(*alts); i++) {
		clientCode(alts[i]);
	}

	cout << endl;
}

}

namespace strategy_skeleton {

class Strategy {		// If the algorithms are varying...
public:	virtual ~Strategy() {}
public:
	virtual void run() {}
};
class Algorithm1 : public Strategy {
public:
	void run() { cout << "  Algorithm 1.\n"; }
};
class Algorithm2 : public Strategy {
public:
	void run() { cout << "  Algorithm 2.\n"; }
};
class Algorithm3 : public Strategy {
public:
	void run() { cout << "  Algorithm 3.\n"; }
};
// Seam point 2 - add another alternative.

void clientCode(Strategy* strategy) {
	strategy->run();
}

void demo() {	// Masks the domain to range mapping.
	Strategy* algorithms[] = { new Algorithm1, new Algorithm2, new Algorithm3 };
	for(size_t i=0; i<sizeof(algorithms)/sizeof(*algorithms); i++) {
		clientCode(algorithms[i]);
	}

	cout << endl;
}

}

namespace strategy_problem {

using namespace strategy_common;

void run1()		{ cout << "  run 1.\n"; }		// Range y.
void run2()		{ cout << "  run 2.\n"; }
void run3()		{ cout << "  run 3.\n"; }
void calc1()	{ cout << "   calc 1.\n"; }		// Range z.
void calc2()	{ cout << "   calc 2.\n"; }
void calc3()	{ cout << "   calc 3.\n"; }
void compute1()	{ cout << "    compute 1.\n"; }	// Range w.
void compute2()	{ cout << "    compute 2.\n"; }
void compute3()	{ cout << "    compute 3.\n"; }
// Seam point 2 - add another alternative.

void clientCodeRun(Domain alt) {	// Client code maps domain to range y.
	switch(alt) {
	case ONE:	run1();	break;
	case TWO:	run2();	break;
	case THREE:	run3();	break;
	// Seam point 3 - insert another alternative.
	default: throw "OOPS"; break;	// Requires error handling.
	}
}
void clientCodeCalc(Domain alt) {	// Client code maps domain to range z.
	switch(alt) {
	case ONE:	calc1();	break;
	case TWO:	calc2();	break;
	case THREE:	calc3();	break;
	// Seam point 4 - insert another alternative.
	default: throw "OOPS"; break;	// Requires error handling.
	}
}
void clientCodeCompute(Domain alt) {	// Client code maps domain to range w.
	switch(alt) {
	case ONE:	compute1();	break;
	case TWO:	compute2();	break;
	case THREE:	compute3();	break;
	// Seam point 5 - insert another alternative.
	default: throw "OOPS"; break;	// Requires error handling.
	}
}

void demo() {
	Domain alts[] = { ONE, TWO, THREE };
	for(size_t i=0; i<sizeof(alts)/sizeof(*alts); i++) {
		clientCodeRun(alts[i]);
		clientCodeCalc(alts[i]);
		clientCodeCompute(alts[i]);
	}

	cout << endl;
}

}

namespace strategy_solution {

using namespace strategy_common;

class Strategy {		// If the algorithms are varying...
public:	virtual ~Strategy() {}
public:
	virtual void run() { cout << "  Strategy base run().\n"; }
	virtual void calc() { cout << "  Strategy base calc().\n"; }
	virtual void compute() { cout << "  Strategy base compute().\n"; }
};
class Algorithm1 : public Strategy {
public:
	void run() { cout << "  Algorithm 1 run().\n"; }
	void calc() { cout << "   Algorithm 1 calc().\n"; }
	void compute() { cout << "    Algorithm 1 compute().\n"; }
};
class Algorithm2 : public Strategy {
public:
	void run() { cout << "  Algorithm 2 run().\n"; }
	void calc() { cout << "   Algorithm 2 calc().\n"; }
	void compute() { cout << "    Algorithm 2 compute().\n"; }
};
class Algorithm3 : public Strategy {
public:
	void run() { cout << "  Algorithm 3 run().\n"; }
	void calc() { cout << "   Algorithm 3 calc().\n"; }
	void compute() { cout << "    Algorithm 3 compute().\n"; }
};
// Seam point 2 - add another alternative.

class Alternative {
public:
	Strategy*	strategy;
public:
	Alternative(Strategy* strategy) : strategy(strategy) {}
};

Alternative mappingCode(Domain alt) {
	switch(alt) {
	case ONE:	return Alternative(new Algorithm1);	break;
	case TWO:	return Alternative(new Algorithm2);	break;
	case THREE:	return Alternative(new Algorithm3);	break;
	// Seam point 3 - insert another alternative.
	default: throw "OOPS"; break;	// Requires error handling.
	}
}

void clientCodeRun(Strategy* strategy) {
	strategy->run();
}
void clientCodeCalc(Strategy* strategy) {
	strategy->calc();
}
void clientCodeCompute(Strategy* strategy) {
	strategy->compute();
}

void demo() {
	Domain alts[] = { ONE, TWO, THREE };
	for(size_t i=0; i<sizeof(alts)/sizeof(*alts); i++) {
		Alternative domain = mappingCode(alts[i]);
		clientCodeRun(domain.strategy);
		clientCodeCalc(domain.strategy);
		clientCodeCompute(domain.strategy);
	}

	cout << endl;
}

}

}

#endif
