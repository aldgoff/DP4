/*
 * meta.h
 *
 *  Created on: Oct 18, 2014
 *      Author: aldgoff
 *
 * Desc: Apply principles of DP's to the class code.
 * 		 In particular, shouldn't have to add code in 5 places
 * 		 for each new design pattern - really? I'm teaching this stuff?!?
 */

#ifndef META_H_
#define META_H_

#define COUNT(x) (sizeof(x)/sizeof(*x))

class DesignPattern {
public:
	string	name;
public:
	DesignPattern(string nameArg="DesPat") : name(nameArg) {
		char lowercase = name[0] - ('A'-'a');
		name[0] = lowercase;
	}
	virtual ~DesignPattern() {}
public:
	virtual void run(int i) {	// Example of the Template Method design pattern.
		cout << i+1 << ") ";	legacy();
		cout << i+1 << ") ";	problem();
		cout << i+1 << ") ";	solution();
	}
	virtual void legacy() {
		cout << "<< " << name << " legacy >>\n";
	}
	virtual void skeleton() {
		cout << "<< " << name << " skeleton >>\n";
	}
	virtual void problem() {
		cout << "<< " << name << " problem >>\n";
	}
	virtual void solution() {
		cout << "<< " << name << " solution >>\n";
	}
	virtual void legacy(int i) {
		cout << i+1 << ") " << "<< " << name << " legacy >>\n";
	}
	virtual void skeleton(int i) {
		cout << i+1 << ") " << "<< " << name << " skeleton >>\n";
	}
	virtual void problem(int i) {
		cout << i+1 << ") " << "<< " << name << " problem >>\n";
	}
	virtual void solution(int i) {
		cout << i+1 << ") " << "<< " << name << " solution >>\n";
	}
};
class Strategy : public DesignPattern {
	enum Option {
		ORIG,
		LECTURES,
		HOMEWORK,
	};
public:
	Strategy() : DesignPattern("Strategy") {}
public:
	void run(int i) {	// Example of the Template Method design pattern.
		Option choice = HOMEWORK;
		switch(choice) {
		case ORIG:
			cout << i+1 << ") ";	legacy();
			cout << i+1 << ") ";	problem();
			cout << i+1 << ") ";	solution();
			break;
		case LECTURES:
			DesignPattern::legacy(i);	lectures::strategy_legacy::demo();
			DesignPattern::skeleton(i);	lectures::strategy_skeleton::demo();
			DesignPattern::problem(i);	lectures::strategy_problem::demo();
			DesignPattern::solution(i);	lectures::strategy_solution::demo();
			break;
		case HOMEWORK:
			DesignPattern::legacy(i);	homework::strategy_legacy::demo();
//			DesignPattern::skeleton(i);	homework::strategy_skeleton::demo();
			DesignPattern::problem(i);	homework::strategy_problem::demo();
			DesignPattern::solution(i);	homework::strategy_solution::demo();
			break;
		}
	}
	void legacy() {
		DesignPattern::legacy();
		strategy_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		strategy_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		strategy_solution::demo();
	}
};
class Adapter : public DesignPattern {
public:
	Adapter() : DesignPattern("Adapter") {}
public:
	void run(int i) {	// Example of the Template Method design pattern.
		cout << i+1 << ") ";	legacy();
		cout << i+1 << ") ";	problem();
		cout << i+1 << ") ";	solution();
		cout << i+1 << ") ";
		cout << "<< " << name << " problem production >>\n";
		adapter_problem_production::demo();
		cout << i+1 << ") ";
		cout << "<< " << name << " solution production >>\n";
		adapter_solution_production::demo();
	}
	void legacy() {
		DesignPattern::legacy();
		adapter_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		adapter_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		adapter_solution::demo();
	}
};
class Facade : public DesignPattern {
public:
	Facade() : DesignPattern("Facade") {}
public:
	void legacy() {
		DesignPattern::legacy();
		facade_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		facade_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		facade_solution::demo();
	}
};
class TemplateMethod : public DesignPattern {
public:
	TemplateMethod() : DesignPattern("TemplateMethod") {}
public:
	void legacy() {
		DesignPattern::legacy();
		template_method_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		template_method_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		template_method_solution::demo();
	}
};
class FactoryMethod : public DesignPattern {
public:
	FactoryMethod() : DesignPattern("FactoryMethod") {}
public:
	void legacy() {
		DesignPattern::legacy();
		factory_method_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		factory_method_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		factory_method_solution::demo();
	}
};
class Decorator : public DesignPattern {
public:
	Decorator() : DesignPattern("Decorator") {}
public:
	void legacy() {
		DesignPattern::legacy();
		decorator_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		decorator_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		decorator_solution::demo();
	}
};
class Observer : public DesignPattern {
public:
	Observer() : DesignPattern("Observer") {}
public:
	void legacy() {
		DesignPattern::legacy();
		observer_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		observer_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		observer_solution::demo();
	}
};
class ChainOfResponsibility : public DesignPattern {
public:
	ChainOfResponsibility() : DesignPattern("ChainOfResponsibility") {}
public:
	void legacy() {
		DesignPattern::legacy();
		chain_of_resp_legacy::demo();
	}
	void problem() {
		DesignPattern::problem();
		chain_of_resp_problem::demo();
	}
	void solution() {
		DesignPattern::solution();
		chain_of_resp_solution::demo();
	}
};

