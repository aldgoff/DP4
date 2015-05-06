/*
 * yong.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */

#ifndef DP4_SRC_STUDENTS_YONG_H_
#define DP4_SRC_STUDENTS_YONG_H_

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <list>
using namespace std;


namespace final_problem_file_yong {

const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }



namespace final_problem_classes {	// Can't change these.


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

// Seam point - add another interface.

}

namespace strategy {		// DP 1.

// Seam point - add another algorithm.

}

namespace observer {		// DP 7.

// Seam point - add another listener.

}

namespace abstract_factory {// DP 10.

// Seam point - add another type1 member.
// Seam point - add another type2 member.
// Seam point - add another type3 member.
// ...

// Seam point - add another family.

}
// ----- Alternatively (may make it hard to match the dtor instrumentation) -----
namespace abstract_factory_solti {	// DP 10 - more like GoF.



class AbstractA{};
class AbstractB{};
class AbstractC{};


// ...




class Observer_7;

class Subject_7
{
	list<Observer_7*> observers;
public:
	void attach(Observer_7* obs) { observers.push_back(obs); }
	void notify();
};



class Observer_7 {		// If the observers are varying...
protected:
	Subject_7* subject;
public:	virtual ~Observer_7() {}
public:
	virtual void update() {}
	void link(Subject_7* _subject) {
		subject = _subject;
		//cout << "  Attached an observer to subject\n";
	}
};
void Subject_7::notify() {
	list<Observer_7*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++)
		(*it)->update();
}

class PackageBin_AF:public Subject_7
{
public:
	virtual void Full()
	{
		cout << "      "<<GetPackagerBinName()<<" package bin full...\n";
		notify();
	}
	virtual string GetPackagerBinName()=0;
	virtual ~PackageBin_AF()
	{

	}

};

class PackagerBin_Observer_7:public Observer_7
{
public:
	PackageBin_AF* subject_PackageBin;
	void linkBin(PackageBin_AF* packagebinAF) {
		subject_PackageBin = packagebinAF;
		//cout << "  Attached an observer to subject\n";
	}
};

class Stuff:public PackagerBin_Observer_7
{
public:

	virtual string GetStuff() = 0;
	void update()
	{
		cout << "        Stuffer filling "<<subject_PackageBin->GetPackagerBinName()<<" package bin with "<<GetStuff()<<" stuffing.\n";
	}
};

class Air:public Stuff
{
public:
	string GetStuff()
	{
		return "air";
	}
};

class Popcorn:public Stuff
{
public:
	string GetStuff()
	{
		return "styrene propcorn";
	}
};

class BubbleWrap:public Stuff
{
public:
	string GetStuff()
	{
		return "bubble wrap";
	}
};
class Foam:public Stuff
{
public:
	string GetStuff()
	{
		return "expanding foam";
	}
};

class Packager:public PackagerBin_Observer_7
{
public:
	virtual string GetPackagerName() = 0;
	void update()
	{
		cout << "        Packager pausing while "<<subject_PackageBin->GetPackagerBinName()<<" package bin is swapped.\n";
	}

};

class Bulk:public Packager
{
public:
	string GetPackagerName(){
		return "Bulk";
	};
};

class ShrinkWrap:public Packager
{
public:
	string GetPackagerName(){
		return "ShrinkWrap";
	};
};
class HardPack:public Packager
{
public:
	string GetPackagerName(){
		return "HardPack";
	};
};

class ZipLock:public Packager
{
public:
	string GetPackagerName(){
		return "ZipLock";
	};
};



class Packager_FM_5
{
public:
	~Packager_FM_5()
	{
		DTOR("~Packager_FM_5 ");
	}
	static Packager* CreatePackager(string s)
	{
		if (s == "Bulk")
		{
			return new Bulk();
		}
		else if (s == "ShrinkWrap")
		{
			return new ShrinkWrap();
		}
		else if (s == "HardPack")
		{
			return new HardPack();
		}
		else if (s == "ZipLock")
		{
			return new ZipLock();
		}
		else
		{
			cout << "  <>Unknown packager |"<<s<<"| defaulting to Bulk packager.\n";
			return new Bulk();
		}
	}
	static Packager_FM_5* GetInstance()
	{
		if (!m_p)
		{
			m_p = new Packager_FM_5();
		}
		return m_p;
	}

	static Packager_FM_5* m_p;
};





class CardboardBox: public PackageBin_AF
{
public:
	string GetPackagerBinName()
	{
		return "CardboardBox";
	}
	virtual ~CardboardBox(){}
};




class PallotBox: public PackageBin_AF
{
public:
	string GetPackagerBinName()
	{
		return "PallotBox";
	}
	virtual ~PallotBox(){}
};

