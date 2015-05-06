/*
 * sergio.h
 *
 *  Created on: Apr 27, 2015
 *      Author: Sergio Sanchez (sergio.sanchez@intel.com)
 *
 *  Project: Final for Intro to Design Patterns Pilot class.
 *  	This file satisfies all parts of the original + new specs.
 */

#ifndef DP4_SRC_STUDENTS_SERGIO_H_
#define DP4_SRC_STUDENTS_SERGIO_H_

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

namespace final_sergio_file {

template <typename T>
string NumberToString ( T Number )
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}

const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }
#define FACTORY_ERROR(type,factory) cout << "FACTORY ERROR: could not use " << type << " in " << factory << "!" << endl;

const int ORDER_SIZE_MAX = 200000;
const int ORDER_SIZE_DEFAULT = 100;
const string PACKAGER_DEFAULT = "Bulk";
const string STUFFER_DEFAULT = "Air";
const string MOLD_DEFAULT = "duck";
const string MOLD_LOC_DEFAULT = "inventory";
const string COLOR_DEFAULT = "black";

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


namespace strategy {		// DP 1 -

class PlasticType {
protected:
	string name;
	int heatTemp;
	int pressure;
	int coolTemp;
	string ejectType;

public:
	virtual ~PlasticType() { DTOR(" ~PlasticType"); }
	string getPlastic() { return name; }
	virtual string getPlasticFamily() { return name; } // for most, plastic family IS the plastic name
	void getInstructions() {
		cout << "      Close - heat to " << heatTemp << " - inject at " << pressure << " PSI - cool to " << coolTemp << " - separate - " << ejectType << " eject." << endl;
	}
};

class Plastic_ABS: public PlasticType {
public:
	Plastic_ABS() {
		this->name = "ABS";
		this->heatTemp = 440;
		this->coolTemp = 360;
		this->pressure = 125;
		this->ejectType = "progressive";
	}
};

class Plastic_Family: public PlasticType {
protected:
	string family;
public:
	string getPlasticFamily() { return family; }
};

class Plastic_Polypropylene: public Plastic_Family {
public:
	Plastic_Polypropylene() {
		this->name = "Polypropylene";
		this->family = "Poly";
		this->heatTemp = 350;
		this->coolTemp = 290;
		this->pressure = 90;
		this->ejectType = "smooth";
	}
};

class Plastic_Polyethelene: public Plastic_Family {
public:
	Plastic_Polyethelene() {
		this->name = "Polyethelene";
		this->family = "Poly";
		this->heatTemp = 350;
		this->coolTemp = 290;
		this->pressure = 90;
		this->ejectType = "smooth";
	}
};

class Plastic_PET: public PlasticType {
public:
	Plastic_PET() {
		this->name = "PET";
		this->heatTemp = 404;
		this->coolTemp = 340;
		this->pressure = 110;
		this->ejectType = "smooth";
	}
};

class Plastic_Styrene: public Plastic_Family {
public:
	Plastic_Styrene() {
		this->name = "Styrene";
		this->family = "Synthetics";
		this->heatTemp = 480;
		this->coolTemp = 390;
		this->pressure = 150;
		this->ejectType = "shock";
	}
};

class Plastic_Nylon66: public Plastic_Family {
public:
	Plastic_Nylon66() {
		this->name = "Nylon66";
		this->family = "Synthetics";
		this->heatTemp = 480;
		this->coolTemp = 390;
		this->pressure = 150;
		this->ejectType = "shock";
	}
};

class Plastic {
private:
	PlasticType* plastic;
public:
	Plastic() {
			cout << "  <>Unknown plastic || defaulting to ABS." << endl;
			plastic = new Plastic_ABS();
	}
	Plastic(string type) {
		if( strcmp(type.c_str(), "ABS") == 0 )
			plastic = new Plastic_ABS();
		else if( strcmp(type.c_str(), "Polypropylene") == 0 )
			plastic = new Plastic_Polypropylene();
		else if( strcmp(type.c_str(), "Polyethelene") == 0 )
			plastic = new Plastic_Polyethelene();
		else if( strcmp(type.c_str(), "PET") == 0 )
			plastic = new Plastic_PET();
		else if( strcmp(type.c_str(), "Styrene") == 0 )
			plastic = new Plastic_Styrene();
		else if( strcmp(type.c_str(), "Nylon66") == 0 )
			plastic = new Plastic_Nylon66();
		else
			cerr << "Unknown plastic type: " << type << "! Exiting dishonorably!" << endl;
	}
	~Plastic() { DTOR(" ~Plastic"); }
	string getPlastic() { return plastic->getPlastic(); }
	string getPlasticType() { return plastic->getPlasticFamily(); }
	void getInstructions() { plastic->getInstructions(); }
};

}

