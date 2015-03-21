/*
 * decorator.h
 *
 * Desc: Dynamically attach additional responsibilities to an object.
 *
 * Category: Structural
 *
 *  Created on: Apr 26, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator
 *  	http://www.dofactory.com/net/decorator-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter17
 *  	http://sourcemaking.com/design_patterns/decorator
 */

#ifndef DECORATOR_H_
#define DECORATOR_H_

namespace lecture {

namespace decorator_wikipedia_problem {

class Window {
public: virtual ~Window() {}
public:
	virtual void draw() { cout << "  Draw window\n"; }
};
class WindowWithBorder : public Window {
public:
	void draw() { cout << "  Draw window with border\n"; }
};
class ScrollingHWindow : public Window {
public:
	void draw() { cout << "  Draw window with horizontal scroll bar\n"; }
};
class ScrollingVWindow : public Window {
public:
	void draw() { cout << "  Draw window with vertical scroll bar\n"; }
};
class ScrollingHVWindow : public Window {
public:
	void draw() { cout << "  Draw window with scroll bars\n"; }
};
class ScrollingHWindowWithBorder : public Window {
public:
	void draw() { cout << "  Draw window with border horizontal scroll bar\n"; }
};
class ScrollingVWindowWithBorder : public Window {
public:
	void draw() { cout << "  Draw window with border vertical scroll bar\n"; }
};
class ScrollingHVWindowWithBorder : public Window {
public:
	void draw() { cout << "  Draw window with border with scroll bars\n"; }
};

void demo() {
	Window().draw();
	WindowWithBorder().draw();
	ScrollingHWindow().draw();
	ScrollingVWindow().draw();
	ScrollingHVWindow().draw();
	ScrollingHWindowWithBorder().draw();
	ScrollingVWindowWithBorder().draw();
	ScrollingHVWindowWithBorder().draw();
	cout << endl;
}

}

namespace decorator_wikipedia_solution {

class Window {
public: virtual ~Window() { cout << "  ** Window dtor\n"; }
public:
	virtual void draw() { cout << "  Draw window"; }
	virtual string getDesc() { return "Simple window"; }
};
class WindowDecorator : public Window {
public:	Window* decoration;
public:
	WindowDecorator(Window* window) : decoration(window) {}
	virtual ~WindowDecorator() { cout << "  >< WindowDecorator dtor\n"; }
public:
};
class WindowWithBorder : public WindowDecorator {
public:
	WindowWithBorder(Window* window) : WindowDecorator(window) {}
	~WindowWithBorder() { cout << "  <> WindowWithBorder dtor\n"; }
public:
	void draw() { decoration->draw(); cout << " with border"; }
	string getDesc() { return "Window with border"; }
};
class ScrollingHWindow : public WindowDecorator {
public:
	ScrollingHWindow(Window* window) : WindowDecorator(window) {}
	~ScrollingHWindow() { cout << "  <> ScrollingHWindow dtor\n"; }
public:
	void draw() { decoration->draw(); cout << " with horizontal scroll bar"; }
	string getDesc() { return "Window with horizontal scrolling"; }
};
class ScrollingVWindow : public WindowDecorator {
public:
	ScrollingVWindow(Window* window) : WindowDecorator(window) {}
	~ScrollingVWindow() { cout << "  <> ScrollingVWindow dtor\n"; }
public:
	void draw() { decoration->draw(); cout << " with vertical scroll bar"; }
	string getDesc() { return "Window with vertical scrolling"; }
};

void demo() {
	{
	Window simpleWindow;
	WindowWithBorder border(&simpleWindow);
	ScrollingHWindow horizontal(&border);
	ScrollingVWindow vertical(&horizontal);
	vertical.draw();
	cout << endl;
	}
	cout << endl;
}

void demoViaHeap() {
	cout << "  lecture::decorator_wikipedia_solution::demoViaHeap()\n";
	Window* window = 0;
	window = new Window();
	window = new WindowWithBorder(window);
	window = new ScrollingHWindow(window);
	window = new ScrollingVWindow(window);
	window->draw();
	cout << endl;
	WindowDecorator* prev = dynamic_cast<WindowDecorator*>(window);
	prev = dynamic_cast<WindowDecorator*>(prev->decoration);
	Window* base = dynamic_cast<WindowDecorator*>(prev->decoration)->decoration;
	cout << base->getDesc() << endl;
	cout << prev->decoration->getDesc() << endl;
	cout << prev->getDesc() << endl;
	cout << window->getDesc() << endl;
	delete base;
	delete prev->decoration;
	delete prev;
	delete window;
}

void demo2() {
	cout << "  auto_ptr();\n";
//    std::shared_ptr<Window> window = 0;
//	window = new Window();

	cout << endl;
}

}

namespace decorator_legacy {

string base() { return "base"; }
string opt1() { return "opt1"; }
string opt2() { return "opt2"; }
string opt3() { return "opt3"; }
string opt4() { return "opt4"; }

void demo() {
	cout << "  lecture::decorator_legacy::demo()\n";

	cout << "  ";
	cout << opt4() << " + ";
	cout << opt2() << " + ";
	cout << opt1() << " + ";
	cout << base() << ".\n";

	cout << endl;
}

}

namespace decorator_problem {

class Option {

};

void clientListOptions(const vector<Option*>& opts) {
	cout << "  List...\n";
}

void clientTallyCosts(const vector<Option*>& opts) {
	cout << "  Tally...\n";
}

void demo() {
	cout << "  lecture::decorator_problem::demo()\n";
	vector<Option*> opts;
	opts.push_back(new Option);
	opts.push_back(new Option);
	clientListOptions(opts);
	clientTallyCosts(opts);

	cout << endl;
}

}

namespace decorator_solution {

class Decorator {
public: virtual ~Decorator() {
	cout << "  ** dtor " << name << ".\n";
	if(chain)
		delete chain;
	}
protected:
	Decorator* chain;
	string		name;
public:
	Decorator(Decorator* chain=0, const string& name="base")
		: chain(chain), name(name) {}
	virtual string option() { return "base"; }
};
class Option1 : public Decorator {
public:
	Option1(Decorator* chain) : Decorator(chain, "opt1") {}
	string option() { return name + " + " + chain->option(); }
};
class Option2 : public Decorator {
public:
	Option2(Decorator* chain) : Decorator(chain, "opt2") {}
	string option() { return name + " + " + chain->option(); }
};
class Option3 : public Decorator {
public:
	Option3(Decorator* chain) : Decorator(chain, "opt3") {}
	string option() { return name + " + " + chain->option(); }
};
class Option4 : public Decorator {
public:
	Option4(Decorator* chain) : Decorator(chain, "opt4") {}
	string option() { return name + " + " + chain->option(); }
};

void demo() {
	cout << "  lecture::decorator_solution::demo()\n";
	Decorator* build = new Decorator;
	build = new Option1(build);
	build = new Option2(build);
	build = new Option4(build);
	cout << "  " << build->option() << ".\n";

	delete build;
	cout << endl;
}

}

}

