/*
 * Solutions/final.h
 *
 *  Created on: Apr 6, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_SOLUTION_FINAL_H_
#define DP4_SRC_SOLUTION_FINAL_H_

namespace design_patterns_chart {}
/* Design Patterns Chart
 * x 1 - Strategy: injection cycle (domain: plastic)
 * x 2 - Adapter: cleaning mold (domains: plastic, metal)
 *   3 - Facade: milling mold
 * x 4 - Template Method: order processing
 * x 5 - Factory Method: packaging (domain: order)
 * x 6 - Decorator: tags, additives
 * x 7 - Observer: bins(Subject) (conveyers & IJM pause on full)
 * x 8 - ChainOfR: mold location (inventory, mill, borrow, purchase)
 * x 9 - Bridge: milling
 * x10 - Abstract Factory: IJM_X, mold(metal, cavities), conveyer belt, bins (domain: size)
 */

namespace final_solution_file {

namespace observer {	// Done (7) - no new spec dependency, darn.

/* Subject is to be the Package bin.
 * Observers are to be the IJM machine, conveyer belt, and eventually Packager.
 */

class Observer;
class Subject;

class Subject {
public:
	const string	name;
private:
	list<Observer*> observers;
public:
	Subject(string name="Named") : name(name) {}
	~Subject();
public:
	void attach(Observer* obs) { observers.push_back(obs); }
	void detach(Observer* obs) { observers.remove(obs); }
	void pause();
};

class Observer {
	Subject* subject;
public:
	Observer(Subject* subject) : subject(subject) {
		subject->attach(this);
	}
	virtual ~Observer() {
		subject->detach(this);
		cout << "~Observer_7\n";
	}
public:
	virtual void update(Subject* subject=0) {}
};

void Subject::pause() {
	cout << "      " << name << " package bin full...\n";
	list<Observer*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++) {
		(*it)->update(this);
	}
}
Subject::~Subject() {
	cout << "~Subject_7 ";
	cout << "Observers left to process (should be zero) = ";
	cout << observers.size() << ".\n";
}

}

