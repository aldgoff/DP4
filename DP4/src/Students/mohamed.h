/*
 * mohamed.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */
//#define DP4_SRC_STUDENTS_MOHAMED_H_	// Just to avoid warnings.
#ifndef DP4_SRC_STUDENTS_MOHAMED_H_
#define DP4_SRC_STUDENTS_MOHAMED_H_
#include <cstdlib>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using namespace std;

#include <typeinfo>
#include <sstream>

namespace final_mohamed_file {

const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }


class IJM{
public:
	IJM (string inMM, int inNC) : mm(inMM), numCavities(inNC) {};
	virtual ~IJM() { cout << "~IJM "; }
	string mm; //enum
	int numCavities;
	virtual void print() = 0;

};

// 10,000
class IJM_110 : public IJM {
public:
	IJM_110() : IJM("aluminum", 1) {};
	~IJM_110() { cout << "~IJM_110 "; }
	void print() {
		cout << "IJM_110 - Aluminum(1)";
	}
};

// 20,000
class IJM_120 : public IJM {
public:
	IJM_120() : IJM("aluminum", 2) {};
	~IJM_120() { cout << "~IJM_120 "; }
	void print() {
		cout << "IJM_120 - Aluminum(2)";
	}
};
// 40,000
class IJM_140 : public IJM {
public:
	IJM_140() : IJM("aluminum", 4) {};
	~IJM_140() { cout << "~IJM_140 "; }
	void print() {
		cout << "IJM_140 - Aluminum(4)";
	}
};
// 50,000
class IJM_210 : public IJM {
public:
	IJM_210() : IJM("steel", 1) {};
	~IJM_210() { cout << "~IJM_210 "; }
	void print() {
		cout << "IJM_210 - Steel(1)";
	}
};
// 100,000
class IJM_220 : public IJM {
public:
	IJM_220() : IJM("steel", 2) {};
	~IJM_220() { cout << "~IJM_220 "; }
	void print() {
		cout << "IJM_220 - Steel(2)";
	}
};
// 200,000
class IJM_240 : public IJM {
public:
	IJM_240() : IJM("steel", 4) {};
	~IJM_240() { cout << "~IJM_240 "; }
	void print() {
		cout << "IJM_240 - Steel(4)";
	}
};
class Tag{
public:
	Tag(int inSize) : size(inSize) {};
	virtual ~Tag() { cout << "~Tag "; }
	int size; //in millimeters
};
class ModelNumber : public Tag{
public:
	ModelNumber() : Tag(2) {};
	~ModelNumber() { cout << "~ModelNumber "; }
};
class Country : public Tag{
public:
	Country() : Tag(2) {};
	~Country() { cout << "~Country "; }
};
class Date : public Tag{
public:
	Date () : Tag(2) {};
	~Date() { cout << "~Date "; }
};
class IncCounter : public Tag{
public:
	IncCounter () : Tag(4) {};
	~IncCounter() { cout << "~IncCounter "; }
};
class PartNumber : public Tag{
public:
	PartNumber () : Tag(2) {};
	~PartNumber() { cout << "~PartNumber "; }
};
class RecycleCode : public Tag{
public:
	RecycleCode () : Tag(6) {};
	~RecycleCode() { cout << "~RecycleCode "; }
};
class Mold{
public:
	Mold(string inShape, string inMM, int inNC, string inFinish, int inVol) :
		shape(inShape), moldMetal(inMM), numCavities(inNC), finish(inFinish), tags(0), tagWidth(0), moldVol(inVol) {};
	virtual ~Mold() {
		vector<Tag *>::iterator tagIT;
		for (tagIT = tags.begin(); tagIT != tags.end(); tagIT++) {
			delete (*tagIT);
		}
		cout << "~Mold ";
	}
	string shape;
	string moldMetal;
	int numCavities;
	string finish;
	vector<Tag *> tags; //initialized in constructor. set in process function
	int tagWidth;    //initialized in constructor. set in process function
	int moldVol; //constant
};