class Crate: public PackageBin_AF
{
public:
	string GetPackagerBinName()
	{
		return "Crate";
	}
	virtual ~Crate(){}
};





class IJM:public PackagerBin_Observer_7
{
public:
	void update()
	{
		cout << "        IJM pausing while "<<subject_PackageBin->GetPackagerBinName()<<" package bin is swapped.\n";
	}
};

class IJM_110:public IJM
{

};

class IJM_120:public IJM
{

};
class IJM_210:public IJM
{

};

class IJM_140:public IJM
{

};

class IJM_220:public IJM
{

};

class IJM_240:public IJM
{

};

class Platform_B_9;

class Metal
{
public:
	virtual ~Metal(){};
	Platform_B_9* m_platform;
	virtual Platform_B_9* GetPlatform(){return m_platform;};

	virtual string GetMetalName()=0;
};


class ConveyerBelt_AF
{

};

class ConveyerBelt:public PackagerBin_Observer_7
{
public:
	void update()
	{
		cout << "        Conveyer belt pausing while "<<subject_PackageBin->GetPackagerBinName()<<" package bin is swapped.\n";
	}
};

class LinearBelt:public ConveyerBelt
{

};

class YSplitBelt:public ConveyerBelt
{

};

class VLevelBelt:public ConveyerBelt
{

};

class Order
{
public:
	Order(int size):m_orderSize(size){};
	int m_orderSize;
	int m_cavitiesNum;
	virtual void InjectionLine() = 0;
	ConveyerBelt* m_conveyerBelt;
	PackageBin_AF*  m_packagerBin;
	IJM*          m_IJM;
	Metal*        m_metal;
	string        m_finish;
	void linkPackagerBin();
};

class Shape_B_9;

class MoldPlace
{
public:
	Order* m_order;
	Shape_B_9* m_shape;
	virtual void GetMold()=0;
	void AttachOrder(Order* order)
	{
		m_order = order;
	}
	void AttachShape(Shape_B_9* shape)
	{
		m_shape = shape;
	}
};

class Shape_B_9
{
public:
	Shape_B_9(MoldPlace* moldPlace):m_moldPlace(moldPlace){};
	void GetMold()
	{
		m_moldPlace->GetMold();
	}
	virtual string GetShapeName()=0;
	MoldPlace* m_moldPlace;
	virtual int GetVolume()=0;
};

class Duck:public Shape_B_9
{
public:
	Duck(MoldPlace* moldPlace):Shape_B_9(moldPlace){};
	string GetShapeName(){
		return "duck";
	}
	int GetVolume(){
		return 35;
	};
};

class Hero:public Shape_B_9
{
public:
	Hero(MoldPlace* moldPlace):Shape_B_9(moldPlace){};
	string GetShapeName(){
		return "hero";
	}
	int GetVolume(){
		return 50;
	};
};

class Car:public Shape_B_9
{
public:
	Car(MoldPlace* moldPlace):Shape_B_9(moldPlace){};
	string GetShapeName(){
		return "car";
	}
	int GetVolume(){
		return 40;
	};
};

class Dino:public Shape_B_9
{
public:
	Dino(MoldPlace* moldPlace):Shape_B_9(moldPlace){};
	string GetShapeName(){
		return "dino";
	}
	int GetVolume(){
		return 30;
	};
};



class Platform_B_9
{
public:
	Order* m_order;
	Shape_B_9 *m_shape;
	virtual void MillMetal()=0;
	void    AttachOrder(Order* order)
	{
		m_order = order;
	}
	void AttachShape(Shape_B_9* shape)
	{
		m_shape = shape;
	}
};

class HighCarbon: public Platform_B_9
{
public:
	void MillMetal()
	{
		cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill "<<m_order->m_metal->GetMetalName()<<" block into "<<m_order->m_cavitiesNum
			<<" "<<m_shape->GetShapeName()<<" shapes with "<<m_order->m_finish<<" finish.\n";
	}
};





class Carbide: public Platform_B_9
{
public:
	void MillMetal()
	{
		cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill "<<m_order->m_metal->GetMetalName()<<" block into "<<m_order->m_cavitiesNum
			<<" "<<m_shape->GetShapeName()<<" shapes with "<<m_order->m_finish<<" finish.\n";
	}
};

class DiamondTipped: public Platform_B_9
{
public:
	void MillMetal()
	{
		cout << "      using DiamondTipped tools (precision drill, oiled cooled cut, and cartoid grind) to mill "<<m_order->m_metal->GetMetalName()<<" block into "<<m_order->m_cavitiesNum
			<<" "<<m_shape->GetShapeName()<<" shapes with "<<m_order->m_finish<<" finish.\n";
	}
};





class Metal;

