/*
 * carlos.h
 *
 *  Created on: May 1st 2015
 *      Author: Carlos Nava
 *
 *  Project: Intro to Design Patterns Pilot class.
 */

#ifndef DP4_SRC_STUDENTS_CARLOS_H_
#define DP4_SRC_STUDENTS_CARLOS_H_

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <list>


namespace final_carlos_file {

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

using namespace legacy_classes;

class CleanPlastic_A {
public:
	virtual void clean(string metal) = 0;
	virtual ~CleanPlastic_A() {DTOR("~CleanPlastic_A\n");};
};

class ABS: public CleanPlastic_A {
private:
	CleanABS abs;
public:
	void clean(string metal) {
		abs.clean();
	};
	~ABS() {DTOR("~adapter::ABS ");};
};

class Poly: public CleanPlastic_A {
private:
	CleanPolys poly;
public:
	void clean(string metal) {
		poly.prepForReuse();
	};
	~Poly() {DTOR("~adapter::Poly ");};
};

class Synth: public CleanPlastic_A {
public:
	void clean(string metal) {
		cout << "    Clean synthetic mold: ozone wash.\n";
	};
	~Synth() {DTOR("~Synth ");};
};


class PET: public CleanPlastic_A {
private:
	PETCleanup pte;
public:
	void clean(string metal) {
		if (metal == "Steel" ) {
			pte.carbonize();
		} else if (metal == "Aluminum") {
			pte.purify();
		} else {
			throw "OOPS!";
		};
	};
	~PET() {DTOR("~adapter::PET ");};
};


}

namespace strategy {		// DP 1.
class Strategy {
public:
	virtual void inject() = 0;
	virtual ~Strategy() {DTOR("~Strategy\n");};
};

class ABS: public Strategy {
	void inject() {
		cout << "      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject." << endl;
	};
	~ABS() {DTOR("~ABS ");};
};

class Poly: public Strategy {
	void inject() {
		cout << "      Close - heat to 350 - inject at 90 PSI - cool to 290 - separate - smooth eject." << endl;
	};
	~Poly() {DTOR("~Poly ");};
};

class PET: public Strategy {
	void inject() {
		cout << "      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject." << endl;
	};
	~PET() {DTOR("~PET ");};
};

class Synth: public Strategy {
	void inject() {
		cout << "      Close - heat to 480 - inject at 150 PSI - cool to 390 - separate - shock eject." << endl;
	};
	~Synth() {DTOR("~Synth ");};
};

}

namespace observer {		// DP 7.
class Observer;
class Subject;

class Subject {
	list<Observer*>	observers;
public:
	~Subject();
public:
	void attach(Observer* obs) { observers.push_back(obs); }
	void detach(Observer* obs) { observers.remove(obs); }
	void order(const int size);
};

class Observer {
	Subject& subject;
public:
	Observer(Subject& subject) : subject(subject) {
		subject.attach(this);
	}
	virtual ~Observer() {
		subject.detach(this);
		cout << " ~Observer.\n";
	}
public:
	virtual void update(Subject* subject=0)=0;
};

class Obs1 : public Observer {
public:
	Obs1(Subject& subject) : Observer(subject) {}
	~Obs1() { cout << "  ~Obs1:"; }
public:
	void update(Subject* subject) { cout << "  Observer 1.\n"; }
};


void Subject::order(const int size) {
	list<Observer*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++) {
		(*it)->update();
	}
	cout << endl;
};

Subject::~Subject() {
	cout << "  Observers left to process (should be zero) = ";
	cout << observers.size() << ".\n";
};


}