class DuckMold : public Mold {
public:
	DuckMold(string inMM, int inNC, string inFinish) : Mold("duck", inMM, inNC, inFinish, 35) {} ;
	//moldVol = 35; colorVol = 3; //10% of moldVol, hardcoded for now but eventually change it to floor(moldVol*0.10)
	~DuckMold() { cout << "~DuckMold "; }
};
class CarMold : public Mold {
public:
	CarMold(string inMM, int inNC, string inFinish) : Mold("car", inMM, inNC, inFinish, 40) {};
	~CarMold() { cout << "~CarMold "; }
};
class HeroMold : public Mold {
public:
	HeroMold(string inMM, int inNC, string inFinish) : Mold("hero", inMM, inNC, inFinish, 50) {};
	~HeroMold() { cout << "~HeroMold "; }
};
class DinoMold : public Mold {
public:
	DinoMold(string inMM, int inNC, string inFinish) : Mold("dino", inMM, inNC, inFinish, 30) {};
	~DinoMold() { cout << "~DinoMold "; }
};
class Plastic {
public:
	Plastic(string inType, string inName, int mP, int iP, int sP, string ej) :
		type(inType), name(inName), meltPoint(mP), injectPressure(iP), solidPoint(sP), eject(ej) {};
	virtual ~Plastic() { cout << "~Plastic "; }
	string type; //name, like ABS
	string name;
	int meltPoint; //heat to this temp
	int injectPressure;
	int solidPoint; //cool to this temp
	string eject; //progressive or smooth
	virtual void clean() = 0;
};
class ABS : public Plastic {
public:
	ABS() : Plastic("ABS", "ABS", 440, 125, 360, "progressive") {};
	~ABS() { cout << "~ABS "; }
	void clean() {
		cout << "    Clean ABS mold: soak in alcohol, rinse with water, dry." << endl;
	}
};
class Polyp : public Plastic {
public:
	Polyp() : Plastic("Polypropylene", "Poly", 350, 90, 290, "smooth") {};
	~Polyp() { cout << "~Polyp "; }
	void clean() {
		cout << "    Clean Poly mold: rinse with acetone, dry." << endl;
	}
};
class Polye : public Plastic {
public:
	Polye() : Plastic("Polyethelene", "Poly", 350, 90, 290, "smooth") {};
	~Polye() { cout << "~Polye "; }
	void clean() {
		cout << "    Clean Poly mold: rinse with acetone, dry." << endl;
	}
};
class PET : public Plastic {
public:
	PET() : Plastic("PET", "PET", 404, 110, 340, "smooth") {};
	~PET() { cout << "~PET "; }
	void clean() {
		cout << "    Clean PET steel mold: heat to 895 C." << endl;
	}
};
class Styrene : public Plastic {
public:
	Styrene() : Plastic("Styrene", "Synthetics", 480, 150, 390, "shock") {};
	~Styrene() { cout << "~Styrene "; }
	void clean() {
		cout << "    Clean synthetic mold: ozone wash." << endl;
	}
};
class Nylon66 : public Plastic {
public:
	Nylon66() : Plastic("Nylon66", "Synthetics", 480, 150, 390, "shock") {};
	~Nylon66() { cout << "~Nylon66 "; }
	void clean() {
		cout << "    Clean synthetic mold: ozone wash." << endl;
	}
};
class Additive {
public:
	Additive(string name, int inVol) : type(name), vol(inVol) {};
	virtual ~Additive() { cout << "~Additive "; }
	string type; //name
	int vol; //cc
};

class UVInhibiter : public Additive {
public:
	UVInhibiter(int inVol) : Additive("UVInhibiter", inVol) {};
	~UVInhibiter() { cout << "~UVInhibiter "; }
};
class AntiBacterial : public Additive {
public:
	AntiBacterial(int inVol) : Additive("AntiBacterial", inVol) {};
	~AntiBacterial() { cout << "~AntiBacterial "; }
};
class MicroFibers : public Additive {
public:
	MicroFibers(int inVol) : Additive("MicroFibers", inVol) {};
	~MicroFibers() { cout << "~MicroFibers "; }
};

class Cushion {
public:
	Cushion(string inType) : type(inType) {};
	virtual ~Cushion() { cout << "~Cushion "; }
	string type;
};