namespace abstract_factory {	// Done (10) - depends on order size.

using namespace observer;

class IJM_AF : public Observer {
public:
	IJM_AF(Subject* subject) : Observer(subject) {}
	virtual ~IJM_AF() { cout << "~IJM_AF "; }
public:
	void update(Subject* subject) {
		cout << "        IJM pausing while " << subject->name;
		cout << " package bin is swapped.\n";
	}
	virtual string setup() { return "IJM_AF base"; }
};
class IJM_110 : public IJM_AF {					// PilotOrder.
public:
	IJM_110(Subject* subject) : IJM_AF(subject) {}
	~IJM_110() { cout << "~IJM_110 "; }
public:
	string setup() { return "IJM_110"; }
};
class IJM_120 : public IJM_AF {					// SmallOrder.
public:
	IJM_120(Subject* subject) : IJM_AF(subject) {}
	~IJM_120() { cout << "~IJM_120 "; }
public:
	string setup() { return "IJM_120"; }
};
class IJM_210 : public IJM_AF {					// MediumOrder.
public:
	IJM_210(Subject* subject) : IJM_AF(subject) {}
	~IJM_210() { cout << "~IJM_210 "; }
public:
	string setup() { return "IJM_210"; }
};
// Seam point - add another InJection Molding machine.
class IJM_140 : public IJM_AF {					// FastOrder.
public:
	IJM_140(Subject* subject) : IJM_AF(subject) {}
	~IJM_140() { cout << "~IJM_140 "; }
public:
	string setup() { return "IJM_140"; }
};
class IJM_220 : public IJM_AF {					// LargeOrder.
public:
	IJM_220(Subject* subject) : IJM_AF(subject) {}
	~IJM_220() { cout << "~IJM_220 "; }
public:
	string setup() { return "IJM_220"; }
};
class IJM_240 : public IJM_AF {					// HugeOrder.
public:
	IJM_240(Subject* subject) : IJM_AF(subject) {}
	~IJM_240() { cout << "~IJM_240 "; }
public:
	string setup() { return "IJM_240"; }
};

class Mold_AF {
	unsigned m_cavities;
public:
	Mold_AF(unsigned cavities=0) : m_cavities(cavities) {}
public: virtual ~Mold_AF() { cout << "~Mold_AF\n"; }
	virtual string setup() { return "Mold_AF base"; }
	virtual string metal() { return "unobtainium"; }
	unsigned cavities() { return m_cavities; }
	string cavitiesAsString() {
		char cav[] = "( )";
		cav[1] = cavities() + '0';
		string str = cav;
		return str;
	}
};
class Aluminum : public Mold_AF {
public: ~Aluminum() { cout << "~Aluminum "; }
	Aluminum(unsigned cavities=0) : Mold_AF(cavities) {}
public:
	string setup() { return "Aluminum" + cavitiesAsString(); }
	string metal() { return "aluminum"; }
};
class Steel : public Mold_AF {
public: ~Steel() { cout << "~Steel "; }
	Steel(unsigned cavities=0) : Mold_AF(cavities) {}
public:
	string setup() { return "Steel" + cavitiesAsString(); }
	string metal() { return "steel"; }
};

class ConveyerBelt_AF : public Observer  {
public:
	ConveyerBelt_AF(Subject* subject) : Observer(subject) {}
	virtual ~ConveyerBelt_AF() { cout << "~ConveyerBelt_AF "; }
public:
	void update(Subject* subject) {
		cout << "        Conveyer belt pausing while " << subject->name;
		cout << " package bin is swapped.\n";
	}
	virtual string setup() { return "ConveyerBelt_AF base"; }
};
class LinearBelt : public ConveyerBelt_AF {
public:
	LinearBelt(Subject* subject) : ConveyerBelt_AF(subject) {}
	~LinearBelt() { cout << "~LinearBelt "; }
public:
	string setup() {return "Linear conveyer belt"; }
};
class YSplitBelt : public ConveyerBelt_AF {
public:
	YSplitBelt(Subject* subject) : ConveyerBelt_AF(subject) {}
	~YSplitBelt() { cout << "~YSplitBelt "; }
public:
	string setup() { return "Y-Split conveyer belt"; }
};
// Seam point - add another conveyer belt.
class VLevelBelt : public ConveyerBelt_AF {
public:
	VLevelBelt(Subject* subject) : ConveyerBelt_AF(subject) {}
	~VLevelBelt() { cout << "~VLevelBelt "; }
public:
	string setup() { return "V-Level conveyer belt"; }
};

class PackageBin_AF : public Subject {
public:
	PackageBin_AF(string name) : Subject(name) {}
	virtual ~PackageBin_AF() { cout << "~PackageBin_AF "; }
public:
	virtual string setup() { return "PackageBin_AF base"; }
};
class CardboardBox : public PackageBin_AF {
public:
	CardboardBox() : PackageBin_AF("CardboardBox") {}
	~CardboardBox() { cout << "~CardboardBox "; }
public:
	string setup() { return "CardboardBox"; }
};
class PallotBox : public PackageBin_AF {
public:
	PallotBox() : PackageBin_AF("PallotBox") {}
	~PallotBox() { cout << "~PallotBox "; }
public:
	string setup() { return "PallotBox"; }
};
// Seam point - add another package bin.
class Crate : public PackageBin_AF {
public:
	Crate() : PackageBin_AF("Crate") {}
	~Crate() { cout << "~Crate "; }
public:
	string setup() { return "Crate"; }
};

class Setup_AF_10 {	// New specs (size).
public:
	virtual ~Setup_AF_10() { cout << "~Setup_AF_10\n"; }
	static Setup_AF_10* createInjectionLine(map<string, string>& order);
public:
	virtual IJM_AF* createIJM(const map<string, string>& order, Subject* subject)=0;
	virtual Mold_AF* createMold(const map<string, string>& order) {
		cout << "    create Mold base\n";
		return new Mold_AF;
	}
	virtual ConveyerBelt_AF* createBelt(const map<string, string>& order, Subject* subject)=0;
	virtual PackageBin_AF* createBin(const map<string, string>& order)=0;
};
class PilotOrder : public Setup_AF_10 {
public: ~PilotOrder() { cout << "~PilotOrder "; }
	IJM_AF* createIJM(const map<string, string>& order, Subject* subject) {
		return new IJM_110(subject);
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Aluminum(1);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order, Subject* subject) {
		return new LinearBelt(subject);
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new CardboardBox;
	}
};
class SmallOrder : public Setup_AF_10 {
public: ~SmallOrder() { cout << "~SmallOrder "; }
	IJM_AF* createIJM(const map<string, string>& order, Subject* subject) {
		return new IJM_120(subject);
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Aluminum(2);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order, Subject* subject) {
		return new YSplitBelt(subject);
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new CardboardBox;
	}
};
class MediumOrder : public Setup_AF_10 {
public: ~MediumOrder() { cout << "~MediumOrder "; }
	IJM_AF* createIJM(const map<string, string>& order, Subject* subject) {
		return new IJM_210(subject);
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(1);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order, Subject* subject) {
		return new LinearBelt(subject);
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new PallotBox;
	}
};
// Seam point - add larger orders.
class FastOrder : public Setup_AF_10 {
public: ~FastOrder() { cout << "~FastOrder "; }
	IJM_AF* createIJM(const map<string, string>& order, Subject* subject) {
		return new IJM_140(subject);
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Aluminum(4);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order, Subject* subject) {
		return new VLevelBelt(subject);
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new PallotBox;
	}
};
class LargeOrder : public Setup_AF_10 {
public: ~LargeOrder() { cout << "~LargeOrder "; }
	IJM_AF* createIJM(const map<string, string>& order, Subject* subject) {
		return new IJM_220(subject);
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(2);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order, Subject* subject) {
		return new YSplitBelt(subject);
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new Crate;
	}
};
class HugeOrder : public Setup_AF_10 {
public: ~HugeOrder() { cout << "~HugeOrder "; }
	IJM_AF* createIJM(const map<string, string>& order, Subject* subject) {
		return new IJM_240(subject);
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(4);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order, Subject* subject) {
		return new VLevelBelt(subject);
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new Crate;
	}
};

Setup_AF_10* Setup_AF_10::createInjectionLine(map<string, string>& order) {
	unsigned size = atoi(order["size"].c_str());

	if(size <= 10000)			return new PilotOrder;
	else if(size <= 20000)		return new SmallOrder;
	// Seam point - add fast order.
	else if(size <= 40000)		return new FastOrder;
	else if(size <= 50000)		return new MediumOrder;
	// Seam point - add larger orders.
	else if(size <= 100000)		return new LargeOrder;
	else if(size <= 200000)		return new HugeOrder;

	else {						// Defaulting to HugeOrder.
		cout << "  <>Size too large |" << size << "|";
		cout << " defaulting to HugeOrder.\n";
		order["size"] = "200000";
		return new HugeOrder;
	}
}

}

