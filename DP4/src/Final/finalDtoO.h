/*
 * finalDtoO.h
 *
 *  Created on: Apr 17, 2015
 *      Author: aldgoff
 *
 *  Project: Intro to Design Patterns Pilot class.
 *  Practice Part I of the final:
 *    replace with finalDesign.h, then hand code upto finalOriginal.h.
 */

#ifndef DP4_SRC_D_TO_O_FINAL_H_
#define DP4_SRC_D_TO_O_FINAL_H_

namespace final_d_to_o_file {

const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }

namespace legacy_classes {	// Can't change these.

class CleanABS {
public: ~CleanABS() { DTOR("~CleanABS "); }
	void clean() {
		cout << "    Clean ABS mold: soak in alcohol, rinse with water, dry.\n";
	}
};

class CleanPolys {
public: ~CleanPolys() { DTOR("~CleanPolys "); }
	void prepForReuse() {
		cout << "    Clean Poly mold: rinse with acetone, dry.\n";
	}
};

class PETCleanup {
public: ~PETCleanup() { DTOR("~PETCleanup "); }
	void carbonize() { // Use only on stainless steel.
		cout << "    Clean PET steel mold: heat to 895 C.\n";
	}
	void purify() {	// Use only on aluminum.
		cout << "    Clean PET aluminum mold: rinse with soap and water, dry.\n";
	}
};

}

namespace adapter {			// DP 2.

class CleanPlastic_A_2 {
public:
	CleanPlastic_A_2() {}
	virtual ~CleanPlastic_A_2() { DTOR("~CleanPlastic_A_2 "); }
public:
	virtual void clean(const string& metal) {
		cout << "    Clean <plastic> <optional metal> mold: <cleaning steps>.\n";
	}
};
class ABS : public CleanPlastic_A_2 {
	legacy_classes::CleanABS plastic;
public:
	~ABS() { DTOR("~adapter::ABS "); }
public:
	void clean(const string& metal) {
		plastic.clean();
	}
};
class Poly : public CleanPlastic_A_2 {
	legacy_classes::CleanPolys plastic;
public:
	~Poly() { DTOR("~adapter::Poly "); }
public:
	void clean(const string& metal) {
		plastic.prepForReuse();
	}
};
class PET : public CleanPlastic_A_2 {
	legacy_classes::PETCleanup plastic;
public:
	~PET() { DTOR("~adapter::PET "); }
public:
	void clean(const string& metal) {
		if(metal == "aluminum")		plastic.purify();
		else if(metal == "steel")	plastic.carbonize();
	}
};
// Seam point - add another interface.

}

namespace strategy {		// DP 1.

class Strategy_1 {
protected:
	adapter::CleanPlastic_A_2* plastic;
public:
	Strategy_1(adapter::CleanPlastic_A_2* plastic=new adapter::CleanPlastic_A_2)
	  : plastic(plastic)
	{}
	virtual ~Strategy_1() {
		delete plastic;
		DTOR("~Strategy_1\n");
	}
public:
	virtual void cycle(map<string, string>& order) {
		cout << "    Cycle IJM for <plastic> <size> times.\n";
		cout << "      Close - heat to <temp> - inject at <psi> PSI - cool to <temp> - separate - <technique> eject.\n";
	}
	void clean(const string& metal="steel") {
		plastic->clean(metal);
	}
};
class ABS : public Strategy_1 {
public:
	ABS() : Strategy_1(new adapter::ABS) {}
	~ABS() { DTOR("~ABS "); }
public:
	void cycle(map<string, string>& order) {
		cout << "    Cycle IJM for ABS " << order["size"] << " times.\n";
		cout << "      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject.\n";
	}
};
class Poly : public Strategy_1 {
public:
	Poly() : Strategy_1(new adapter::Poly) {}
	~Poly() { DTOR("~Poly "); }
public:
	void cycle(map<string, string>& order) {
		cout << "    Cycle IJM for Poly " << order["size"] << " times.\n";
		cout << "      Close - heat to 350 - inject at  90 PSI - cool to 290 - separate - smooth eject.\n";
	}
};
class PET : public Strategy_1 {
public:
	PET() : Strategy_1(new adapter::PET) {}
	~PET() { DTOR("~PET "); }
public:
	void cycle(map<string, string>& order) {
		cout << "    Cycle IJM for PET " << order["size"] << " times.\n";
		cout << "      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject.\n";
	}
};
// Seam point - add another algorithm.

}