namespace abstract_factory {// DP 10.

class IJM_AF {
public:
	virtual ~IJM_AF() {DTOR("~IJM_AF\n")};
};

class IJM_110: public IJM_AF {
public:
	IJM_110() {cout << "    IJM_110 - ";};
	~IJM_110() {DTOR("~IJM_110 ")};
};

class IJM_120: public IJM_AF {
public:
	IJM_120() {cout << "    IJM_120 - ";};
	~IJM_120() {DTOR("~IJM_120 ")};
};

class IJM_210: public IJM_AF {
public:
	IJM_210() {cout << "    IJM_210 - ";};
	~IJM_210() {DTOR("~IJM_210 ")};
};

class IJM_140: public IJM_AF {
public:
	IJM_140() {cout << "    IJM_140 - ";};
	~IJM_140() {DTOR("~IJM_140 ")};
};

class IJM_220: public IJM_AF {
public:
	IJM_220() {cout << "    IJM_220 - ";};
	~IJM_220() {DTOR("~IJM_220 ")};
};

class IJM_240: public IJM_AF {
public:
	IJM_240() {cout << "    IJM_240 - ";};
	~IJM_240() {DTOR("~IJM_240 ")};
};

class Mold_AF {
protected:
	string type;
	int cavities;
public:
	string getType() { return type;};
	int getCavities() {return cavities;};
	Mold_AF(int cavities=1): cavities(cavities) {};
	virtual ~Mold_AF() {DTOR("~Mold_AF\n")};
};

class Aluminum: public Mold_AF {
public:
	Aluminum(int cavities=1): Mold_AF(cavities) {cout << "Aluminum(" << cavities << ") - "; type = "Aluminum";}
	~Aluminum() {DTOR("~Aluminum")};
};

class Steel: public Mold_AF {
public:
	Steel(int cavities=1): Mold_AF(cavities) {cout << "Steel(" << cavities << ")- "; type = "Steel";}
	~Steel() {DTOR("~Steel ")};
};

class ConveyerBelt_AF {
public:
	virtual ~ConveyerBelt_AF() {DTOR("~ConveyerBelt_AF\n")};
};

class LinearBelt: public ConveyerBelt_AF {
public:
	LinearBelt() {cout << "Linear conveyer belt - ";}
	~LinearBelt() {DTOR("~Linear ")};
};

class YSplitBelt: public ConveyerBelt_AF {
public:
	YSplitBelt() { cout << "Y-Split conveyer belt - ";}
	~YSplitBelt() {DTOR("~YSplitBelt ")};

};

class VLevelBelt: public ConveyerBelt_AF {
public:
	VLevelBelt() { cout << "V-Level conveyer belt - ";}
	~VLevelBelt() {DTOR("~VLevelBelt ")};

};

class PackageBin_AF {
protected:
	string packageBin;
public:
	PackageBin_AF(string package =""): packageBin(package) {};
	string getPackageBin() { return packageBin;};
	virtual ~PackageBin_AF() {DTOR("~PackageBin_AF\n")};
};

class CardboardBox: public PackageBin_AF {
public:
	CardboardBox() {
		packageBin = "CardboardBox";
		cout << packageBin << endl;
	};
	~CardboardBox() {DTOR("~CardboardBox ");}
};

class PallotBox: public PackageBin_AF {
public:
	PallotBox() {
		packageBin = "PallotBox";
		cout << packageBin << endl;
	}
	~PallotBox() {DTOR("~PallotBox ");}
};


class Crate: public PackageBin_AF {
public:
	Crate() {
		packageBin = "Crate";
		cout << packageBin << endl;
	}
	~Crate() {DTOR("~Crate ");}
};


class Setup_AF {
public:
	virtual ~Setup_AF() {DTOR("~Setup_AF\n");}
	static Setup_AF* setupLine(int size);

	virtual IJM_AF* createIJM() = 0;
	virtual Mold_AF* createMold() = 0;
	virtual ConveyerBelt_AF* createConveyer() = 0;
	virtual PackageBin_AF* createPackage() = 0;
};

class PilotOrder: public Setup_AF {
public:
	IJM_AF* createIJM() {return new IJM_110;};
	Mold_AF* createMold() { return new Aluminum;};
	ConveyerBelt_AF* createConveyer() { return new LinearBelt;};
	PackageBin_AF* createPackage() { return new CardboardBox;};