// Still a bit of a mess - see homework namespace below.

struct Data {
	int	optA;
	int	optB;
	int optC;
};

namespace decorator_legacy {

void optionA(int variation) {
	switch(variation) {
	case 1:
		cout << "  option A - variation 1.\n";
		break;
	case 2:
		cout << "  option A - variation 2.\n";
		break;
	default:
	throw "OOPS";
	}
}

void optionB(int variation) {
	switch(variation) {
	case 1:
		cout << "  option B - variation 1.\n";
		break;
	case 2:
		cout << "  option B - variation 2.\n";
		break;
	case 3:
		cout << "  option B - variation 3.\n";
		break;
	default:
	throw "OOPS";
	}
}

void optionC(int variation) {
	switch(variation) {
	case 1:
		cout << "  option C - variation 1.\n";
		break;
	case 2:
		cout << "  option C - variation 2.\n";
		break;
	default:
	throw "OOPS";
	}
}

void clientCode(Data data) {
	if(data.optA)	optionA(data.optA);
	if(data.optB)	optionB(data.optB);
	if(data.optC)	optionC(data.optC);
}

void demo() {
	cout << "  decorator_legacy::demo().\n";
	Data data[] = {
		{ 0, 1, 0 },
		{ 1, 2, 1 },
		{ 2, 3, 2 },
	};
	for(size_t i=0; i<sizeof(data)/sizeof(*data); i++) {
		clientCode(data[i]);
		cout << endl;
	}
}

}

