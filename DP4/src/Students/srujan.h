/*
 * srujan.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */

#ifndef DP4_SRC_STUDENTS_SRUJAN_H_
#define DP4_SRC_STUDENTS_SRUJAN_H_

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;

namespace final_srujan_file {

const bool on = false;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }

namespace legacy_classes {	// Can't change these.

	class CleanABS {
	public: ~CleanABS() { DTOR(" ~CleanABS "); }
			void clean() {
				cout << "    Clean ABS mold: soak in alcohol, rinse with water, dry.\n";
			}
	};

	class CleanPolys {
	public: ~CleanPolys() { DTOR(" ~CleanPolys "); }
			void prepForReuse() {
				cout << "    Clean Poly mold: rinse with acetone, dry.\n";
			}
	};

	class PETCleanup {
	public: ~PETCleanup() { DTOR(" ~PETCleanup "); }
			void carbonize() { // Use only on stainless steel.
				cout << "    Clean PET steel mold: heat to 895 C.\n";
			}
			void purify() {	// Use only on aluminum.
				cout << "    Clean PET aluminum mold: rinse with soap and water, dry.\n";
			}
	};

	class CleanSynthetics {
	public: ~CleanSynthetics() { DTOR(" ~CleanSynthetics "); }
			void ozoneClean() {
				cout << "    Clean synthetic mold: ozone wash.\n";
			}
	};
}

namespace strategy {		// DP 1.

	// Mold cleaner strategy
	class Strategy_1 {
	public:	virtual ~Strategy_1() {DTOR(" ~Strategy_1")}
	public:
		virtual void cleanmold() {}
	};
}

namespace adapter {			// DP 2.
	using namespace strategy;
	using namespace legacy_classes;

	class CleanPlastic_A_2: public Strategy_1 {
	public:	virtual ~CleanPlastic_A_2() {DTOR(" ~CleanPlastic_A_2")}
	};

	class ABSCleaner : public CleanPlastic_A_2 {
		CleanABS	cleanABS;
	public:
		virtual ~ABSCleaner(){DTOR(" ~ABS ~adapter::ABS")}
		void cleanmold() { cleanABS.clean(); }
	};

	class PolysCleaner : public CleanPlastic_A_2 {
		CleanPolys	cleanPolys;
	public:
		virtual ~PolysCleaner(){DTOR(" ~Poly ~adapter::Poly")}
		void cleanmold() { cleanPolys.prepForReuse(); }
	};

	class PETAluminumCleaner : public CleanPlastic_A_2 {
		PETCleanup	petCleanup;
	public:
		virtual ~PETAluminumCleaner(){DTOR(" ~PET ~adapter::PET")}
		void cleanmold() { petCleanup.purify(); }
	};

	class PETSteelCleaner : public CleanPlastic_A_2 {
		PETCleanup	petCleanup;
	public:
		virtual ~PETSteelCleaner(){DTOR(" ~PET ~adapter::PET")}
		void cleanmold() { petCleanup.carbonize(); }
	};

	class SyntheticsCleaner : public CleanPlastic_A_2 {
		CleanSynthetics	cleanSynthetics;
	public:
		virtual ~SyntheticsCleaner(){DTOR(" ~Synthetics ~adapter::Synthetics")}
		void cleanmold() { cleanSynthetics.ozoneClean(); }
	};

}



namespace observer {		// DP 7.

	class Observer_7;
	class Subject_7;

	class Subject_7 {
		list<Observer_7*>	observers;
	public:
		~Subject_7();
	public:
		void attach(Observer_7* obs) { observers.push_back(obs); }
		void detach(Observer_7* obs) { observers.remove(obs); }
		void says(const int& size, const string& packager);
	};

	class Observer_7 {
		Subject_7& subject;
	public:
		Observer_7(Subject_7& subject) : subject(subject) {
			subject.attach(this);
		}
		virtual ~Observer_7() {
			subject.detach(this);
			cout << " ~Observer_7\n";
		}
	public:
		virtual void update(Subject_7* subject=0)=0;
	};

	void Subject_7::says(const int& size, const string& packager) {
		list<Observer_7*>::iterator it;
		for(it=observers.begin(); it!=observers.end(); it++) {
			(*it)->update();
		}
		cout << endl;
	}
	Subject_7::~Subject_7() {
		DTOR("  ~Subject ");
		DTOR( "  Observers left to process (should be zero) = ");
		DTOR( observers.size() << ".\n");
		DTOR( endl);
	}

}

namespace abstract_factory {// DP 10.

// Seam point - add another type1 member.
// Seam point - add another type2 member.
// Seam point - add another type3 member.
// ...

// Seam point - add another family.

	class IJM {
	public:
		virtual ~IJM() {DTOR(" ~IJM_AF");}
		virtual string getIjmType()=0;
	};

	class Mold{
	protected:
		int numCavities;
	public:
		Mold(int numCavities): numCavities(numCavities){}
		virtual ~Mold() {DTOR(" ~Mold_AF");}
		virtual string getMetalType()=0;
		int getNumCavities(){ return numCavities; }
	};

	class ConveyerBelt{
	public:
		virtual ~ConveyerBelt() {DTOR(" ~ConveyerBelt_AF");}
		virtual string getConveyerBeltType()=0;
	};

