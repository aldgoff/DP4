/*
 * principles.h
 *
 *  Created on: Jun 14, 2014
 *      Author: aldgoff
 */

#ifndef PRINCIPLES_H_
#define PRINCIPLES_H_

// Find what varies and encapsulate it.
// Encapsulate generally means a base class and an extensible set of derived classes.

class Base {};
class Derived1 : public Base {};
class Derived2 : public Base {};
// ...

namespace principles {

/* Summary
 * Have one virtual function, ideally operator().
 * Use polymorphically.
 * A User class will assign the right algorithm to its internal strategy pointer.
 * The User class dtor needs to delete the strategy unless using a smart pointer.
 */

class Strategy {
public:
	virtual ~Strategy() { cout << "~Strategy\n"; }
public:
	virtual void f()=0;
	virtual void operator()()=0;
};
class Strategy1 : public Strategy {
public:
	void f() {}
	void operator()() { cout << "Strategy1\n"; }
};
class Strategy2 : public Strategy {
public:
	void f() {}
	void operator()() { cout << "Strategy2\n"; }
};

class User {
	Strategy* strategy;
public:
	User(Strategy* strategy) : strategy(strategy) {}
	~User() { delete strategy; }
public:
	void run() {
		(*strategy)();
	}
};

class Strat1Base { public: virtual void operator()() {} virtual ~Strat1Base() {} };
class Strat1Algor1 : public Strat1Base { void operator()() {} };
class Strat1Algor2 : public Strat1Base { void operator()() {} };
// Seam point 1D...
class Strat1AlgorM : public Strat1Base { void operator()() {} };

class Strat2Base { public: virtual void operator()() {} virtual ~Strat2Base() {} };
class Strat2Algor1 : public Strat2Base { void operator()() {} };
class Strat2Algor2 : public Strat2Base { void operator()() {} };
// Seam point 1D...
class Strat2AlgorL : public Strat2Base { void operator()() {} };

class Strat3Base { public: virtual void operator()() {} virtual ~Strat3Base() {} };
class Strat3Algor1 : public Strat3Base { void operator()() {} };
class Strat3Algor2 : public Strat3Base { void operator()() {} };
// Seam point 1D...
class Strat3AlgorK : public Strat3Base { void operator()() {} };

// Seam point 2D...
class StratNBase { public: virtual void operator()() {} virtual ~StratNBase() {} };
class StratNAlgor1 : public StratNBase { void operator()() {} };
class StratNAlgor2 : public StratNBase { void operator()() {} };
// Seam point 1D...
class StratNAlgorJ : public StratNBase { void operator()() {} };


class Scaling { // A user class that want's to avoid quadratic scaling of the source code.
	Strat1Base* stratImp1;
	Strat2Base* stratImp2;
	Strat3Base* stratImp3;
	// Seam point 2D...
	StratNBase* stratImpN;
public:
	Scaling(
			Strat1Base* stratImp1,
			Strat2Base* stratImp2,
			Strat3Base* stratImp3,
			// Seam point 2D...
			StratNBase* stratImpN
		) :
		stratImp1(stratImp1),
		stratImp2(stratImp2),
		stratImp3(stratImp3),
		// Seam point 2D...
		stratImpN(stratImpN)
	{}
	~Scaling() {
		delete stratImp1;
		delete stratImp2;
		delete stratImp3;
		// Seam point 2D...
		delete stratImpN;
	}
public:
	void run() {
		(*stratImp1)();
		(*stratImp2)();
		(*stratImp3)();
		// Seam point 2D...
		(*stratImpN)();
	}
};

void demo() {
	Strategy* strategies[] = { new Strategy1, new Strategy2 };
	for(size_t i=0; i<sizeof(strategies)/sizeof(Strategy*); i++) {
		(*strategies[i])();
		strategies[i]->f();
	}
	for(size_t i=0; i<sizeof(strategies)/sizeof(Strategy*); i++) {
		delete strategies[i];
	}
	cout << endl;

	{
		Strategy1 strat1;
		Strategy2 strat2;
		Strategy* strat = &strat1;
		(*strat)();
		strat->f();
		strat2();
	}
	cout << endl;

	User sam(new Strategy1);
	User iam(new Strategy2);

	sam.run();
	iam.run();
}

}

#endif /* PRINCIPLES_H_ */