	~PilotOrder() {DTOR("~PilotOrder")};
};

class SmallOrder: public Setup_AF {
public:
	IJM_AF* createIJM() {return new IJM_120;};
	Mold_AF* createMold() { return new Aluminum(2);};
	ConveyerBelt_AF* createConveyer() { return new YSplitBelt;};
	PackageBin_AF* createPackage() { return new CardboardBox;};

	~SmallOrder() {DTOR("~SmallOrder ")};
};

class MediumOrder: public Setup_AF {
public:
	IJM_AF* createIJM() {return new IJM_210;};
	Mold_AF* createMold() { return new Steel;};
	ConveyerBelt_AF* createConveyer() { return new LinearBelt;};
	PackageBin_AF* createPackage() { return new PallotBox;};

	~MediumOrder() {DTOR("~MediumOrder ")};
};

class FastOrder: public Setup_AF {
public:
	IJM_AF* createIJM() {return new IJM_140;};
	Mold_AF* createMold() { return new Aluminum(4);};
	ConveyerBelt_AF* createConveyer() { return new VLevelBelt;};
	PackageBin_AF* createPackage() { return new PallotBox;};

	~FastOrder() {DTOR("~FastOrder ")};
};

class LargeOrder: public Setup_AF {
public:
	IJM_AF* createIJM() {return new IJM_220;};
	Mold_AF* createMold() { return new Steel(2);};
	ConveyerBelt_AF* createConveyer() { return new YSplitBelt;};
	PackageBin_AF* createPackage() { return new Crate;};

	~LargeOrder() {DTOR("~LargeOrder ")};
};

class HugeOrder: public Setup_AF {
public:
	IJM_AF* createIJM() {return new IJM_240;};
	Mold_AF* createMold() { return new Steel(4);};
	ConveyerBelt_AF* createConveyer() { return new VLevelBelt;};
	PackageBin_AF* createPackage() { return new Crate;};
	~HugeOrder() {DTOR("~HugeOrder ")};
};


Setup_AF* Setup_AF::setupLine(int size) {

	if (size <= 10000) return new PilotOrder;

	if (size <= 20000) return new SmallOrder;

	if (size <= 40000) return new FastOrder;

	if (size <= 50000) return new MediumOrder;

	if (size <= 100000) return new LargeOrder;

	if (size <= 200000) return new HugeOrder;

	throw "OOPS!";
};


}
// ----- Alternatively (may make it hard to match the dtor instrumentation) -----
namespace abstract_factory_solti {	// DP 10 - more like GoF.

class AbstractA{};
class AbstractB{};
class AbstractC{};
// ...

class AbstractFactory {};
class InjectionLine {};

// 10,000
class ConcreteA_1 : public AbstractA {};
class ConcreteB_1 : public AbstractB {};
class ConcreteC_1 : public AbstractC {};
class AF_1 : public AbstractFactory {};
class IL_1 : public InjectionLine {};

// 20,000
class ConcreteA_2 : public AbstractA {};
class ConcreteB_2 : public AbstractB {};
class ConcreteC_2 : public AbstractC {};
class AF_2 : public AbstractFactory {};
class IL_2 : public InjectionLine {};

// 50,000
class ConcreteA_3 : public AbstractA {};
class ConcreteB_3 : public AbstractB {};
class ConcreteC_3 : public AbstractC {};
class AF_3 : public AbstractFactory {};
class IL_3 : public InjectionLine {};

// Seam line - add another family.

}

namespace bridge {			// DP 9.

class Platform_B {
public:
	virtual void build(string metal, string finish, string shape, int n) = 0;
	virtual ~Platform_B() {DTOR("~Platform_B\n");};
};

class HighCarbon: public Platform_B {
public:
	void build(string metal, string finish, string shape, int n) {
		cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill ";
		cout << metal <<" block into " << n << " " << shape << " shapes with " << finish << " finish.\n";
	};