class AirCushion : public Cushion {
public:
	AirCushion() : Cushion("air") {};
	~AirCushion() { cout << "~AirCushion "; }
};
class Popcorn : public Cushion {
public:
	Popcorn() : Cushion("styrene popcorn") {};
	~Popcorn() { cout << "~Popcorn "; }
};
class BubbleWrap : public Cushion {
public:
	BubbleWrap() : Cushion("bubblewrap") {};
	~BubbleWrap() { cout << "~BubbleWrap "; }
};
class Foam : public Cushion {
public:
	Foam() : Cushion("expanding foam") {};
	~Foam() { cout << "~Foam "; }
};
class Recipe {
public:
	Plastic * plastic;
	string color;  //red/black/yellow etc set at runtime
	double colorVol; //constant
	vector<Additive *> additives;
	double totalVol;
	~Recipe() {
		delete plastic;
		vector<Additive *>::iterator AddIT;
		for (AddIT = additives.begin(); AddIT != additives.end(); AddIT++) {
			delete (*AddIT);
		}
		cout << "~Recipe ";
	}
};

class ConveyorBelt {
public:
	virtual void print() = 0;
	virtual ~ConveyorBelt() { cout << "~ConveyorBelt "; }
};

class LinearBelt : public ConveyorBelt {
public:
	LinearBelt() : ConveyorBelt() {};
	~LinearBelt() { cout << "~LinearBelt "; }
	void print() {
		cout << "Linear conveyer belt";
	}
};
class YsplitBelt : public ConveyorBelt {
public:
	YsplitBelt() : ConveyorBelt() {};
	~YsplitBelt() { cout << "~YsplitBelt "; }
	void print() {
		cout << "Y-Split conveyer belt";
	}
};
class VlevelBelt : public ConveyorBelt {
public:
	VlevelBelt() : ConveyorBelt() {};
	~VlevelBelt() { cout << "~VlevelBelt "; }
	void print() {
		cout << "V-Level conveyer belt";
	}
};
class Packager {
public:
	virtual ~Packager() { cout << "~Packager "; }
};

class Bulk : public Packager {
public:
	Bulk() : Packager() {};
	~Bulk() { cout << "~Bulk "; }
};
class ShrinkWrap : public Packager {
public:
	ShrinkWrap() : Packager() {};
	~ShrinkWrap() { cout << "~ShrinkWrap "; }
};
class HardPack : public Packager {
public:
	HardPack() : Packager() {};
	~HardPack() { cout << "~HardPack "; }
};
class ZipLock : public Packager {
public:
	ZipLock() : Packager() {};
	~ZipLock() { cout << "~ZipLock "; }
};
class OutputBin {
public:
	OutputBin(string inType) : type(inType) {};
	virtual ~OutputBin() { cout << "~OutputBin "; }
	const string type;
};
class CardboardBox : public OutputBin {
public:
	CardboardBox() : OutputBin("CardboardBox") {};
	~CardboardBox() { cout << "~CardboardBox "; }
};
class PallotBox : public OutputBin {
public:
	PallotBox() : OutputBin("PallotBox") {};
	~PallotBox() { cout << "~PallotBox "; }
};
class Crate : public OutputBin {
public:
	Crate() : OutputBin("Crate") {};
	~Crate() { cout << "~Crate "; }
};


class MoldFactory{
public:
	//pull from invt or Mill the mold (create and return a Mold object)
	MoldFactory(string loc, string inMM, string inSh, int inNC, string inFin) : moldLoc(loc), moldMetal(inMM), shape(inSh), numCavities(inNC), finish(inFin) {} ;
	virtual ~MoldFactory() { cout << "~MoldLoc "; }
	virtual Mold* returnMold() = 0;//string inShape, string moldMetal, int numCavities, string inFinish);
	string moldLoc;
	string moldMetal;
	string shape;
	int numCavities;
	string finish;
	Mold * createShape();//use internal variables that should already be set. string inSh, string inMM, int inNC, string inFin);
};

