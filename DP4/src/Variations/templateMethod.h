/*
 * templateMethod.h
 *
 * Desc: Define the skeleton of an algorithm.
 *
 * Category: Behavioral
 *
 *  Created on: Feb 20, 2015
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Template_Method
 *  	http://www.dofactory.com/net/template-method-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter19
 *  	http://sourcemaking.com/design_patterns/template_method
 */

#ifndef TEMPLATEMETHOD_VARIATIONS_H_
#define TEMPLATEMETHOD_VARIATIONS_H_

namespace template_method_variation_strategy {

/* Question: should the differing steps be implemented as Strategy patterns
 * or by direct extension of the TemplateMethod class?
 *
 * In the code below, steps 1 through 4 are the legacy features.
 * Step 3 was the one that could differ.
 * The run method executes the code that extended the TemplateMethod class.
 * The calc method executes the code that extended via the Strategy pattern.
 *
 * The new spec is to add step 5 which can vary.
 * If it depends on the same domain as step 3, either extension works.
 * However, if it doesn't, extending the TemplateMethod class scales
 * quadratically (not shown), but the Strategy pattern scales linearly.
 *
 * There are 4 demo routines...
 *  demo_TM_Hierarchy - shows run() (extension of TemplateMethod with new spec).
 *  demo_Strat1Hierarchy - shows calc() (extension by Strategy - Stat1 class).
 *  demo_Strat2Hierarchy - shows calc() (addition of step 5 - Stat2 class).
 *  demo_Strat2IndependentDomains - shows calc() (independent domains).
 *
 * We should return to this after covering the Bridge design pattern.
 *
 * The example properly manages memory.
 */

class Strat1 {	// Extending by Strategy pattern.
public: virtual ~Strat1() { cout << " ** Strat1 dtor\n"; }
public:
	virtual void step3()=0;
};
class This_Way : public Strat1 {
public: ~This_Way() { cout << "** This_Way dtor\n"; }
public:
	void step3() { cout << "    This_Way3.\n"; }
};
class That_Way : public Strat1 {
public: ~That_Way() { cout << "** That_Way dtor\n"; }
public:
	void step3() { cout << "    That_Way3.\n"; }
};
class Your_Way : public Strat1 {
public: ~Your_Way() { cout << "** Your_Way dtor\n"; }
public:
	void step3() { cout << "    Your_Way3.\n"; }
};
// Seam point 1 - add new step3 (follows SOLID).

class Strat2 {	// New spec.
public: virtual ~Strat2() { cout << " ** Strat2 dtor\n"; }
public:
	virtual void step5()=0;
};
class This_Last : public Strat2 {
public: ~This_Last() { cout << "** This_Last dtor\n"; }
public:
	void step5() { cout << "      This_Last5.\n"; }
};
class That_Last : public Strat2 {
public: ~That_Last() { cout << "** That_Last dtor\n"; }
public:
	void step5() { cout << "      That_Last5.\n"; }
};
class Your_Last : public Strat2 {
public: ~Your_Last() { cout << "** Your_Last dtor\n"; }
public:
	void step5() { cout << "      Your_Last5.\n"; }
};
// Seam point 1 - add new step5 (follows SOLID).

class TemplateMethod {
// To extend TemplateMethod this way
// allows each diff step to depend on different domains.
	Strat1* diffStep;
	Strat2* lastStep;
public:
	virtual ~TemplateMethod() {
		delete diffStep;
		delete lastStep;
		cout << "  ** TM dtor\n";
	}
//	TemplateMethod(Strat1* diffStep) : diffStep(diffStep) {}
	TemplateMethod(Strat1* diffStep, Strat2* lastStep=0)
	: diffStep(diffStep), lastStep(lastStep) {}
public:
	void run() {	// Use TemplateMethod hierarchy.
		step1();
		step2();
		step3();	// Steps which differ (3,5) must
		step4();
		step5();	// depend on same domain.
	}
	void calc() {	// Use Strategy hierarchies.
		step1();
		step2();
		diffStep ? diffStep->step3() : step3();	// Steps which differ (3,5) can
		step4();
		lastStep ? lastStep->step5() : step5();	// depend on different domains.
	}
protected:
	void step1() { cout << "  Step1.\n"; }
	void step2() { cout << "   Step2.\n"; }
	virtual void step3() { cout << "    Diff3.\n"; }
	void step4() { cout << "     Step4.\n"; }
	virtual void step5() { cout << "      Default5.\n"; }
};
// To extend TemplateMethod this way
// requires all diff steps to depend on same domain.
class ThisWay : public TemplateMethod {
public: ~ThisWay() { cout << " ** This dtor\n"; }
public:
	ThisWay(Strat1* diffStep=0) : TemplateMethod(diffStep) {}
public:
	void step3() { cout << "    ThisWay3.\n"; }
	void step5() { cout << "      ThisLast5.\n"; }
};
class ThatWay : public TemplateMethod {
public: ~ThatWay() { cout << " ** That dtor\n"; }
public:
	ThatWay(Strat1* diffStep=0) : TemplateMethod(diffStep) {}
public:
	void step3() { cout << "    ThatWay3.\n"; }
	void step5() { cout << "      ThatLast5.\n"; }
};
class YourWay : public TemplateMethod {
public: ~YourWay() { cout << " ** Your dtor\n"; }
public:
	YourWay(Strat1* diffStep=0) : TemplateMethod(diffStep) {}
public:
	void step3() { cout << "    YourWay3.\n"; }
	void step5() { cout << "      YourLast5.\n"; }
};
// Seam point 1 - add new step3 (follows SOLID).

void demo_TM_Hierarchy() {
	TemplateMethod* steps[] = {
		new ThisWay,
		new ThatWay,
		new YourWay,
	};
	for(size_t i=0; i<sizeof(steps)/sizeof(*steps); i++) {
		steps[i]->run();
	}
	for(size_t i=0; i<sizeof(steps)/sizeof(*steps); i++) {
		delete steps[i];
	}
}

void demo_Strat1Hierarchy() {
	TemplateMethod strats[] = {
		TemplateMethod(new This_Way),
		TemplateMethod(new That_Way),
		TemplateMethod(new Your_Way),
	};
	for(size_t i=0; i<sizeof(strats)/sizeof(*strats); i++) {
		strats[i].calc();
	}
}

void demo_Strat2Hierarchy() {
	TemplateMethod strats[] = {
		TemplateMethod(new This_Way, new This_Last),
		TemplateMethod(new That_Way, new That_Last),
		TemplateMethod(new Your_Way, new Your_Last),
	};
	for(size_t i=0; i<sizeof(strats)/sizeof(*strats); i++) {
		strats[i].calc();
	}
}

void demo_Strat2IndependentDomains() {
	TemplateMethod strats[] = {
		TemplateMethod(new This_Way, new This_Last),
		TemplateMethod(new This_Way, new That_Last),
		TemplateMethod(new This_Way, new Your_Last),
		TemplateMethod(new That_Way, new This_Last),
		TemplateMethod(new That_Way, new That_Last),
		TemplateMethod(new That_Way, new Your_Last),
		TemplateMethod(new Your_Way, new This_Last),
		TemplateMethod(new Your_Way, new That_Last),
		TemplateMethod(new Your_Way, new Your_Last),
	};
	for(size_t i=0; i<sizeof(strats)/sizeof(*strats); i++) {
		strats[i].calc();
	}
}

void demo() {
	demo_TM_Hierarchy();	// Extend TemplateMethod class directly.
	cout << endl;

	demo_Strat1Hierarchy();	// Extend via Strategy pattern.
	cout << endl;

	demo_Strat2Hierarchy();	// Ditto, but for new spec (step 5).
	cout << endl;

	demo_Strat2IndependentDomains();	// Requires extension via Strategy.
	cout << endl;
}

}

#endif /* TEMPLATEMETHOD_VARIATIONS_H_ */
