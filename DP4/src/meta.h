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
 *   	problems:
 *   	solutions:
 *   	experimentals:
 *   	pariwiseLab1/2/3/4/5:
 *   	final:
 */

/* Program control table
 * Pattern/Group   | Lectures | Problems | Solutions | Skeletons | SideBySide | Pairwise |
 * ----------------+----------+----------+-----------+-----------+------------+----------+
 * Strategy        | lecture1 | strategy | sstrategy | kstrategy | bystrategy | lab1     |
 * Adapter         |  l<dp>   | adapter  | sadapter  | kadapter  | byadapter  |          |
 * Facade          | lecture2 | facade   | sfacade   | kfacade   | byfacade   | lab2     |
 * TemplateMethod  |  l<dp>   | templateM| stemplateM| ktemplateM| bytemplateM|          |
 * FactoryMethod   | lecture3 | factoryMe| sfactoryMe| kfactoryMe| byfactoryMe| lab3     |
 * Decorator       |  l<dp>   | decorator| sdecorator| kdecorator| bydecorator|          |
 * Observer        | lecture4 | observer | sobserver | kobserver | byobserver | lab4     |
 * ChainOfResp     |  l<dp>   | chainOfRe| schainOfRe| kchainOfRe| bychainOfRe|          |
 * Bridge          | lecture5 | bridge   | sbridge   | kbridge   | bybridge   | lab5     |
 * AbstractFactory |  l<dp>   | abstractF| sabstractF| kabstractF| byabstractF|          |
 * ----------------+----------+----------+-----------+-----------+------------+----------+
 * Singleton       |          |          | s         | k         | by         |          |
 * Composite       |          |          | s         | k         | by         |          |
 * Iterator        |          |          | s         | k         | by         |          |
 * Visitor         |          |          | s         | k         | by         |          |
 * Command         |          |          | s         | k         | by         |          |
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
	virtual void run()  { cout << "  DesignPattern Base.run().\n"; }
	virtual void runC(int i) { cout << "  DesignPattern Base.runC().\n"; }	// Class (lecture).
	virtual void runL(int i) { cout << "  DesignPattern Base.runL().\n"; }	// Legacy.
	virtual void runP(int i) { cout << "  DesignPattern Base.runP().\n"; }	// Problem.
	virtual void runS(int i) { cout << "  DesignPattern Base.runS().\n"; }	// Solution.
	virtual void runK(int i) { cout << "  DesignPattern Base.runK().\n"; }	// Skeleton.
	virtual void runBy(int i){ cout << "  DesignPattern Base.runBy().\n"; }	// SideBySide.
	virtual void runProblem(int i) {
//		out(i); problems::legacy();
	}
	virtual void run(int i) {	// Example of the Template Method design pattern.
		cout << i << ") ";	legacy();
		cout << i << ") ";	problem();
		cout << i << ") ";	solution();
	}

	virtual void lecture() {
		cout << "<< " << name << " lecture >>\n";
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

	virtual void legacy(int i) {
		cout << i << ") " << "<< " << name << " legacy >>\n";
	}
	virtual void skeleton(int i) {	// abstract is better name.
		cout << i << ") " << "<< " << name << " skeleton >>\n";
	}
	virtual void problem(int i) {
		cout << i << ") " << "<< " << name << " problem >>\n";
	}
	virtual void solution(int i) {
		cout << i << ") " << "<< " << name << " solution >>\n";
	}

	virtual void skeleton() {
		cout << "<< " << name << " skeleton >>\n";
	}
	virtual void sideBySide() {
		cout << "<< " << name << " sideBySide >>\n";
	}
	virtual void pairWise() {
		cout << "<< " << name << " pairWise >>\n";
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
		out(i); cout << endl;
		Option choice = HOMEWORK;
		switch(choice) {
		case ORIG:
			cout << i+1 << ") ";	legacy();
			cout << i+1 << ") ";	problem();
			cout << i+1 << ") ";	solution();
			break;
//		case LECTURES:
//			DesignPattern::legacy(i);	lectures::strategy_legacy::demo();
//			DesignPattern::skeleton(i);	lectures::strategy_skeleton::demo();
//			DesignPattern::problem(i);	lectures::strategy_problem::demo();
//			DesignPattern::solution(i);	lectures::strategy_solution::demo();
//			break;
//		case HOMEWORK:
//			DesignPattern::legacy(i);	homework::strategy_legacy::demo();
////			DesignPattern::skeleton(i);	homework::strategy_skeleton::demo();
//			DesignPattern::problem(i);	homework::strategy_problem::demo();
//			DesignPattern::solution(i);	homework::strategy_solution::demo();
//			break;
		}
	}
	void skeleton() {
		skeleton::clientStrategy();
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
	void skeleton() {
		skeleton::clientAdapter();
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
	void skeleton() {
		skeleton::clientFacade();
	}
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

class Lectures : public DesignPattern {
public:
	Lectures() : DesignPattern("Lectures") {}
public:
	void run() {
		cout << "  Lectures\n";
	}
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
		for(size_t i=0; i<COUNT(desPats); i++) {
			desPats[i]->lecture();
		}
	}
	void scanLegacies() {
		for(size_t i=0; i<COUNT(desPats); i++) {
			desPats[i]->legacy();
		}
	}
	void scanProblems() {
		for(size_t i=0; i<COUNT(desPats); i++) {
			desPats[i]->problem();
		}
	}
	void scanSolutions() {
		for(size_t i=0; i<COUNT(desPats); i++) {
			desPats[i]->solution();
		}
	}
	void scanSkeletons() {
		for(size_t i=0; i<COUNT(desPats); i++) {
			desPats[i]->skeleton();
		}
	}
	void scanSideBySide() {
		for(size_t i=0; i<COUNT(desPats); i++) {
			desPats[i]->sideBySide();
		}
	}
	void scanPairWise(int n) {
		assert(!(n%2));	// n should be even.
		for(int i=n; i<n+2; i++) {
			desPats[i]->pairWise();
		}
	}
}

bool dispatch(const string& arg) {
	using namespace dp_list;
	for(size_t i=0; i<COUNT(desPats); i++) {
		if(		arg == 				 desPats[i]->name) desPats[i]->run(i); // lps.

		else if(arg == string("c") + desPats[i]->name) desPats[i]->runC(i);
		else if(arg == string("l") + desPats[i]->name) desPats[i]->runL(i);
		else if(arg == string("p") + desPats[i]->name) desPats[i]->runP(i);
		else if(arg == string("s") + desPats[i]->name) desPats[i]->runS(i);
		else if(arg == string("k") + desPats[i]->name) desPats[i]->runK(i);
		else if(arg == string("by")+ desPats[i]->name) desPats[i]->runBy(i);

		else if(arg == "lectures")		scanLectures();		// Code for lectures.
		else if(arg == "legacies")		scanLegacies();		// Homework clean original code.
		else if(arg == "problems")		scanProblems();		// Homework anti pattern.
		else if(arg == "solutions")		scanSolutions();	// Homework dp.
		else if(arg == "skeletons")		scanSkeletons();	// Brief abstractions.
		else if(arg == "sideBySide")	scanSideBySide();	// White spaced to align.

		else if(arg == "lab1")			scanPairWise(0);	// Lab pair wise compare.
		else if(arg == "lab2")			scanPairWise(2);	// ...
		else if(arg == "lab3")			scanPairWise(4);
		else if(arg == "lab4")			scanPairWise(6);
		else if(arg == "lab5")			scanPairWise(8);
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