namespace decorator_problem {

void demo() {
	cout << "  decorator_problem::demo().\n";
}

}

namespace decorator_solution {

class Decorator {		// If the options are varying...
public: virtual ~Decorator() {}
public:
	virtual void costs() { cout << "  Base decorator cost.\n"; }
};

class Option1 : public Decorator {
public:
	Option1(Decorator* decorator) { cout << "  Option1\n"; }
public:
	virtual void costs() { cout << "  Option1 decorator cost.\n"; }
};
class Option2 : public Decorator {
public:
	Option2(Decorator* decorator) { cout << "  Option2\n"; }
};
class Option3 : public Decorator {
public:
	Option3(Decorator* decorator) { cout << "  Option3\n"; }
};

struct Data {
	vector<Decorator*>	decorators;
};

void clientCode(Decorator* option) {
	cout << "Decorator\n";
	option->costs();
//	Decorator *decorator = new Decorator;
//	decorator = new Option1(decorator);
//	decorator = new Option2(decorator);
//	decorator = new Option3(decorator);
//	cout << endl;
}

void demo() {
	cout << "  decorator_solution::demo().\n";
	Decorator* orders[] = {
		new Option2(new Decorator),
		new Option1(new Option2(new Option3(new Decorator))),
		new Option3(new Decorator),
	};
	for(size_t i=0; i<sizeof(orders)/sizeof(*orders); i++) {
		clientCode(orders[i]);
		cout << endl;
	}

//	vector<Decorator*>	order1, order2, order3;
//	order1.push_back(new Decorator);
//	order2.push_back(new Decorator);	order2.push_back(new Decorator);	order2.push_back(new Decorator);
//	order3.push_back(new Decorator);
//	Data data[] = { {order1}, {order2}, {order3} };
//	clientCodeDecorator();

	cout << endl;
}

}

namespace homework {

/* Consider options for a car.
 * One might subclass a base class, Car, for each set of options,
 * but then the options code gets duplicated leading to scaling problems,
 * and the options are statically linked.
 * For the 4 classes and 9 options implied by the following procedural code,
 * rewrite with the Decorator pattern to eliminate the combinatorial explosion,
 * reduce duplication, improve code locality, and allow for dynamic linking.
 * Pay particular attention to the problem of memory leaks with this pattern.
 */

namespace decorator_common {

class Car {
protected:
	string str;
public:
	Car(string str="Undefined car") : str(str) {}
	virtual string getDesc() { return str; }
	virtual double getCost()=0;
	virtual ~Car() {
		cout << "~Car " << str << "\n";
	}
};

}

namespace decorator_legacy {

using namespace decorator_common;

class RunAbout : public Car {
public:
	RunAbout() : Car("RunAbout") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors";
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00;
		return cost;
	}
};

class SUV : public Car {
public:
	SUV() : Car("SUV") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 4 doors"
			+ ", AC"
			+ ", automatic transmission";
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 3000.00;
		return cost;
	}
};

void demo() {
	Car* cars[] = { new RunAbout, new SUV};

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		cout << cars[i]->getDesc() << " costs $" << cars[i]->getCost() << ".\n";
	cout << endl;

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		delete cars[i];
	cout << endl;
}

}

namespace decorator_problem {

using namespace decorator_common;

class RunAbout : public Car {
public:
	RunAbout() : Car("RunAbout") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00
		;
		return cost;
	}
};

class SUV : public Car {
public:
	SUV() : Car("SUV") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 4 doors"
			+ ", AC"
			+ ", automatic transmission"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 3000.00
		;
		return cost;
	}
};