class Steel : public Metal {
public:
	Steel(string finish)
	{
		if (finish=="satin")
		{
			m_platform = new DiamondTipped;
		}
		else
		{
			m_platform = new Carbide;
		}
	}
	~Steel(){delete m_platform;}
	string GetMetalName(){return "steel";}

};


class Aluminum : public Metal {
public:
	Aluminum()
	{
		m_platform = new HighCarbon;
	}
	~Aluminum(){delete m_platform;}
	string GetMetalName(){return "aluminum";}
};


void Order::linkPackagerBin()
{
	m_packagerBin->attach(m_IJM);
	m_packagerBin->attach(m_conveyerBelt);
	m_IJM->linkBin(m_packagerBin);
	m_conveyerBelt->linkBin(m_packagerBin);
}
class PilotOrder:public Order
{
public:
	PilotOrder(int size):Order(size)
	{
		m_cavitiesNum = 1;
		m_conveyerBelt = new LinearBelt();
		m_packagerBin = new CardboardBox();
		m_IJM         = new IJM_110;
		linkPackagerBin();
		m_metal       = new Aluminum;
	}
	void InjectionLine(){
		cout << "    IJM_110 - Aluminum(1) - Linear conveyer belt - CardboardBox\n";
	}
};

class SmallOrder:public Order
{
public:
	SmallOrder(int size):Order(size){
		m_cavitiesNum = 2;
		m_conveyerBelt = new YSplitBelt();
		m_packagerBin = new CardboardBox();
		m_IJM         = new IJM_120;
		linkPackagerBin();
		m_metal       = new Aluminum;
	}
	void InjectionLine(){
		cout << "    IJM_120 - Aluminum(2) - Y-Split conveyer belt - CardboardBox\n";
	}
};

class MediumOrder:public Order
{
public:
	MediumOrder(int size,string finish):Order(size){
		m_cavitiesNum = 1;
		m_conveyerBelt = new LinearBelt();
		m_packagerBin = new PallotBox();
		m_IJM         = new IJM_210;
		linkPackagerBin();
		m_metal       = new Steel(finish);
	}
	void InjectionLine(){
		cout << "    IJM_210 - Steel(1) - Linear conveyer belt - PallotBox\n";
	}
};

class FastOrder:public Order
{
public:
	FastOrder(int size):Order(size){
		m_cavitiesNum = 4;
		m_conveyerBelt = new VLevelBelt();
		m_packagerBin = new PallotBox();
		m_IJM         = new IJM_140;
		linkPackagerBin();
		m_metal       = new Aluminum;
	}
	void InjectionLine(){
		cout << "    IJM_140 - Aluminum(4) - V-Level conveyer belt - PallotBox\n";
	}
};

class LargeOrder:public Order
{
public:
	LargeOrder(int size,string finish):Order(size){
		m_cavitiesNum = 2;
		m_conveyerBelt = new YSplitBelt();
		m_packagerBin = new Crate();
		m_IJM         = new IJM_220;
		linkPackagerBin();
		m_metal       = new Steel(finish);
	}
	void InjectionLine(){
		cout << "    IJM_220 - Steel(2) - Y-split conveyer belt - Crate\n";
	}
};

class HugeOrder:public Order
{
public:
	HugeOrder(int size,string finish):Order(size){
		m_cavitiesNum = 4;
		m_conveyerBelt = new VLevelBelt();
		m_packagerBin = new Crate();
		m_IJM         = new IJM_240;
		linkPackagerBin();
		m_metal       = new Steel(finish);
	}
	void InjectionLine(){
		cout << "    IJM_240 - Steel(4) - V-Level conveyer belt - Crate\n";
	}
};





class Mold_AF {

};






class Plastic;
class ABS;
class Polypropylene;
class Polyethelene;
class PET;



class Plastic
{
public:
	Plastic(){};
	virtual string GetPlasticName()=0;
	virtual string GetPlasticCategory()=0;
	virtual string InjectionCycle()=0;
};

class ABS:public Plastic
{
public:
	ABS(){};
	 string GetPlasticName(){return "ABS";};
	 string GetPlasticCategory(){return "ABS";};
	 string InjectionCycle()
	 {
		 return "heat to 440 - inject at 125 PSI - cool to 360 - progressive eject\n";
	 }
};

class Poly:public Plastic
{
public:
	Poly(){};
	string GetPlasticName(){return "Poly";};
	string GetPlasticCategory(){return "Poly";};
	string InjectionCycle()
	{
		return "heat to 350 - inject at  90 PSI - cool to 290 - smooth eject\n";
	}
};