namespace observer {		// DP 7.

// Packager will be the Subject, the injection line machines the Observers.

class Observer_7;
class Subject_7;

class Subject_7 {
	list<Observer_7*>	observers;
public:
	const string name;
public:
	Subject_7(const string& name) : name(name) {}
	~Subject_7();
public:
	void attach(Observer_7* observer) {
		observers.push_back(observer);
	}
	void detach(Observer_7* observer) {
		observers.remove(observer);
	}
	void pause();
};

class Observer_7 {
protected:
	Subject_7* subject;
public:
	Observer_7(Subject_7* subject) : subject(subject) {
		subject->attach(this);
	}
	virtual ~Observer_7() {
		subject->detach(this);
		DTOR("~Observer_7\n");
	}
public:
	virtual void update() {
		cout << "        <machine> pausing while <Packager> package is swapped.\n";
	}
};

Subject_7::~Subject_7() {
	DTOR("~Subject_7");
	DTOR("~Observers left to process (should be zero) = ");
	char str[80];
	sprintf(str, "%d.\n", observers.size());
	DTOR(str);
}

void Subject_7::pause() {
	cout << "      " << name << " package bin is full...\n";
	list<Observer_7*>::iterator it=observers.begin();
	for(; it!=observers.end(); it++)
		(*it)->update();
}

}

namespace abstract_factory {// DP 10.

class IJM_AF {};
class IJM_110 : public IJM_AF {};
class IJM_120 : public IJM_AF {};
class IJM_210 : public IJM_AF {};
// Seam point - add another InJection Molding machine.

class Mold_AF {};
class Aluminum : public Mold_AF {};
class Steel : public Mold_AF {};

class ConveyerBelt_AF {};
class Linear : public ConveyerBelt_AF {};
class YSplit : public ConveyerBelt_AF {};
// Seam point - add another conveyer belt.

class PackageBin_AF {};
class CardboarBox : public PackageBin_AF {};
class PallotBox : public PackageBin_AF {};
// Seam point - add another package bin.

class Setup_AF_10 {};
class PilotOrder : public Setup_AF_10 {};
class SmallOrder : public Setup_AF_10 {};
class MediumOrder : public Setup_AF_10 {};
// Seam point - add another family.

}

// ----- Alternatively (may make it hard to match the dtor instrumentation) -----
namespace abstract_factory_solti {	// DP 10 - more like GoF.

using namespace observer;

class IJM_AF : public Observer_7 {
public:
	IJM_AF(Subject_7* subject) : Observer_7(subject) {}
	virtual ~IJM_AF() { DTOR("~IJM_AF "); }
public:
};
class Mold_AF {};
class ConveyerBelt_AF : public Observer_7 {
public:
	ConveyerBelt_AF(Subject_7* subject) : Observer_7(subject) {}
	virtual ~ConveyerBelt_AF() { DTOR("~ConveyerBelt_AF "); }
public:
};
class PackageBin_AF : public Subject_7 {
public:
	PackageBin_AF(const string& name="bin") : Subject_7(name) {}
	virtual ~PackageBin_AF() { DTOR("~PackageBin_AF "); }
public:
};

class AbstractFactory_10 {
public:
	virtual ~AbstractFactory_10() { DTOR("AbstractFactory_10 "); }
public:
	virtual IJM_AF* createIJM() {
		return new IJM_AF(new Subject_7("base"));
	}
	virtual Mold_AF* createMold() {
		return new Mold_AF;
	}
	virtual ConveyerBelt_AF* createConveyerBelt() {
		return new ConveyerBelt_AF(new Subject_7("base"));
	}
	virtual PackageBin_AF* createPackageBin() {
		return new PackageBin_AF("base");
	}
};
class InjectionLine_AF {
protected:
	AbstractFactory_10*	factory;
	IJM_AF*				ijm;
	Mold_AF*			mold;
	ConveyerBelt_AF*	belt;
	PackageBin_AF*		bin;
public:
	virtual ~InjectionLine_AF() { DTOR("~InjectionLine_AF\n"); }
public:
	void init() {
		ijm  = factory->createIJM();
		mold = factory->createMold();
		belt = factory->createConveyerBelt();
		bin  = factory->createPackageBin();
	}
	virtual AbstractFactory_10* buildFactory() { return new AbstractFactory_10; }
};

// 10,000
class IJM_110 : public IJM_AF {};
class Aluminum : public Mold_AF {};
class Linear : public ConveyerBelt_AF {};
class CardboarBox : public PackageBin_AF {
public:
	CardboarBox() : PackageBin_AF("CardboarBox") {}
	~CardboarBox() { DTOR("~CardboarBox "); }
};
class PilotOrder_AF : public AbstractFactory_10 {
public:
	~PilotOrder_AF() { DTOR("~PilotOrder_AF "); }
};
class PilotOrder_IL : public InjectionLine_AF {};

// 20,000
class IJM_120 : public IJM_AF {};
//class Aluminum : public Mold_AF {};
class YSplit : public ConveyerBelt_AF {};
class PallotBox : public PackageBin_AF {
public:
	PallotBox() : PackageBin_AF("PallotBox") {}
	 ~PallotBox() { DTOR("~PallotBox "); }
};
class SmallOrder_AF : public AbstractFactory_10 {
public:
	~SmallOrder_AF() { DTOR("~SmallOrder_AF "); }
};
class SmallOrder_IL : public InjectionLine_AF {};

// 50,000
class IJM_210 : public IJM_AF {};
class Steel : public Mold_AF {};
//class Linear : public ConveyerBelt_AF {};
//class CardboarBox : public PackageBin_AF {};
class MediumOrder_AF : public AbstractFactory_10 {
public:
	~MediumOrder_AF() { DTOR("~MediumOrder_AF "); }
public:
	IJM_AF* createIJM() {
		return new IJM_AF(new Subject_7("base"));
	}
	Mold_AF* createMold() {
		return new Mold_AF;
	}
	ConveyerBelt_AF* createConveyerBelt() {
		return new ConveyerBelt_AF(new Subject_7("base"));
	}
	PackageBin_AF* createPackageBin() {
		return new CardboarBox;
	}
};
class MediumOrder_IL : public InjectionLine_AF {};

// Seam line - add another family.

}