class Bridge : public DesignPattern {
public:
	Bridge() : DesignPattern("Bridge") {}
public:
	void problem() {
		DesignPattern::problem();
		cout << "    details...\n";
	}
	void solution() {
		DesignPattern::solution();
		cout << "    details...\n";
	}
};
class AbstractFactory : public DesignPattern {
public:
	AbstractFactory() : DesignPattern("AbstractFactory") {}
};
class Singleton : public DesignPattern {
public:
	Singleton() : DesignPattern("Singleton") {}
};
class Composite : public DesignPattern {
public:
	Composite() : DesignPattern("Composite") {}
};
class Iterator : public DesignPattern {
public:
	Iterator() : DesignPattern("Iterator") {}
};
class Visitor : public DesignPattern {
public:
	Visitor() : DesignPattern("Visitor") {}
};
class Command : public DesignPattern {
public:
	Command() : DesignPattern("Command") {}
};
class DesPats : public DesignPattern {
public:
	DesPats() : DesignPattern("DesPats") {}
};
// Seam point.
/*
 *
midterm
varies
solti
sideBySide

 */
void meta(const string& arg) {
	// Array and loop is O(n), inefficient if desPats is large.
	// Map would be better, hash dispatch, but if n ~ 20, no big deal.
	DesignPattern* desPats[] = {
		new Strategy,
		new Adapter,
		new Facade,
		new TemplateMethod,
		new FactoryMethod,
		new Decorator,
		new Observer,
		new ChainOfResponsibility,

		new Bridge,
		new AbstractFactory,
		new Singleton,
		new Composite,
		new Iterator,
		new Visitor,
		new Command,
		new DesPats,
		// Seam point.
	};

	if(arg == "") {	// Auto generate to avoid 2 more seam points.
		for(size_t i=0; i<COUNT(desPats); i++) {	// List for Run Configurations...
			cout << desPats[i]->name << endl;
		}
		cout << "skeletons\n";

		cout << endl;
		for(size_t i=0; i<COUNT(desPats); i++) {	// Include list (#include "desPat.h").
			cout << "#include \"" << desPats[i]->name << ".h\"\n";
		}
		cout << endl;
	}

	for(size_t i=0; i<COUNT(desPats); i++) {
		if(arg == desPats[i]->name) {
			desPats[i]->run(i);
//			cout << "\n";
			break;
		}
	}
}

#endif /* META_H_ */