	class PackageBin{
	public:
		virtual ~PackageBin() {DTOR(" ~PackageBin_AF");}
		virtual string getPackageBinType()=0;

	};

	class Setup_AF_10 { // Setup Injection Line
	public:
		virtual ~Setup_AF_10() {DTOR(" ~Setup_AF_10");}
		static Setup_AF_10* createInjectionLine(int orderSize);
		virtual IJM* create_ijm()=0;
		virtual Mold* create_mold()=0;
		virtual ConveyerBelt* create_converyerbelt()=0;
		virtual PackageBin* create_packagebin()=0;
	};

	//10,000
	class IJM_110 : public IJM  {
	public:
		virtual ~IJM_110() {DTOR(" ~IJM_110");}
		string getIjmType(){return "IJM_110"; }
	};

	class Aluminum : public Mold {
	public:
		Aluminum(int numCavities): Mold(numCavities){}
		virtual ~Aluminum() {DTOR(" ~Aluminum");}
		virtual string getMetalType() {return "Aluminum";}
	};

	class LinearBelt : public ConveyerBelt  {
	public:
		virtual ~LinearBelt() {DTOR(" ~LinearBelt");}
		string getConveyerBeltType(){return "Linear conveyer belt"; }
	};

	class CardboardBox : public PackageBin  {
	public:
		virtual ~CardboardBox() {DTOR(" ~CardboardBox");}
		string getPackageBinType(){return "CardboardBox"; }
	};

	class PilotOrder: public Setup_AF_10 {
	public:
		virtual ~PilotOrder() {DTOR(" ~PilotOrder");}
		virtual IJM* create_ijm(){return new IJM_110;}
		virtual Mold* create_mold(){return new Aluminum(1);}
		virtual ConveyerBelt* create_converyerbelt(){return new LinearBelt;}
		virtual PackageBin* create_packagebin(){return new CardboardBox;}
	};

	//20,000
	class IJM_120 : public IJM  {
	public:
		virtual ~IJM_120() {DTOR(" ~IJM_120");}
		string getIjmType(){return "IJM_120"; }
	};

	class YSplitBelt : public ConveyerBelt  {
	public:
		virtual ~YSplitBelt() {DTOR(" ~YSplitBelt");}
		string getConveyerBeltType(){return "Y-Split conveyer belt"; }
	};

	class SmallOrder: public Setup_AF_10 {
	public:
		virtual ~SmallOrder() {DTOR(" ~SmallOrder");}
		virtual IJM* create_ijm(){return new IJM_120;}
		virtual Mold* create_mold(){return new Aluminum(2);}
		virtual ConveyerBelt* create_converyerbelt(){return new YSplitBelt;}
		virtual PackageBin* create_packagebin(){return new CardboardBox;}
	};

	//50,000
	class IJM_210 : public IJM  {
	public:
		virtual ~IJM_210() {DTOR( " ~IJM_210");}
		string getIjmType(){return "IJM_210"; }
	};

	class Steel : public Mold {
	public:
		Steel(int numCavities): Mold(numCavities){}
		virtual ~Steel() {DTOR(" ~Steel");}
		virtual string getMetalType() {return "Steel";}
	};

	class PallotBox : public PackageBin  {
	public:
		virtual ~PallotBox() {DTOR(" ~PallotBox");}
		string getPackageBinType(){return "PallotBox"; }
	};

	class MediumOrder: public Setup_AF_10 {
	public:
		virtual ~MediumOrder() {DTOR(" ~MediumOrder");}
		virtual IJM* create_ijm(){return new IJM_210;}
		virtual Mold* create_mold(){return new Steel(1);}
		virtual ConveyerBelt* create_converyerbelt(){return new LinearBelt;}
		virtual PackageBin* create_packagebin(){return new PallotBox;}
	};

	//40,000
	class IJM_140 : public IJM  {
	public:
		virtual ~IJM_140() {DTOR( " ~IJM_140");}
		string getIjmType(){return "IJM_140"; }
	};

	class VLevelBelt : public ConveyerBelt  {
	public:
		virtual ~VLevelBelt() {DTOR(" ~VLevelBelt");}
		string getConveyerBeltType(){return "V-Level conveyer belt"; }
	};

	class FastOrder: public Setup_AF_10 {
	public:
		virtual ~FastOrder() {DTOR(" ~FastOrder");}
		virtual IJM* create_ijm(){return new IJM_140;}
		virtual Mold* create_mold(){return new Aluminum(4);}
		virtual ConveyerBelt* create_converyerbelt(){return new VLevelBelt;}
		virtual PackageBin* create_packagebin(){return new PallotBox;}
	};

	//100,000
	class IJM_220 : public IJM  {
	public:
		virtual ~IJM_220() {DTOR( " ~IJM_220");}
		string getIjmType(){return "IJM_220"; }
	};

	class Crate : public PackageBin  {
	public:
		virtual ~Crate() {DTOR(" ~Crate");}
		string getPackageBinType(){return "Crate"; }
	};

	class LargeOrder: public Setup_AF_10 {
	public:
		virtual ~LargeOrder() {DTOR(" ~LargeOrder");}
		virtual IJM* create_ijm(){return new IJM_220;}
		virtual Mold* create_mold(){return new Steel(2);}
		virtual ConveyerBelt* create_converyerbelt(){return new YSplitBelt;}
		virtual PackageBin* create_packagebin(){return new Crate;}
	};