class AlumMill : public MoldFactory{
public:
	AlumMill(string inSh, int inNC, string inFin) : MoldFactory("AlumMill", "aluminum", inSh, inNC, inFin) {};
	~AlumMill() { cout << "~AlumMill "; }
	Mold * returnMold();
};
class SteelMill: public MoldFactory{
public:
	SteelMill(string inSh, int inNC, string inFin) : MoldFactory("SteelMill", "steel", inSh, inNC, inFin) {};
	~SteelMill() { cout << "~SteelMill "; }
	Mold * returnMold();
};
class DiamondMill: public MoldFactory{
public:
	DiamondMill(string inSh, int inNC, string inFin) : MoldFactory("DiamondMill", "steel", inSh, inNC, inFin) {};
	~DiamondMill() { cout << "~DiamondMill "; }
	Mold * returnMold();
};
class Inventory : public MoldFactory{
public:
	Inventory(string inSh, string inMM, int inNC, string inFin) : MoldFactory("Inventory", inMM, inSh, inNC, inFin) {};
	~Inventory() { cout << "~Inventory "; }
	Mold * returnMold();
};
class SisterCompany : public MoldFactory{
public:
	SisterCompany(string inSh, string inMM, int inNC, string inFin) : MoldFactory("SisterCompany", inMM, inSh, inNC, inFin) {};
	~SisterCompany() { cout << "~SisterCompany "; }
	Mold * returnMold();
};
class Purchase : public MoldFactory{
public:
	Purchase(string inSh, string inMM, int inNC, string inFin) : MoldFactory("Purchase", inMM, inSh, inNC, inFin) {};
	~Purchase() { cout << "~Purchase "; }
	Mold * returnMold();
};
class InjectionLine {
public:
	InjectionLine (IJM* inIJM, double inCyc, ConveyorBelt* inCB, Packager* inPkg, Cushion * inCu, OutputBin* inOB) : //, Mold* inMold)
		ijm(inIJM), numCycles(inCyc), cb(inCB), pkgr(inPkg), cushion(inCu), ob(inOB) {}; //, mold(inMold)
	~InjectionLine() {
		delete ijm;
		delete cb;
		delete pkgr;
		delete cushion;
		delete ob;
		cout << "~InjectionLine ";
	}
	IJM* ijm;
	double numCycles;
	ConveyorBelt* cb;
	Packager* pkgr;
	Cushion * cushion;
	OutputBin* ob;
	void print(){
		cout << "    " ;
		ijm->print(); //IJM_110 - Aluminum(1)
		cout << " - " ;
		cb->print(); //Linear conveyer belt
		cout << " - " << ob->type << endl;
	}
};

/*** From his .cpp file. ***/

#include <typeinfo>
#include <sstream>

using namespace final_design_file;

Mold * AlumMill::returnMold()
{
	//alum
	cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill aluminum block into " << numCavities << " " << shape << " shapes with " << finish << " finish." << endl;
	return createShape();
}
Mold * SteelMill::returnMold()
{
	cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill steel block into " << numCavities << " " << shape << " shapes with " << finish << " finish." << endl;
	return createShape();
}
Mold * DiamondMill::returnMold()
{
	cout << "      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind) to mill steel block into " << numCavities << " " << shape << " shapes with " << finish << " finish." << endl;
	return createShape();
}
Mold * Inventory::returnMold()
{
	return createShape();
}
Mold * SisterCompany::returnMold() { return createShape(); }
Mold * Purchase::returnMold() { return createShape(); }