class Status : public Car {
public:
	Status() : Car("Status") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 4 doors"
			+ ", AC"
			+ ", premium sound system"
			+ ", navigation"
			+ ", automatic transmission"
			// Seam: new options scales as the number of car models.
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 1000.00
			+ 2000.00
			+ 3000.00
		;
		return cost;
	}
};

class Performance : public Car {
public:
	Performance() : Car("Performance") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors"
			+ ", AC"
			+ ", premium sound system"
			+ ", navigation"
			+ ", manual transmission"
			+ ", V8"
			+ ", super-charger"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00
			+ 1500.00
			+ 1000.00
			+ 2000.00
			+ 2500.00
			+ 6000.00
			+ 3000.00
		;
		return cost;
	}
};
// Seam: new car models scale as the number of options.

void demo() {
	Car* mine  = new RunAbout;
	Car* yours = new SUV;
	Car* hers  = new Status;
	Car* boss  = new Performance;

	Car* cars[] = {mine, yours, hers, boss};

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		cout << cars[i]->getDesc() << " costs $" << cars[i]->getCost() << ".\n";
	cout << endl;

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		delete cars[i];
	cout << endl;
}

}

namespace decorator_solution {

using namespace decorator_common;

class BaseModel : public Car {
public:
	BaseModel(string name="missing") : Car(name+" with 4 wheels") {}
	string getDesc() {
		string desc = str;
		return desc;
	}
	double getCost() { return 12000.00; }
	~BaseModel() { cout << "~BaseModel: "; }
};

class OptionsDecorator : public Car {
// This is the surprise, options are not cars,
// inheriting from Car violates the "is-a" principle,
// but it is the key to dynamically attaching additional responsibilities.
protected:
	Car* build;
public:
	OptionsDecorator(Car* build, string str="OD") : Car(str), build(build) {}
	string getDesc() { return build->getDesc() + ", " + str; }
	virtual ~OptionsDecorator() {
		cout << "~OptionsDecorator: ";
	}
};

#define OD_Dtor { cout << "~" << str << "\n"; build->~Car(); } // Reduces dups.
//#define OD_Dtor { build->~Car(); cout << "~" << str << "\n"; } // Less clear.

class TwoDoors : public OptionsDecorator {
public:
	TwoDoors(Car* build) : OptionsDecorator(build, "2 doors") {}
	double getCost() { return build->getCost() + 2000.00; }
	~TwoDoors() OD_Dtor
};
class FourDoors : public OptionsDecorator {
public:
	FourDoors(Car* build) : OptionsDecorator(build, "4 doors") {}
	double getCost() { return build->getCost() + 4000.00; }
	~FourDoors() OD_Dtor
};
class AC : public OptionsDecorator {
public:
	AC(Car* build) : OptionsDecorator(build, "AC") {}
	double getCost() { return build->getCost() + 1500.00; }
	~AC() OD_Dtor
};
class PremiumSoundSystem : public OptionsDecorator {
public:
	PremiumSoundSystem(Car* build) : OptionsDecorator(build, "premium sound system") {}
	double getCost() { return build->getCost() + 1000.00; }
	~PremiumSoundSystem() OD_Dtor
};
class Navigation : public OptionsDecorator {
public:
	Navigation(Car* build) : OptionsDecorator(build, "navigation") {}
	double getCost() { return build->getCost() + 2000.00; }
	~Navigation() OD_Dtor
};
class ManualTransmission : public OptionsDecorator {
public:
	ManualTransmission(Car* build) : OptionsDecorator(build, "manual transmission") {}
	double getCost() { return build->getCost() + 2500.00; }
	~ManualTransmission() OD_Dtor
};
class AutomaticTransmission : public OptionsDecorator {
public:
	AutomaticTransmission(Car* build) : OptionsDecorator(build, "automatic transmission") {}
	double getCost() { return build->getCost() + 3000.00; }
	~AutomaticTransmission() OD_Dtor
};
class V8 : public OptionsDecorator {
public:
	V8(Car* build) : OptionsDecorator(build, "V8") {}
	double getCost() { return build->getCost() + 6000.00; }
	~V8() OD_Dtor
};
class SuperCharger : public OptionsDecorator {
public:
	SuperCharger(Car* build) : OptionsDecorator(build, "super-charger") {}
	double getCost() { return build->getCost() + 3000.00; }
	~SuperCharger() OD_Dtor
};

void demo() {
	Car* mine = new BaseModel("RunAbout");
	mine = new TwoDoors(mine);

	Car* yours = new BaseModel("SUV");
	yours = new FourDoors(yours);
	yours = new AC(yours);
	yours = new AutomaticTransmission(yours);

	Car* hers = new BaseModel("Status");
	hers = new FourDoors(hers);
	hers = new AC(hers);
	hers = new PremiumSoundSystem(hers);
	hers = new Navigation(hers);
	hers = new AutomaticTransmission(hers);

	Car* boss = new BaseModel("Performance");
	boss = new TwoDoors(boss);
	boss = new AC(boss);
	boss = new PremiumSoundSystem(boss);
	boss = new Navigation(boss);
	boss = new ManualTransmission(boss);
	boss = new V8(boss);
	boss = new SuperCharger(boss);

	Car* cars[] = {mine, yours, hers, boss};

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		cout << cars[i]->getDesc() << " costs $" << cars[i]->getCost() << ".\n";
	cout << endl;

	if(false) {	// Formally correct, but verbose output.
		for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
			delete cars[i];	cout << endl;
		}
	else {
		delete hers; cout << endl; // For demo only, to limit output.
	}
}

}

}

