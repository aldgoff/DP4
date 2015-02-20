/*
 * templateMethod.h
 *
 * Desc: Define the skeleton of an algorithm.
 *
 * Category: Behavioral
 *
 *  Created on: May 10, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Template_Method
 *  	http://www.dofactory.com/net/template-method-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter19
 *  	http://sourcemaking.com/design_patterns/template_method
 */

#ifndef TEMPLATEMETHOD_H_
#define TEMPLATEMETHOD_H_

namespace home_work {

/* Consider a 6 step process as implied by the legacy namespace below.
 * Optimization is the only difference between the processes.
 * Consider new specs (ala problem namespace below):
 * 	 Two more processes with different optimizations, critical and npc.
 *   For both of these the cleanup step must be better and different.
 * Refactor using the Template Method design pattern.
 */

namespace template_method_common {

bool morning() { return true; }

void fast() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  Fast optimized\n";
	cout << "  usual cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

void economic() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  Economic optimized\n";
	cout << "  usual cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

}

namespace template_method_new_specs {

using namespace template_method_common;

void critical() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  Critical optimized\n";
	cout << "  meticulous cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

void npc() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  NPC optimized\n";
	cout << "  meticulous cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

}

namespace template_method_solution {

using namespace template_method_common;

class TemplateMethod {
public: virtual ~TemplateMethod() {}
public:
	void run() {	// A 6 step process.
		setup();		// Most steps the same.
		schedule();
		if(morning())
			highHeat();
		else
			lowHeat();
		optimize();		// Must differ.
		cleanup();		// May differ.
		putaway();
		cout << endl;
	}
private:
	void setup()    { cout << "  setup\n"; }	// Same steps.
	void schedule() { cout << "  schedule\n"; }
	void highHeat() { cout << "  highHeat\n"; }
	void lowHeat()  { cout << "  lowHeat\n"; }
protected:
	virtual void optimize()=0;	// Subclasses must supply.
	virtual void cleanup() { cout << "  usual cleanup\n"; }	// Default behavior.
private:
	void putaway() { cout << "  putaway\n"; }	// Same steps.
};
class Fast : public TemplateMethod {
public:
	void optimize() { cout << "  Fast optimized\n"; }
};
class Economic : public TemplateMethod {
public:
	void optimize() { cout << "  Economic optimized\n"; }
};
class Critical : public TemplateMethod {
public:
	void optimize() { cout << "  Critical optimized\n"; }
	void cleanup()  { cout << "  detailed cleanup\n"; }
};
class NPC : public TemplateMethod {
public:
	void optimize() { cout << "  NPC optimized\n"; }
	void cleanup()  { cout << "  meticulous cleanup\n"; }
};

void demo() {
	TemplateMethod* process[] = {new Fast, new Economic, new Critical, new NPC};
	for(size_t i=0; i<sizeof(process)/sizeof(*process); i++) {
		process[i]->run();
	}
}

}

}

#endif /* TEMPLATEMETHOD_H_ */