	~HighCarbon() {DTOR("~HighCarbon ");};
};

class Carbibe: public Platform_B {
public:
	void build(string metal, string finish, string shape, int n) {
		cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill ";
		cout << metal <<" block into " << n << " " << shape << " shapes with " << finish << " finish.\n";
	};

	~Carbibe() {DTOR("~Carbibe ");};
};

class Diamond: public Platform_B {
public:
	void build(string metal, string finish, string shape, int n) {
		cout << "      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind) to mill ";
		cout << metal <<" block into " << n << " " << shape << " shapes with " << finish << " finish.\n";
	};
	~Diamond() {DTOR("~Diamond ");};
};

class Shape_B {
protected:
	int vol;
public:
	Shape_B(int volume=0): vol(volume) {};
	virtual void create(Platform_B* platform, string metal, string finish, int n) {};
	virtual int getVolume() {return vol;};
	virtual ~Shape_B() {DTOR("~Shape_B ");};
};

class Duck: public Shape_B{
public:
	Duck(): Shape_B(35) {};
	void create(Platform_B* plat, string metal, string finish, int n) {
		plat->build(metal, finish, "duck", n);
	};
	~Duck() {DTOR("~Duck ");};
};

class Car: public Shape_B{
public:
	Car(): Shape_B(40) {};
	void create(Platform_B* plat, string metal, string finish, int n) {
		plat->build(metal, finish, "car", n);
	};
	~Car() {DTOR("~Car ");};
};

class Hero: public Shape_B{
public:
	Hero(): Shape_B(50) {};
	void create(Platform_B* plat, string metal, string finish, int n) {
		plat->build(metal, finish, "hero", n);
	};
	~Hero() {DTOR("~Hero ");};
};

class Dino: public Shape_B{
public:
	Dino(): Shape_B(30) {};
	void create(Platform_B* plat, string metal, string finish, int n) {
		plat->build(metal, finish, "dino", n);
	};
	~Dino() {DTOR("~Dino ");};
};


}

namespace chain_of_resp {	// DP 8.

using namespace bridge;
using namespace abstract_factory;

class GetMold_CofR {
protected:
	GetMold_CofR* succ;
public:
	GetMold_CofR(): succ(0) {};
	virtual ~GetMold_CofR() {DTOR("~GetMold_CofR\n")};

	void setSuccessor(GetMold_CofR* succ) {
		this->succ = succ;
	};
	virtual void handleRequest(map<string, string>& order, Mold_AF* mold, Shape_B* shape, Platform_B* platform) {
		cout << "    <>Can't find place || to get || mold from, defaulting to duck from inventory.\n";
	};

};

class Inventory: public GetMold_CofR {
public:
	void handleRequest(map<string, string>& order, Mold_AF* mold, Shape_B* shape, Platform_B* platform) {
		if (order["moldLoc"] == "inventory") {
			cout << "    Pull " << order["mold"] << " mold from inventory.\n";
		} else if (succ) succ->handleRequest(order, mold, shape, platform);
		else GetMold_CofR::handleRequest(order, mold, shape, platform);
	};
	~Inventory() {DTOR("~Inventory ")};
};

class Sister: public GetMold_CofR {
public:
	void handleRequest(map<string, string>& order, Mold_AF* mold, Shape_B* shape, Platform_B* platform) {
		if (order["moldLoc"] == "sisterCompany") {
			cout << "    Borrow " << order["mold"] << " mold from sister company.\n";
		} else if (succ) succ->handleRequest(order, mold, shape, platform);
		else GetMold_CofR::handleRequest(order, mold, shape, platform);
	};
	~Sister() {DTOR("~Sister ")};
};

class Purchase: public GetMold_CofR {
public:
	void handleRequest(map<string, string>& order, Mold_AF* mold, Shape_B* shape, Platform_B* platform) {
		if (order["moldLoc"] == "purchase") {
			cout << "    Acquire " << order["mold"] << " mold via purchase.\n";
		} else if (succ) succ->handleRequest(order, mold, shape, platform);
		else GetMold_CofR::handleRequest(order, mold, shape, platform);
	};
	~Purchase() {DTOR("~Purchase ")};
};

class Mill: public GetMold_CofR {
public:
	void handleRequest(map<string, string>& order, Mold_AF* mold, Shape_B* shape, Platform_B* platform) {
		if (order["moldLoc"] == "mill") {
			cout << "    Create " << order["mold"] << " mold from mill with " << mold->getCavities() << " cavities:\n";
			string moldT = mold->getType();
			shape->create(platform, moldT, order["finish"], mold->getCavities());
		} else if (succ) succ->handleRequest(order, mold, shape, platform);
		else GetMold_CofR::handleRequest(order, mold, shape, platform);
	};
	~Mill() {DTOR("~MIll ")};
};


}