namespace bridge {	// Done (9) - depends on shape, metal and finish.

class Platform {
public:
	static Platform* getPlatform(map<string,string>& order);
public: virtual ~Platform() { cout << "~Platform_B_9\n"; }
	virtual string name() { return "base"; }
	virtual string drill()=0;
	virtual string cut()=0;
	virtual string grind()=0;
};
class HighCarbon : public Platform {	// Aluminum metal.
public: ~HighCarbon() { cout << "~HighCarbon "; }
	string name() { return "HighCarbon"; }
	string drill() { return "drill"; }
	string cut() { return "cut"; }
	string grind() { return "high speed grind"; }
};
class Carbide : public Platform {		// Steel metal.
public: ~Carbide() { cout << "~Carbide "; }
	string name() { return "Carbide"; }
	string drill() { return "high speed drill"; }
	string cut() { return "cross cut"; }
	string grind() { return "layer grind"; }
};
// Seam Point - add another platform.
class DiamondTipped : public Platform {	// Satin finish.
public: ~DiamondTipped() { cout << "~DiamondTipped "; }
	string name() { return "DiamondTipped"; }
	string drill() { return "precision drill"; }
	string cut() { return "oil cooled cut"; }
	string grind() { return "cartoid grind"; }
};

Platform* Platform::getPlatform(map<string,string>& order) {
	string metal = order["metal"];
	string finish = order["finish"];

	if(finish != "satin") {
		if(metal == "aluminum")		return new HighCarbon;
		else if(metal == "steel")	return new Carbide;
		}
	// Seam Point - add another platform.
	else if(finish == "satin"){
		return new DiamondTipped;
	}

	cout << "  <>Default milling platform is HighCarbon.\n";	// Should never happen.
	return new HighCarbon;	// Default.
}

class Shape {
protected:
	Platform* platform;
public:
	const unsigned volume_m3;
public:
	Shape(Platform* platform, unsigned volume_cc=0)
	  : platform(platform), volume_m3(volume_cc) {}
	virtual ~Shape() { cout << "~Shape_B_9 "; delete platform; }
public:
	static Shape* getShape(map<string,string>& order);
public:
	virtual void mill(map<string,string>& order) {
		cout << "    Unknown shape " << order["mold"] << ".\n";
	}
};
class Duck : public Shape {
	string	name;
public: ~Duck() { cout << "~Duck "; }
	Duck(Platform* platform) : Shape(platform, 35), name("duck") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "      using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};
class Car : public Shape {
	string	name;
public: ~Car() { cout << "~Car "; }
	Car(Platform* platform) : Shape(platform, 40), name("car") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "      using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};
class Hero : public Shape {
	string	name;
public: ~Hero() { cout << "~Hero "; }
	Hero(Platform* platform) : Shape(platform, 50), name("hero") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "      using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};
// Seam Point - add another shape.
class Dino : public Shape {
	string	name;
public: ~Dino() { cout << "~Dino "; }
	Dino(Platform* platform) : Shape(platform, 30), name("dino") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "      using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};

Shape* Shape::getShape(map<string,string>& order) {
	Platform* platform = Platform::getPlatform(order);

	if(order["mold"] == "duck")			return new Duck(platform);
	else if(order["mold"] == "car")		return new Car(platform);
	else if(order["mold"] == "hero")	return new Hero(platform);
	// Seam Point - add another shape.
	else if(order["mold"] == "dino")	return new Dino(platform);

	else {								// Defaulting to duck shape.
		cout << "    <>Unknown shape |" << order["mold"] << "|";
		cout << " defaulting to duck.\n";
		order["mold"] = "duck";
		return new Duck(platform);	// Reports shape unknown.
	}
}

}

namespace chain_of_resp {	// Done (8) - depends on mold location.

using namespace bridge;

class GetMold {
protected:
	GetMold* successor;
public:
	GetMold(GetMold* successor=0) : successor(successor) {};
	virtual ~GetMold() { cout << "~GetMold_CofR_8 "; }
public:
	virtual Shape* from(map<string, string>& order) {
		string place = order["moldLoc"];
		string mold = order["mold"];
		cout << "    <>Can't find place |" << place << "|";
		cout << " to get |" << mold << "| mold from, ";
		cout << "defaulting to duck from inventory.\n";
		order["moldLoc"] = "inventory";
		order["mold"]	 = "duck";

		return Shape::getShape(order);
	}
};
class Inventory : public GetMold {
public: ~Inventory() { cout << "~Inventory "; delete successor; }
	Inventory(GetMold* successor=0) : GetMold(successor) {};
public:
	Shape* from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "inventory") {
			cout << "    Pull " << order["mold"] << " mold from inventory.\n";
			return Shape::getShape(order);
			}
		else if(successor != 0)
			return successor->from(order);
		else
			return GetMold::from(order);	// Default.
	}
};
class Mill : public GetMold {
public: ~Mill() { cout << "~Mill "; delete successor; }
	Mill(GetMold* successor=0) : GetMold(successor) {};
public:
	Shape* from(map<string, string>& order) {
		using namespace bridge;
		string place = order["moldLoc"];
		if(place == "mill") {
			Shape* shape = Shape::getShape(order);
			cout << "    Create " << order["mold"] << " mold from mill ";
			cout << "with " << order["cavities"] << " cavities:\n";
			shape->mill(order);
			return shape;
			}
		else if(successor != 0)
			return successor->from(order);
		else
			return GetMold::from(order);	// Default.
	}
};
// Seam points - add another mold source.
class SisterCompany : public GetMold {
public: ~SisterCompany() { cout << "~SisterCompany "; delete successor; }
	SisterCompany(GetMold* successor=0) : GetMold(successor) {};
public:
	Shape* from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "sisterCompany") {
			cout << "    Borrow " << order["mold"] << " mold from sister company.\n";
			return Shape::getShape(order);
		}
		else if(successor != 0)
			return successor->from(order);
		else
			return GetMold::from(order);	// Default.
	}
};
class Purchase : public GetMold {
public: ~Purchase() { cout << "~Purchase "; delete successor; }
	Purchase(GetMold* successor=0) : GetMold(successor) {};
public:
	Shape* from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "purchase") {
			cout << "    Acquire " << order["mold"] << " mold via purchase.\n";
			return Shape::getShape(order);
		}
		else if(successor != 0)
			return successor->from(order);
		else
			return GetMold::from(order);	// Default.
	}
};

}