class IngredientList {
protected:
	int volume;
	string name;
public:
	virtual ~IngredientList() { DTOR("  ~Ingredients"); }
	virtual string getRecipe()=0;
	virtual int getVolume()=0;
};

class BaseIngredient: public IngredientList {
public:
	BaseIngredient() {}
	string getRecipe() { return "      Recipe: "; }
	int getVolume() { return 0; }
};

class AdditionalIngredient: public IngredientList {
private:
	IngredientList* ingredients;
public:
	AdditionalIngredient(IngredientList* ingredients, string color, int volume): ingredients(ingredients) {
		this->name = color;
		this->volume = volume;
	}
	string getRecipe() {
		return ingredients->getRecipe() + name + "(" + NumberToString(volume) + ") ";
	}

	int getVolume() {
		return ingredients->getVolume() + volume;
	}

};


namespace observer {		// DP 7.

class Observer;

class Subject {
private:
	list<Observer*> observers;
public:
	void registerObserver( Observer* observer ) { observers.push_back(observer); }
	void deregisterObserver( Observer* observer ) { observers.remove(observer); }
	void notifyObservers();
};

class Observer {
protected:
	Subject& subject;
public:
	Observer( Subject& subject ): subject(subject) { subject.registerObserver(this); }
	virtual ~Observer() {
		subject.deregisterObserver(this);
		DTOR("  ~Observer");
	}
	virtual void notify()=0;
};

}

namespace abstract_factory {	// DP 10 - more like GoF.

class Stuffer {
protected:
	string stuffer;
public:
	static Stuffer* MakeStuffer( string stufferType );
	virtual ~Stuffer() { DTOR("  ~Stuffer"); }
	string getStufferType() { return stuffer; }
};

class Air: public Stuffer {
public:
	Air() { stuffer = "air"; }
};

class Popcorn: public Stuffer {
public:
	Popcorn() { stuffer = "styrene popcorn"; }
};

class BubbleWrap: public Stuffer {
public:
	BubbleWrap() { stuffer = "bubble wrap"; }
};

class Foam: public Stuffer {
public:
	Foam() { stuffer = "expanding foam"; }
};

Stuffer* Stuffer::MakeStuffer( string stufferType ) {
	if( strcmp(stufferType.c_str(), "Air") == 0 )
		return new Air();
	else if( strcmp(stufferType.c_str(), "Popcorn") == 0)
		return new Popcorn();
	else if( strcmp(stufferType.c_str(), "BubbleWrap") == 0)
		return new BubbleWrap();
	else if( strcmp(stufferType.c_str(), "Foam") == 0)
		return new Foam();
	else
	{
		FACTORY_ERROR(stufferType,"MakeStuffer");
		exit(1);
	}
}

class Conveyer {
protected:
	string beltType;
public:
	string getBeltType() { return beltType; }
};

class Y_Split: public Conveyer {
public: Y_Split() {	beltType = "Y-Split conveyer belt"; }
};

class V_Level: public Conveyer {
public: V_Level() {	beltType = "V-Level conveyer belt"; }
};

class Linear: public Conveyer {
public: Linear() {	beltType = "Linear conveyer belt"; }
};

class Bin {
protected:
	string binType;
public:
	string getBinType() { return binType; }
};

class CardboardBox: public Bin {
public: CardboardBox() { binType = "CardboardBox"; }
};

class PallotBox: public Bin {
public: PallotBox() { binType = "PallotBox"; }
};

class ZipLock: public Bin {
public: ZipLock() { binType = "ZipLock"; }
};

class Crate: public Bin {
public: Crate() { binType = "Crate"; }
};

class Metal {
protected:
	string metal;
public:
	string getMetal() { return metal; }
};

class Aluminum: public Metal  {
public: Aluminum(){ metal = "Aluminum"; }
};

class Steel: public Metal {
public: Steel() { metal = "Steel"; }
};

class Cavities {
protected:
	int numCavities;
public:
	int getNumCavities() { return numCavities; }
};

class SingleCavity: public Cavities {
public: SingleCavity() { numCavities = 1; }
};

class DualCavity: public Cavities {
public: DualCavity() { numCavities = 2; }
};

class QuadCavity: public Cavities {
public: QuadCavity() { numCavities = 4; }
};

class AbstractFactory {
public:
	virtual ~AbstractFactory() { DTOR("  ~AbstractFactory"); }
	virtual Metal* MakeMetal()=0;
	virtual Cavities* MakeCavities()=0;
	virtual Bin* MakePackager()=0;
	virtual Conveyer* MakeConveyer()=0;
};

class InjectionLine {
protected:
	Metal* metal;
	Cavities* cavities;
	Bin* packager;
	Conveyer* conveyer;
	Stuffer* stuffer;
	string name;
public:
	virtual ~InjectionLine() { DTOR("  ~InjectionLine"); }
	virtual void Init( AbstractFactory* af ) {
		metal = af->MakeMetal();
		cavities = af->MakeCavities();
		packager = af->MakePackager();
		conveyer = af->MakeConveyer();
	}
	string getMetal() { return metal->getMetal(); }
	string getBin() { return packager->getBinType(); }
	int getNumCavities() { return cavities->getNumCavities(); }
	string getBelt() { return conveyer->getBeltType(); }
	string getName() { return name; }