namespace decorator {		// DP 6.

class Tag {
protected:
	string str;
public:
	Tag(string s=""): str(s) {};
	virtual string getDesc() {return str;};
	virtual int getWidth() {return 0;};
	virtual ~Tag() {DTOR("~Tag\n");};
};

class Tag_D: public Tag {
protected:
	Tag* tag;
public:
	Tag_D(Tag* tag, string str=""): Tag(str), tag(tag) {};
	string getDesc() {return tag->getDesc() + str;}
	virtual ~Tag_D() {DTOR("~Tag_D ");};
};

class Blank: public Tag {
public:
	Blank(string s ="") {};
	~Blank() {DTOR("~Blank ");};
};

class Model: public Tag_D {
public:
	Model(Tag* tag): Tag_D(tag, "ModelNumber ") {};
	int getWidth() {return tag->getWidth() + 2;};
	~Model() {DTOR("~Model "); tag->~Tag();};
};

class Country: public Tag_D{
public:
	Country(Tag* tag): Tag_D(tag, "Country ") {};
	int getWidth() {return tag->getWidth() + 2;};
	~Country() {DTOR("~Country "); tag->~Tag();};
};

class Date: public Tag_D{
public:
	Date(Tag* tag): Tag_D(tag, "Date") {};
	int getWidth() {return tag->getWidth() + 2;};
	~Date() {DTOR("~Date "); tag->~Tag();};
};

class Increment: public Tag_D{
public:
	Increment(Tag* tag): Tag_D(tag, "IncCounter") {};
	int getWidth() {return tag->getWidth() + 4;};
	~Increment() {DTOR("~Increment "); tag->~Tag();};
};

class PartNumber: public Tag_D{
public:
	PartNumber(Tag* tag): Tag_D(tag, "PartNumber") {};
	int getWidth() {return tag->getWidth() + 2;};
	~PartNumber() {DTOR("~PartNumber "); tag->~Tag();};
};

class RecycleCode: public Tag_D{
public:
	RecycleCode(Tag* tag): Tag_D(tag, "RecycleCode") {};
	int getWidth() {return tag->getWidth() + 6;};
	~RecycleCode() {DTOR("~RecycleCode "); tag->~Tag();};
};

class Plastic_D {
protected:
	string str;
	int vol;
public:
	Plastic_D(string s="", int vol=0): str(s), vol(vol) {};
	virtual string getDesc() {return str + "(" + to_string(vol) + ") ";};
	virtual int getVol() { return vol;};
	virtual ~Plastic_D() {DTOR("~Plastic_D\n");};
};

class Color: public Plastic_D {
public:
	Color(int vol=0, string color=""): Plastic_D(color , vol) {};
	~Color() {DTOR("~Color ");};
};

class Additive: public Plastic_D {
protected:
	Plastic_D* dec;
public:
	Additive(Plastic_D* dec, string str="", int vol = 0): Plastic_D(str, vol), dec(dec){};
	string getDesc() {return dec->getDesc() + str + "(" + to_string(vol) + ") ";}
	virtual ~Additive() {DTOR("~Additive ");};
};

class UVInhibiter: public Additive {
public:
	UVInhibiter(Plastic_D* dec, int vol): Additive(dec, "UVInhibiter", vol) {};
	int getVol() { return dec->getVol() + vol;};
	~UVInhibiter() {DTOR("~UVInhiviter ");};
};

class MicroFibers: public Additive {
public:
	MicroFibers(Plastic_D* dec, int vol): Additive(dec, "MicroFibers", vol) {};
	int getVol() { return dec->getVol() + vol; };
	~MicroFibers() {DTOR("MicroFibers ");};
};

class AntiBacterial: public Additive {
public:
	AntiBacterial(Plastic_D* dec, int vol): Additive(dec, "AntiBacterial", vol) {};
	int getVol() { return dec->getVol() + vol; };
	~AntiBacterial() {DTOR("AntiBacterial ");};
};

}

