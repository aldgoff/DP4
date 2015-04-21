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
	Subject_7(string name="SubjectName") : name(name) {}
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
	virtual void update(Subject_7* subject=0) {
		cout << "        <machine> pausing while <Packager> package bin is swapped.\n";
	}
};

Subject_7::~Subject_7() {
	DTOR("~Subject_7 ");
	DTOR("Observers left to process (should be zero) = ");
	char str[80];
	sprintf(str, "%d.\n", observers.size());
	DTOR(str);
}

void Subject_7::pause() {
	cout << "      " << name << " package bin full...\n";
	list<Observer_7*>::iterator it=observers.begin();
	for(; it!=observers.end(); it++)
		(*it)->update(this);
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
class LinearBelt : public ConveyerBelt_AF {};
class YSplitBelt : public ConveyerBelt_AF {};
// Seam point - add another conveyer belt.

class PackageBin_AF {};
class CardboadrBox : public PackageBin_AF {};
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
	virtual void update(Subject_7* bin) {
		cout << "        <machine> pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
	virtual string setup() { return "IJM_AF base"; }
};
class Mold_AF {
public:
	const unsigned cavities;
public:
	Mold_AF(const unsigned cavities) : cavities(cavities) {}
	virtual ~Mold_AF() { DTOR("~Mold_AF\n"); }
public:
	virtual string setup() { return "Mold_AF base"; }
	virtual string metal() { return "unobtainium"; }
};
class ConveyerBelt_AF : public Observer_7 {
public:
	ConveyerBelt_AF(Subject_7* subject) : Observer_7(subject) {}
	virtual ~ConveyerBelt_AF() { DTOR("~ConveyerBelt_AF "); }
public:
	virtual void update(Subject_7* bin) {
		cout << "        <machine> pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
	virtual string setup() { return "ConveyerBelt_AF base"; }
};
class PackageBin_AF : public Subject_7 {
public:
	PackageBin_AF(string name="bin") : Subject_7(name) {}
	virtual ~PackageBin_AF() { DTOR("~PackageBin_AF ");	}
public:
	virtual string setup() { return "PackageBin_AF base"; }
};
class AbstractFactory_10 {
public:
	virtual ~AbstractFactory_10() { DTOR("AbstractFactory_10 "); }
public:
	virtual IJM_AF* createIJM(PackageBin_AF* bin) {
		return new IJM_AF(bin);
	}
	virtual Mold_AF* createMold() {
		return new Mold_AF(0);
	}
	virtual ConveyerBelt_AF* createConveyerBelt(PackageBin_AF* bin) {
		return new ConveyerBelt_AF(bin);
	}
	virtual PackageBin_AF* createPackageBin() {
		return new PackageBin_AF("PackageBin");
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
	InjectionLine_AF()
	  :	factory(0),
		ijm(0),
		mold(0),
		belt(0),
		bin(0)
	{}
	virtual ~InjectionLine_AF() {
		delete ijm;
		delete mold;
		delete belt;
		delete bin;
		delete factory;
		DTOR("~InjectionLine_AF\n");
	}
public:
	virtual AbstractFactory_10* buildFactory() { return new AbstractFactory_10; }
public:
	void createLine(map<string, string>& order) {
		factory = buildFactory();

		bin  = factory->createPackageBin();		// Subject in Observer pattern.

		ijm  = factory->createIJM(bin);			// Observer #1 in Observer pattern.
		mold = factory->createMold();
		belt = factory->createConveyerBelt(bin);// Observer #2 in Observer pattern.

		order["metal"] = mold->metal();
		char str[80];
		sprintf(str, "%d", mold->cavities);
		order["cavities"] = str;
	}
	virtual string getName() { return "BaseOrder"; }
	void setup() {
		cout << "    ";
		cout << ijm->setup() << " - ";
		cout << mold->setup() << " - ";
		cout << belt->setup() << " - ";
		cout << bin->setup();
		cout << endl;
	}
	PackageBin_AF* getBin() { return bin; }
public:
	static InjectionLine_AF* determineInjectionLine(map<string, string>& order);
};

// 10,000
class IJM_110 : public IJM_AF {
public:
	IJM_110(Subject_7* bin) : IJM_AF(bin) {}
	~IJM_110() { DTOR("~IJM_110 "); }
public:
	virtual void update(Subject_7* bin) {
		cout << "        IJM_110 pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
	string setup() { return "IJM_110"; }
};
class Aluminum : public Mold_AF {
public:
	Aluminum(const unsigned cavities) : Mold_AF(cavities) {}
	~Aluminum() { DTOR("~Aluminum "); }
public:
	string setup() {
		char str[80];
		sprintf(str, "(%d)", cavities);
		return(string("Aluminum") + str);
	}
	string metal() { return "aluminum"; }
};
class LinearBelt : public ConveyerBelt_AF {
public:
	LinearBelt(Subject_7* bin) : ConveyerBelt_AF(bin) {}
	~LinearBelt() { DTOR("~LinearBelt "); }
public:
	virtual void update(Subject_7* bin) {
		cout << "        Linear conveyer belt pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
	string setup() { return "Linear conveyer belt"; }
};
class CardboardBox : public PackageBin_AF {
public:
	CardboardBox() : PackageBin_AF("CardboardBox") {}
	~CardboardBox() { DTOR("~CardboardBox "); }
public:
	string setup() { return "CardboardBox"; }
};
class PilotOrder_AF : public AbstractFactory_10 {
public:
	~PilotOrder_AF() { DTOR("~PilotOrder_AF "); }
public:
	IJM_AF* createIJM(PackageBin_AF* bin) {
		return new IJM_110(bin);
	}
	Mold_AF* createMold() {
		return new Aluminum(1);
	}
	ConveyerBelt_AF* createConveyerBelt(PackageBin_AF* bin) {
		return new LinearBelt(bin);
	}
	PackageBin_AF* createPackageBin() {
		return new CardboardBox;
	}
};
class PilotOrder_IL : public InjectionLine_AF {
public:
	AbstractFactory_10* buildFactory() { return new PilotOrder_AF; }
	virtual string getName() { return "PilotOrder"; }
};

// 20,000
class IJM_120 : public IJM_AF {
public:
	IJM_120(Subject_7* bin) : IJM_AF(bin) {}
	~IJM_120() { DTOR("~IJM_120 "); }
public:
	virtual void update(Subject_7* bin) {
		cout << "        IJM_120 pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
	string setup() { return "IJM_120"; }
};
//class Aluminum : public Mold_AF {};
class YSplitBelt : public ConveyerBelt_AF {
public:
	YSplitBelt(Subject_7* bin) : ConveyerBelt_AF(bin) {}
	~YSplitBelt() { DTOR("~YSplitBelt "); }
public:
	virtual void update(Subject_7* bin) {
		cout << "        Y-Split conveyer belt pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
	string setup() { return "Y-Split conveyer belt"; }
};
//class CardboardBox : public PackageBin_AF {};
class SmallOrder_AF : public AbstractFactory_10 {
public:
	~SmallOrder_AF() { DTOR("~SmallOrder_AF "); }
public:
	IJM_AF* createIJM(PackageBin_AF* bin) {
		return new IJM_120(bin);
	}
	Mold_AF* createMold() {
		return new Aluminum(2);
	}
	ConveyerBelt_AF* createConveyerBelt(PackageBin_AF* bin) {
		return new YSplitBelt(bin);
	}
	PackageBin_AF* createPackageBin() {
		return new CardboardBox;
	}
};
class SmallOrder_IL : public InjectionLine_AF {
public:
	AbstractFactory_10* buildFactory() { return new SmallOrder_AF; }
	virtual string getName() { return "SmallOrder"; }
};

// 50,000
class IJM_210 : public IJM_AF {
public:
	IJM_210(Subject_7* bin) : IJM_AF(bin) {}
	~IJM_210() { DTOR("~IJM_210 "); }
public:
	virtual void update(Subject_7* bin) {
		cout << "        IJM_210 pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
	string setup() { return "IJM_210"; }
};
class Steel : public Mold_AF {
public:
	Steel(const unsigned cavities) : Mold_AF(cavities) {}
	~Steel() { DTOR("~Steel "); }
public:
	string setup() {
		char str[80];
		sprintf(str, "(%d)", cavities);
		return(string("Steel") + str);
	}
	string metal() { return "steel"; }
};
//class LinearBelt : public ConveyerBelt_AF {};
class PallotBox : public PackageBin_AF {
public:
	PallotBox() : PackageBin_AF("PallotBox") {}
	 ~PallotBox() { DTOR("~PallotBox "); }
public:
	string setup() { return "PallotBox"; }
};
class MediumOrder_AF : public AbstractFactory_10 {
public:
	~MediumOrder_AF() { DTOR("~MediumOrder_AF "); }
public:
	IJM_AF* createIJM(PackageBin_AF* bin) {
		return new IJM_210(bin);
	}
	Mold_AF* createMold() {
		return new Steel(1);
	}
	ConveyerBelt_AF* createConveyerBelt(PackageBin_AF* bin) {
		return new LinearBelt(bin);
	}
	PackageBin_AF* createPackageBin() {
		return new PallotBox;
	}
};
class MediumOrder_IL : public InjectionLine_AF {
public:
	AbstractFactory_10* buildFactory() { return new MediumOrder_AF; }
	virtual string getName() { return "MediumOrder"; }
};

// Seam point - add another family.

InjectionLine_AF* InjectionLine_AF::determineInjectionLine(map<string, string>& order) {
	unsigned size = atoi(order["size"].c_str());
	if(		size <= 10000) return new PilotOrder_IL;
	else if(size <= 20000) return new SmallOrder_IL;
	else if(size <= 50000) return new MediumOrder_IL;
	// Seam point - insert another family.

	else {						// Default.
		cout << "<>Size too large |";
		cout << order["size"] << "| defaulting to ";
		order["size"] = "50000";
		cout << order["size"] << ".\n";
		return new MediumOrder_IL;
	}
}

}

namespace bridge {			// DP 9.

class Platform_B_9 {
public:
	const string name;
public:
	Platform_B_9(const string name="platform") : name(name) {}
	virtual ~Platform_B_9() { DTOR("~Platform_B_9\n"); }
public:
	virtual string drill() { return "drill"; }
	virtual string cut() { return "cut"; }
	virtual string grind() { return "grind"; }
public:
	static Platform_B_9* getPlatform(map<string,string>& order);
};
class HighCarbon : public Platform_B_9 {
public:
	HighCarbon() : Platform_B_9("HighCarbon") {}
	virtual ~HighCarbon() { DTOR("~HighCarbon "); }
public:
	string drill() { return "drill"; }
	string cut() { return "cut"; }
	string grind() { return "high speed grind"; }
};
class Carbide : public Platform_B_9 {
public:
	Carbide() : Platform_B_9("Carbide") {}
	virtual ~Carbide() { DTOR("~Carbide "); }
public:
	string drill() { return "high speed drill"; }
	string cut() { return "cross cut"; }
	string grind() { return "layer grind"; }
};
// Seam Point - add another platform implementation.

Platform_B_9* Platform_B_9::getPlatform(map<string,string>& order) {
	string metal = order["metal"];
	if(		metal == "aluminum") return new HighCarbon;
	else if(metal == "steel") 	 return new Carbide;
	// Seam Point - insert another platform implementation.

	else {
		cout << "UNKNOWN METAL.\n";
		return new Platform_B_9;
	}
}

class Shape_B_9 {
protected:
	Platform_B_9* platform;
public:
	const unsigned volume_cc;
public:
	Shape_B_9(Platform_B_9* platform=0, const unsigned volume_cc=0)
	  : platform(platform),
		volume_cc(volume_cc)
	{}
	virtual ~Shape_B_9() {
		DTOR("~Shape_B_9 ");
		delete platform;
	}
public:
	virtual void mill(map<string,string>& order) {
		cout << "      using " << platform->name << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", ";
		cout << platform->grind() << ")";
		cout << " to mill <metal> block into <n> <shape> shapes with <finish> finish.\n";
	}
public:
	static Shape_B_9* getShape(map<string,string>& order);
};
class Duck : public Shape_B_9 {
public:
	Duck(Platform_B_9* platform)
		: Shape_B_9(platform, 35) {}
	~Duck() { DTOR("~Duck "); }
public:
	void mill(map<string,string>& order) {
		cout << "      using " << platform->name << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ")";
		cout << " to mill " << order["metal"] << " block";
		cout << " into " << order["cavities"] << " duck shapes";
		cout << " with " << order["finish"] << " finish.\n";
	}
};
class Car : public Shape_B_9 {
public:
	Car(Platform_B_9* platform)
		: Shape_B_9(platform, 40) {}
	~Car() { DTOR("~Car "); }
public:
	void mill(map<string,string>& order) {
		cout << "      using " << platform->name << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ")";
		cout << " to mill " << order["metal"] << " block";
		cout << " into " << order["cavities"] << " car shapes";
		cout << " with " << order["finish"] << " finish.\n";
	}
};
class Hero : public Shape_B_9 {
public:
	Hero(Platform_B_9* platform)
		: Shape_B_9(platform, 50) {}
	~Hero() { DTOR("~Hero "); }
public:
	void mill(map<string,string>& order) {
		cout << "      using " << platform->name << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ")";
		cout << " to mill " << order["metal"] << " block";
		cout << " into " << order["cavities"] << " hero shapes";
		cout << " with " << order["finish"] << " finish.\n";
	}
};
// Seam Point - add another shape abstraction.

Shape_B_9* Shape_B_9::getShape(map<string,string>& order) {
	Platform_B_9* platform = Platform_B_9::getPlatform(order);

	string shape = order["mold"];
	if(		shape == "duck")	return new Duck(platform);
	else if(shape == "car")		return new Car(platform);
	else if(shape == "hero")	return new Hero(platform);
	// Seam Point - insert another shape abstraction.

	else {					// Default.
		return new Duck(platform);
	}
}

}

namespace chain_of_resp {	// DP 8.

using namespace bridge;

class GetMold {
protected:
	GetMold* successor;
public:
	GetMold(GetMold* successor=0) : successor(successor) {}
	virtual ~GetMold() { DTOR("~GetMold_CofR_8 "); }
public:
	virtual Shape_B_9* from(map<string,string>& order) {
		string shape = order["mold"];
		string place = order["moldLoc"];
		cout << "    <>Can't find place |" << place << "|";
		cout << " to get |" << shape << "| mold from, ";
		cout << "defaulting to ";
		order["mold"] = "duck";
		order["moldLoc"] = "inventory";
		cout << order["mold"] << " from " << order["moldLoc"] << ".\n";
		return Shape_B_9::getShape(order);
	}
};
class Inventory : public GetMold {
public:
	Inventory(GetMold* successor) : GetMold(successor) {}
	~Inventory() { DTOR("~Inventory "); delete successor; }
public:
	virtual Shape_B_9* from(map<string,string>& order) {
		if(order["moldLoc"] == "inventory") {
			cout << "    Pull " << order["mold"] << " mold from inventory.\n";
			return Shape_B_9::getShape(order);
			}
		else if(successor)
			return successor->from(order);
		else {
			return GetMold::from(order);
		}
	}
};
class Mill : public GetMold {
public:
	Mill(GetMold* successor) : GetMold(successor) {}
	~Mill() { DTOR("~Mill "); delete successor; }
public:
	virtual Shape_B_9* from(map<string,string>& order) {
		if(order["moldLoc"] == "mill") {
			cout << "    Create " << order["mold"] << " mold";
			cout << " from mill with " << order["cavities"] << " cavities:\n";
			Shape_B_9* shape = Shape_B_9::getShape(order);
			shape->mill(order);
			return shape;
			}
		else if(successor)
			return successor->from(order);
		else {
			return GetMold::from(order);
		}
	}
};
// Seam points - add another responder.

}

namespace decorator {		// DP 6.

// Seam point - add another option.

}

namespace factory_method {	// DP 5.

using namespace observer;

class Packager_FM_5 : public Observer_7 {	// Observer #3 in Observer pattern.
public:
	Packager_FM_5(Subject_7* subject) : Observer_7(subject) {}
	virtual ~Packager_FM_5() { DTOR("~Packager_FM_5 "); }
public:
	static Packager_FM_5* createPackager(map<string,string>& order, Subject_7* bin);
public:
	virtual void update(Subject_7* bin) {
		cout << "        <machine> pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
public:
	virtual string name() { return "Default packager"; }
};
class Bulk : public Packager_FM_5 {
public:
	Bulk(Subject_7* bin) : Packager_FM_5(bin) {
		bin->detach(this);	// Bulk packager is a null machine.
	}
	~Bulk() { DTOR("~Bulk "); }
public:
	string name() { return "Bulk"; }
	virtual void update(Subject_7* bin) {
		cout << "        Bulk Packager pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
};
class ShrinkWrap : public Packager_FM_5 {
public:
	ShrinkWrap(Subject_7* bin) : Packager_FM_5(bin) {}
	~ShrinkWrap() { DTOR("~ShrinkWrap "); }
public:
	string name() { return "ShrinkWrap"; }
	virtual void update(Subject_7* bin) {
		cout << "        ShrinkWrap Packager pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
};
class HardPack : public Packager_FM_5 {
public:
	HardPack(Subject_7* bin) : Packager_FM_5(bin) {}
	~HardPack() { DTOR("~HardPack "); }
public:
	string name() { return "HardPack"; }
	virtual void update(Subject_7* bin) {
		cout << "        HardPack Packager pausing while ";
		cout << bin->name << " package bin is swapped.\n";
	}
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
using namespace chain_of_resp;

class ProcessOrder_TM_4 {
protected:
	strategy::Strategy_1* algorithm;
	abstract_factory_solti::InjectionLine_AF* injectionLine;
	Packager_FM_5*		packager;
	GetMold*			theMold;
	Shape_B_9*			shape;
public:
	ProcessOrder_TM_4()
	  : algorithm(0),	// When no derived classes (new strategy::Strategy_1).
		injectionLine(0),
		packager(0),
		theMold(0),
		shape(0)
	{}
	virtual ~ProcessOrder_TM_4() {
		delete packager;	// Must delete before injectionLine.
		delete injectionLine;
		delete theMold;
		DTOR("\n");
		delete shape;
		delete algorithm;
		DTOR("~ProcessOrder_TM_4\n");
	}
private:
	void setupInjectionLine(map<string, string>& order) {
		if(order.find("size") == order.end()) {
			order["size"] = "100";
			cout << "  <>No size specified, defaulting to " << order["size"] << ".\n";
		}

		injectionLine = InjectionLine_AF::determineInjectionLine(order);
		injectionLine->createLine(order);
		packager = Packager_FM_5::createPackager(order, injectionLine->getBin());

		cout << "  Setup " << injectionLine->getName() << " injection line";
		cout << " for " << order["size"] << " run";
		cout << " with " << packager->name() << " packager";
		cout << ":\n";

		injectionLine->setup();
	}
	void getMold(map<string, string>& order) {
		theMold =
			new Inventory(
			new Mill(
			new GetMold(
		)));

		shape = theMold->from(order);
	}
	void insertTags(map<string, string>& order) {
		cout << "    Insert tags [] of width 0/20 mm.\n";
	}
	void loadAdditives(map<string, string>& order) {
		cout << "    Load plastic, color, and additive bins.\n";
		if(order.find("color") == order.end()) {
			order["color"] = "black";
			cout << "      <>No color specified, defaulting to " << order["color"] << ".\n";
		}
		unsigned volume_cc = shape->volume_cc*0.1;
		cout << "      Recipe: <plastic>(" << shape->volume_cc << ") ";
		cout << order["color"] << " (" << volume_cc << ")";
		cout << " <additive1>(<vol>) <additive2>(<vol>) Total = <vol>.\n";

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
		// Seam point - insert another step.
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
		injectionLine->getBin()->pause();
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
		injectionLine->getBin()->pause();
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
		injectionLine->getBin()->pause();
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
		injectionLine->getBin()->pause();
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