	//200,000
	class IJM_240 : public IJM  {
	public:
		virtual ~IJM_240() {DTOR( " ~IJM_240");}
		string getIjmType(){return "IJM_240"; }
	};


	class HugeOrder: public Setup_AF_10 {
	public:
		virtual ~HugeOrder() {DTOR(" ~HugeOrder");}
		virtual IJM* create_ijm(){return new IJM_240;}
		virtual Mold* create_mold(){return new Steel(4);}
		virtual ConveyerBelt* create_converyerbelt(){return new VLevelBelt;}
		virtual PackageBin* create_packagebin(){return new Crate;}
	};

	Setup_AF_10* Setup_AF_10::createInjectionLine(int orderSize) {
		if(orderSize <= 10000) return new PilotOrder;
		else if(orderSize <= 20000) return new SmallOrder;
		else if(orderSize <= 40000) return new FastOrder;
		else if(orderSize <= 50000) return new MediumOrder;
		else if(orderSize <= 100000) return new LargeOrder;
		else if(orderSize <= 400000) return new HugeOrder;
		else {
			cout << "Size not supported to create injection line";
			throw "Size not supported to create injection line";
		}

	}

}

namespace bridge {			// DP 9.

	using namespace abstract_factory;

	class Platform_B_9 {
	public:
		virtual ~Platform_B_9(){DTOR(" ~Platform_B_9")}
		virtual void mill()=0;
	};
	class HighCarbon : public Platform_B_9 {
	public:
		virtual ~HighCarbon(){DTOR(" ~HighCarbon")}
		void mill() { cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill aluminum block "; }
	};
	class Carbide : public Platform_B_9 {
	public:
		virtual ~Carbide(){DTOR(" ~Carbide")}
		void mill() { cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill steel block "; }
	};
	class DiamondTipped : public Platform_B_9 {
	public:
		virtual ~DiamondTipped(){DTOR(" ~DiamondTipped")}
		void mill() { cout << "      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind) to mill steel block "; }
	};

	class Shape_B_9 {
	protected:
		Platform_B_9*	platform;
		int				numCavities;
		string			finish;
	public:
		Shape_B_9(Platform_B_9* platform, int numCavities, string finish) : platform(platform), numCavities(numCavities), finish(finish) {}
		virtual ~Shape_B_9(){DTOR(" ~Shape_B_9"); delete platform; }
		virtual void create()=0;
		static Shape_B_9* getShape(map<string,string>& order, Mold* mold);
	};
	class Duck : public Shape_B_9 {
	public:
		virtual ~Duck(){DTOR(" ~Duck")}
		Duck(Platform_B_9* platform, int numCavities, string finish) : Shape_B_9(platform,numCavities,finish) {}
		void create() { platform->mill();cout << "into "<< numCavities << " duck shapes with " << finish << " finish.\n"; }
	};
	class Car : public Shape_B_9 {
	public:
		virtual ~Car(){DTOR(" ~Car")}
		Car(Platform_B_9* platform, int numCavities, string finish) : Shape_B_9(platform,numCavities,finish) {}
		void create() { platform->mill();cout << "into "<< numCavities << " car shapes with " << finish << " finish.\n"; }
	};
	class Hero : public Shape_B_9 {
	public:
		virtual ~Hero(){DTOR(" ~Hero")}
		Hero(Platform_B_9* platform, int numCavities, string finish) : Shape_B_9(platform,numCavities,finish) {}
		void create() { platform->mill();cout << "into "<< numCavities << " hero shapes with " << finish << " finish.\n"; }
	};
	class Dino : public Shape_B_9 {
	public:
		virtual ~Dino(){DTOR(" ~Dino")}
		Dino(Platform_B_9* platform, int numCavities, string finish) : Shape_B_9(platform,numCavities,finish) {}
		void create() { platform->mill();cout << "into "<< numCavities << " dino shapes with " << finish << " finish.\n"; }
	};

	Shape_B_9* Shape_B_9::getShape(map<string,string>& order, Mold* mold)
	{
		Platform_B_9* platform;

		if(mold->getMetalType() == "Aluminum") {
			platform = new HighCarbon();
		} else if(mold->getMetalType() == "Steel" && order["finish"] == "satin") {
			platform = new DiamondTipped();
		} else if(mold->getMetalType() == "Steel") {
			platform = new Carbide();
		}
		else {
			cout << "Platform not supported for the metal type";
			throw "Platform not supported for the metal type";
		}

		if(order["mold"] == "duck") {
			return new Duck(platform,mold->getNumCavities(),order["finish"]);
		} else if(order["mold"] == "car") {
			return new Car(platform,mold->getNumCavities(),order["finish"]);
		} else if(order["mold"] == "hero") {
			return new Hero(platform,mold->getNumCavities(),order["finish"]);
		} else if(order["mold"] == "dino") {
			return new Dino(platform,mold->getNumCavities(),order["finish"]);
		} else {
			cout << "Shape not supported\n";
			throw "Shape not supported";
		}
	}
}

namespace chain_of_resp {	// DP 8.
	using namespace abstract_factory;