namespace factory_method {	// DP 5.

class Stuffer_FM {
public:
	static Stuffer_FM* makeObject(const string& type);
	virtual ~Stuffer_FM() {DTOR("~Stuffer_FM\n");};
};

class Air: public Stuffer_FM {
public:
	Air() { cout << "air";};
	~Air() {DTOR("~Air ");};
};

class Popcorn: public Stuffer_FM {
public:
	Popcorn() { cout << "styrene popcorn";};
	~Popcorn() {DTOR("~Popcorn ");};
};

class BubbleWrap: public Stuffer_FM {
public:
	BubbleWrap() { cout << "bubble wrap";};
	~BubbleWrap() {DTOR("~BubbleWrap ");};
};

class Foam: public Stuffer_FM {
public:
	Foam() { cout << "expanding foam";};
	~Foam() {DTOR("~Foam ");};
};

Stuffer_FM* Stuffer_FM::makeObject(const string& type) {
	if(     type == "Air")	return new Air;
	else if(type == "Popcorn")	return new Popcorn;
	else if(type == "BubbleWrap")	return new BubbleWrap;
	else if(type == "Foam")	return new Foam;
	else {
		throw "OOPS";
	}
}


class Packager_FM {
public:
	static Packager_FM* makeObject(const string& type);
	virtual ~Packager_FM() {DTOR("~Packager_FM\n");};
};

class Bulk: public Packager_FM {
public:
	Bulk() { cout << "Bulk";};
	~Bulk() {DTOR("~Bulk ");};
};

class ShrinkWrap: public Packager_FM {
public:
	ShrinkWrap() { cout << "ShrinkWrap";};
	~ShrinkWrap() {DTOR("~ShrinkWrap ");};
};

class HardPack: public Packager_FM {
public:
	HardPack() { cout << "HardPack";};
	~HardPack() {DTOR("~HardPack ");};
};

class ZipLock: public Packager_FM {
public:
	ZipLock() { cout << "ZipLock";};
	~ZipLock() {DTOR("~ZipLock ");};
};

Packager_FM* Packager_FM::makeObject(const string& type) {
	if(     type == "Bulk")	return new Bulk;
	else if(type == "ShrinkWrap")	return new ShrinkWrap;
	else if(type == "HardPack")	return new HardPack;
	else if(type == "ZipLock")	return new ZipLock;
	else {
		throw "OOPS";
	}
}


}