namespace decorator {	// Done (6) - Tags and Additives.

class Tags_D_6 {
public: virtual ~Tags_D_6() { cout << "~Tags_D_6 "; };
public:
	virtual unsigned width_mm() { return 0; }
	virtual string list() { return ""; }
public:
	void addTags(Tags_D_6* cavity, const string& list);
};
class Cavity : public Tags_D_6 {
public:
//	unsigned blankWidth_mm = 20;	// Default with no tags.
public: virtual ~Cavity() { cout << "~Cavity "; };
public:
	unsigned width_mm() { return 0; }
};
class Tag : public Tags_D_6 {
protected:
	Tags_D_6* delegate;
public:
	Tag(Tags_D_6* delegate) : delegate(delegate) {}
	virtual ~Tag() { cout << "~Tag "; delete delegate; }
};
class Blank : public Tag {
public:
	unsigned width;
public:
	Blank(Tags_D_6* delegate, unsigned width) : Tag(delegate), width(width) {}
	~Blank() { cout << "~Blank "; };
public:
	unsigned width_mm() { return delegate->width_mm() + width; }
	string list() { return delegate->list(); }
};
class ModelNumber : public Tag {
public:
	ModelNumber(Tags_D_6* delegate) : Tag(delegate) {}
	~ModelNumber() { cout << "~ModelNumber "; };
public:
	unsigned width_mm() { return delegate->width_mm() + 2; }
	string list() { return delegate->list() + "ModelNumber "; }
};
class Country : public Tag {
public:
	Country(Tags_D_6* delegate) : Tag(delegate) {}
	~Country() { cout << "~Country "; };
public:
	unsigned width_mm() { return delegate->width_mm() + 2; }
	string list() { return delegate->list() + "Country "; }
};
class Date : public Tag {
public:
	Date(Tags_D_6* delegate) : Tag(delegate) {}
	~Date() { cout << "~Date "; };
public:
	unsigned width_mm() { return delegate->width_mm() + 2; }
	string list() { return delegate->list() + "Date "; }
};
// Seam point - add more tags.
class IncCounter : public Tag {
public:
	IncCounter(Tags_D_6* delegate) : Tag(delegate) {}
	~IncCounter() { cout << "~IncCounter "; };
public:
	unsigned width_mm() { return delegate->width_mm() + 4; }
	string list() { return delegate->list() + "IncCounter "; }
};
class PartNumber : public Tag {
public:
	PartNumber(Tags_D_6* delegate) : Tag(delegate) {}
	~PartNumber() { cout << "~PartNumber "; };
public:
	unsigned width_mm() { return delegate->width_mm() + 2; }
	string list() { return delegate->list() + "PartNumber "; }
};
class RecycleCode : public Tag {
public:
	RecycleCode(Tags_D_6* delegate) : Tag(delegate) {}
	~RecycleCode() { cout << "~RecycleCode "; };
public:
	unsigned width_mm() { return delegate->width_mm() + 6; }
	string list() { return delegate->list() + "RecycleCode "; }
};

Tags_D_6* addTags(Tags_D_6* cavity, const string& list) {
	char val[83] = {0};
	const char*	remainingTokens = list.c_str();
	while(remainingTokens) {
		if(0 == sscanf(remainingTokens, "%s", val))
			break;
		if(!strcmp(val, "ModelNumber"))
			cavity = new ModelNumber(cavity);
		else if(!strcmp(val, "Country"))
			cavity = new Country(cavity);
		else if(!strcmp(val, "Date"))
			cavity = new Date(cavity);
		// Seam point - add more tags.
		else if(!strcmp(val, "IncCounter"))
			cavity = new IncCounter(cavity);
		else if(!strcmp(val, "PartNumber"))
			cavity = new PartNumber(cavity);
		else if(!strcmp(val, "RecycleCode"))
			cavity = new RecycleCode(cavity);

		else {
			cout << "Ignoring unknown tag " << val << ".\n";
		}

		remainingTokens = strchr(remainingTokens+1, ' ');
	}

	return cavity;
}

Tags_D_6* addBlankToFit(Tags_D_6* cavity) {
	return new Blank(cavity, 20 - cavity->width_mm());
}

class Plastic_D_6 {
public: virtual ~Plastic_D_6() { cout << "~Plastic_D_6 "; }
	virtual unsigned mix(unsigned cavities) { return 0; }
	virtual string idNvol() { return ""; }
};
class Color : public Plastic_D_6 {
	string		plastic;
	string		color;
	unsigned	volume;
	unsigned	colorVol;
public:
	Color(string plastic, string color, unsigned volume_m3=0)
	  : plastic(plastic), color(color),
		volume(volume_m3),
		colorVol(volume_m3/10) {
	}
	~Color() { cout << "~Color "; }
public:
	unsigned mix(unsigned cavities) {
		return cavities*(volume + colorVol);
	}
	string idNvol() {
		char volP[80]; sprintf(volP, "(%d) ", volume);
		char volC[80]; sprintf(volC, "(%d)", colorVol);
		return plastic + string(volP) + color + string(volC);
	}
};
class Additive : public Plastic_D_6 {
protected:
	Plastic_D_6* 	delegate;
	unsigned		volume_m3;
public:
	Additive(Plastic_D_6* delegate, unsigned volume_m3)
	  : delegate(delegate), volume_m3(volume_m3) {}
	 ~Additive() { cout << "~Additive "; delete delegate; }
public:
	 string volAsStr() {
		char vol[80];
		sprintf(vol, "(%d)", volume_m3);
		return vol;
	}
};
class UVInhibiter : public Additive {
public:
	UVInhibiter(Plastic_D_6* delegate, unsigned volume_m3)
	  : Additive(delegate, volume_m3) {}
	~UVInhibiter() { cout << "~UVInhibiter "; }
public:
	unsigned mix(unsigned cavities) {
		return delegate->mix(cavities) + cavities*volume_m3;
	}
	string idNvol() { return delegate-> idNvol() + " UVInhibiter" + volAsStr(); }
};
class AntiBacterial : public Additive {
public:
	AntiBacterial(Plastic_D_6* delegate, unsigned volume_m3)
	  : Additive(delegate, volume_m3) {}
	~AntiBacterial() { cout << "~AntiBacterial "; }
public:
	unsigned mix(unsigned cavities) {
		return delegate->mix(cavities) + cavities*volume_m3;
	}
	string idNvol() { return delegate-> idNvol() + " AntiBacterial" + volAsStr(); }
};
// Seam point - add another additive.
class MicroFibers : public Additive {
public:
	MicroFibers(Plastic_D_6* delegate, unsigned volume_m3)
	  : Additive(delegate, volume_m3) {}
	~MicroFibers() { cout << "~MicroFibers "; }
public:
	unsigned mix(unsigned cavities) {
		return delegate->mix(cavities) + cavities*volume_m3;
	}
	string idNvol() { return delegate-> idNvol() + " MicroFibers" + volAsStr(); }
};

Plastic_D_6* addAdditives(Plastic_D_6* color, map<string,string>& order) {
	if(order.find("UVInhibiter") != order.end()) {
		color = new UVInhibiter(color, atoi(order["UVInhibiter"].c_str()));
	}
	if(order.find("AntiBacterial") != order.end()) {
		color = new AntiBacterial(color, atoi(order["AntiBacterial"].c_str()));
	}
	// Seam point - add another additive.
	if(order.find("MicroFibers") != order.end()) {
		color = new MicroFibers(color, atoi(order["MicroFibers"].c_str()));
	}

	return color;
}

}

