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
	virtual void problem() {
		cout << "<< " << name << " problem >>\n";
	}
	virtual void solution() {
		cout << "<< " << name << " solution >>\n";
	}
};
class Strategy : public DesignPattern {
public:
	Strategy() : DesignPattern("Strategy") {}
public:
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
class Decorator : public DesignPattern {
public:
	Decorator() : DesignPattern("Decorator") {}
};
class Observer : public DesignPattern {
public:
	Observer() : DesignPattern("Observer") {}
};
class Singleton : public DesignPattern {
public:
	Singleton() : DesignPattern("Singleton") {}
};
class FactoryMethod : public DesignPattern {
public:
	FactoryMethod() : DesignPattern("FactoryMethod") {}
};
class Composite : public DesignPattern {
public:
	Composite() : DesignPattern("Composite") {}
};
class ChainOfResponsibility : public DesignPattern {
public:
	ChainOfResponsibility() : DesignPattern("ChainOfResponsibility") {}
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

		new Bridge,
		new AbstractFactory,
		new Decorator,
		new Observer,
		new Singleton,
		new FactoryMethod,
		new Composite,
		new ChainOfResponsibility,
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