class Polypropylene:public Poly
{
public:
	Polypropylene(){};
	string GetPlasticName(){return "Polypropylene";};
};
class Polyethelene:public Poly
{
public:
	Polyethelene(){};
	string GetPlasticName(){return "Polyethelene";};

};
class PET:public Plastic
{
public:
	PET(){};
	string GetPlasticName(){return "PET";};
	string GetPlasticCategory(){return "PET";};
	string InjectionCycle()
	{
		return "heat to 404 - inject at 110 PSI - cool to 340 - smooth eject\n";
	}
};

class Synthetics:public Plastic
{
public:
	Synthetics(){};
	string GetPlasticName(){return "Synthetics";};
	string GetPlasticCategory(){return "Synthetics";};
	string InjectionCycle()
	{
		return "heat to 480 - inject at 150 PSI - cool to 390 - shock eject.\n";
	}
};
class Styrene:public Synthetics
{
public:
	Styrene(){};
	string GetPlasticName(){return "Styrene";};
};

class Nylon66:public Synthetics
{
public:
	Nylon66(){};
	string GetPlasticName(){return "Nylon66";};
};


class Setup_AF_10
{
public:

	virtual ~Setup_AF_10(){
		delete m_plastic;
		delete m_packager;
		delete m_order;
		delete m_stuff;
	};



	void SetupPlastic(map<string, string>& order)
	{
		if (order["plastic"]=="ABS")
		{
			m_plastic = new ABS();
		}
		else if (order["plastic"]=="Polypropylene")
		{
			m_plastic = new Polypropylene();
		}
		else if (order["plastic"]=="Polyethelene")
		{
			m_plastic = new Polyethelene();
		}
		else if (order["plastic"]=="PET")
		{
			m_plastic = new PET();
		}
		else if (order["plastic"]=="Styrene")
		{
			m_plastic = new Styrene();
		}
		else if (order["plastic"]=="Nylon66")
		{
			m_plastic = new Nylon66();
		}
		else
		{
			cout << "  <>Unknown plastic |"<<order["plastic"]<<"| defaulting to ABS.\n";
			m_plastic = new ABS();
		}
	}

	void SetupFinishes(map<string, string>& order)
	{
		if (order["finish"]=="smooth")
			m_order->m_finish = "smooth";
		else if (order["finish"]=="rippled")
			m_order->m_finish = "rippled";
		else if (order["finish"]=="dimpled")
			m_order->m_finish = "dimpled";
		else if (order["finish"]=="sanded")
			m_order->m_finish = "sanded";
		else if (order["finish"]=="satin")
			m_order->m_finish = "satin";
		else
		{
			//unknown
		}

	}
	void SetupOrder(map<string, string>& order)
	{
		SetupSize(order);
		SetupFinishes(order);
	}

	void SetupSize(map<string, string>& order)
	{
		int runSize = 0;
		if (order.find("size")!=order.end())
		{
			int size  = atoi(order["size"].c_str());

			if (size<=10000)
			{
				m_order = new PilotOrder(size);
				runSize = size/1; //cavites 1;
			}
			else if (size <= 20000)
			{
				m_order = new SmallOrder(size);
				runSize = size/2; //cavites 2;
			}
			else if (size <= 40000)
			{
				m_order = new FastOrder(size);
				runSize = size/4; //cavites 1;
			}
			else if (size <= 50000)
			{
				m_order = new MediumOrder(size,order["finish"]);
				runSize = size/1; //cavites 1;
			}
			else if (size <= 100000)
			{
				m_order = new LargeOrder(size,order["finish"]);
				runSize = size/2;
			}
			else if (size <= 200000)
			{
				m_order = new HugeOrder(size,order["finish"]);
				runSize = size/4;
			}
			else if (size == 400000)
			{
				//If size > 50,000, default to 50,000
				cout<<"  <>Size too large |400000| defaulting to HugeOrder of 200000\n";
				m_order = new HugeOrder(size,order["finish"]);
				runSize = 200000/4;
			}
		}
		else
		{
			cout << "  <>No size specified, defaulting to 100.\n";
			m_order = new PilotOrder(100);
			runSize = 100/1; //cavites 1;
		}
		order["runSize"] = to_string(runSize);
	}
	void SetupPackager(map<string, string>& order)
	{
		m_packager = Packager_FM_5::CreatePackager(order["packager"]);

		if (m_packager->GetPackagerName()!="Bulk")
		{
			m_order->m_packagerBin->attach(m_packager);
			m_packager->linkBin(m_order->m_packagerBin);
		}
	}