namespace template_method {	// DP 4.

using namespace abstract_factory;
using namespace decorator;
using namespace legacy_classes;
using namespace bridge;
using namespace chain_of_resp;
using namespace factory_method;
using namespace strategy;

class ProcessOrder_TM_4 {
private:
	map<string, string>& order;
	Setup_AF * setup;
	Packager_FM* packager;
	Stuffer_FM* stuffer;
	IJM_AF* ijm;
	Mold_AF* mold;
	ConveyerBelt_AF* conveyer;
	PackageBin_AF* package;
	Tag* tag;
	Plastic_D* plastic_d;
	adapter::CleanPlastic_A* clean;
	Shape_B* shape;
	Platform_B* platform;
	GetMold_CofR* inventory;
	GetMold_CofR* sister;
	GetMold_CofR* purchase;
	GetMold_CofR* mill;
	Strategy* inject;

public:

	ProcessOrder_TM_4(map<string, string>& order): order(order) {};
	void run() {

		setupLine();
		cout << "  Process order." << endl;
		getMold();
		insertTags();
		load();
		simulateClean();
		shipAddress();
//		destroy();	// Crashed when I ran it, right after order #1.
	};

	~ProcessOrder_TM_4() {DTOR("~ProcessOrder_TM_4\n")};
private:
	void setupLine() {
		int size = 0;

		//TODO: need to add a check for unknown plastic type.
		if (order.find("plastic") == order.end()) {
			cout << "  <>Unknown plastic || defaulting to ABS." << endl;
			order["plastic"] = "ABS";
		};

		if (order.find("size") == order.end()) {
			cout << "  <>No size specified, defaulting to 100." << endl;
			size = 100;
			order["size"] = "100";
		};

		if (order.find("packager")== order.end()) {
			cout << "  <>Unknown packager || defaulting to Bulk packager." << endl;
			order["packager"] = "Bulk";
		};


		if (order.find("stuffer")== order.end()) {
			cout << "  <>Unknown stuffer || defaulting to Air stuffer." << endl;
			order["stuffer"] = "Air";
		};

		size = stoi(order["size"]);
		if ( size > 200000) {
			  cout << "  <>Size too large |" << size << "| defaulting to HugeOrder of 200000.\n";
			  size = 200000;
		}

		cout << "  Setup injection line for " << size << " run with ";
		packager = Packager_FM::makeObject(order["packager"]);

		cout << " packager and ";
		stuffer = Stuffer_FM::makeObject(order["stuffer"]);
		cout << " stuffing." << endl;

		setup = Setup_AF::setupLine(size);
		ijm =  setup->createIJM();
		mold = setup->createMold();
		conveyer = setup->createConveyer();
		package = setup->createPackage();
	};

	void getMold() {

		//TODO: No idea why the || operator does not work below.
		if (order.find("mold") == order.end()) {
			shape = new Duck();
		};
		if (order["mold"] == "duck")  {
			shape = new Duck();
		} else if (order["mold"] == "car") {
			shape = new Car();
		} else if (order["mold"] == "hero") {
			shape = new Hero();
		} else if (order["mold"] == "dino") {
			shape = new Dino();
		};

		if (order["moldLoc"] == "mill") {
			string moldT = mold->getType();
			if ( moldT == "Aluminum") {
				platform = new HighCarbon();
			} else {
				if (order["finish"] == "satin") {
					platform = new Diamond();
				} else {
					platform = new Carbibe();
				};
			};
		};
		inventory = new Inventory();
		mill = new Mill();
		sister = new Sister();
		purchase = new Purchase();
		inventory->setSuccessor(sister);
		sister->setSuccessor(purchase);
		purchase->setSuccessor(mill);
		inventory->handleRequest(order, mold, shape, platform);
	};

	void insertTags() {
		cout << "    Insert tags [";

		tag = new Blank();

		if (order["tags"].find("IncCounter") != std::string::npos) {
			tag = new Increment(tag);
		};

		if (order["tags"].find("PartNumber") != std::string::npos) {
			tag = new PartNumber(tag);
		};

		if (order["tags"].find("RecycleCode") != std::string::npos) {
			tag = new RecycleCode(tag);
		};

		if (order["tags"].find("ModelNumber") != std::string::npos) {
			tag = new Model(tag);
		};

		if (order["tags"].find("Country") != std::string::npos) {
			tag = new Country(tag);
		};

		if (order["tags"].find("Date") != std::string::npos) {
			tag = new Date(tag);
		};

		cout << tag->getDesc() << "] of width " << tag->getWidth() << "/20 mm." << endl;
	};