namespace bridge {			// DP 9.

// Seam Point - add another implementation.

// Seam Point - add another abstraction.

}

namespace chain_of_resp {	// DP 8.

// Seam points - add another responder.

}

namespace decorator {		// DP 6.

// Seam point - add another option.

}

namespace factory_method {	// DP 5.

using namespace observer;

class Packager_FM_5 : public Observer_7 {
public:
	Packager_FM_5(Subject_7* subject) : Observer_7(subject) {}
	virtual ~Packager_FM_5() { DTOR("~Packager_FM_5 "); }
public:
	static Packager_FM_5* createPackager(map<string,string>& order, Subject_7* bin);
public:
//	void update() {}
public:
	virtual string name() { return "Default packager"; }
};
class Bulk : public Packager_FM_5 {
public:
	Bulk(Subject_7* bin) : Packager_FM_5(bin) {}
	~Bulk() { DTOR("~Bulk "); }
public:
	string name() { return "Bulk"; }
};
class ShrinkWrap : public Packager_FM_5 {
public:
	ShrinkWrap(Subject_7* bin) : Packager_FM_5(bin) {}
	~ShrinkWrap() { DTOR("~ShrinkWrap "); }
public:
	string name() { return "ShrinkWrap"; }
};
class HardPack : public Packager_FM_5 {
public:
	HardPack(Subject_7* bin) : Packager_FM_5(bin) {}
	~HardPack() { DTOR("~HardPack "); }
public:
	string name() { return "HardPack"; }
};
// Seam point - add another class.

Packager_FM_5* Packager_FM_5::createPackager(map<string,string>& order, Subject_7* bin) {
	if(		order["packager"] == "Bulk")		return new Bulk(bin);
	else if(order["packager"] == "ShrinkWrap")	return new ShrinkWrap(bin);
	else if(order["packager"] == "HardPack")	return new HardPack(bin);
	// Seam point - insert another packager.

	else {										// Default.
		cout << "  <>Unknown packager |" << order["packager"] << "| ";
		order["packager"] = "Bulk";
		cout << "defaulting to " << order["packager"] << " packager.\n";
		return new Bulk(bin);
	}
}

}