/*-----------------------------------------------------------------------------*/


class Car {
protected:
	string str;
public:
	Car(string str="Undefined car") : str(str) {}
	virtual string getDesc() { return str; }
	virtual double getCost()=0;
	virtual ~Car() {
		cout << "~Car " << str << "\n";
	}
};

namespace too_many_car_model_options {

/* Consider options for a car.
 * One might subclass a base class, Car, for each set of options,
 * but then the options code gets duplicated leading to scaling problems,
 * and the options are statically linked.
 * For the 4 classes and 9 options implied by the following procedural code,
 * rewrite with the Decorator pattern to eliminate the combinatorial explosion,
 * reduce duplication, improve code locality, and allow for dynamic linking.
 * Pay particular attention to the problem of memory leaks with this pattern.
 */

class RunAbout : public Car {
public:
	RunAbout() : Car("RunAbout") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00
		;
		return cost;
	}
};

class SUV : public Car {
public:
	SUV() : Car("SUV") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 4 doors"
			+ ", AC"
			+ ", automatic transmission"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 3000.00
		;
		return cost;
	}
};

class Status : public Car {
public:
	Status() : Car("Status") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 4 doors"
			+ ", AC"
			+ ", premium sound system"
			+ ", navigation"
			+ ", automatic transmission"
			// Seam: new options scales as the number of car models.
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 1000.00
			+ 2000.00
			+ 3000.00
		;
		return cost;
	}
};

class Performance : public Car {
public:
	Performance() : Car("Performance") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors"
			+ ", AC"
			+ ", premium sound system"
			+ ", navigation"
			+ ", manual transmission"
			+ ", V8"
			+ ", super-charger"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00
			+ 1500.00
			+ 1000.00
			+ 2000.00
			+ 2500.00
			+ 6000.00
			+ 3000.00
		;
		return cost;
	}
};
// Seam: new car models scale as the number of options.

void demo() {
	Car* mine  = new RunAbout;
	Car* yours = new SUV;
	Car* hers  = new Status;
	Car* boss  = new Performance;

	Car* ours[] = {mine, yours, hers, boss};

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
		cout << ours[i]->getDesc() << " costs $" << ours[i]->getCost() << ".\n";
	}
	cout << endl;

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
		delete ours[i];
	}
	cout << endl;
}

}