	void load() {
		int color_vol;
		cout << "    Load plastic, color, and additive bins." << endl;
		if (order.find("color") == order.end()) {
			cout << "      <>No color specified, defaulting to black." << endl;
			order["color"] = "black";
		};

		cout << "      Recipe: " << order["plastic"] << "(" << shape->getVolume() << ") ";
		color_vol = shape->getVolume()*0.1;
		plastic_d = new Color(color_vol, order["color"]);

		if (order.find("UVInhibiter") != order.end()) {
			plastic_d = new UVInhibiter(plastic_d, stoi(order["UVInhibiter"]));
		};

		if (order.find("AntiBacterial") != order.end()) {
			plastic_d = new AntiBacterial(plastic_d, stoi(order["AntiBacterial"]));
		};

		if (order.find("MicroFibers") != order.end()) {
			plastic_d = new MicroFibers(plastic_d, stoi(order["MicroFibers"]));
		};

		cout << plastic_d->getDesc() << "Total = " << (shape->getVolume() + plastic_d->getVol())*mold->getCavities() << "." << endl;
	};

	void simulateClean() {
		if (order["plastic"] == "ABS") {
			clean = new adapter::ABS();
			inject = new strategy::ABS();
		} else if (order["plastic"].find("Poly") != std::string::npos) {
			clean = new adapter::Poly();
			inject = new strategy::Poly();
		} else if (order["plastic"] == "PET") {
			clean = new adapter::PET();
			inject = new strategy::PET();
		} else if (order["plastic"] == "Styrene") {
			clean = new adapter::Synth();
			inject = new strategy::Synth();
		} else if (order["plastic"] == "Nylon66") {
			clean = new adapter::Synth();
			inject = new strategy::Synth();
		} else {
			throw "OOOPS";
		};

		cout << "    Cycle IJM for " << order["plastic"] << " " << order["size"] << " times.\n";

		inject->inject();

		cout << "      " << package->getPackageBin() << " package bin full...\n";
		cout << "        IJM pausing while " << package->getPackageBin() << " package bin is swapped.\n";
		cout << "        Conveyer belt pausing while " << package->getPackageBin() << " package bin is swapped.\n";
		cout << "        Packager pausing while " << package->getPackageBin() << " package bin is swapped.\n";
		cout << "        Stuffer filling " << package->getPackageBin() << " package bin with ";
		Stuffer_FM::makeObject(order["stuffer"]);
		cout << " stuffing.\n";
		clean->clean(mold->getType());
	};

	void shipAddress() {
		cout << "    Ship to \"" << order["address"] << "\"" << endl;
	};

	void destroy() {
		delete packager;
		delete stuffer;
		delete ijm;
		delete mold;
		delete conveyer;
		delete package;
		delete setup;
		delete inventory;
		delete sister;
		delete purchase;
		delete mill;
		delete shape;
		delete platform;
		delete tag;
		delete plastic_d;
		delete inject;
		delete clean;
	};
};

}

void process(map<string, string>& order) {
	using namespace template_method;
	ProcessOrder_TM_4 processOrder(order);
	processOrder.run();

}

pair<string, string> parse(string line) {
	char key[83];
	char val[83] = {0};

	sscanf(line.c_str(), "%s", key);

	const char* equalSign = strchr(line.c_str(), '=');
	string value = "";
	if(equalSign) {	// tags = sam i am
		const char*	nextToken = equalSign += 2;
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
	cout << "<<< final design >>>\n";

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}
}

}

#endif /* DP4_SRC_STUDENTS_CARLOS_H_ */