namespace factory_method {	// Done (5) - depends on order request.

using namespace observer;

class Packager_FM_5 : public Observer {
public:
	Packager_FM_5(Subject* subject) : Observer(subject) {}
	virtual ~Packager_FM_5() { cout << "~Packager_FM_5 "; }
public:
	static Packager_FM_5* makeObject(map<string,string>& order, Subject* subject);
	void update(Subject* subject) {
		cout << "        Packager pausing while " << subject->name;
		cout << " package bin is swapped.\n";
	}
	virtual string wrap() { return "Bulk packager (default)"; }
};
class Bulk : public Packager_FM_5 {
public:
	Bulk(Subject* subject) : Packager_FM_5(subject) {}
	~Bulk() { cout << "~Bulk "; }
public:
	string wrap() { return "Bulk packager"; }
};
class ShrinkWrap : public Packager_FM_5 {
public:
	ShrinkWrap(Subject* subject) : Packager_FM_5(subject) {}
	~ShrinkWrap() { cout << "~ShrinkWrap "; }
public:
	string wrap() { return "ShrinkWrap packager"; }
};
class HardPack : public Packager_FM_5 {
public:
	HardPack(Subject* subject) : Packager_FM_5(subject) {}
	~HardPack() { cout << "~HardPack "; }
public:
	string wrap() { return "HardPack packager"; }
};
// Seam point - add another packager.
class ZipLock : public Packager_FM_5 {
public:
	ZipLock(Subject* subject) : Packager_FM_5(subject) {}
	~ZipLock() { cout << "~ZipLock "; }
public:
	string wrap() { return "ZipLock packager"; }
};

Packager_FM_5* Packager_FM_5::makeObject(map<string,string>& order, Subject* subject) {
	if(     order["packager"] == "Bulk")		return new Bulk(subject);
	else if(order["packager"] == "ShrinkWrap")	return new ShrinkWrap(subject);
	else if(order["packager"] == "HardPack")	return new HardPack(subject);
	// Seam point - add another packager.
	else if(order["packager"] == "ZipLock")		return new ZipLock(subject);

	else {										// Defaulting to bulk packager.
		cout << "  <>Unknown packager |" << order["packager"] << "|";
		cout << " defaulting to Bulk packager.\n";
		order["packager"] = "Bulk";
		return new Bulk(subject);
	}
}

// Seam point - add another Observer.

class Stuffer_FM_5 : public Observer {
public:
	Stuffer_FM_5(Subject* subject) : Observer(subject) {}
	virtual ~Stuffer_FM_5() { cout << "~Stuffer_FM_5 "; }
public:
	static Stuffer_FM_5* makeObject(map<string,string>& order, Subject* subject);
	void update(Subject* subject) {
		cout << "        Stuffer filling " << subject->name;
		cout << " package bin with " << fill() << ".\n";
	}
public:
	virtual string fill() { return "<cushion> stuffing"; }
};
class Air : public Stuffer_FM_5 {
public:
	Air(Subject* subject) : Stuffer_FM_5(subject) {
//		subject->detach(this);	// Air stuffer is a null machine.
	}
	virtual ~Air() { cout << "~Air "; }
public:
	virtual string fill() { return "air stuffing"; }
};
class Popcorn : public Stuffer_FM_5 {
public:
	Popcorn(Subject* subject) : Stuffer_FM_5(subject) {}
	virtual ~Popcorn() { cout << "~Popcorn "; }
public:
	virtual string fill() { return "styrene popcorn stuffing"; }
};
class BubbleWrap : public Stuffer_FM_5 {
public:
	BubbleWrap(Subject* subject) : Stuffer_FM_5(subject) {}
	virtual ~BubbleWrap() { cout << "~BubbleWrap "; }
public:
	virtual string fill() { return "bubble wrap stuffing"; }
};
// Seam point - add another stuffer.
class Foam : public Stuffer_FM_5 {
public:
	Foam(Subject* subject) : Stuffer_FM_5(subject) {}
	virtual ~Foam() { cout << "~Foam "; }
public:
	virtual string fill() { return "expanding foam stuffing"; }
};

Stuffer_FM_5* Stuffer_FM_5::makeObject(map<string,string>& order, Subject* subject) {
	if(     order["stuffer"] == "Air")			return new Air(subject);
	else if(order["stuffer"] == "Popcorn")		return new Popcorn(subject);
	else if(order["stuffer"] == "BubbleWrap")	return new BubbleWrap(subject);
	// Seam point - add another stuffer.
	else if(order["stuffer"] == "Foam")			return new Foam(subject);

	else {									// Defaulting to Air stuffer.
		cout << "  <>Unknown stuffer |" << order["stuffer"] << "|";
		order["stuffer"] = "Air";
		cout << " defaulting to " << order["stuffer"] << " stuffer.\n";
		return new Air(subject);
	}
}

}

