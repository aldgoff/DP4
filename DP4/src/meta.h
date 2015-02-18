/*
 * meta.h
 *
 *  Created on: Oct 18, 2014
 *      Author: aldgoff
 *
 * Desc: Apply principles of DP's to the class code.
 * 		 In particular, shouldn't have to add code in 5 places
 * 		 for each new design pattern - really? I'm teaching this stuff?!?
 *
 * Specs:
 *   1) Separate files for problems and solutions to upload to Inside Blue.
 *   2) All code runnable to confirm correctness.
 *   3) Minimal duplication.
 *   4) Experimental instances to explore phase space of implementations.
 *   5) Displayable in class with Eclipse IDE.
 *   6) Fit on single screen page.
 *   7) Apply design patterns to general layout and architecture.
 *   8) Support side by side comparisons.
 *   9) Support pairwise comparisons.
 *  10) Support skeletons.
 *  11) Collect features across design patterns for orthogonality.
 *  12) Snippets to PowerPoint lectures.
 *  13) High orthogonality between design patterns.
 *  14) Show temporal evolution of code.
 *  15) Unknown args should produce error message.
 *
 * Requirements:
 *   1) Folders:
 *   		Problems, Solutions
 *   	Namespaces:
 *   		problem, solution
 *  12) Folders:
 *  		Lectures
 *  	Namespace:
 *  		lectures
 *  	Sub namespaces <dp>_legacy/skeleton/problem/solution
 *  13) namespaces <dp>_legacy/skeleton/problem/solution
 *  14) namespaces <dp>_legacy/skeleton/problem/solution
 *   8) namespace side_by_side
 *   2) Args
 *   	<dp> ala strategy, adapter, facade, templateMethod, etc.
 *   	skeletons: runs all skeleton code
 *   	sideBySide: runs all side_by_side code
 *   	lectures:
 *   	legacies:
 *   	problems:
 *   	solutions:
 *   	experimentals:
 *   	lab1/2/3/4/5:
 *   	final
 */

/* Program control table
 * Pattern/Group   | Lectures | Problems | Solutions | Skeletons | SideBySide | Pairwise |
 * ----------------+----------+----------+-----------+-----------+------------+----------+
 * Strategy        |          | strategy | sstrategy | kstrategy | bystrategy | lab1     |
 * Adapter         |          | adapter  | sadapter  | kadapter  | byadapter  |          |
 * Facade          |          | facade   | sfacade   | kfacade   | byfacade   | lab2     |
 * TemplateMethod  |          | templateM| stemplateM| ktemplateM| bytemplateM|          |
 * FactoryMethod   |          | factoryMe| sfactoryMe| kfactoryMe| byfactoryMe| lab3     |
 * Decorator       |          | decorator| sdecorator| kdecorator| bydecorator|          |
 * Observer        |          | observer | sobserver | kobserver | byobserver | lab4     |
 * ChainOfResp     |          | chainOfRe| schainOfRe| kchainOfRe| bychainOfRe|          |
 * Bridge          |          | bridge   | sbridge   | kbridge   | bybridge   | lab5     |
 * AbstractFactory |          | abstractF| sabstractF| kabstractF| byabstractF|          |
 * ----------------+----------+----------+-----------+-----------+------------+----------+
 * Singleton       | c        | l/p      | s         | k         | by         |          |
 * Composite       | c        | l/p      | s         | k         | by         |          |
 * Iterator        | c        | l/p      | s         | k         | by         |          |
 * Visitor         | c        | l/p      | s         | k         | by         |          |
 * Command         | c        | l/p      | s         | k         | by         |          |
 * ----------------+----------+----------+-----------+-----------+------------+----------+
 * midterm         |          |          |           |           |            |          |
 * varies          |          |          |           |           |            |          |
 * principles      |          |          |           |           |            |          |
 * solti           |          |          |           |           |            |          |
 * whatVaries      |          |          |           |           |            |          |
 * virtualDtorBug  |          |          |           |           |            |          |
 * final           |          |          |           |           |            |          |
 */

#ifndef META_H_
#define META_H_

#define COUNT(x) (sizeof(x)/sizeof(*x))