	void SetupStuff(map<string, string>& order)
	{
		string s = order["stuffer"];
		if (s == "Air")
		{
			m_stuff =  new Air();
		}
		else if (s == "Popcorn")
		{
			m_stuff =  new Popcorn();
			linkBinAndStuff();
		}
		else if (s == "BubbleWrap")
		{
			m_stuff =  new BubbleWrap();
			linkBinAndStuff();
		}
		else if (s == "Foam")
		{
			m_stuff =  new Foam();
			linkBinAndStuff();
		}
		else
		{
			cout << "  <>Unknown stuffer |"<<s<<"| defaulting to Air stuffer.\n";
			m_stuff =  new Air();
		}
	}
	void SetupInjectionLine(map<string, string>& order)
	{
		cout << "  Setup injection line for "<<order["runSize"]<<" run with "<< m_packager->GetPackagerName() <<" packager and "<<m_stuff->GetStuff()<<" stuffing:\n";
		m_order->InjectionLine();
	}
private:
		void linkBinAndStuff()
		{
			m_order->m_packagerBin->attach(m_stuff);
			m_stuff->linkBin(m_order->m_packagerBin);
		}

public:
	Plastic *m_plastic;
	Order   *m_order;
	Packager *m_packager;
	Stuff*   m_stuff;
};



class GetMold_CofR_8
{

};



class Inventory:public MoldPlace
{
public:
	void GetMold()
	{
		cout << "    Pull "<<m_shape->GetShapeName()<<" mold from inventory.\n";
	}
};


class SisterCompany:public MoldPlace
{
public:
	void GetMold()
	{
		cout << "    Borrow "<<m_shape->GetShapeName()<<" mold from sister company.\n";
	}

private:

};

class Purchase:public MoldPlace
{
public:
	void GetMold()
	{
		cout << "    Acquire "<<m_shape->GetShapeName()<<" mold via purchase.\n";
	}

private:

};


class Mill:public MoldPlace
{
public:
	void GetMold()
	{
		cout << "    Create "<<m_shape->GetShapeName()<<" mold from mill with "<<m_order->m_cavitiesNum<<" cavities:\n";

		m_order->m_metal->GetPlatform()->AttachOrder(m_order);
		m_order->m_metal->GetPlatform()->AttachShape(m_shape);
		m_order->m_metal->GetPlatform()->MillMetal();
	}

private:

};


class Plastic_D_6
{
public:
	Plastic_D_6* m_Plastic_D_6;
	Plastic_D_6(Plastic_D_6* plastic)
	{
		m_Plastic_D_6 = plastic;
	}
	virtual string GetRecipe()=0;
	virtual int GetVolume() = 0;

};

class Color: public Plastic_D_6
{
public:
	Plastic *m_platics;
	Shape_B_9 *m_shape;
	string colorName;

	Color(string color):Plastic_D_6(NULL){
		colorName = color;
	};
	void AttachPlastic(Plastic* plastic){
		m_platics = plastic;
	}
	void AttachShape(Shape_B_9* shape){
		m_shape = shape;
	}


	string GetRecipe()
	{
		//cout << "      Recipe: <plastic>(<vol>) <color>(<vol>) <additive1>(<vol>) <additive2>(<vol>) Total = <vol>.\n";
		return m_platics->GetPlasticName()+"("+to_string(m_shape->GetVolume())+") "+colorName+"("+to_string(m_shape->GetVolume()/10)+") ";
	}
	int GetVolume(){
		return m_shape->GetVolume()+m_shape->GetVolume()/10;
	}
};

class Additive: public Plastic_D_6
{
public:
	int m_volume;
	Additive(Plastic_D_6* plasticD,int volume):Plastic_D_6(plasticD),m_volume(volume){};
	string GetRecipe()
	{
		//cout << "      Recipe: <plastic>(<vol>) <color>(<vol>) <additive1>(<vol>) <additive2>(<vol>) Total = <vol>.\n";
		return m_Plastic_D_6->GetRecipe()+GetAdditiveName()+"("+to_string(m_volume)+") ";
	}

	virtual string GetAdditiveName()=0;
	int GetVolume(){
		return m_Plastic_D_6->GetVolume()+m_volume;
	}
};

class UVInhibiter: public Additive
{
public:
	UVInhibiter(Plastic_D_6* plastic,int volume):Additive(plastic,volume){};

	string GetAdditiveName(){return "UVInhibiter";};

};

class AntiBacterial: public Additive
{
public:
	AntiBacterial(Plastic_D_6* plastic,int volume):Additive(plastic,volume){};

	string GetAdditiveName(){return "AntiBacterial";};
};

class MicroFibers: public Additive
{
public:
	MicroFibers(Plastic_D_6* plastic,int volume):Additive(plastic,volume){};

	string GetAdditiveName(){return "MicroFibers";};
};


class Strategy_1
{

};

class CleanPlastic_A_2:public Strategy_1
{
public:
	virtual void CleanMold()=0;
};


class CleanPolys:public CleanPlastic_A_2
{
private:
	final_problem_classes::CleanPolys m_polys;
public:
	void CleanMold(){
		m_polys.prepForReuse();
	}
};

class CleanPet:public CleanPlastic_A_2
{
protected:
	final_problem_classes::PETCleanup m_pet;
};