Mold * MoldFactory::createShape(){//string inSh, string inMM, int inNC, string inFin) {
	if (shape.compare("duck") == 0) {
		return new DuckMold(moldMetal, numCavities, finish);
	} else if (shape.compare("car") == 0) {
		return new CarMold(moldMetal, numCavities, finish);
	}  else if (shape.compare("hero") == 0) {
		return new HeroMold(moldMetal, numCavities, finish);
	}  else if (shape.compare("dino") == 0) {
		return new DinoMold(moldMetal, numCavities, finish);
	} else {
		cout << "ERROR: unknown shape given to mold factory" << endl;
		return NULL;
	}
}
InjectionLine* createInjectionLine(map<string, string>& order)
{

	IJM * ijm;
	ConveyorBelt * cb;
	Packager * pkgr;
	Cushion * cushion;
	OutputBin * ob;

	int orderSize = stoi(order["size"]);

	//IJM (set metal and cavities, which also used to set mold later), Conveyor belt, Mill
	switch (orderSize)
	{
	case 100:
		ijm = new IJM_110(); //If this 100 is by default, we use inventory anyway. but its possible to request 100 on purpose
		cb = new LinearBelt();
		ob = new CardboardBox();
		break;
	case 10000:
		ijm = new IJM_110();
		cb = new LinearBelt();
		ob = new CardboardBox();
		break;
	case 20000:
		ijm = new IJM_120();
		cb = new YsplitBelt();
		ob = new CardboardBox();
		break;
	case 40000:
		ijm = new IJM_140();
		cb = new VlevelBelt();
		ob = new PallotBox();
		break;
	case 50000:
		ijm = new IJM_210();
		cb = new LinearBelt();
		ob = new PallotBox();
		break;
	case 100000:
		ijm = new IJM_220();
		cb = new YsplitBelt();
		ob = new Crate();
		break;
	case 200000:
		ijm = new IJM_240();
		cb = new VlevelBelt();
		ob = new Crate();
		break;
	default:
		cout << endl << "ERROR: unhandled order size" << endl;
		std::exit(EXIT_FAILURE);
		break;
	}

	//Packager and OutputBin
	if (order["packager"].compare("Bulk") == 0) {
		pkgr = new Bulk();
	} else if (order["packager"].compare("ShrinkWrap") == 0) {
		pkgr = new ShrinkWrap();
	} else if (order["packager"].compare("HardPack") == 0) {
		pkgr = new HardPack();
	} else if (order["packager"].compare("ZipLock") == 0) {
		pkgr = new ZipLock();
	}

	//Stuffing
	if (order["stuffer"].compare("Air") == 0) {
		cushion = new AirCushion();
	} else if (order["stuffer"].compare("Popcorn") == 0) {
		cushion = new Popcorn();
	} else if (order["stuffer"].compare("BubbleWrap") == 0) {
		cushion = new BubbleWrap();
	} else if (order["stuffer"].compare("Foam") == 0) {
		cushion = new Foam();
	}


	double numCycles = orderSize / ijm->numCavities;
	cout << "  Setup injection line for " << numCycles <<" run with " << order["packager"] <<" packager and " << cushion->type << " stuffing:" << endl;

	InjectionLine * IL = new InjectionLine(ijm, numCycles, cb, pkgr, cushion, ob);
	IL->print(); //    IJM_110 - Aluminum(1) - Linear conveyer belt - CardboardBox

	return IL;
}


