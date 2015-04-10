/*
 * Solutions/final.h
 *
 *  Created on: Apr 6, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_SOLUTIONS_FINAL_H_
#define DP4_SRC_SOLUTIONS_FINAL_H_

namespace design_patterns_chart {}
/* Design Patterns Chart
 *   1 - Strategy: injection cycle (domain: plastic)
 *   2 - Adapter: cleaning mold (domains: plastic, metal)
 *   3 - Facade: milling mold
 * x 4 - Template Method: order processing
 * x 5 - Factory Method: packaging (domain: order)
 * - 6 - Decorator: tags, additives
 *   7 - Observer: bins(Subject) (conveyers & IJM pause on full)
 * x 8 - ChainOfR: mold location (inventory, mill, borrow, purchase)
 * x 9 - Bridge: milling
 * x10 - Abstract Factory: IJM_X, mold(metal, cavities), conveyer belt, bins (domain: size)
 */

namespace final_solution_file {

namespace abstract_factory {	// Done - depends on order size.

class IJM_AF {
public: virtual ~IJM_AF() { cout << "~IJM_AF "; }
	virtual string setup() { return "IJM_AF base"; }
};
class IJM_100 : public IJM_AF {
public: ~IJM_100() { cout << "~IJM_100 "; }
	string setup() { return "IJM_100"; }
};
class IJM_200 : public IJM_AF {
public: ~IJM_200() { cout << "~IJM_200 "; }
	string setup() { return "IJM_200"; }
};
// Seam point - add another InJection Molding machine.
class IJM_400 : public IJM_AF {
public: ~IJM_400() { cout << "~IJM_400 "; }
	string setup() { return "IJM_400"; }
};

class Mold_AF {
	unsigned m_cavities;
public:
	Mold_AF(unsigned cavities=0) : m_cavities(cavities) {}
public: virtual ~Mold_AF() { cout << "~Mold_AF "; }
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
// Seam point?

class ConveyerBelt_AF {
public: virtual ~ConveyerBelt_AF() { cout << "~ConveyerBelt_AF "; }
	virtual string setup() { return "ConveyerBelt_AF base"; }
};
class LinearBelt : public ConveyerBelt_AF {
public: ~LinearBelt() { cout << "~LinearBelt "; }
	string setup() { return "Linear conveyer belt"; }
};
class YSplitBelt : public ConveyerBelt_AF {
public: ~YSplitBelt() { cout << "~YSplitBelt "; }
	string setup() { return "Y-Split conveyer belt"; }
};
// Seam point - add another conveyer belt.
class VLevelBelt : public ConveyerBelt_AF {
public: ~VLevelBelt() { cout << "~VLevelBelt "; }
	string setup() { return "V-Level conveyer belt"; }
};

class PackageBin_AF {
public: virtual ~PackageBin_AF() { cout << "~PackageBin_AF\n"; }
	virtual string setup() { return "PackageBin_AF base"; }
};
class CardboardBox : public PackageBin_AF {
public: ~CardboardBox() { cout << "~CardboardBox "; }
	string setup() { return "CardboardBox"; }
};
class PallotBox : public PackageBin_AF {
public: ~PallotBox() { cout << "~PallotBox "; }
	string setup() { return "PallotBox"; }
};
// Seam point - add another conveyer belt.
class Crate : public PackageBin_AF {
public: ~Crate() { cout << "~Crate "; }
	string setup() { return "Crate"; }
};

class Setup_AF_10 {	// New specs (size).
public:
	virtual ~Setup_AF_10() { cout << "~Setup_AF_10\n"; }
	static Setup_AF_10* createInjectionLine(map<string, string> order);
public:
	virtual IJM_AF* createIJM(const map<string, string>& order) {
		cout << "    create IJM base\n";
		return new IJM_AF;
	}
	virtual Mold_AF* createMold(const map<string, string>& order) {
		cout << "    create Mold base\n";
		return new Mold_AF;
	}
	virtual ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		cout << "    create Belt base\n";
		return new ConveyerBelt_AF;
	}
	virtual PackageBin_AF* createBin(const map<string, string>& order) {
		cout << "    create Bin base\n";
		return new PackageBin_AF;
	}
};
class SmallOrder : public Setup_AF_10 {
public: ~SmallOrder() { cout << "~SmallOrder "; }
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_100;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Aluminum(1);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new LinearBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new CardboardBox;
	}
};
class MediumOrder : public Setup_AF_10 {
public: ~MediumOrder() { cout << "~MediumOrder "; }
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_200;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(1);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new LinearBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new PallotBox;
	}
};
// Seam point - add larger orders.
class LargeOrder : public Setup_AF_10 {
public: ~LargeOrder() { cout << "~LargeOrder "; }
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_400;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(2);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new YSplitBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new Crate;
	}
};
class HugeOrder : public Setup_AF_10 {
public: ~HugeOrder() { cout << "~HugeOrder "; }
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_400;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(4);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new VLevelBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new Crate;
	}
};