namespace legacy_classes {	// Can't change these.

class CleanABS {
public: ~CleanABS() { cout << "~CleanABS "; }
	void clean() {
		cout << "    Clean ABS mold: soak in alcohol, rinse with water, dry.\n";
	}
};

class CleanPolys {
public: ~CleanPolys() { cout << "~CleanPolys "; }
	void prepForReuse() {
		cout << "    Clean Poly mold: rinse with acetone, dry.\n";
	}
};

class PETCleanup {
public: ~PETCleanup() { cout << "~PETCleanup "; }
	void carbonize() { // Use only on stainless steel.
		cout << "    Clean PET steel mold: heat to 895 C.\n";
	}
	void purify() {	// Use only on aluminum.
		cout << "    Clean PET aluminum mold: rinse with soap and water, dry.\n";
	}
};

}

namespace adapter {	// Done (2) - depends on plastic and metal.

class CleanPlastic_A_2 {
public: virtual ~CleanPlastic_A_2() { cout << "~CleanPlastic_A_2 "; }
	virtual void clean(const string& metal) { cout << "  CleanPlastic base.\n"; }
};
class ABS : public CleanPlastic_A_2 {
	legacy_classes::CleanABS	plastic;
public: ~ABS() { cout << "~adapter::ABS "; }
	void clean(const string& metal) {
		plastic.clean();
	}
};
class Poly : public CleanPlastic_A_2 {
	legacy_classes::CleanPolys	plastic;
public: ~Poly() { cout << "~adapter::Poly "; }
	void clean(const string& metal) {
		plastic.prepForReuse();
	}
};
class PET : public CleanPlastic_A_2 {
	legacy_classes::PETCleanup	plastic;
public: ~PET() { cout << "~adapter::PET "; }
	void clean(const string& metal) {
		if(metal == "steel")
			plastic.carbonize();
		else
			plastic.purify();
	}
};
// Seam point - add new cleaning algorithm.
class Synthetics : public CleanPlastic_A_2 {
public: ~Synthetics() { cout << "~adapter::Synthetics "; }
	void clean(const string& metal) {
		cout << "    Clean synthetic mold: ozone wash.\n";
	}
};

}