pair<string, string> parse(string line) {
	char key[83];
	char val[83] = {0};

	sscanf(line.c_str(), "%s", key);

	char* equalSign = (char*)strchr(line.c_str(), '=');
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
void setDefaults(map<string, string>& order) {

	if (order.count("mold") == 0) {
		//cout << " unknown mold specified, defaulting to Duck" << endl;
		order["mold"] = "duck";
	}
	if (order.count("finish") == 0) {
		//cout << " unknown finish specified, defaulting to smooth" << endl;
		order["finish"] = "smooth";
	}
	if (order.count("plastic") == 0) {
		cout << "  <>Unknown plastic || defaulting to ABS." << endl;
		order["plastic"] = "ABS";
	}
	if (order.count("size") == 0) {
		cout << "  <>No size specified, defaulting to 100." << endl;
		order["size"] = "100";
	}
	//Now that we know size is set, set max to 200,000
	if (stoi(order["size"]) > 200000) {
		cout << "  <>Size too large |400000| defaulting to HugeOrder of 200000." << endl;
		order["size"] = "200000";
	}
	if (order.count("packager") == 0) {
		cout << "  <>Unknown packager || defaulting to Bulk packager." << endl;
		order["packager"] = "Bulk";
	}
	if (order.count("stuffer") == 0) {
		cout << "  <>Unknown stuffer || defaulting to Air stuffer." << endl;
		order["stuffer"] = "Air";
	}
	if (order.count("tags") == 0) {
		order["tags"] = "";
	}
	if (order.count("address") == 0) {
		order["address"] = "";
	}
}

//This is the injection run.
//The process doesnt really change, but the parts of the process do.
//We may use different objects depending on the order attributes.
//We always need a mold machine, but we may need a IJM110 or 120
//or 210 object depending on the size of the order

void process(map<string, string>& order) {
	//order is a hash where the keys are order attributes like size, moldshape, plastic
	//the values are the values like 10,000, duck, ABS

	//Set default values for missing attributes in the order
	setDefaults(order);

	//Setup the injection Line

	InjectionLine* IL = createInjectionLine(order);

	cout << "  Process order." << endl;

	//get/create and install mold from inventory or using mill to create
	MoldFactory * mFactory;
	Mold * mold = NULL;
	//where are we getting the mold from: inventory obj or mill obj
	if (order.count("moldLoc") == 0) {
		cout << "    <>Can't find place || to get || mold from, defaulting to " << order["mold"] << " from inventory." << endl;
		mFactory = new Inventory(order["mold"], IL->ijm->mm, IL->ijm->numCavities, order["finish"]);
	} else if (order["moldLoc"].compare("inventory") == 0){
		cout << "    Pull " << order["mold"] << " mold from inventory. " << endl;
		mFactory = new Inventory(order["mold"], IL->ijm->mm, IL->ijm->numCavities, order["finish"]);
	} else if (order["moldLoc"].compare("sisterCompany") == 0) {
		cout << "    Borrow " << order["mold"] << " mold from sister company. " << endl;
		mFactory = new SisterCompany(order["mold"], IL->ijm->mm, IL->ijm->numCavities, order["finish"]);
	} else if (order["moldLoc"].compare("purchase") == 0) {
		cout << "    Acquire " << order["mold"] << " mold via purchase. " << endl;
		mFactory = new Purchase(order["mold"], IL->ijm->mm, IL->ijm->numCavities, order["finish"]);
	} else if (order["moldLoc"].compare("mill") == 0) {

		string ijmType = typeid(*(IL->ijm)).name(); //get the derived class name of this object (pointer is base class)
		if (ijmType.compare("class final_design_file::IJM_110") == 0) {
			//i know its aluminum with 1 cavity
			mFactory = new AlumMill(order["mold"], 1, order["finish"]);
		} else if (ijmType.compare("class final_design_file::IJM_120") == 0) {
			//aluminum with 2 cavity
			mFactory = new AlumMill(order["mold"], 2, order["finish"]);
		} else if (ijmType.compare("class final_design_file::IJM_140") == 0) {
			//aluminum with 4 cavity
			mFactory = new AlumMill(order["mold"], 4, order["finish"]);
		} else if (ijmType.compare("class final_design_file::IJM_210") == 0) {
			//steel with 1 cavity
			mFactory = new SteelMill(order["mold"], 1, order["finish"]);
		} else if (ijmType.compare("class final_design_file::IJM_220") == 0) {
			//steel with 2 cavity
			mFactory = new SteelMill(order["mold"], 2, order["finish"]);
		} else if (ijmType.compare("class final_design_file::IJM_240") == 0) {
			//steel with 4 cavity
			mFactory = new DiamondMill(order["mold"], 4, order["finish"]);
		}

		cout << "    Create " << mFactory->shape << " mold from mill with " << mFactory->numCavities << " cavities:" << endl;
	}
	mold = NULL;
	mold = mFactory->returnMold();
	if (mold == NULL) {
		cout << "ERROR: factory could not create mold" << endl;
		exit(EXIT_FAILURE);
	}

	//insert tags into mold
	istringstream iss (order["tags"]);
	string tagName;
	if (order["tags"].compare("") == 0) {
		//no tag was set, dnot push any tag objects, but set width to 0
		mold->tagWidth = 0;
	} else {
		//parse the list of strings and for loop. set size to defalut for now
		Tag * moldTag;
		while (iss >> tagName) {
			if (tagName.compare("ModelNumber") == 0) {
				moldTag = new ModelNumber();
			} else if (tagName.compare("Country") == 0) {
				moldTag = new Country();
			} else if (tagName.compare("Date") == 0) {
				moldTag = new Date();
			} else if (tagName.compare("IncCounter") == 0) {
				moldTag = new IncCounter();
			} else if (tagName.compare("PartNumber") == 0) {
				moldTag = new PartNumber();
			} else if (tagName.compare("RecycleCode") == 0) {
				moldTag = new RecycleCode();
			}
			mold->tags.push_back(moldTag);
			mold->tagWidth += moldTag->size;
		}
	}
	cout << "    Insert tags [" << order["tags"] << "] of width " << mold->tagWidth << "/20 mm." <<endl;

	//Create Recipe by loading additive components (plastic, color, optional additives like uvinhibiter)
	Recipe * recipe = new Recipe;
	cout << "    Load plastic, color, and additive bins." << endl;
	if (order.count("color") == 0) {
		cout << "      <>No color specified, defaulting to black." << endl;
		order["color"] = "black";
	}
	//Plastic * plastic;
	if (order["plastic"].compare("ABS") == 0) {
		recipe->plastic = new ABS();
	} else if (order["plastic"].compare("Polypropylene") == 0) {
		recipe->plastic = new Polyp();
	} else if (order["plastic"].compare("Polyethelene") == 0) {
		recipe->plastic = new Polye();
	} else if (order["plastic"].compare("PET") == 0) {
		recipe->plastic = new PET();
	} else if (order["plastic"].compare("Styrene") == 0) {
		recipe->plastic = new Styrene();
	} else if (order["plastic"].compare("Nylon66") == 0) {
		recipe->plastic = new Nylon66();
	}

	//recipe->plastic = plastic;
	recipe->color = order["color"];
	recipe->colorVol = floor(mold->moldVol * 0.10); //color vol is floor( 10% of mold volume)
	recipe->totalVol = mold->moldVol + recipe->colorVol;
	//optional additives
	if (order.count("UVInhibiter") != 0) {
		//if this key exists in order hash, add this additive to recipe
		recipe->additives.push_back(new UVInhibiter(stoi(order["UVInhibiter"]))); //the value of the key-value pair is the volume of additive.
	}
	if (order.count("AntiBacterial") != 0) {
		recipe->additives.push_back(new AntiBacterial(stoi(order["AntiBacterial"])));
	}
	if (order.count("MicroFibers") != 0) {
		recipe->additives.push_back(new MicroFibers(stoi(order["MicroFibers"])));
	}

	cout << "      Recipe: " << recipe->plastic->type << "(" << mold->moldVol << ") "
							<< recipe->color << "(" << recipe->colorVol << ") ";
	vector<Additive *>::iterator it;
	for (it = recipe->additives.begin(); it != recipe->additives.end(); it++) {
		cout << (*it)->type << "(" << (*it)->vol << ") ";
		recipe->totalVol += (*it)->vol;
	}
	//ACCOUNT FOR NUMBER OF CAVITIES
	recipe->totalVol *= mold->numCavities;
	cout << "Total = " << recipe->totalVol << "." << endl;

	//run the injection til done
	cout << "    Cycle IJM for " << recipe->plastic->name << " " << IL->numCycles << " times." << endl;

	cout << "      Close - heat to " << recipe->plastic->meltPoint << " - inject at " << recipe->plastic->injectPressure << " PSI - cool to "
		<< recipe->plastic->solidPoint << " - separate - " << recipe->plastic->eject << " eject." << endl;

	cout << "      " << IL->ob->type << " package bin full..." << endl;

	cout << "        IJM pausing while " << IL->ob->type << " package bin is swapped." << endl;
	cout << "        Conveyer belt pausing while " << IL->ob->type << " package bin is swapped." << endl;
	cout << "        Packager pausing while " << IL->ob->type << " package bin is swapped." << endl;
	cout << "        Stuffer filling " << IL->ob->type << " package bin with " << IL->cushion->type << " stuffing." << endl;

	//clean the mold
	recipe->plastic->clean();

	//optional ship to address

	cout << "Ship to \"" << order["address"] << "\"" << endl;

	//destory dynamically allocated objects
	delete IL;
	cout << endl;
	delete mFactory;
	cout << endl;
	delete mold;
	cout << endl;
	delete recipe; //recipe will delete Plastic obj
	cout << endl;


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

#endif /* DP4_SRC_STUDENTS_MOHAMED_H_ */