/* Test args

strategy
adapter
facade
templateMethod
factoryMethod
decorator
observer
chainOfResponsibility
bridge
abstractFactory

lectures
legacies
problems
solutions
skeletons
sideBySide

lab1
lab2
lab3
lab4
lab5

final
...

cstrategy
lstrategy
pstrategy
sstrategy
kstrategy
bystrategy

cadapter
ladapter
padapter
sadapter
kadapter
byadapter

cfacade
lfacade
pfacade
sfacade
kfacade
byfacade

ctemplateMethod
ltemplateMethod
ptemplateMethod
stemplateMethod
ktemplateMethod
bytemplateMethod

cfactoryMethod
lfactoryMethod
pfactoryMethod
sfactoryMethod
kfactoryMethod
byfactoryMethod

cdecorator
ldecorator
pdecorator
sdecorator
kdecorator
bydecorator

cobserver
lobserver
pobserver
sobserver
kobserver
byobserver

cchainOfResponsibility
lchainOfResponsibility
pchainOfResponsibility
schainOfResponsibility
kchainOfResponsibility
bychainOfResponsibility

cbridge
lbridge
pbridge
sbridge
kbridge
bybridge

cabstractFactory
labstractFactory
pabstractFactory
sabstractFactory
kabstractFactory
byabstractFactory

 */

class DesignPattern {
public:
	string	name;
public:
	DesignPattern(string nameArg="DesPat") : name(nameArg) {
		char lowercase = name[0] - ('A'-'a');
		name[0] = lowercase;
	}
	virtual ~DesignPattern() {}
protected:
	void out(int i) { cout << i << ") "; }
public:
	virtual void run(int i) {	// Run homework example.
		legacy(i);
		problem(i);
		solution(i);
	}

	virtual void lecture(int i) {	// PowerPoint Class lecture.
		cout << i << ") " << "<< " << name << " lecture >>\n";
	}

	virtual void legacy(int i) {	// Legacy example.
		cout << i << ") " << "<< " << name << " legacy >>\n";
	}
	virtual void abstract(int i) {	// Abstract example.
		cout << i << ") " << "<< " << name << " abstract >>\n";
	}
	virtual void problem(int i) {	// Problem example.
		cout << i << ") " << "<< " << name << " problem >>\n";
	}
	virtual void solution(int i) {	// Solution example.
		cout << i << ") " << "<< " << name << " solution >>\n";
	}