	class GetMold_CofR_8 {		// If handler is varying....
	public:
		GetMold_CofR_8*	successor;
	public:
		GetMold_CofR_8() : successor(0) {}
		virtual ~GetMold_CofR_8(){DTOR(" ~GetMold_CofR_8")}
		void setSuccessor(GetMold_CofR_8* successor) { this->successor = successor; }
		virtual void handleRequest(map<string,string>& order, Mold* mold)=0;
	};

	class Inventory : public GetMold_CofR_8 {
	public:
		virtual ~Inventory(){DTOR(" ~Inventory"); delete successor;}
		void handleRequest(map<string,string>& order, Mold* mold) {
			if(order["moldLoc"] == "inventory")
				cout << "    Pull " << order["mold"] << " mold from inventory.\n";
			else if(successor != 0)
				successor->handleRequest(order,mold);
			else {
				order["mold"] = "duck";
				order["moldLoc"] = "inventory";
				cout << "    <>Can't find place || to get || mold from, defaulting to duck from inventory.\n";
			}
		}
	};

	class SisterCompany : public GetMold_CofR_8 {
	public:
		virtual ~SisterCompany(){DTOR(" ~SisterCompany"); delete successor;}
		void handleRequest(map<string,string>& order, Mold* mold) {
			if(order["moldLoc"] == "sisterCompany")
				cout << "    Borrow " << order["mold"] << " mold from sister company.\n";
			else if(successor != 0)
				successor->handleRequest(order,mold);
			else {
				order["mold"] = "duck";
				order["moldLoc"] = "inventory";
				cout << "    <>Can't find place || to get || mold from, defaulting to duck from inventory.\n";
			}
		}
	};

	class Purchase : public GetMold_CofR_8 {
	public:
		virtual ~Purchase(){DTOR(" ~Purchase"); delete successor;}
		void handleRequest(map<string,string>& order, Mold* mold) {
			if(order["moldLoc"] == "purchase")
				cout << "    Acquire " << order["mold"] << " mold via purchase.\n";
			else if(successor != 0)
				successor->handleRequest(order,mold);
			else {
				order["mold"] = "duck";
				order["moldLoc"] = "inventory";
				cout << "    <>Can't find place || to get || mold from, defaulting to duck from inventory.\n";
			}
		}
	};

	class Mill : public GetMold_CofR_8 {
	public:
		virtual ~Mill(){DTOR(" ~Mill"); delete successor; }
		void handleRequest(map<string,string>& order, Mold* mold) {
			if(order["moldLoc"] == "mill")
				cout << "    Create " << order["mold"] << " mold from mill with " << mold->getNumCavities() << " cavities:\n";
			else if(successor != 0)
				successor->handleRequest(order,mold);
			else{
				order["mold"] = "duck";
				order["moldLoc"] = "inventory";
				cout << "    <>Can't find place || to get || mold from, defaulting to duck from inventory.\n";
			}
		}
	};

}

namespace decorator {		// DP 6.

// Decorator for tags
	class TagBase {
	protected:
		string str;
		int width;
	public:
		TagBase(string str,int width) : str(str),width(width) {}
		virtual ~TagBase(){}
		virtual string getDesc() { return str;}
		virtual int getWidth() {return width;}
	};

	class Tags_D_6 : public TagBase {
	protected:
		TagBase* tagbase;
	public:
		Tags_D_6(TagBase* tagbase, string str, int width) : TagBase(str,width), tagbase(tagbase){}
		virtual ~Tags_D_6(){DTOR(" ~Tags_D_6");}
		string getDesc() { return tagbase->getDesc() + str; }
		int getWidth() { return tagbase->getWidth() + width; }
	};

	class Cavity : public Tags_D_6 {
	public:
		Cavity(TagBase* tag) : Tags_D_6(tag, "",0) {}
		virtual ~Cavity(){DTOR(" ~Cavity"); delete tagbase;}
	};

	class Tag : public Tags_D_6 {
	public:
		Tag(TagBase* tag, string tagName, int width) : Tags_D_6(tag, tagName,width) {}
		virtual ~Tag(){DTOR(" ~Tag"); delete tagbase;}
	};

	class BlankTag : public Tag {
	public:
		BlankTag(TagBase* tagbase) : Tag(tagbase,"",0) {}
		virtual ~BlankTag(){DTOR(" ~Blank");}
	};

	class ModelNumber : public Tag {
	public:
		ModelNumber(TagBase* tagbase) : Tag(tagbase,"ModelNumber ",2) {}
		virtual ~ModelNumber(){DTOR(" ~ModelNumber");}
	};

	class Country : public Tag {
	public:
		Country(TagBase* tagbase) : Tag(tagbase,"Country ",2) {}
		virtual ~Country(){DTOR(" ~Country");}
	};

	class Date : public Tag {
	public:
		Date(TagBase* tagbase) : Tag(tagbase,"Date ",2) {}
		virtual ~Date(){DTOR(" ~Date");}
	};

	class IncCounter : public Tag {
	public:
		IncCounter(TagBase* tagbase) : Tag(tagbase,"IncCounter ",4) {}
		virtual ~IncCounter(){DTOR(" ~IncCounter");}
	};