Setup_AF_10* Setup_AF_10::createInjectionLine(map<string, string> order) {
	unsigned size = atoi(order["size"].c_str());

	if(size <= 10000)	return new SmallOrder;
	else if(size <= 50000)	return new MediumOrder;
	// Seam point - add larger orders.
	else if(size <= 100000)	return new LargeOrder;
	else if(size <= 200000)	return new HugeOrder;

	return new Setup_AF_10;
}

}

namespace bridge {	// Done - depends on shape and metal.

class Platform {
public:
	static Platform* getPlatform(map<string,string> order);
public: virtual ~Platform() { cout << "~Platform_B_9\n"; }
	virtual string name() { return "base"; }
	virtual string drill()=0;
	virtual string cut()=0;
	virtual string grind()=0;
};
class HighCarbon : public Platform {	// Aluminum.
public: ~HighCarbon() { cout << "~HighCarbon "; }
	string name() { return "HighCarbon"; }
	string drill() { return "drill"; }
	string cut() { return "cut"; }
	string grind() { return "high speed grind"; }
};
class DiamondTipped : public Platform {	// Steel.
public: ~DiamondTipped() { cout << "~DiamondTipped "; }
	string name() { return "DiamondTipped"; }
	string drill() { return "precision drill"; }
	string cut() { return "oil cooled cut"; }
	string grind() { return "cartoid grind"; }
};
// Seam Point - add another platform.
class Carbide : public Platform {		// Brass.
public: ~Carbide() { cout << "~Carbide "; }
	string name() { return "Carbide"; }
	string drill() { return "high speed drill"; }
	string cut() { return "cross cut"; }
	string grind() { return "layer grind"; }
};

Platform* Platform::getPlatform(map<string,string> order) {
	string metal = order["metal"];
	if(metal == "aluminum")		return new HighCarbon;
	else if(metal == "steel")	return new DiamondTipped;
	// Seam Point - add another platform.
	else if(metal == "brass")	return new Carbide;

	return new HighCarbon;	// Default.
}

class Shape {
protected:
	Platform* platform;
public:
	Shape(Platform* platform) : platform(platform) {}
	virtual ~Shape() { cout << "~Shape_B_9 "; delete platform; }
public:
	static Shape* getShape(map<string,string> order);
public:
	virtual void mill(map<string,string>& order) {
		cout << "    Unknown shape " << order["mold"] << ".\n";
	}
};
class Duck : public Shape {
	string	name;
public: ~Duck() { cout << "~Duck "; }
	Duck(Platform* platform) : Shape(platform), name("duck") {};
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
	Car(Platform* platform) : Shape(platform), name("car") {};
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
	Hero(Platform* platform) : Shape(platform), name("hero") {};
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
	Dino(Platform* platform) : Shape(platform), name("dino") {};
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

Shape* Shape::getShape(map<string,string> order) {
	Platform* platform = Platform::getPlatform(order);
	string mold = order["mold"];

	if(mold == "duck")		return new Duck(platform);
	else if(mold == "car")	return new Car(platform);
	else if(mold == "hero")	return new Hero(platform);
	// Seam Point - add another shape.
	else if(mold == "dino")	return new Dino(platform);

	return new Shape(platform);	// Reports shape unknown.
}

}

namespace chain_of_resp {	// Done - depends on mold location.

class GetMold {
protected:
	GetMold* successor;
public:
	GetMold(GetMold* successor=0) : successor(successor) {};
	virtual ~GetMold() { cout << "~GetMold_CofR_8 "; }
public:
	virtual void from(map<string, string>& order) {
		string place = order["moldLoc"];
		string mold = order["mold"];
		cout << "  Can't find place " << place;
		cout << " to get " << mold << " mold from.\n";
	}
};
class Inventory : public GetMold {
public: ~Inventory() { cout << "~Inventory "; delete successor; }
	Inventory(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "inventory")
			cout << "    Pull " << order["mold"] << " mold from inventory.\n";
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};
class Mill : public GetMold {
public: ~Mill() { cout << "~Mill "; delete successor; }
	Mill(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		using namespace bridge;
		string place = order["moldLoc"];
		if(place == "mill") {
			cout << "    Create " << order["mold"] << " mold from mill ";
			cout << "with " << order["cavities"] << " cavities:\n";
			Shape* shape = Shape::getShape(order);
			shape->mill(order);
			delete shape;
			}
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};
// Seam points - add another mold source.
class SisterCompany : public GetMold {
public: ~SisterCompany() { cout << "~SisterCompany "; delete successor; }
	SisterCompany(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "sisterCompany")
			cout << "    Borrow " << order["mold"] << " mold from sister company.\n";
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};
class Purchase : public GetMold {
public: ~Purchase() { cout << "~Purchase "; delete successor; }
	Purchase(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "purchase")
			cout << "    Acquire " << order["mold"] << " mold via purchase.\n";
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};

}

namespace decorator {	// Additives(Done), Tags(Inwork).

class Tags_D_6 {
protected:
	Tags_D_6*	tag;
public:
	Tags_D_6(Tags_D_6* tag) : tag(tag) {}
	virtual ~Tags_D_6() {};
public:
	virtual unsigned width_mm() { return 0; }
};
class ModelNumber : public Tags_D_6 {
public:
	ModelNumber(Tags_D_6* tag) : Tags_D_6(tag) {}
public:
	unsigned width_mm() { return tag->width_mm() + 2; }
};

class Plastic {
public: virtual ~Plastic() { cout << "~Plastic_D_6\n"; }
	virtual unsigned mix() { return 0; }
	virtual string idNvol() { return ""; }
};
class Color : public Plastic {
	string		plastic;
	string		color;
	string		volstr;
	unsigned	volume;
	unsigned	colorVol;
public: ~Color() { cout << "~Color "; }
	Color(string plastic, string color="blue", string volstr="30")
	  : plastic(plastic), color(color), volstr(volstr),
		volume(atoi(volstr.c_str())),
		colorVol(volume/10) {
	}
	unsigned mix() { return volume + colorVol; }
	string idNvol() {
		char vol[80];
		sprintf(vol, "(%d)", colorVol);
		return plastic + "(" + volstr + ") " + color + string(vol);
	}
};
class Decorator : public Plastic {
protected: ~Decorator() { cout << "~Decorator "; }
	Plastic* 	delegate;
	unsigned	volume_m3;
public:
	Decorator(Plastic* delegate, unsigned volume_m3)
	  : delegate(delegate), volume_m3(volume_m3) {}
	string volAsStr() {
		char vol[80];
		sprintf(vol, "(%d)", volume_m3);
		return vol;
	}
};
class UVInhibiter : public Decorator {
public: ~UVInhibiter() { cout << "~UVInhibiter "; }
	UVInhibiter(Plastic* delegate, unsigned volume_m3)
	: Decorator(delegate, volume_m3) {}
	unsigned mix() { return delegate->mix() + volume_m3; }
	string idNvol() { return delegate-> idNvol() + " UVInhibiter" + volAsStr(); }
};
class AntiBacterial : public Decorator {
public: ~AntiBacterial() { cout << "~AntiBacterial "; }
	AntiBacterial(Plastic* delegate, unsigned volume_m3)
	: Decorator(delegate, volume_m3) {}
	unsigned mix() { return delegate->mix() + volume_m3; }
	string idNvol() { return delegate-> idNvol() + " AntiBacterial" + volAsStr(); }
};
// Seam point - add another additive.
class MicroFibers : public Decorator {
public: ~MicroFibers() { cout << "~MicroFibers "; }
	MicroFibers(Plastic* delegate, unsigned volume_m3)
	: Decorator(delegate, volume_m3) {}
	unsigned mix() { return delegate->mix() + volume_m3; }
	string idNvol() { return delegate-> idNvol() + " MicroFibers" + volAsStr(); }
};

}

namespace factory_method {	// Done - depends on order request.

class Packager_FM_5 {
public: virtual ~Packager_FM_5() { cout << "~Packager_FM_5\n"; }
public:
	static Packager_FM_5* makeObject(const string& type);
	virtual string wrap() { return "Packager_FM_5 base"; }
};
class Bulk : public Packager_FM_5 {
public: ~Bulk() { cout << "~Bulk "; }
	string wrap() { return "Bulk packager"; }
};
class ShrinkWrap : public Packager_FM_5 {
public: ~ShrinkWrap() { cout << "~ShrinkWrap "; }
	string wrap() { return "ShrinkWrap packager"; }
};
class HardPack : public Packager_FM_5 {
public: ~HardPack() { cout << "~HardPack "; }
	string wrap() { return "HardPack packager"; }
};
// Seam point - insert another packager.
class ZipLock : public Packager_FM_5 {
public: ~ZipLock() { cout << "~ZipLock "; }
	string wrap() { return "ZipLock packager"; }
};

Packager_FM_5* Packager_FM_5::makeObject(const string& type) {
	if(     type == "Bulk")			return new Bulk;
	else if(type == "ShrinkWrap")	return new ShrinkWrap;
	else if(type == "HardPack")		return new HardPack;
	// Seam point - insert another packager.
	else if(type == "ZipLock")		return new ZipLock;
	else {
		return new Packager_FM_5;
	}
}

}

namespace strategy {	// Inwork - depends on plastic (and metal?).

class Strategy {
public: virtual ~Strategy() { cout << "~Strategy\n"; }
public:
	virtual void cycle(int run) {
		cout << "    Cycle IJM via Strategy base.\n";
	}
	virtual void clean() {
		cout << "    Clean mold via Strategy base.\n";
	}
};
class ABS : public Strategy {
public: ~ABS() { cout << "~ABS "; }
	void cycle(int run) {
		cout << "    Cycle IJM for ABS " << run << " times.\n";
	}
	void clean() {
		cout << "    Clean mold used with ABS.\n";
	}
};
class Poly : public Strategy {
public: ~Poly() { cout << "~Poly "; }
	void cycle(int run) {
		cout << "    Cycle IJM for Poly " << run << " times.\n";
	}
	void clean() {
		cout << "    Clean mold used with Poly.\n";
	}
};
class PET : public Strategy {
public: ~PET() { cout << "~PET "; }
	void cycle(int run) {
		cout << "    Cycle IJM for PET " << run << " times.\n";
	}
	void clean() {
		cout << "    Clean mold used with PET.\n";
	}
};
class Synthetics : public Strategy {
public: ~Synthetics() { cout << "~Synthetics "; }
	void cycle(int run) {
		cout << "  Cycle IJM for Synthetics " << run << " times.\n";
	}
	void clean() {
		cout << "  Clean mold used with Synthetics.\n";
	}
};

}

namespace template_method {	// Inwork - depends on plastic.

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
	Plastic*			color;
	strategy::Strategy*	algorithm;
private:
	void setupLine(map<string, string>& order) {	// Abstract Factory.
		packager = Packager_FM_5::makeObject(order["packager"]);

		injectionLine = Setup_AF_10::createInjectionLine(order);

		ijm		= injectionLine->createIJM(order);
		mold	= injectionLine->createMold(order);	// CofR.
		belt	= injectionLine->createBelt(order);	// Factory Method.
		bin		= injectionLine->createBin(order);

		order["metal"] = mold->metal();
		char str[80];
		sprintf(str, "%d", mold->cavities());
		order["cavities"] = str;

		cout << "  Setup injection line for ";
		cout << order["size"] << " run with ";
		cout << packager->wrap() << ":\n    ";
		cout << ijm->setup() << " - ";
		cout << mold->setup() << " - ";
		cout << belt->setup() << " - ";
		cout << bin->setup();
		cout << endl;
	}
	void getMold(map<string, string>& order) {	// Chain of Responsibility.
		theMold =
			new Inventory(
			new Mill(
			// Seam point - add more mold sources.
			new SisterCompany(
			new Purchase(
			// ...
			new GetMold(
		)))));
		theMold->from(order);
	}
	void insertTags(map<string, string>& order) {	// Inwork Decorator.
		cout << "    Insert tags via decorator pattern.\n";
//		Tags_D_6* tags = new Tags_D_6;
		if(order.find("tag1") != order.end())
			cout << "      FOUND tag1\n";
	}
	void loadAdditiveBins(map<string, string>& order) {	// Decorator.
		cout << "    Load additive bins via decorator pattern.\n";
		color = new Color(order["plastic"], order["color"], order["volume"]);
		if(order.find("UVInhibiter") != order.end()) {
			unsigned volume = atoi(order["UVInhibiter"].c_str());
			color = new UVInhibiter(color, volume);
		}
		if(order.find("AntiBacterial") != order.end()) {
			unsigned volume = atoi(order["AntiBacterial"].c_str());
			color = new AntiBacterial(color, volume);
		}
		if(order.find("MicroFibers") != order.end()) {
			unsigned volume = atoi(order["MicroFibers"].c_str());
			color = new MicroFibers(color, volume);
		}
		cout << "      Recipe: " << color->idNvol();
		cout << " Total = " << color->mix() << ".\n";
	}
	virtual void injectionRun(map<string, string>& order) {
		cout << "    Example injection run - base class.\n";
	}
	void cleanMold() {
		algorithm->clean();
	}
public:
	virtual ~ProcessOrder_TM_4() {
		delete packager;
		delete ijm;
		delete mold;
		delete belt;
		delete bin;
		delete injectionLine;
		delete theMold;	cout << endl;
		delete color;
		delete algorithm;
		cout << "~ProcessOrder_TM_4\n";
	}
	void run(map<string, string>& order) {
		setupLine(order);
		cout << "  Run order via TemplateMethod\n";
		getMold(order);
		insertTags(order);
		loadAdditiveBins(order);
		injectionRun(order);	// Polymorphic step.
		cleanMold();
	}
};
class ABS : public ProcessOrder_TM_4 {
public: ~ABS() { cout << "~ABS\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::ABS;
		algorithm->cycle(atoi(order["size"].c_str()));
	}
};
class Polypropylene : public ProcessOrder_TM_4 {
public: ~Polypropylene() { cout << "~Polypropylene\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Poly;
		algorithm->cycle(atoi(order["size"].c_str()));
	}
};
class Polyethelene : public ProcessOrder_TM_4 {
public: ~Polyethelene() { cout << "~Polyethelene\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Poly;
		algorithm->cycle(atoi(order["size"].c_str()));
	}
};
class PET : public ProcessOrder_TM_4 {
public: ~PET() { cout << "~PET\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::PET;
		algorithm->cycle(atoi(order["size"].c_str()));
	}
};
// Seam point - add another plastic.
class Styrene : public ProcessOrder_TM_4 {
public: ~Styrene() { cout << "~Styrene\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Synthetics;
		algorithm->cycle(atoi(order["size"].c_str()));
	}
};
class Nylon66 : public ProcessOrder_TM_4 {
public: ~Nylon66() { cout << "~Nylon66\n"; }
	void injectionRun(map<string, string>& order) {
		algorithm = new strategy::Synthetics;
		algorithm->cycle(atoi(order["size"].c_str()));
	}
};

}

namespace patterns_todo {

class Mill_F_3 {};				// New specs (laser).
class PauseOnFull_O_7 {};
class InjectionCycle_S_1 {};	// New specs (plastics).
class Cleaning_A_2 {};			// New specs (plastics).

}

using namespace abstract_factory;
using namespace chain_of_resp;
using namespace template_method;

pair<string, string> parse(string line) {
	char key[83];
	char val[83];

	sscanf(line.c_str(), "%s", key);
	char* equalSign = strchr(line.c_str(), '=');
	if(equalSign) {
		sscanf(++equalSign, "%s", val);
	}

	return make_pair(key, val);
}

void process(map<string, string> order) {
	ProcessOrder_TM_4* processOrder = 0;

	if(		order["plastic"] == "ABS")			processOrder = new ABS;
	else if(order["plastic"] == "Polypropylene")processOrder = new Polypropylene;
	else if(order["plastic"] == "Polyethelene")	processOrder = new Polyethelene;
	else if(order["plastic"] == "PET")			processOrder = new PET;
	// Seam point - add another plastic.
	else if(order["plastic"] == "Styrene")		processOrder = new Styrene;
	else if(order["plastic"] == "Nylon66")		processOrder = new Nylon66;

	else {
		processOrder = new ProcessOrder_TM_4;	// Default process
	}

	processOrder->run(order);

	delete processOrder;
}

void reveal(map<string, string> order) {	// Diagnostic.
	map<string, string>::iterator it = order.begin();
	for(; it!=order.end(); it++) {
		cout << "[" << it->first << "] = " << it->second << "\n";
	}
	cout << "order[orderNum] = " << order["orderNum"] << "\n";
	cout << "order[mold] = " << order["mold"] << "\n";
	cout << "order[moldLoc] = " << order["moldLoc"] << "\n";
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


#endif /* DP4_SRC_SOLUTIONS_FINAL_H_ */