class CleanPet_Steel:public CleanPet
{
public:
	void CleanMold(){
		m_pet.carbonize();
	}
};

class CleanPet_Aluminum:public CleanPet
{
public:
	void CleanMold(){
		m_pet.purify();
	}
};

class CleanABS:public CleanPlastic_A_2
{
private:
	final_problem_classes::CleanABS m_abs;
public:
	void CleanMold(){
		m_abs.clean();
	}
};

class CleanSynthetics:public CleanPlastic_A_2
{
private:
	final_problem_classes::CleanABS m_abs;
public:
	void CleanMold(){
		cout << "    Clean synthetic mold: ozone wash.\n";
	}
};



class Tags_D_6
{
public:
	virtual ~Tags_D_6(){
		//cout<<"Tags_D_6\n";
	}
	virtual string GetTagName(){return "";}
	virtual int GetTagLength(){return 0;};
};

class Cavity:public Tags_D_6
{
public:
	Cavity(Tags_D_6 *tag):m_tag(tag){}
	Tags_D_6* m_tag;
	~Cavity(){delete m_tag;}
	void InsertSimulation()
	{
		cout << "    Insert tags ["<<m_tag->GetTagName()<<"] of width "<<m_tag->GetTagLength()<<"/20 mm.\n";
	}
};



class Tag:public Tags_D_6
{
public:
	Tags_D_6* m_tag;
	Tag(Tags_D_6 *tag):m_tag(tag){};


	virtual ~Tag()
	{
		//cout<<" ~Tag";
		if (m_tag)
		{
			delete m_tag;
		}
	}
};



class ModelNumber: public Tag
{
public:
	ModelNumber(Tags_D_6 *tag):Tag(tag){};
	virtual ~ModelNumber(){
		//cout<<"~ModelNumber";
	}
	string GetTagName(){return m_tag->GetTagName()+"ModelNumber ";}
	int GetTagLength(){return m_tag->GetTagLength()+2;};
};

class Blank: public Tag
{
public:
	Blank(Tags_D_6 *tag):Tag(tag){};
	Blank():Tag(NULL){};
	virtual ~Blank(){
		//cout<<"~Blank";
	}
	string GetTagName(){return "";}
	int GetTagLength(){return 0;};
};

class Country: public Tag
{
public:
	Country(Tags_D_6 *tag):Tag(tag){};
	virtual ~Country(){
		//cout<<"~Country";
	}
	string GetTagName(){return m_tag->GetTagName()+"Country ";}
	int GetTagLength(){return m_tag->GetTagLength()+2;};
};

class Date: public Tag
{
public:
	Date(Tags_D_6 *tag):Tag(tag){};
	virtual ~Date(){
		//cout<<"~Date";
	}
	string GetTagName(){return m_tag->GetTagName()+"Date ";}
	int GetTagLength(){return m_tag->GetTagLength()+2;};
};

class IncCounter: public Tag
{
public:
	IncCounter(Tags_D_6 *tag):Tag(tag){};
	virtual ~IncCounter(){
		//cout<<"~Date";
	}
	string GetTagName(){return m_tag->GetTagName()+"IncCounter ";}
	int GetTagLength(){return m_tag->GetTagLength()+4;};
};

class PartNumber: public Tag
{
public:
	PartNumber(Tags_D_6 *tag):Tag(tag){};
	virtual ~PartNumber(){
		//cout<<"~Date";
	}
	string GetTagName(){return m_tag->GetTagName()+"PartNumber ";}
	int GetTagLength(){return m_tag->GetTagLength()+2;};
};

class RecycleCode: public Tag
{
public:
	RecycleCode(Tags_D_6 *tag):Tag(tag){};
	virtual ~RecycleCode(){
		//cout<<"~Date";
	}
	string GetTagName(){return m_tag->GetTagName()+"RecycleCode ";}
	int GetTagLength(){return m_tag->GetTagLength()+6;};
};







class ProcessOrder_TM_4
{
public:
	ProcessOrder_TM_4(Order* order){
		cout<<"  Process order.\n";
		m_order = order;
	}
	virtual ~ProcessOrder_TM_4(){

		if (m_moldLoc)
		{
			delete m_moldLoc;
		}
		if (m_shape)
		{
			delete m_shape;
		}
	};
	Shape_B_9*    m_shape;
	MoldPlace*    m_moldLoc;
	Order*        m_order;


private:

	bool IsPlaceAndShapeUnknown(map<string, string>& order)
	{
		bool IsPlaceUnknown = true;
		if (order["moldLoc"]=="inventory")
			IsPlaceUnknown = false;
		else if (order["moldLoc"]=="mill")
			IsPlaceUnknown = false;
		else if (order["moldLoc"]=="sisterCompany")
			IsPlaceUnknown = false;
		else if (order["moldLoc"]=="purchase")
			IsPlaceUnknown = false;


		bool IsShapeUnknown = true;
        if (order["mold"]=="car")
			IsShapeUnknown = false;
		else if (order["mold"]=="hero")
			IsShapeUnknown = false;
		else if (order["mold"]=="duck")
			IsShapeUnknown = false;
		else if (order["mold"]=="dino")
			IsShapeUnknown = false;

		return IsPlaceUnknown||IsShapeUnknown;
	}


public:
	Plastic* m_plastic;
	void AttachPlastic(Plastic* plastic){m_plastic = plastic;}
	void GetAndInstallMold(map<string, string>& order)
	{
		//moldLoc and shape unknown
		if (IsPlaceAndShapeUnknown(order))
		{
			cout << "    <>Can't find place |"<<order["moldLoc"]<<"| to get |"<<order["mold"]<<"| mold from, defaulting to duck from inventory.\n";

			m_moldLoc = new Inventory;
			m_shape = new Duck(m_moldLoc);
		}
		else
		{
			if (order["moldLoc"]=="inventory")
			{
				// use inventory
				m_moldLoc = new Inventory;
			}
			else if (order["moldLoc"]=="sisterCompany")
			{
				m_moldLoc = new SisterCompany;
			}
			else if (order["moldLoc"]=="purchase")
			{
				m_moldLoc = new Purchase;
			}
			else if (order["moldLoc"]=="mill")
			{
				m_moldLoc = new Mill;
			}

			if (order["mold"]=="car")
			{
				// use inventory
				m_shape = new Car(m_moldLoc);
			}
			else if (order["mold"]=="hero")
			{
				m_shape = new Hero(m_moldLoc);
			}
			else if (order["mold"]=="duck")
			{
				m_shape = new Duck(m_moldLoc);
			}
			else if (order["mold"]=="dino")
			{
				m_shape = new Dino(m_moldLoc);
			}
			m_moldLoc->AttachShape(m_shape);
			m_moldLoc->AttachOrder(m_order);
			m_shape->GetMold();
		}

	}
	void InsertTagsIntoMold(map<string, string>& order)
	{
		string tagString=order["tags"];

		istringstream iss(tagString);

		Tags_D_6 * tag = new Blank();

		do
		{
			string sub;
			iss>>sub;
			if (sub!="")
			{
				if (sub=="ModelNumber")
				{
					tag = new ModelNumber(tag);
				}
				else if (sub=="Country")
				{
					tag = new Country(tag);
				}
				else if (sub=="Date")
				{
					tag = new Date(tag);
				}
				else if (sub=="IncCounter")
				{
					tag = new IncCounter(tag);
				}
				else if (sub=="PartNumber")
				{
					tag = new PartNumber(tag);
				}
				else if (sub=="RecycleCode")
				{
					tag = new RecycleCode(tag);
				}
				else
				{
					//unknown
					cout << "Ignoring unknown tag "<<sub<<".\n";
				}
			}
		} while (iss);
		Cavity *cal = new Cavity(tag);
		cal->InsertSimulation();
		delete cal;
	}

	void LoadAdditiveBins(map<string, string>& order)
	{
		cout << "    Load plastic, color, and additive bins.\n";
		LoadColor(order);
		Plastic_D_6* plasticD = LoadAdditive(order);
		cout << "      Recipe: "<<plasticD->GetRecipe()<<"Total = "<<plasticD->GetVolume()*m_order->m_cavitiesNum<<".\n";
		if (plasticD)
		{
			delete plasticD;
		}

	}
	void RunInjectionCycle(map<string, string>& order)
	{
		cout << "    Cycle IJM for "<<m_plastic->GetPlasticCategory()<<" "<<order["runSize"]<<" times.\n";
		cout << "      Close - "<<m_plastic->InjectionCycle();

		m_order->m_packagerBin->Full();

	}
	void CleanMold(map<string, string>& order)
	{
		CleanPlastic_A_2*  cleanPlastic = CreateCleanPlastic();;
		if (cleanPlastic)
		{
			cleanPlastic->CleanMold();
		}
	}
	void Ship(map<string, string>& order)
	{
		cout << "    Ship to \""<<order["address"]<<"\"\n";
	}
private:
	CleanPlastic_A_2*  CreateCleanPlastic()
	{
		CleanPlastic_A_2*  cleanPlastic = NULL;
		if (m_plastic->GetPlasticName()=="ABS")
		{
			cleanPlastic = new CleanABS();
		}
		else if (m_plastic->GetPlasticName()=="Polypropylene"||m_plastic->GetPlasticName()=="Polyethelene")
		{
			cleanPlastic = new CleanPolys();
		}
		else if (m_plastic->GetPlasticName()=="PET")
		{
			if (m_order->m_metal->GetMetalName()=="Steel")
			{
				cleanPlastic = new CleanPet_Steel;
			}
			else if (m_order->m_metal->GetMetalName()=="Aluminum")
			{
				cleanPlastic = new CleanPet_Aluminum;
			}
		}
		else if (m_plastic->GetPlasticName()=="Styrene"||m_plastic->GetPlasticName()=="Nylon66")
		{
			cleanPlastic = new CleanSynthetics();
		}
		return cleanPlastic;
	}
	Plastic_D_6* LoadAdditive(map<string, string>& order)
	{
		Plastic_D_6* pD=m_color;
		if (order["UVInhibiter"]!="")
		{
			pD = new UVInhibiter(pD,atoi(order["UVInhibiter"].c_str()));
		}
		if (order["AntiBacterial"]!="")
		{
			pD = new AntiBacterial(pD,atoi(order["AntiBacterial"].c_str()));
		}
		if (order["MicroFibers"]!="")
		{
			pD = new MicroFibers(pD,atoi(order["MicroFibers"].c_str()));
		}
		return pD;
	}
	void  LoadColor(map<string, string>& order)
	{

		if (order["color"]=="")
		{
			cout << "      <>No color specified, defaulting to black.\n";
			m_color = new Color("black");
		}
		else
		{
			m_color = new Color(order["color"]);
		}

		m_color->AttachPlastic(m_plastic);
		m_color->AttachShape(m_shape);

	}
	void SimulateMix();