	class PartNumber : public Tag {
	public:
		PartNumber(TagBase* tagbase) : Tag(tagbase,"PartNumber ",2) {}
		virtual ~PartNumber(){DTOR(" ~PartNumber");}
	};

	class RecycleCode : public Tag {
	public:
		RecycleCode(TagBase* tagbase) : Tag(tagbase,"RecycleCode ",6) {}
		virtual ~RecycleCode(){DTOR(" ~RecycleCode");}
	};


// Decorator for plastic color and additives
	class ColorAdditiveBase {
	protected:
		string str;
		int width;
	public:
		ColorAdditiveBase(string str, int width) : str(str), width(width) {}
		virtual ~ColorAdditiveBase(){}
		virtual string getRecipe() { return str + "(" + to_string(width) +")"; }
		virtual int getWidth() { return width; }
	};

	//class Additive: public ColorAdditiveBase {
	//public:
	//	Additive(string additive, int width) : ColorAdditiveBase(additive,width) {}
	//	virtual ~Additive(){DTOR(" ~Additive")}
	//};

	class Plastic_D_6 : public ColorAdditiveBase {
	protected:
		ColorAdditiveBase* colorAdditive;
	public:
		Plastic_D_6(ColorAdditiveBase* build, string str, int width) : ColorAdditiveBase(str, width), colorAdditive(build) {}
		virtual ~Plastic_D_6(){DTOR(" ~Plastic_D_6")}
		string getRecipe() { return colorAdditive->getRecipe() + " " + str + "(" + to_string(width) +")"; }
		int getWidth() { return colorAdditive->getWidth() + width; }
	};

	class Color : public Plastic_D_6 {
	public:
		Color(ColorAdditiveBase* colorAdditiveBase, string color, int width) : Plastic_D_6(colorAdditiveBase, color, width) {}
		virtual ~Color(){DTOR(" ~Color"); delete colorAdditive;}
	};

	class Additive : public Plastic_D_6 {
	public:
		Additive(ColorAdditiveBase* colorAdditiveBase, string additive, int width) : Plastic_D_6(colorAdditiveBase, additive, width) {}
		virtual ~Additive(){DTOR(" ~Additive"); delete colorAdditive;}
	};

	class UVInhibiter : public Additive {
	public:
		UVInhibiter(ColorAdditiveBase* colorAdditiveBase, int width) : Additive(colorAdditiveBase, "UVInhibiter", width) {}
		virtual ~UVInhibiter(){DTOR(" ~UVInhibiter");}
	};

	class AntiBacterial : public Additive {
	public:
		AntiBacterial(ColorAdditiveBase* colorAdditiveBase, int width) : Additive(colorAdditiveBase, "AntiBacterial", width) {}
		virtual ~AntiBacterial(){DTOR(" ~AntiBacterial");}
	};

	class MicroFibers : public Additive {
	public:
		MicroFibers(ColorAdditiveBase* colorAdditiveBase, int width) : Additive(colorAdditiveBase, "MicroFibers", width) {}
		virtual ~MicroFibers(){DTOR(" ~MicroFibers");}
	};
}

namespace factory_method {	// DP 5.

	class Packager_FM_5 {	// If the classes are varying...
	public:
		virtual ~Packager_FM_5() {DTOR(" ~Packager_FM_5");}
		virtual string pack()=0;
		static Packager_FM_5* makePackager(const string& packagerType);
	};

	class Bulk : public Packager_FM_5 {
	public:
		virtual ~Bulk(){DTOR(" ~Bulk");}
		string pack() { return "Bulk packager"; }
	};
	class ShrinkWrap : public Packager_FM_5 {
	public:
		virtual ~ShrinkWrap(){DTOR(" ~ShrinkWrap");}
		string pack() { return "ShrinkWrap packager"; }
	};
	class HardPack : public Packager_FM_5 {
	public:
		virtual ~HardPack(){DTOR(" ~HardPack");}
		string pack() { return "HardPack packager"; }
	};
	class ZipLock : public Packager_FM_5 {
	public:
		virtual ~ZipLock(){DTOR(" ~ZipLock");}
		string pack() { return "ZipLock packager"; }
	};

	Packager_FM_5* Packager_FM_5::makePackager(const string& packagerType) {
		if(packagerType == "Bulk") return new Bulk;
		else if(packagerType == "ShrinkWrap") return new ShrinkWrap;
		else if(packagerType == "HardPack") return new HardPack;
		else if(packagerType == "ZipLock") return new ZipLock;
		else {
			cout << "Package type not supported";
			throw "Package type not supported";
		}
	}

	class Stuffer_FM_5 {	// If the classes are varying...
	public:
		virtual ~Stuffer_FM_5() {DTOR(" ~Stuffer_FM_5");}
		virtual string stuff() = 0;
		static Stuffer_FM_5* makeStuffer(const string& stufferType);
	};

	class Air : public Stuffer_FM_5 {
	public:
		virtual ~Air(){DTOR(" ~Air");}
		string stuff() { return "air stuffing"; }
	};

	class Popcorn : public Stuffer_FM_5 {
	public:
		virtual ~Popcorn(){DTOR(" ~Popcorn");}
		string stuff() { return "styrene popcorn stuffing"; }
	};