	void isFull( string stuffer ) {
		cout << "      " << getBin() << " package bin full..." << endl;
		cout << "        IJM pausing while " << getBin() << " package bin is swapped." << endl;
		cout << "        Conveyer belt pausing while " << getBin() << " package bin is swapped." << endl;
		cout << "        Packager pausing while " << getBin() << " package bin is swapped." << endl;
		cout << "        Stuffer filling " << getBin() << " package bin with " << stuffer << " stuffing." << endl;
	}
};

// 10,000
class AF_10K : public AbstractFactory {
public:
	Metal* MakeMetal() { return new Aluminum(); }
	Cavities* MakeCavities() { return new SingleCavity(); }
	Bin* MakePackager() { return new CardboardBox(); }
	Conveyer* MakeConveyer() { return new Linear(); }
};
class IJM_110 : public InjectionLine {
public:
	IJM_110() {
		Init(new AF_10K());
		name = "IJM_110";
	}
};

// 20,000
class AF_20K : public AbstractFactory {
	Metal* MakeMetal() { return new Aluminum(); }
	Cavities* MakeCavities() { return new DualCavity(); }
	Bin* MakePackager() { return new CardboardBox(); }
	Conveyer* MakeConveyer() { return new Y_Split(); }
};
class IJM_120 : public InjectionLine {
public:
	IJM_120() {
		Init(new AF_20K());
		name = "IJM_120";
	}
};

// 40,000
class AF_40K : public AbstractFactory {
	Metal* MakeMetal() { return new Aluminum(); }
	Cavities* MakeCavities() { return new QuadCavity(); }
	Bin* MakePackager() { return new PallotBox(); }
	Conveyer* MakeConveyer() { return new V_Level(); }
};
class IJM_140 : public InjectionLine {
public:
	IJM_140() {
		Init(new AF_40K());
		name = "IJM_140";
	}
};

// 50,000
class AF_50K : public AbstractFactory {
	Metal* MakeMetal() { return new Steel(); }
	Cavities* MakeCavities() { return new SingleCavity(); }
	Bin* MakePackager() { return new PallotBox(); }
	Conveyer* MakeConveyer() { return new Linear(); }
};
class IJM_210 : public InjectionLine {
public:
	IJM_210() {
		Init(new AF_50K());
		name = "IJM_210";
	}
};

// 10,000
class AF_100K : public AbstractFactory {
	Metal* MakeMetal() { return new Steel(); }
	Cavities* MakeCavities() { return new DualCavity(); }
	Bin* MakePackager() { return new Crate(); }
	Conveyer* MakeConveyer() { return new Y_Split(); }
};
class IJM_220 : public InjectionLine {
public:
	IJM_220() {
		Init(new AF_100K());
		name = "IJM_220";
	}
};

// 200,000
class AF_200K : public AbstractFactory {
	Metal* MakeMetal() { return new Steel(); }
	Cavities* MakeCavities() { return new QuadCavity(); }
	Bin* MakePackager() { return new Crate(); }
	Conveyer* MakeConveyer() { return new V_Level(); }
};
class IJM_240 : public InjectionLine {
public:
	IJM_240() {
		Init(new AF_200K());
		name = "IJM_240";
	}
};

}