	Color* m_color;

};


class InjectionLine {

//public:
//	virtual ~InjectionLine(){};
//	static injectionline* createinjectionline (map<string, string>& order);
//
//public:

};


// 10,000
class ConcreteA_1 : public AbstractA {};
class ConcreteB_1 : public AbstractB {};
class ConcreteC_1 : public AbstractC {};

class IL_1 : public InjectionLine {};

// 20,000
class ConcreteA_2 : public AbstractA {};
class ConcreteB_2 : public AbstractB {};
class ConcreteC_2 : public AbstractC {};

class IL_2 : public InjectionLine {};

// 50,000
class ConcreteA_3 : public AbstractA {};
class ConcreteB_3 : public AbstractB {};
class ConcreteC_3 : public AbstractC {};
class AF_3 : public Mold_AF {};
class IL_3 : public InjectionLine {};

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

// Seam point - add another class.

}

namespace template_method {	// DP 4.

// Seam point - add another step.

}











// setup injection line - size and packager
//void setupInjectionLine(Order& order)
//{
//	cout << "  Setup injection line for "<<order.GetSize()<<" run with "<<order.packager<<" packager:\n";
//	if (order.m_size<10000)
//	{
//		cout << "    IJM_110 - Aluminum(1) - Linear conveyer belt - CardboardBox\n";
//	}
//	else if (order.m_size<20000)
//	{
//		cout << "    IJM_120 - Aluminum(2) - Y-Split conveyer belt - CardboardBox\n";
//	}
//	else if (order.m_size<50000)
//	{
//		cout << "    IJM_210 - Steel(1) - Linear conveyer belt - PallotBox\n";
//	}
//}

void process(map<string, string>& order) {
    using namespace abstract_factory_solti;
	Setup_AF_10* setup = new Setup_AF_10();
	setup->SetupPlastic(order);   // plastic
	setup->SetupOrder(order);      // order size
	setup->SetupPackager(order);  // Packager
	setup->SetupStuff(order);  // Stuff


	//Setup the injection run:
	// setup Injection Line
	setup->SetupInjectionLine(order);
	//Setup the injection line

	//set up IJM

	// set up Mold

	//set up Conveyer belt

	//Packager

	//Output bin

	   // Process order:
	ProcessOrder_TM_4* orderProcess  = new ProcessOrder_TM_4(setup->m_order);

	orderProcess->AttachPlastic(setup->m_plastic);
	//orderProcess->AttachPlastic();
	orderProcess->GetAndInstallMold(order);//Get and install the mold
	orderProcess->InsertTagsIntoMold(order);	//Insert tags into mold
	orderProcess->LoadAdditiveBins(order);//Load additive bins
	orderProcess->RunInjectionCycle(order);
	orderProcess->CleanMold(order);
	orderProcess->Ship(order);

		//Run the injection cycle till done

		//Clean the mold

	//process order
	//


	delete setup;
	delete orderProcess;

}

pair<string, string> parse(string line) {
	char key[83];
	char val[83] = {0};

	sscanf(line.c_str(), "%s", key);

	char* equalSign = (char *)strchr(line.c_str(), '=');
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

#endif /* DP4_SRC_STUDENTS_YONG_H_ */