namespace strategy {	// Done (1) - depends on plastic.

class Strategy {
protected:
	adapter::CleanPlastic_A_2* plastic;
public:
	Strategy(adapter::CleanPlastic_A_2* plastic) : plastic(plastic) {}
	virtual ~Strategy() { delete plastic; cout << "~Strategy_1\n"; }
public:
	virtual void cycle(int run) {
		cout << "    Cycle IJM via Strategy base.\n";
	}
	void clean(map<string, string>& order) {
		plastic->clean(order["metal"]);
	}
};
class ABS : public Strategy {
public:
	ABS() : Strategy(new adapter::ABS) {}
	~ABS() { cout << "~ABS "; }
public:
	void cycle(int run) {
		cout << "    Cycle IJM for ABS " << run << " times.\n";
		cout << "      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject.\n";
	}
};
class Poly : public Strategy {
public:
	Poly() : Strategy(new adapter::Poly) {}
	~Poly() { cout << "~Poly "; }
public:
	void cycle(int run) {
		cout << "    Cycle IJM for Poly " << run << " times.\n";
		cout << "      Close - heat to 350 - inject at 90 PSI - cool to 290 - separate - smooth eject.\n";
	}
};
class PET : public Strategy {
public:
	PET() : Strategy(new adapter::PET) {}
	~PET() { cout << "~PET "; }
public:
	void cycle(int run) {
		cout << "    Cycle IJM for PET " << run << " times.\n";
		cout << "      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject.\n";
	}
};
// Seam point - add more strategies.
class Synthetics : public Strategy {
public:
	Synthetics() : Strategy(new adapter::Synthetics) {}
	~Synthetics() { cout << "~Synthetics "; }
public:
	void cycle(int run) {
		cout << "    Cycle IJM for Synthetics " << run << " times.\n";
		cout << "      Close - heat to 480 - inject at 150 PSI - cool to 390 - separate - shock eject.\n";
	}
};

}