namespace adapter {			// DP 2.

class CleanInterface {
public:
	static CleanInterface* MakeCleaner( string plastic, string metal );
	virtual ~CleanInterface() { DTOR("  ~CleanInterface"); }
	virtual void clean()=0;
};

class CI_ABS: public CleanInterface {
private: legacy_classes::CleanABS cleaner;
public:	void clean() { cleaner.clean(); }
};

class CI_Poly: public CleanInterface {
private: legacy_classes::CleanPolys cleaner;
public: void clean() { cleaner.prepForReuse(); }
};

class CI_PET_Aluminum: public CleanInterface {
private: legacy_classes::PETCleanup cleaner;
public: void clean() { cleaner.purify(); }
};

class CI_PET_Steel: public CleanInterface {
private: legacy_classes::PETCleanup cleaner;
public: void clean() { cleaner.carbonize(); }
};

class CI_Synthetic: public CleanInterface {
public: void clean() { cout << "    Clean synthetic mold: ozone wash.\n"; }
};

CleanInterface* CleanInterface::MakeCleaner( string plastic, string metal ) {

	if( strcmp(plastic.c_str(), "ABS") == 0 )
		return new CI_ABS();

	if( strcmp(plastic.c_str(), "Poly") == 0 )
		return new CI_Poly();

	if( strcmp(plastic.c_str(), "PET") == 0 ) {
		if( strcmp(metal.c_str(), "Aluminum") == 0 )
			return new CI_PET_Aluminum();

		if( strcmp(metal.c_str(), "Steel") == 0 )
				return new CI_PET_Steel();
	}

	if( strcmp(plastic.c_str(), "Synthetics") == 0 )
		return new CI_Synthetic();

	FACTORY_ERROR(plastic,"MakeCleaner");
	exit(1);
}

}

namespace chain_of_resp {	// DP 8.

}