namespace template_method {	// DP 4.

//using namespace abstract_factory;
using namespace abstract_factory_solti;
using namespace factory_method;

class ProcessOrder_TM_4 {
protected:
	strategy::Strategy_1* algorithm;
	abstract_factory_solti::InjectionLine_AF* injectionLine;
	Packager_FM_5*	packager;
public:
	ProcessOrder_TM_4()
	  : algorithm(0),	// When no derived classes (new strategy::Strategy_1).
		injectionLine(0),
		packager(0)
	{}
	virtual ~ProcessOrder_TM_4() {
		delete injectionLine;
		delete packager;
		delete algorithm;
		DTOR("~ProcessOrder_TM_4\n");
	}
private:
	void setupInjectionLine(map<string, string>& order) {
		if(order.find("size") == order.end()) {
			order["size"] = "100";
			cout << "  <>No size specified, defaulting to " << order["size"] << ".\n";
		}
		injectionLine = new InjectionLine_AF;

		packager = Packager_FM_5::createPackager(order, new PackageBin_AF);

		cout << "  Setup <AF_IL> injection line for " << order["size"] ;
		cout << " run with " << packager->name() << " packager:\n";
	}
	void getMold(map<string, string>& order) {
		cout << "    Get mold:\n";
	}
	void insertTags(map<string, string>& order) {
		cout << "    Insert tags [] of width 0/20 mm.\n";
	}
	void loadAdditives(map<string, string>& order) {
		cout << "    Load plastic, color, and additive bins.\n";
	}
protected:
	virtual void injectionCycle(map<string, string>& order) {
		cout << "    Injection cycle - no plastic specified:\n";
	}
private:
	void cleanMold(map<string, string>& order) {
		algorithm->clean();
	}
public:
	void run(map<string, string>& order) {
		setupInjectionLine(order);
		cout << "  Process order.\n";
		getMold(order);
		insertTags(order);
		loadAdditives(order);
		injectionCycle(order);
		cleanMold(order);
	}
};
class ABS : public ProcessOrder_TM_4 {
public:
	ABS() {}
	~ABS() { DTOR("~ABS\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		algorithm = new strategy::ABS;
		algorithm->cycle(order);
	}
};
class Polypropylene : public ProcessOrder_TM_4 {
public:
	Polypropylene() {}
	~Polypropylene() { DTOR("~Polypropylene\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		algorithm = new strategy::Poly;
		algorithm->cycle(order);
	}
};
class Polyethelene : public ProcessOrder_TM_4 {
public:
	Polyethelene() {}
	~Polyethelene() { DTOR("~Polyethelene\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		algorithm = new strategy::Poly;
		algorithm->cycle(order);
	}
};
class PET : public ProcessOrder_TM_4 {
public:
	PET() {}
	~PET() { DTOR("~PET\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		algorithm = new strategy::PET;
		algorithm->cycle(order);
	}
};
// Seam point - add another plastic.

}

void process(map<string, string> order) {
	using namespace template_method;

	ProcessOrder_TM_4* processOrder = 0;

	if(		order["plastic"] == "ABS")				processOrder = new ABS;
	else if(order["plastic"] == "Polypropylene")	processOrder = new Polypropylene;
	else if(order["plastic"] == "Polyethelene")		processOrder = new Polyethelene;
	else if(order["plastic"] == "PET")				processOrder = new PET;
	// Seam point - add another plastic.

	else {											// Default is ABS.
		cout << "  <>Unknown plastic |" << order["plastic"] << "|";
		cout << " defaulting to ABS.\n";
		order["plastic"] = "ABS";
		processOrder = new ABS;
	}

	processOrder->run(order);

	delete processOrder;
}

pair<string, string> parse(string line) {
	char key[83];
	char val[83] = {0};

	sscanf(line.c_str(), "%s", key);

	char* equalSign = strchr(line.c_str(), '=');
	string value = "";
	if(equalSign) {	// tags = sam i am
		char*	nextToken = equalSign += 2;
		while(nextToken) {
			sscanf(nextToken, "%s", val);
			value += val;
			nextToken = strchr(nextToken+1, ' ');
			value += " ";
		}
		value.erase(value.length()-1, 1);
	}

	return make_pair(key, value);
}

map<string, string> getCompleteOrder(FILE* orderFilePtr) {
	map<string, string> order;
	char line[80+3];
	pair<string, string>	keyValue;

	while(fgets(line, 80, orderFilePtr)) {
		cout << line;
		if(strstr(line, "endOfOrder")) {
			return(order);
			}
		else {
			keyValue = parse(line);
			string key = keyValue.first;
			if(strchr(key.c_str(), ':'))	// Skip left justified order number.
				continue;
			string value = keyValue.second;
			order[key] = value;
		}
	}

	return order;
}

void demo(const string& orderFile) {
	cout << "<<< final design to original >>>\n";

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}
}

}

#endif /* DP4_SRC_D_TO_O_FINAL_H_ */