	virtual void skeleton(int i) {	// Skeleton example.
		cout << i << ") " << "<< " << name << " skeleton >>\n";
	}
	virtual void sideBySide(int i) {// Side by side example.
		cout << i << ") " << "<< " << name << " sideBySide >>\n";
	}
	virtual void pairWise(int i) {	// Pair wise example.
		cout << i << ") " << "<< " << name << " pairWise >>\n";
	}
};
class Strategy : public DesignPattern {
public:
	Strategy() : DesignPattern("Strategy") {}
public:
	void lecture(int i) {	// PowerPoint Class lecture.
		DesignPattern::lecture(i);
		lecture::strategy_legacy::demo();
		lecture::strategy_abstract::demo();
		lecture::strategy_problem::demo();
		lecture::strategy_solution::demo();
	}
	void legacy(int i) {	// Legacy example.
		DesignPattern::legacy(i);
		homework::strategy_legacy::demo();
	}
	void problem(int i) {	// Problem example.
		DesignPattern::problem(i);
		homework::strategy_problem::demo();
	}
	void solution(int i) {	// Solution example.
		DesignPattern::solution(i);
		homework::strategy_solution::demo();
	}
	void skeleton(int i) {	// Skeleton example.
		DesignPattern::skeleton(i);
		skeleton::clientStrategy();
	}
	void sideBySide(int i) {// Side by side example.
		DesignPattern::sideBySide(i);
		side_by_side::clientStrategy();
	}
	void pairWise(int i) {	// Pair wise example.
		DesignPattern::pairWise(i);
		pair_wise::clientStrategy();
	}
};
class Adapter : public DesignPattern {
public:
	Adapter() : DesignPattern("Adapter") {}
public:
	void legacy(int i) {
		DesignPattern::legacy(i);
		adapter_legacy::demo();
	}
	void problem(int i) {
		DesignPattern::problem(i);
		adapter_problem::demo();
	}
	void solution(int i) {
		DesignPattern::solution(i);
		adapter_solution::demo();
	}
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientAdapter();
	}
	void sideBySide(int i) {
		DesignPattern::sideBySide(i);
		side_by_side::clientAdapter();
	}
	void pairWise(int i) {	// Pair wise example.
		DesignPattern::pairWise(i);
		pair_wise::clientAdapter();
	}
};
class Facade : public DesignPattern {
public:
	Facade() : DesignPattern("Facade") {}
public:
	void lecture(int i) {	// PowerPoint Class lecture.
		DesignPattern::lecture(i);
		lecture::facade_legacy::demo();
		lecture::facade_problem::demo();
		lecture::facade_solution::demo();
	}
	void legacy(int i) {	// Legacy example.
		DesignPattern::legacy(i);
		homework::facade_legacy::demo();
	}
	void problem(int i) {	// Problem example.
		DesignPattern::problem(i);
		homework::facade_problem::demo();
	}
	void solution(int i) {	// Solution example.
		DesignPattern::solution(i);
		homework::facade_solution::demo();
	}
	void skeleton(int i) {	// Skeleton example.
		DesignPattern::skeleton(i);
		skeleton::clientFacade();
	}
	void sideBySide(int i) {// Side by side example.
		DesignPattern::sideBySide(i);
		side_by_side::clientFacade();
	}
	void pairWise(int i) {	// Pair wise example.
		DesignPattern::pairWise(i);
		pair_wise::clientFacade();
	}
};
class TemplateMethod : public DesignPattern {
public:
	TemplateMethod() : DesignPattern("TemplateMethod") {}
public:
	void run(int i) {	// Run homework example.
		DesignPattern::legacy(i);
		experimental::template_method_legacy::demo();
		DesignPattern::problem(i);
		experimental::template_method_problem::demo();
		DesignPattern::problem(i);
		experimental::template_method_solution::demo();
	}
	void lecture(int i) {	// PowerPoint Class lecture.
		DesignPattern::lecture(i);
		lecture::template_method_legacy::demo();
		lecture::template_method_problem::demo();
		lecture::template_method_solution::demo();
	}
	void legacy(int i) {
		DesignPattern::legacy(i);
		homework::template_method_legacy::demo();
	}
	void problem(int i) {
		DesignPattern::problem(i);
		homework::template_method_problem::demo();
	}
	void solution(int i) {
		DesignPattern::solution(i);
		homework::template_method_solution::demo();
	}
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientTemplateMethod();
	}
	void sideBySide(int i) {
		DesignPattern::sideBySide(i);
		side_by_side::clientTemplateMethod();
	}
	void pairWise(int i) {	// Pair wise example.
		DesignPattern::pairWise(i);
		pair_wise::clientTemplateMethod();
	}
};
class FactoryMethod : public DesignPattern {
public:
	FactoryMethod() : DesignPattern("FactoryMethod") {}
public:
	void legacy(int i) {
		DesignPattern::legacy(i);
		factory_method_legacy::demo();
	}
	void problem(int i) {
		DesignPattern::problem(i);
		factory_method_problem::demo();
	}
	void solution(int i) {
		DesignPattern::solution(i);
		factory_method_solution::demo();
	}
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientFactoryMethod();
	}
	void sideBySide(int i) {
		DesignPattern::sideBySide(i);
		side_by_side::clientFactoryMethod();
	}
};
class Decorator : public DesignPattern {
public:
	Decorator() : DesignPattern("Decorator") {}
public:
	void legacy(int i) {
		DesignPattern::legacy(i);
		decorator_legacy::demo();
	}
	void problem(int i) {
		DesignPattern::problem(i);
		decorator_problem::demo();
	}
	void solution(int i) {
		DesignPattern::solution(i);
		decorator_solution::demo();
	}
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientDecorator();
	}
	void sideBySide(int i) {
		DesignPattern::sideBySide(i);
		side_by_side::clientDecorator();
	}
};
class Observer : public DesignPattern {
public:
	Observer() : DesignPattern("Observer") {}
public:
	void legacy(int i) {
		DesignPattern::legacy(i);
		observer_legacy::demo();
	}
	void problem(int i) {
		DesignPattern::problem(i);
		observer_problem::demo();
	}
	void solution(int i) {
		DesignPattern::solution(i);
		observer_solution::demo();
	}
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientObserver();
	}
	void sideBySide(int i) {
		DesignPattern::sideBySide(i);
		side_by_side::clientObserver();
	}
};
class ChainOfResponsibility : public DesignPattern {
public:
	ChainOfResponsibility() : DesignPattern("ChainOfResponsibility") {}
public:
	void legacy(int i) {
		DesignPattern::legacy(i);
		chain_of_resp_legacy::demo();
	}
	void problem(int i) {
		DesignPattern::problem(i);
		chain_of_resp_problem::demo();
	}
	void solution(int i) {
		DesignPattern::solution(i);
		chain_of_resp_solution::demo();
	}
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientChainOfResponsibility();
	}
};