namespace bridge {			// DP 9.

class Tool {
protected:
	string name;

public:
	static Tool* PickTool( string metal, string finish ); // factory
	virtual ~Tool() { DTOR("  ~Tool"); }
	virtual string getName() { return name; }
	virtual void useTool( string metalStr, int numCavities, string moldStr, string finishStr )=0;
};

class HighCarbon: public Tool {
public:
	HighCarbon() { name = "HighCarbon";	}
	void useTool( string metalStr, int numCavities, string moldStr, string finishStr ) {
		cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill "
				<< "aluminum" << " block into " << numCavities << " " << moldStr
					<< " shapes with " << finishStr << " finish.\n";
	}
};

class Carbide: public Tool {
public:
	Carbide() {	name = "Carbide"; }
	void useTool( string metalStr, int numCavities, string moldStr, string finishStr ) {
		cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill "
				<< "steel" << " block into " << numCavities << " " << moldStr
					<< " shapes with " << finishStr << " finish.\n";
	}
};

class DiamondTipped: public Tool {
public:
	DiamondTipped() {	name = "DiamondTipped"; }
	void useTool( string metalStr, int numCavities, string moldStr, string finishStr ) {
		cout << "      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind)  to mill "
				<< "steel" << " block into " << numCavities << " " << moldStr
					<< " shapes with " << finishStr << " finish.\n";
	}
};

Tool* Tool::PickTool( string metal, string finish ) {
	if( strcmp(metal.c_str(), "Aluminum") == 0 )
		return new HighCarbon();
	else if( strcmp(metal.c_str(), "Steel") == 0 && strcmp(finish.c_str(), "satin") == 0)
		return new DiamondTipped();
	else if( strcmp(metal.c_str(), "Steel") == 0)
		return new Carbide();

	else
	{
		FACTORY_ERROR(metal,"PickTool");
		exit(1);
	}
}

class MoldLocation {
protected:
	string name;
public:
	static MoldLocation* MakeMoldLocation( string moldLoc, string finish ); // factory
	virtual ~MoldLocation() { DTOR("  ~MoldLocation"); }
	virtual string getName() { return name; }
	virtual void useMold(string shape, int cavities)=0;
};

class Inventory: public MoldLocation {
public:
	Inventory() {
		name = "inventory";
	}
	void useMold(string shape, int cavities) {
		cout << "    Pull " << shape << " mold from inventory.\n";
	}
};

class SisterCompany: public MoldLocation {
public:
	SisterCompany() {
		name = "sister company";
	}
	void useMold(string shape, int cavities) {
		cout << "    Borrow " << shape << " mold from sister company.\n";
	}
};

class Purchase: public MoldLocation {
public:
	Purchase() {
		name = "inventory";
	}
	void useMold(string shape, int cavities) {
		cout << "    Acquire " << shape << " mold via purchase.\n";
	}
};

class Mill: public MoldLocation {
private:
	string finish;
public:
	Mill( string finish ): finish(finish) {
		name = "mill";
	}
	void useMold(string shape, int cavities) {
		cout << "    Create " << shape << " mold from mill with " << cavities << " cavities:\n";
	}
	string getFinish() { return finish; }
};

MoldLocation* MoldLocation::MakeMoldLocation( string moldLoc, string finish )
{
	if( strcmp(moldLoc.c_str(), "inventory") == 0 )
		return new Inventory();
	else if( strcmp(moldLoc.c_str(), "sisterCompany") == 0)
		return new SisterCompany( );
	else if( strcmp(moldLoc.c_str(), "purchase") == 0)
		return new Purchase( );
	else if( strcmp(moldLoc.c_str(), "mill") == 0)
		return new Mill( finish );
	else
	{
		FACTORY_ERROR(moldLoc,"MakeMoldLocation");
		exit(1);
	}
}

class Mold {
protected:
	MoldLocation* moldLoc;
	Tool* tool;
	string shape;
	int volume;
public:
	static Mold* MakeMold( string moldStr, string moldLoc, string metal, string finish ); // factory
	virtual ~Mold() { DTOR("  ~Mold"); }
	virtual string getLocation() { return moldLoc->getName(); }
	virtual string getTool() { return tool->getName(); }
	virtual string getShape() { return shape; }
	virtual int getVolume() { return volume; }
	virtual void simGetMold(int cavities, string metal) {
		moldLoc->useMold(shape, cavities);
		if( Mill* mill = dynamic_cast<Mill*>(moldLoc) )
			tool->useTool(metal, cavities, shape, mill->getFinish());
	}
//string metalStr, int numCavities, string moldStr, string finishStr
	void setMoldLocation( MoldLocation* moldLoc ) { this->moldLoc = moldLoc; }
	void setTool( Tool* tool ) { this->tool = tool; }
};

class Duck: public Mold {
public:
	Duck( ) {
		shape = "duck";
		volume = 35;
	}
};

class Car: public Mold {
public:
	Car( ) {
		shape = "car";
		volume = 40;
	}
};

class Hero: public Mold {
public:
	Hero( ) {
		shape = "hero";
		volume = 50;
	}
};

class Dino: public Mold {
public:
	Dino( ) {
		shape = "dino";
		volume = 30;
	}
};

Mold* Mold::MakeMold( string moldStr, string moldLocStr, string metalStr, string finishStr )
{
	// Make a mold based on the string input
	Mold* mold = NULL;

	if( strcmp(moldStr.c_str(), "duck") == 0 )
		mold = new Duck();
	else if( strcmp(moldStr.c_str(), "car") == 0 )
		mold = new Car();
	else if( strcmp(moldStr.c_str(), "hero") == 0 )
		mold = new Hero();
	else if( strcmp(moldStr.c_str(), "dino") == 0 )
		mold = new Dino();
	else
	{
		FACTORY_ERROR(mold,"MakeMold");
		exit(1);
	}

	// Make a MoldLocation based on the metal (from InjectionLine)
	MoldLocation* moldLoc = MoldLocation::MakeMoldLocation(moldLocStr, finishStr);

	// Make a Tool based on metal and finish
	Tool* tool = Tool::PickTool( metalStr, finishStr );

	// Bridge MoldLocation and Tool to Mold and return the Mold
	mold->setMoldLocation(moldLoc);
	mold->setTool(tool);

	return mold;
}

}