	class BubbleWrap : public Stuffer_FM_5 {
	public:
		virtual ~BubbleWrap(){DTOR(" ~BubbleWrap");}
		string stuff() { return "bubble wrap stuffing"; }
	};

	class Foam : public Stuffer_FM_5 {
	public:
		virtual ~Foam(){DTOR(" ~Foam");}
		string stuff() { return "expanding foam stuffing"; }
	};

	Stuffer_FM_5* Stuffer_FM_5::makeStuffer(const string& stufferType) {
		if(stufferType == "Air") return new Air;
		else if(stufferType == "Popcorn") return new Popcorn;
		else if(stufferType == "BubbleWrap") return new BubbleWrap;
		else if(stufferType == "Foam") return new Foam;
		else {
			cout << "Stuffer type not supported";
			throw "Stuffer type not supported";
		}
	}
}

namespace template_method {	// DP 4.

	using namespace abstract_factory;
	using namespace factory_method;
	using namespace chain_of_resp;
	using namespace decorator;
	using namespace adapter;
	using namespace bridge;

	class ProcessOrder_TM_4 {
	protected:
		Stuffer_FM_5* stuffer;
		Packager_FM_5* packager;
		IJM* ijm;
		Mold* mold;
		ConveyerBelt* conveyerbelt;
		PackageBin* packagebin;
		Setup_AF_10* injectionLineFactory;
		GetMold_CofR_8* moldLoc;
		Shape_B_9* moldCreateTool;
		TagBase* tagbase;
		ColorAdditiveBase* colorAdditiveBase;
		CleanPlastic_A_2* cleaner;
	public:
		virtual ~ProcessOrder_TM_4() {
			cout <<"\n";
			delete stuffer; cout <<"\n";
			delete packager; cout <<"\n";
			delete ijm; cout <<"\n";
			delete mold; cout <<"\n";
			delete conveyerbelt; cout <<"\n";
			delete packagebin; cout <<"\n";
			delete injectionLineFactory; cout <<"\n";
			delete moldLoc; cout <<"\n";
			delete moldCreateTool; cout <<"\n";
			delete tagbase; cout <<"\n";
			delete colorAdditiveBase; cout <<"\n";
			delete cleaner; cout <<"\n";
			DTOR(" ~ProcessOrder_TM_4" << endl);
		}
		static ProcessOrder_TM_4* createProcessLine(const string& plasticType);
		void run(map<string, string>& order);
	protected:
		void SetupInjectionLine(map<string, string>& order);
		void GetAndInstallMold(map<string,string>& order);
		void InsertTagsIntoMold(map<string,string>& order);
		void LoadColorAndAdditivebins(map<string,string>& order);
		void ProcessPackager();
		void ShipOrder(map<string,string>& order);
		virtual void SimulateIJM(map<string,string>& order)=0;
		virtual void LoadPlasticColorAndAdditivebins(map<string,string>& order)=0;
		virtual void CleanMold()=0;

	};

	class ABS : public ProcessOrder_TM_4 {
	public:
		virtual ~ABS(){DTOR(" ~ABS");}
		virtual void LoadPlasticColorAndAdditivebins(map<string,string>& order) {
			colorAdditiveBase = new ColorAdditiveBase("ABS",35);
			LoadColorAndAdditivebins(order);
		}
		virtual void SimulateIJM(map<string,string>& order) {
			int orderSize = atoi(order["size"].c_str());
			int runSize = orderSize/mold->getNumCavities();
			cout << "    Cycle IJM for ABS " << runSize << " times.\n";
			cout << "      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject.\n";
			ProcessPackager();

		}
		virtual void CleanMold() {
			cleaner = new ABSCleaner;
			cleaner->cleanmold();
		}
	};

	class Polypropylene : public ProcessOrder_TM_4 {
	public:
		virtual ~Polypropylene(){DTOR(" ~Polypropylene");}
		virtual void LoadPlasticColorAndAdditivebins(map<string,string>& order) {
			colorAdditiveBase = new ColorAdditiveBase("Polypropylene",40);
			LoadColorAndAdditivebins(order);
		}
		virtual void SimulateIJM(map<string,string>& order) {
			int orderSize = atoi(order["size"].c_str());
			int runSize = orderSize/mold->getNumCavities();
			cout << "    Cycle IJM for Poly " << runSize << " times.\n";
			cout << "      Close - heat to 350 - inject at 90 PSI - cool to 290 - separate - smooth eject.\n";
			ProcessPackager();
		}
		virtual void CleanMold() {
			cleaner = new PolysCleaner;
			cleaner->cleanmold();
		}
	};

	class Polyethelene : public ProcessOrder_TM_4 {
	public:
		virtual ~Polyethelene(){DTOR(" ~Polyethelene");}
		virtual void LoadPlasticColorAndAdditivebins(map<string,string>& order) {
			colorAdditiveBase = new ColorAdditiveBase("Polyethelene",50);
			LoadColorAndAdditivebins(order);
		}

		virtual void SimulateIJM(map<string,string>& order) {
			int orderSize = atoi(order["size"].c_str());
			int runSize = orderSize/mold->getNumCavities();
			cout << "    Cycle IJM for Poly " << runSize << " times.\n";
			cout << "      Close - heat to 350 - inject at 90 PSI - cool to 290 - separate - smooth eject.\n";
			ProcessPackager();
		}
		virtual void CleanMold() {
			cleaner = new PolysCleaner;
			cleaner->cleanmold();
		}
	};