class Bridge : public DesignPattern {
public:
	Bridge() : DesignPattern("Bridge") {}
public:
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientBridge();
	}
};
class AbstractFactory : public DesignPattern {
public:
	AbstractFactory() : DesignPattern("AbstractFactory") {}
public:
	void skeleton(int i) {
		DesignPattern::skeleton(i);
		skeleton::clientAbstractFactory();
	}
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

namespace dp_list {
	DesignPattern* desPats[] = {
		new DesPats,	// Needs to be first to absorb the 0th element.
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
	};

	void scanLectures() {
		cout << "Lectures:\n";
		for(size_t i=1; i<COUNT(desPats); i++) {
			desPats[i]->lecture(i);
		}
		cout << endl;
	}
	void scanLegacies() {
		cout << "Legacies:\n";
		for(size_t i=1; i<COUNT(desPats); i++) {
			desPats[i]->legacy(i);
		}
		cout << endl;
	}
	void scanProblems() {
		cout << "Problems:\n";
		for(size_t i=1; i<COUNT(desPats); i++) {
			desPats[i]->problem(i);
		}
		cout << endl;
	}
	void scanSolutions() {
		cout << "Solutions:\n";
		for(size_t i=1; i<COUNT(desPats); i++) {
			desPats[i]->solution(i);
		}
		cout << endl;
	}
	void scanSkeletons() {
		cout << "Skeletons:\n";
		for(size_t i=1; i<COUNT(desPats); i++) {
			desPats[i]->skeleton(i);
		}
		cout << endl;
	}
	void scanSideBySide() {
		cout << "SideBySide:\n";
		for(size_t i=1; i<COUNT(desPats); i++) {
			desPats[i]->sideBySide(i);
		}
		cout << endl;
	}
	void scanPairWise(int n) {
		cout << "PairWise:\n";
		assert(n%2);	// n should be odd.
		for(int i=n; i<n+2; i++) {
			desPats[i]->pairWise(i);
		}
		cout << endl;
	}
}

bool dispatch(const string& arg) {
	using namespace dp_list;
	for(size_t i=0; i<COUNT(desPats); i++) {
		if(		arg == 				 desPats[i]->name) desPats[i]->run(i); // LPS.

		else if(arg == string("c") + desPats[i]->name) desPats[i]->lecture(i);
		else if(arg == string("l") + desPats[i]->name) desPats[i]->legacy(i);
		else if(arg == string("p") + desPats[i]->name) desPats[i]->problem(i);
		else if(arg == string("s") + desPats[i]->name) desPats[i]->solution(i);
		else if(arg == string("k") + desPats[i]->name) desPats[i]->skeleton(i);
		else if(arg == string("by")+ desPats[i]->name) desPats[i]->sideBySide(i);

		else if(arg == "lectures")		scanLectures();		// Code for lectures.
		else if(arg == "legacies")		scanLegacies();		// Homework clean original code.
		else if(arg == "problems")		scanProblems();		// Homework anti pattern.
		else if(arg == "solutions")		scanSolutions();	// Homework dp.
		else if(arg == "skeletons")		scanSkeletons();	// Brief abstractions.
		else if(arg == "sideBySide")	scanSideBySide();	// White spaced to align.

		else if(arg == "lab1")			scanPairWise(1);	// Lab pair wise compare.
		else if(arg == "lab2")			scanPairWise(3);	// ...
		else if(arg == "lab3")			scanPairWise(5);
		else if(arg == "lab4")			scanPairWise(7);
		else if(arg == "lab5")			scanPairWise(9);
		else {
			continue;
		}

		return true;
	}

	return false;
}

bool meta(const string& arg) {
	using namespace dp_list;
	// Array and loop is O(n), inefficient if desPats is large.
	// Map would be better, hash dispatch, but if n ~ 20, no big deal.
//	DesignPattern* desPats[] = {
//		new Singleton,
//		new Composite,
//		new Iterator,
//		new Visitor,
//		new Command,
//		// Seam point.
//	};

	if(arg == "") {	// Auto generate to avoid 2 more seam points.
		for(size_t i=0; i<COUNT(dp_list::desPats); i++) {	// List for Run Configurations...
			cout << desPats[i]->name << endl;
		}
		cout << "prefixes: c, l, p, s, k, by\n";
		cout << "lectures\n";
		cout << "legacies\n";
		cout << "problems\n";
		cout << "solutions\n";
		cout << "skeletons\n";
		cout << "sideBySide\n";
		cout << endl;

		for(size_t i=0; i<COUNT(dp_list::desPats); i++) {	// Include list (#include "desPat.h").
			cout << "#include \"" << desPats[i]->name << ".h\"\n";
		}
		cout << endl;
	}

	if(dispatch(arg))
		return true;

	return false;
}

#endif /* META_H_ */