namespace decorator {		// DP 6.

class Tag {
protected:
	int width;
	string strOnTag;
public:
	static Tag* TagFactory( string allTheTags );
	virtual ~Tag() { DTOR("  ~Tag"); }
	virtual string getTag()=0;
	virtual int getSize()=0;
};

class EmptyTag: public Tag {
public:
	EmptyTag() {}
	string getTag() { return ""; }
	int getSize() { return 0; }
};

class ModelTag: public Tag {
private: Tag* tag;
public:
	ModelTag( Tag* tag ): tag(tag) {}
	string getTag() { return tag->getTag()+ " ModelNumber"; }
	int getSize() { return tag->getSize() + 2; }
};

class CountryTag: public Tag {
private: Tag* tag;
public:
	CountryTag( Tag* tag ): tag(tag) {}
	string getTag() { return tag->getTag() + " Country"; }
	int getSize() { return tag->getSize() + 2; }
};

class DateTag: public Tag {
private: Tag* tag;
public:
	DateTag( Tag* tag ): tag(tag) {}
	string getTag() { return tag->getTag() + " Date"; }
	int getSize() { return tag->getSize() + 2; }
};

class PartNumberTag: public Tag {
private: Tag* tag;
public:
	PartNumberTag( Tag* tag ): tag(tag) {}
	string getTag() { return tag->getTag() + " PartNumber"; }
	int getSize() { return tag->getSize() + 2; }
};

class IncCounterTag: public Tag {
private: Tag* tag;
public:
	IncCounterTag( Tag* tag ): tag(tag) {}
	string getTag() { return tag->getTag() + " IncCounter"; }
	int getSize() { return tag->getSize() + 4; }
};

class RecycleCodeTag: public Tag {
private: Tag* tag;
public:
	RecycleCodeTag( Tag* tag ): tag(tag) {}
	string getTag() { return tag->getTag() + " RecycleCode"; }
	int getSize() { return tag->getSize() + 6; }
};

Tag* Tag::TagFactory( string tagsToPrint ) {
	Tag* tag = new EmptyTag();

	char* allTheTags = (char*) tagsToPrint.c_str();

	char* token = strtok(allTheTags, " ");
	while( token != NULL ) {
		if( strcmp(token, "ModelNumber") == 0 )
			tag = new decorator::ModelTag(tag);
		else if( strcmp(token, "Country") == 0 )
			tag = new decorator::CountryTag(tag);
		else if( strcmp(token, "Date") == 0 )
			tag = new decorator::DateTag(tag);
		else if( strcmp(token, "IncCounter") == 0 )
			tag = new decorator::IncCounterTag(tag);
		else if( strcmp(token, "PartNumber") == 0 )
			tag = new decorator::PartNumberTag(tag);
		else if( strcmp(token, "RecycleCode") == 0 )
			tag = new decorator::RecycleCodeTag(tag);
		else
		{
			FACTORY_ERROR(token,"TagFactory");
			exit(1);
		}

		token = strtok(NULL, " ");

	}

	return tag;
}

}

namespace factory_method {	// DP 5.

// Seam point - add another class.

}

namespace template_method {	// DP 4.

// Seam point - add another step.

}