	class PET : public ProcessOrder_TM_4 {
	public:
		virtual ~PET(){DTOR(" ~PET");}
		virtual void LoadPlasticColorAndAdditivebins(map<string,string>& order) {
			colorAdditiveBase = new ColorAdditiveBase("PET",50);
			LoadColorAndAdditivebins(order);
		}
		virtual void SimulateIJM(map<string,string>& order) {
			int orderSize = atoi(order["size"].c_str());
			int runSize = orderSize/mold->getNumCavities();
			cout << "    Cycle IJM for PET " << runSize << " times.\n";
			cout << "      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject.\n";
			ProcessPackager();
		}
		virtual void CleanMold() {
			if(mold->getMetalType() == "Aluminum") cleaner = new PETAluminumCleaner;
			else if(mold->getMetalType() == "Steel") cleaner = new PETSteelCleaner;
			else throw "Not a supported metal type for cleaning PET";
			cleaner->cleanmold();
		}
	};

	class Styrene : public ProcessOrder_TM_4 {
	public:
		virtual ~Styrene(){DTOR(" ~Styrene");}
		virtual void LoadPlasticColorAndAdditivebins(map<string,string>& order) {
			colorAdditiveBase = new ColorAdditiveBase("Styrene",30);
			LoadColorAndAdditivebins(order);
		}
		virtual void SimulateIJM(map<string,string>& order) {
			int orderSize = atoi(order["size"].c_str());
			int runSize = orderSize/mold->getNumCavities();
			cout << "    Cycle IJM for Synthetics " << runSize << " times.\n";
			cout << "      Close - heat to 480 - inject at 150 PSI - cool to 390 - separate - shock eject.\n";
			ProcessPackager();
		}
		virtual void CleanMold() {
			cleaner = new SyntheticsCleaner;
			cleaner->cleanmold();
		}
	};

	class Nylon66 : public ProcessOrder_TM_4 {
	public:
		virtual ~Nylon66(){DTOR(" ~Nylon66");}
		virtual void LoadPlasticColorAndAdditivebins(map<string,string>& order) {
			colorAdditiveBase = new ColorAdditiveBase("Nylon66",30);
			LoadColorAndAdditivebins(order);
		}
		virtual void SimulateIJM(map<string,string>& order) {
			int orderSize = atoi(order["size"].c_str());
			int runSize = orderSize/mold->getNumCavities();
			cout << "    Cycle IJM for Synthetics " << runSize << " times.\n";
			cout << "      Close - heat to 480 - inject at 150 PSI - cool to 390 - separate - shock eject.\n";
			ProcessPackager();
		}
		virtual void CleanMold() {
			cleaner = new SyntheticsCleaner;
			cleaner->cleanmold();
		}
	};

	ProcessOrder_TM_4* ProcessOrder_TM_4::createProcessLine(const string& plasticType) {
		if(plasticType == "ABS") return new ABS;
		else if(plasticType == "Polypropylene") return new Polypropylene;
		else if(plasticType == "Polyethelene") return new Polyethelene;
		else if(plasticType == "PET") return new PET;
		else if(plasticType == "Styrene") return new Styrene;
		else if(plasticType == "Nylon66") return new Nylon66;
		else {
			cout << "Plastic type not supported for creating process line";
			throw "Plastic type not supported for creating process line";
		}
	}

	void ProcessOrder_TM_4::run(map<string, string>& order) {

		SetupInjectionLine(order);

		cout << "  Process order." << endl;
		GetAndInstallMold(order);
		InsertTagsIntoMold(order);
		cout << "    Load plastic, color, and additive bins." << endl;
		LoadPlasticColorAndAdditivebins(order);
		SimulateIJM(order);
		CleanMold();
		ShipOrder(order);
	}

	void ProcessOrder_TM_4::GetAndInstallMold(map<string,string>& order) {
		GetMold_CofR_8* inventory = new Inventory;
		GetMold_CofR_8* sister = new SisterCompany;
		GetMold_CofR_8* purchase = new Purchase;
		GetMold_CofR_8* mill = new Mill;

		inventory->successor = sister;
		sister->successor = purchase;
		purchase->successor = mill;

		moldLoc = inventory;
		moldLoc->handleRequest(order,mold);

		moldCreateTool = Shape_B_9::getShape(order,mold);
		if(order["moldLoc"] == "mill") {
			moldCreateTool->create();
		}

	}

	void ProcessOrder_TM_4::InsertTagsIntoMold(map<string,string>& order) {
		string tagsString = order["tags"];
		tagbase = new Cavity(new TagBase("",0));
		if(tagsString.find("IncCounter") != string::npos) tagbase = new IncCounter(tagbase);
		if(tagsString.find("PartNumber") != string::npos) tagbase = new PartNumber(tagbase);
		if(tagsString.find("RecycleCode") != string::npos) tagbase = new RecycleCode(tagbase);
		if(tagsString.find("ModelNumber") != string::npos) tagbase = new ModelNumber(tagbase);
		if(tagsString.find("Country") != string::npos) tagbase = new Country(tagbase);
		if(tagsString.find("Date") != string::npos) tagbase = new Date(tagbase);
		tagbase = new BlankTag(tagbase);

		cout << "    Insert tags [" << tagbase->getDesc() << "] of width "<< tagbase->getWidth() << "/20 mm." << endl;
	}