namespace decorator {

class BaseModel : public Car {
public:
	BaseModel(string name="missing") : Car(name+" with 4 wheels") {}
	string getDesc() {
		string desc = str;
		return desc;
	}
	double getCost() { return 12000.00; }
	~BaseModel() { cout << "~BaseModel: "; }
};

class OptionsDecorator : public Car {
// This is the surprise, options are not cars,
// inheriting from Car violates the "is-a" principle,
// but it is the key to dynamically attaching additional responsibilities.
protected:
	Car* build;
public:
	OptionsDecorator(Car* build, string str="OD") : Car(str), build(build) {}
	string getDesc() { return build->getDesc() + ", " + str; }
	virtual ~OptionsDecorator() {
		cout << "~OptionsDecorator: ";
	}
};

#define OD_Dtor { cout << "~" << str << "\n"; build->~Car(); } // Just to reduce duplication.

class TwoDoors : public OptionsDecorator {
public:
	TwoDoors(Car* build) : OptionsDecorator(build, "2 doors") {}
	double getCost() { return build->getCost() + 2000.00; }
	~TwoDoors() OD_Dtor
};

class FourDoors : public OptionsDecorator {
public:
	FourDoors(Car* build) : OptionsDecorator(build, "4 doors") {}
	double getCost() { return build->getCost() + 4000.00; }
	~FourDoors() OD_Dtor
};

class AC : public OptionsDecorator {
public:
	AC(Car* build) : OptionsDecorator(build, "AC") {}
	double getCost() { return build->getCost() + 1500.00; }
	~AC() OD_Dtor
};

class PremiumSoundSystem : public OptionsDecorator {
public:
	PremiumSoundSystem(Car* build) : OptionsDecorator(build, "premium sound system") {}
	double getCost() { return build->getCost() + 1000.00; }
	~PremiumSoundSystem() OD_Dtor
};

class Navigation : public OptionsDecorator {
public:
	Navigation(Car* build) : OptionsDecorator(build, "navigation") {}
	double getCost() { return build->getCost() + 2000.00; }
	~Navigation() OD_Dtor
};

class ManualTransmission : public OptionsDecorator {
public:
	ManualTransmission(Car* build) : OptionsDecorator(build, "manual transmission") {}
	double getCost() { return build->getCost() + 2500.00; }
	~ManualTransmission() OD_Dtor
};

class AutomaticTransmission : public OptionsDecorator {
public:
	AutomaticTransmission(Car* build) : OptionsDecorator(build, "automatic transmission") {}
	double getCost() { return build->getCost() + 3000.00; }
	~AutomaticTransmission() OD_Dtor
};

class V8 : public OptionsDecorator {
public:
	V8(Car* build) : OptionsDecorator(build, "V8") {}
	double getCost() { return build->getCost() + 6000.00; }
	~V8() OD_Dtor
};

class SuperCharger : public OptionsDecorator {
public:
	SuperCharger(Car* build) : OptionsDecorator(build, "super-charger") {}
	double getCost() { return build->getCost() + 3000.00; }
	~SuperCharger() OD_Dtor
};

void demo() {
	Car* mine = new BaseModel("RunAbout");
	mine = new TwoDoors(mine);

	Car* yours = new BaseModel("SUV");
	yours = new FourDoors(yours);
	yours = new AC(yours);
	yours = new AutomaticTransmission(yours);

	Car* hers = new BaseModel("Status");
	hers = new FourDoors(hers);
	hers = new AC(hers);
	hers = new PremiumSoundSystem(hers);
	hers = new Navigation(hers);
	hers = new AutomaticTransmission(hers);

	Car* boss = new BaseModel("Performance");
	boss = new TwoDoors(boss);
	boss = new AC(boss);
	boss = new PremiumSoundSystem(boss);
	boss = new Navigation(boss);
	boss = new ManualTransmission(boss);
	boss = new V8(boss);
	boss = new SuperCharger(boss);

	Car* ours[] = {mine, yours, hers, boss};

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
		cout << ours[i]->getDesc() << " costs $" << ours[i]->getCost() << ".\n";
	}
	cout << endl;

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
//		delete ours[i];	cout << endl;
	}
	delete hers; cout << endl; // For demo only, to limit output, loop above is formally correct.
}

}

#endif /* DECORATOR_H_ */