void process(map<string, string>& order) {

	strategy::Plastic* plastic;
	int orderSize, runSize;
	string packager;
	abstract_factory::Stuffer* stuffer;
	abstract_factory::InjectionLine* injLine;
	bridge::Mold* mold;
	decorator::Tag* tag;
	IngredientList* recipe;

	// setup plastic
	if( order.find("plastic") != order.end() )
		plastic = new strategy::Plastic(order["plastic"]);
	else // no plastic specified
		plastic = new strategy::Plastic();

	// setup order size
	if( order.find("size") != order.end() ) {
		orderSize = atoi(order["size"].c_str());

		if( orderSize > ORDER_SIZE_MAX )
		{
			cout << "  <>Size too large |" << orderSize << "| defaulting to HugeOrder of " << ORDER_SIZE_MAX  << "." << endl;
			orderSize = ORDER_SIZE_MAX;
		}
	}
	else
	{
		cout << "  <>No size specified, defaulting to " << ORDER_SIZE_DEFAULT << "." << endl;
		orderSize = ORDER_SIZE_DEFAULT;
	}

	// setup packager
	if( order.find("packager") != order.end() )
		packager = order["packager"];
	else
	{
		cout << "  <>Unknown packager || defaulting to " << PACKAGER_DEFAULT << " packager." << endl;
		packager = PACKAGER_DEFAULT;
		order["packager"] = PACKAGER_DEFAULT;
	}

	// setup stuffer
	if( order.find("stuffer") == order.end() )
	{
		cout << "  <>Unknown stuffer || defaulting to " << STUFFER_DEFAULT << " stuffer." << endl;
		order["stuffer"] = STUFFER_DEFAULT;
	}

	stuffer = abstract_factory::Stuffer::MakeStuffer(order["stuffer"]);

	// setup the injection line based on size
	if( orderSize <= 10000 )
		injLine = new abstract_factory::IJM_110();
	else if( orderSize <= 20000 )
		injLine = new abstract_factory::IJM_120();
	else if( orderSize <= 40000 )
		injLine = new abstract_factory::IJM_140();
	else if( orderSize <= 50000 )
		injLine = new abstract_factory::IJM_210();
	else if( orderSize <= 100000 )
		injLine = new abstract_factory::IJM_220();
	else if( orderSize <= 200000 )
		injLine = new abstract_factory::IJM_240();
	else
		cerr << "Error setting up injection line due to invalid order size " << orderSize << "!" << endl;

	runSize = orderSize / injLine->getNumCavities();

	cout << "Setup injection line for " << runSize << " run with " << order["packager"] << " packager and " << stuffer->getStufferType() << " stuffing:" << endl;

	cout << "  " << injLine->getName() << " - " << injLine->getMetal() << "("
			<< injLine->getNumCavities() << ") - " << injLine->getBelt() <<
			" - " << injLine->getBin() << endl;

	order["metal"] = injLine->getMetal();

	cout << "Process order." << endl;

	// need a dummy finishStr to make the Mold object
	if( order.find("finish") == order.end() )
		order["finish"] = "";

	// get mold and mold location -- assume that both must be specified
	if( ( order.find("mold") != order.end() ) && ( order.find("moldLoc") != order.end() ) )
	{
		mold = bridge::Mold::MakeMold(order["mold"], order["moldLoc"], injLine->getMetal(), order["finish"]);
		mold->simGetMold( injLine->getNumCavities(), injLine->getMetal() );
	}
	else
	{
		order["mold"] = MOLD_DEFAULT;
		order["moldLoc"] = MOLD_LOC_DEFAULT;

		mold = bridge::Mold::MakeMold(order["mold"], order["moldLoc"], injLine->getMetal(), order["finish"]);
		cout << "  <>Can't find place || to get || mold from, defaulting to " << mold->getShape() << " from " << mold->getLocation() << "." << endl;
	}

	// insert tags into mold
	if( order.find("tags") == order.end() )
		order["tags"] = ""; // if no tags specified, pass an empty string to the factory

	tag = decorator::Tag::TagFactory(order["tags"]);

	cout << "    Insert tags [" << tag->getTag() << "] of width " << tag->getSize() << "/20 mm.\n";

	// load plastic, color die, and additive bins
	cout << "    Load plastic, color, and additive bins." << endl;
	recipe = new BaseIngredient();

	recipe = new AdditionalIngredient(recipe, plastic->getPlastic(), mold->getVolume());

	if( order.find("color") == order.end() )
	{
		cout << "      <>No color specified, defaulting to black.\n";
		order["color"] = COLOR_DEFAULT;
	}

	recipe = new AdditionalIngredient(recipe, order["color"], mold->getVolume()/10);

	if( order.find("UVInhibiter") != order.end() )
		recipe = new AdditionalIngredient(recipe, "UVInhibiter", atoi(order["UVInhibiter"].c_str()));

	if( order.find("AntiBacterial") != order.end() )
		recipe = new AdditionalIngredient(recipe, "AntiBacterial", atoi(order["AntiBacterial"].c_str()));

	if( order.find("MicroFibers") != order.end() )
		recipe = new AdditionalIngredient(recipe, "MicroFibers", atoi(order["MicroFibers"].c_str()));

	cout << recipe->getRecipe() << "Total = " << (recipe->getVolume()*injLine->getNumCavities()) << "." << endl;

	// Support three injection cycles, depends on plastic
	cout << "    Cycle IJM for " << plastic->getPlasticType() << " " << runSize << " times." << endl;
	plastic->getInstructions();

	// simulate cycling the injector for the specified plastic <size> times
	injLine->isFull( stuffer->getStufferType() );

	// clean the mold
	adapter::CleanInterface* cleaner = adapter::CleanInterface::MakeCleaner(plastic->getPlasticType(), injLine->getMetal());
	cleaner->clean();

	// add shipping step to injection run process
	if( order.find("address") == order.end() )
		order["address"] = "";

	cout << "Ship to \"" << order["address"] << "\"" << endl;

	cout << endl;


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

#endif /* DP4_SRC_STUDENTS_SERGIO_H_ */