	void ProcessOrder_TM_4::LoadColorAndAdditivebins(map<string,string>& order) {
		if(order.find("color") == order.end()) {
			cout << "      <>No color specified, defaulting to black.\n";
			colorAdditiveBase = new Color(colorAdditiveBase,"black",3);
		} else {
			string color = order["color"];
			if(color.find("black") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,3);
			if(color.find("brown") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,3);
			if(color.find("red") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,3);
			if(color.find("orange") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,4);
			if(color.find("yellow") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,5);
			if(color.find("green") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,5);
			if(color.find("blue") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,3);
			if(color.find("violet") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,3);
			if(color.find("gray") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,3);
			if(color.find("white") != string::npos) colorAdditiveBase = new Color(colorAdditiveBase,color,3);
		}
		if(order.find("UVInhibiter") != order.end()){
			int width = atoi(order["UVInhibiter"].c_str());
			colorAdditiveBase = new UVInhibiter(colorAdditiveBase,width);
		}
		if(order.find("AntiBacterial") != order.end()){
			int width = atoi(order["AntiBacterial"].c_str());
			colorAdditiveBase = new AntiBacterial(colorAdditiveBase,width);
		}
		if(order.find("MicroFibers") != order.end()){
			int width = atoi(order["MicroFibers"].c_str());
			colorAdditiveBase = new MicroFibers(colorAdditiveBase,width);
		}
		cout << "      Recipe: " << colorAdditiveBase->getRecipe() << " Total = " << colorAdditiveBase->getWidth()*mold->getNumCavities() << ".\n";
	}

	void ProcessOrder_TM_4::ProcessPackager() {
		string packagerType = packagebin->getPackageBinType();
		cout << "      "<< packagerType << " package bin full...\n";
		cout << "        IJM pausing while " << packagerType << " package bin is swapped.\n";
		cout << "        Conveyer belt pausing while " << packagerType << " package bin is swapped.\n";
		cout << "        Packager pausing while " << packagerType << " package bin is swapped.\n";
		cout << "        Stuffer filling " << packagerType << " package bin with " << stuffer->stuff() << ".\n";
	}

	void ProcessOrder_TM_4::ShipOrder(map<string,string>& order)
	{
		cout << "    Ship to \"" << order["address"] <<"\"\n";
	}

	void ProcessOrder_TM_4::SetupInjectionLine(map<string, string>& order) {

		packager = Packager_FM_5::makePackager(order["packager"]);
		stuffer = Stuffer_FM_5::makeStuffer(order["stuffer"]);

		int orderSize = atoi(order["size"].c_str());

		injectionLineFactory = Setup_AF_10::createInjectionLine(orderSize);
		ijm = injectionLineFactory->create_ijm();
		mold = injectionLineFactory->create_mold();
		conveyerbelt = injectionLineFactory->create_converyerbelt();
		packagebin = injectionLineFactory->create_packagebin();

		int runSize = orderSize/mold->getNumCavities();
		cout << "  Setup injection line for " << runSize << " run with " << packager->pack() << " and " << stuffer->stuff() << ":" << endl;
		cout << "    " << ijm->getIjmType() << " - " << mold->getMetalType() << "(" << mold->getNumCavities() << ")";
		cout << " - " << conveyerbelt->getConveyerBeltType() << " - " << packagebin->getPackageBinType() << endl;
	}

}


using namespace template_method;
void process(map<string, string>& order) {
	if(order.find("plastic") == order.end()){
		cout << "  <>Unknown plastic || defaulting to ABS.\n";
		order["plastic"] = "ABS";
	}

	if(order.find("size") == order.end()){
			cout << "  <>No size specified, defaulting to 100.\n";
			order["size"] = "100";
	}
	else {
		int orderSize = atoi(order["size"].c_str());
		if(orderSize > 200000) {
			cout << "  <>Size too large |400000| defaulting to HugeOrder of 200000.\n";
			order["size"] = "200000";
		}

	}



	if(order.find("packager") == order.end()){
			cout << "  <>Unknown packager || defaulting to Bulk packager.\n";
			order["packager"] = "Bulk";
	}

	if(order.find("stuffer") == order.end()){
		cout << "  <>Unknown stuffer || defaulting to Air stuffer.\n";
		order["stuffer"] = "Air";
	}

	ProcessOrder_TM_4* processLine = ProcessOrder_TM_4::createProcessLine(order["plastic"]);
	processLine->run(order);
	delete processLine;
}

pair<string, string> parse(string line) {
	char key[83];
	char val[83] = {0};

	sscanf(line.c_str(), "%s", key);

	char* equalSign = const_cast<char*>(strchr(line.c_str(), '='));
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
	cout << "Hello DP4.\n\n";
	cout << "<<< final solution >>>\n";

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}
	cout << "Aloha DP4.\n";
}


}

#endif /* DP4_SRC_STUDENTS_SRUJAN_H_ */