namespace template_method {	// Done (4) - depends on plastic.

using namespace abstract_factory;
using namespace factory_method;
using namespace decorator;
using namespace chain_of_resp;

class ProcessOrder_TM_4 {
protected:
	Packager_FM_5*		packager;
	Setup_AF_10*		injectionLine;
	IJM_AF*				ijm;
	Mold_AF*			mold;
	ConveyerBelt_AF*	belt;
	PackageBin_AF*		bin;
	GetMold* 			theMold;
	Shape*				shape;
	Tags_D_6*			cavity;
	Plastic_D_6*		color;
	strategy::Strategy*	algorithm;
	Stuffer_FM_5*		cushion;
private:
	void setupLine(map<string, string>& order) {	// Abstract Factory.
		if(order.find("size") == order.end()) {
			cout << "  <>No size specified, defaulting to 100.\n";
			order["size"] = "100";
		}

		injectionLine = Setup_AF_10::createInjectionLine(order);

		bin		= injectionLine->createBin(order);			// Observer Subject.

		ijm		= injectionLine->createIJM(order, bin);		// Observer.
		mold	= injectionLine->createMold(order);			// CofR, # of cavities.
		belt	= injectionLine->createBelt(order, bin);	// Observer.

		packager = Packager_FM_5::makeObject(order, bin);	// FM & O.

		cushion = Stuffer_FM_5::makeObject(order, bin);		// FM & O.

		order["metal"] = mold->metal();
		char str[80];
		sprintf(str, "%d", mold->cavities());
		order["cavities"] = str;

		cout << "  Setup injection line for ";
		cout << order["size"] << " run with ";
		cout << packager->wrap() << " and ";
		cout << cushion->fill() << ":\n    ";
		cout << ijm->setup() << " - ";
		cout << mold->setup() << " - ";
		cout << belt->setup() << " - ";
		cout << bin->setup();
		cout << endl;
	}
	void getMold(map<string, string>& order) {		// Chain of Responsibility.
		theMold =
			new Inventory(
			// Seam point - add more mold sources.
			new SisterCompany(
			new Purchase(
			// Seam point - mill likely location of last resort.
			new Mill(
			// ...
			new GetMold(
		)))));

		shape = theMold->from(order);	// Volume_m3.
	}
	void insertTags(map<string, string>& order) {	// Decorator.
		cavity = new Cavity();

		string list = "";
		if(order.find("tags") != order.end()) {
			list = order["tags"];
			cavity = decorator::addTags(cavity, list);
		}
		unsigned widthOfTags_mm = cavity->width_mm();
		cavity = decorator::addBlankToFit(cavity);
		cout << "    Insert tags [" << cavity->list() << "] of width ";
		cout << widthOfTags_mm << "/" << cavity->width_mm() << " mm.\n";
	}
	void loadAdditiveBins(map<string, string>& order) {	// Decorator.
		cout << "    Load plastic, color, and additive bins.\n";

		if(order.find("color") == order.end()) {
			cout << "      <>No color specified, defaulting to black.\n";
			order["color"] = "black";
		}
		color = new Color(order["plastic"], order["color"], shape->volume_m3);

		color = decorator::addAdditives(color, order);

		cout << "      Recipe: " << color->idNvol();
		cout << " Total = " << color->mix(mold->cavities()) << ".\n";
	}
protected:
	virtual void injectionRun(map<string, string>& order) {
		algorithm->cycle(atoi(order["size"].c_str()));
		bin->pause();
	}
private:
	void cleanMold(map<string, string>& order) {
		algorithm->clean(order);
	}
	// Seam point - add another step to the order processing.
	void ship(map<string, string>& order) {
		cout << "    Ship to \"" << order["address"] << "\"\n";
	}
public:
	virtual ~ProcessOrder_TM_4() {
		delete cushion;
		delete packager;
		delete ijm;
		delete mold;
		delete belt;
		delete bin;
		delete injectionLine;
		delete theMold;	cout << endl;
		delete shape;
		delete cavity;	cout << endl;
		delete color;	cout << endl;
		delete algorithm;
		cout << "~ProcessOrder_TM_4\n";
	}
	void run(map<string, string>& order) {
		setupLine(order);
		cout << "  Process order.\n";
		getMold(order);
		insertTags(order);
		loadAdditiveBins(order);
		injectionRun(order);	// Polymorphic step.
		cleanMold(order);
		// Seam point - add another step to the order processing.
		ship(order);
	}
};
class ABS : public ProcessOrder_TM_4 {
public: ~ABS() { cout << "~ABS\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::ABS;
		ProcessOrder_TM_4::injectionRun(order);
	}
};
class Polypropylene : public ProcessOrder_TM_4 {
public: ~Polypropylene() { cout << "~Polypropylene\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Poly;
		ProcessOrder_TM_4::injectionRun(order);
	}
};
class Polyethelene : public ProcessOrder_TM_4 {
public: ~Polyethelene() { cout << "~Polyethelene\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Poly;
		ProcessOrder_TM_4::injectionRun(order);
	}
};
class PET : public ProcessOrder_TM_4 {
public: ~PET() { cout << "~PET\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::PET;
		ProcessOrder_TM_4::injectionRun(order);
	}
};
// Seam point - add another plastic.
class Styrene : public ProcessOrder_TM_4 {
public: ~Styrene() { cout << "~Styrene\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Synthetics;
		ProcessOrder_TM_4::injectionRun(order);
	}
};
class Nylon66 : public ProcessOrder_TM_4 {
public: ~Nylon66() { cout << "~Nylon66\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Synthetics;
		ProcessOrder_TM_4::injectionRun(order);
	}
};

}

using namespace abstract_factory;
using namespace template_method;

void process(map<string, string> order) {
	ProcessOrder_TM_4* processOrder = 0;

	if(		order["plastic"] == "ABS")			processOrder = new ABS;
	else if(order["plastic"] == "Polypropylene")processOrder = new Polypropylene;
	else if(order["plastic"] == "Polyethelene")	processOrder = new Polyethelene;
	else if(order["plastic"] == "PET")			processOrder = new PET;
	// Seam point - add another plastic.
	else if(order["plastic"] == "Styrene")		processOrder = new Styrene;
	else if(order["plastic"] == "Nylon66")		processOrder = new Nylon66;

	else {										// Default process.
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
	cout << "<<< final solution >>>\n";

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}
}

}

#endif /* DP4_SRC_SOLUTION_FINAL_H_ */
