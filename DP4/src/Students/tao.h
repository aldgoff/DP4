/*
 * tao.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */

#ifndef DP4_SRC_STUDENTS_TAO_H_
#define DP4_SRC_STUDENTS_TAO_H_

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <vector>


using namespace std;
//using namespace boost;

std::ofstream fos;
namespace final_tao_file {

namespace legacy_classes {	// Can't change these.

class CleanABS {
public: ~CleanABS() { fos << "~CleanABS "; }
	void clean() {
		fos << "    Clean ABS mold: soak in alcohol, rinse with water, dry.\n";
	}
};

class CleanPolys {
public: ~CleanPolys() { fos << "~CleanPolys "; }
	void prepForReuse() {
		fos << "    Clean Poly mold: rinse with acetone, dry.\n";
	}
};

class PETCleanup {
public: ~PETCleanup() { fos << "~PETCleanup "; }
	void carbonize() { // Use only on stainless steel.
		fos << "    Clean PET steel mold: heat to 895 C.\n";
	}
	void purify() {	// Use only on aluminum.
		fos << "    Clean PET aluminum mold: rinse with soap and water, dry.\n";
	}
};

}

namespace adapter {			// DP 2.
	using namespace legacy_classes;

// Seam point - add another interface.
	class CleanPlastic_A_2
	{
	public:
		string sPlasticName;
		virtual void clean(){}
		virtual ~CleanPlastic_A_2(){fos<<"CleanPlastic_A_2 ";}
		static CleanPlastic_A_2 *create_PlasticCleanObj(string &sPlasticName, string &sMetal);
	};

	class Synthetics_Clean: public CleanPlastic_A_2
	{
	public:
		Synthetics_Clean(){sPlasticName = "Synthetics";}
		~Synthetics_Clean(){fos<<"~adapter::Synthetics_Clean ";}
		void clean()
		{
			fos<<"    Clean synthetic mold: ozone wash."<<endl;
		}
	};

	class PET_Clean: public CleanPlastic_A_2
	{
		PETCleanup oPETCleanup;
		string sMetal;
	public:
		PET_Clean(string &in_Metal) : sMetal(in_Metal){sPlasticName = "PET";};
		~PET_Clean(){fos<<"~adapter::PET_Clean ";}
		void clean(){
			if(!sMetal.compare("aluminum"))
				oPETCleanup.purify();
			else if(!sMetal.compare("steel"))
				oPETCleanup.carbonize();
		}
	};

	class Poly_Clean: public CleanPlastic_A_2
	{
		CleanPolys oCleanPolys;
	public:
		Poly_Clean(){sPlasticName = "Poly";}
		~Poly_Clean(){fos<<"~adapter::Poly_Clean ";}
		void clean()
		{
			oCleanPolys.prepForReuse();
		}
	};

	class ABS_Clean: public CleanPlastic_A_2
	{
		CleanABS oCleanABS;
	public:
		ABS_Clean(){sPlasticName = "ABS";}
		~ABS_Clean(){fos<<"~adapter::ABS_Clean ";}
		void clean()
		{
			oCleanABS.clean();
		}
	};

	CleanPlastic_A_2 * CleanPlastic_A_2::create_PlasticCleanObj(string &sPlastic, string &sMetal)
	{
		if(sPlastic.compare("ABS") == 0)
		{
			return new adapter::ABS_Clean;
		}
		else if(sPlastic.compare("PET") == 0)
		{
			return new adapter::PET_Clean(sMetal);
		}
		else if(sPlastic.compare("Polypropylene") == 0 || sPlastic.compare("Polyethelene") == 0)
		{
			return new adapter::Poly_Clean;
		}
		else if(sPlastic.compare("Styrene") == 0 || sPlastic.compare("Nylon66") == 0)
		{
			return new adapter::Synthetics_Clean;
		}
		else
		{
			return new adapter::ABS_Clean;
		}
	}
}

namespace strategy {		// DP 1.

// Seam point - add another algorithm.
	class Strategy_1{
	public:
		virtual void Inject()
		{
			fos <<"      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject."<<endl;
		}
		virtual ~Strategy_1(){fos <<" ~Strategy_1"<<endl;};
		static Strategy_1 *Create_InjectionObj(string &sPlastic);
	};

	class ABS: public Strategy_1
	{
	public:
		~ABS(){fos<<"~ABS "<<endl;}
		void Inject()
		{
			fos <<"      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject."<<endl;
		}
	};

	class Poly: public Strategy_1
	{
	public:
		~Poly(){fos<<"~Poly "<<endl;}
		void Inject()
		{
			fos <<"      Close - heat to 350 - inject at 90 PSI - cool to 290 - separate - smooth eject."<<endl;
		}
	};
	class PET: public Strategy_1
	{
	public:
		~PET(){fos<<"~PET "<<endl;}
		void Inject()
		{
			fos <<"      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject."<<endl;
		}
	};
	class Synthetics: public Strategy_1
	{
	public:
		~Synthetics(){fos<<"~Synthetics "<<endl;}
		void Inject()
		{
			fos <<"      Close - heat to 480 - inject at 150 PSI - cool to 390 - separate - shock eject."<<endl;
		}
	};

	Strategy_1 * Strategy_1::Create_InjectionObj(string &sPlasticName)
	{
		if(!sPlasticName.compare("ABS"))
		{
			return new strategy::ABS;
		}
		else if(!sPlasticName.compare("Poly"))
		{
			return new strategy::Poly;
		}
		else if(!sPlasticName.compare("PET"))
		{
			return new strategy::PET;
		}
		else if(!sPlasticName.compare("Synthetics"))
		{
			return new strategy::Synthetics;
		}
		else
		{
			return new strategy::ABS;
		}
	}
}

namespace observer {		// DP 7.
	class Subject_7;
	class Observer_7
	{
	public:
		virtual ~Observer_7(){fos<<"Observer_7"<<endl;}
		virtual void update(Subject_7 *pSubject){};
	};

	class Stuffer : public Observer_7
	{
	public:
		string sStufferName;
		virtual ~Stuffer(){fos<<"~Stuffer ";}
		virtual void update(observer::Subject_7 *pSubject);
		static Stuffer *create_stuffer(string &sStufferName);
	};
	class Air : public Stuffer
	{
	public:
		Air()
		{
			sStufferName = "air";
		}
		virtual ~Air(){fos<<"~Air ";}
		void update(observer::Subject_7 *pSubject)
		{
			Stuffer::update(pSubject);
		}
	};
	class Popcorn : public Stuffer
	{
	public:
		Popcorn(){sStufferName = "styrene popcorn";}
		virtual ~Popcorn(){fos<<"~Popcorn ";}
		void update(observer::Subject_7 *pSubject)
		{
			Stuffer::update(pSubject);
		}
	};
	class BubbleWrap : public Stuffer
	{
	public:
		BubbleWrap(){sStufferName = "bubble wrap";}
		virtual ~BubbleWrap(){fos<<"~BubbleWrap ";}
		void update(observer::Subject_7 *pSubject)
		{
			Stuffer::update(pSubject);
		}
	};
	class Foam : public Stuffer
	{
	public:
		Foam(){sStufferName = "expanding foam";}
		virtual ~Foam(){fos<<"~Foam ";}
		void update(observer::Subject_7 *pSubject)
		{
			Stuffer::update(pSubject);
		}
	};
	Stuffer * Stuffer::create_stuffer(string &sStufferName)
	{
		if(sStufferName.compare("Popcorn") == 0)
		{
			return new observer::Popcorn;
		}
		else if (sStufferName.compare("BubbleWrap") == 0)
		{
			return new observer::BubbleWrap;
		}
		else if (sStufferName.compare("Foam") == 0)
		{
			return new observer::Foam;
		}
		else if (sStufferName.compare("Air") == 0)
		{
			return new observer::Air;
		}
		else
		{
			fos<<"  <>Unknown stuffer || defaulting to Air stuffer."<<endl;
			return new observer::Air;
		}
	}


	class Subject_7
	{
		list<Observer_7 *> observers;
	public:
		string sPackageBinName;

	public:
		~Subject_7(){fos<<"~Subject_7 Observers left to process (should be zero) = 0."<<endl;}

		void Attach(Observer_7 *obj)
		{
			observers.push_back(obj);
		};
		void Detach(Observer_7 *obj)
		{
			observers.remove(obj);
		};
		bool getState()
		{
			return true;
		};
		void notify()
		{
			fos<<"      "<<sPackageBinName.c_str()<<" package bin full..."<<endl;
			list<Observer_7 *>::iterator iter;
			for(iter = observers.begin(); iter != observers.end(); ++iter)
			{
				(*iter)->update(this);
			}
		}
	};

	void Stuffer::update(observer::Subject_7 *pSubject)
	{
		fos<<"        Stuffer filling "<<pSubject->sPackageBinName.c_str()<<" package bin with "<<sStufferName.c_str()<<" stuffing."<<endl;
	}
}

namespace abstract_factory {// DP 10.
	class observer::Subject_7;

	// Seam point - add another family.
	class IJM_AF : public observer::Observer_7
	{
	public:
		int CavityNum;
		virtual ~IJM_AF(){fos<<"~IJM_AF ";}
		void update(observer::Subject_7 *pSubject)
		{
			fos<<"        IJM pausing while "<<pSubject->sPackageBinName.c_str()<<" package bin is swapped."<<endl;
		}
	};
	class IJM_110 : public IJM_AF
	{
	public:
		IJM_110(){
			CavityNum = 1;
			fos<<"    IJM_110 - ";
		}
		~IJM_110(){fos<<"~IJM_110 ";}
	};
	class IJM_120 : public IJM_AF
	{
	public:
		IJM_120(){
			CavityNum = 2;
			fos<<"    IJM_120 - ";
		}
		~IJM_120(){fos<<"~IJM_120 ";}
	};
	class IJM_210 : public IJM_AF
	{
	public:
		IJM_210(){
			CavityNum = 1;
			fos<<"    IJM_210 - ";
		}
		~IJM_210(){fos<<"~IJM_210 ";}
	};
	class IJM_140 : public IJM_AF
	{
	public:
		IJM_140(){
			CavityNum = 4;
			fos<<"    IJM_140 - ";
		}
		~IJM_140(){fos<<"~IJM_140 ";}
	};
	class IJM_220 : public IJM_AF
	{
	public:
		IJM_220(){
			CavityNum = 2;
			fos<<"    IJM_220 - ";
		}
		~IJM_220(){fos<<"~IJM_220 ";}
	};
	class IJM_240 : public IJM_AF
	{
	public:
		IJM_240(){
			CavityNum = 4;
			fos<<"    IJM_240 - ";
		}
		~IJM_240(){fos<<"~IJM_240 ";}
	};

	class Mold_AF
	{
	public:
		string sMetal;
		virtual ~Mold_AF(){fos<<"~Mold_AF"<<endl;}
	};
	class Aluminum : public Mold_AF
	{
	public:
		Aluminum(){sMetal = "aluminum";}
		~Aluminum(){fos<<"~Aluminum ";}
	};
	class Steel : public Mold_AF
	{
	public:
		Steel(){sMetal = "steel";}
		~Steel(){fos<<"~Steel ";}
	};

	class ConveyerBelt_AF : public observer::Observer_7
	{
	public:
		virtual ~ConveyerBelt_AF(){fos<<"~ConveyerBelt_AF ";}
		void update(observer::Subject_7 *pSubject)
		{
			fos<<"        Conveyer Belt pausing while "<<pSubject->sPackageBinName.c_str()<<" package bin is swapped."<<endl;
		}
	};
	class LinearBelt : public ConveyerBelt_AF
	{
	public:
		LinearBelt(){fos<<"Linear conveyer belt - ";}
		~LinearBelt(){fos<<"~LinearBelt ";}
	};
	class YSplitBelt : public ConveyerBelt_AF
	{
	public:
		YSplitBelt(){fos<<"Y-Split conveyer belt - ";}
		~YSplitBelt(){fos<<"~YSplitBelt ";}
	};
	class VlevelBelt : public ConveyerBelt_AF
	{
	public:
		VlevelBelt(){fos<<"V-Level conveyer belt - ";}
		~VlevelBelt(){fos<<"~VlevelBelt ";}
	};

	class PackageBin_AF : public observer::Subject_7
	{
	public:
		virtual ~PackageBin_AF(){fos<<"~PackageBin_AF ";}
	};
	class CardboardBox : public PackageBin_AF
	{
	public:
		CardboardBox()
		{
			sPackageBinName = "CardboardBox";
			fos<<"CardboardBox"<<endl;
		}
		~CardboardBox(){fos<<"~CardboardBox ";}
	};
	class PallotBox : public PackageBin_AF
	{
	public:
		PallotBox()
		{
			sPackageBinName = "PallotBox";
			fos<<"PallotBox"<<endl;
		}
		~PallotBox(){fos<<"~PallotBox ";}
	};
	class Crate : public PackageBin_AF
	{
	public:
		Crate()
		{
			sPackageBinName = "Crate";
			fos<<"Crate"<<endl;
		}
		~Crate(){fos<<"~Crate ";}
	};

	class Setup_AF_10
	{
	public:
		int m_orderSize;

		virtual ~Setup_AF_10(){fos<<"~Setup_AF_10"<<endl;}

		virtual IJM_AF *createIJM()=0;
		virtual Mold_AF *createMold()=0;
		virtual ConveyerBelt_AF *createConveyerBelt() = 0;
		virtual PackageBin_AF *createPackbin()=0;

		static Setup_AF_10 * createOrder(int &orderSize);
	};

	class PilotOrder : public Setup_AF_10
	{
	public:
		PilotOrder(int orderSize){m_orderSize = orderSize;}
		~PilotOrder(){fos<<"~PilotOrder";}
		IJM_AF *createIJM(){return new IJM_110;}
		Mold_AF *createMold(){fos<<"Aluminum(1) - "; return new Aluminum;}
		ConveyerBelt_AF *createConveyerBelt(){return new LinearBelt;}
		PackageBin_AF *createPackbin(){return new CardboardBox;}
	};
	class SmallOrder : public Setup_AF_10
	{
	public:
		SmallOrder(int orderSize){m_orderSize = orderSize;}
		~SmallOrder(){fos<<"~SmallOrder";}
		IJM_AF *createIJM(){return new IJM_120;}
		Mold_AF *createMold(){fos<<"Aluminum(2) - "; return new Aluminum;}
		ConveyerBelt_AF *createConveyerBelt(){return new YSplitBelt;}
		PackageBin_AF *createPackbin(){return new CardboardBox;};
	};
	class FastOrder : public Setup_AF_10
	{
	public:
		FastOrder(int orderSize){m_orderSize = orderSize;}
		~FastOrder(){fos<<"~FastOrder";}
		IJM_AF *createIJM(){return new IJM_140;}
		Mold_AF *createMold(){fos<<"Aluminum(4) - "; return new Aluminum;}
		ConveyerBelt_AF *createConveyerBelt(){return new VlevelBelt;}
		PackageBin_AF *createPackbin(){return new PallotBox;}
	};
	class MediumOrder : public Setup_AF_10
	{
	public:
		MediumOrder(int orderSize){m_orderSize = orderSize;}
		~MediumOrder(){fos<<"~MediumOrder";}
		IJM_AF *createIJM(){return new IJM_210;}
		Mold_AF *createMold(){fos<<"Steel(1) - "; return new Steel;}
		ConveyerBelt_AF *createConveyerBelt(){return new LinearBelt;}
		PackageBin_AF *createPackbin(){return new PallotBox;}
	};
	class LargeOrder : public Setup_AF_10
	{
	public:
		LargeOrder(int orderSize){m_orderSize = orderSize;}
		~LargeOrder(){fos<<"~LargeOrder";}
		IJM_AF *createIJM(){return new IJM_220;}
		Mold_AF *createMold(){fos<<"Steel(2) - "; return new Steel;}
		ConveyerBelt_AF *createConveyerBelt(){return new YSplitBelt;}
		PackageBin_AF *createPackbin(){return new Crate;}
	};
	class HugeOrder : public Setup_AF_10
	{
	public:
		HugeOrder(int orderSize){m_orderSize = orderSize;}
		~HugeOrder(){fos<<"~HugeOrder";}
		IJM_AF *createIJM(){return new IJM_240;}
		Mold_AF *createMold(){fos<<"Steel(4) - "; return new Steel;}
		ConveyerBelt_AF *createConveyerBelt(){return new VlevelBelt;}
		PackageBin_AF *createPackbin(){return new Crate;}
	};

	Setup_AF_10 * Setup_AF_10::createOrder(int &orderSize)
	{
		if(orderSize == 0)
		{
			fos<<"  <>No size specified, defaulting to 100."<<endl;
			orderSize = 100;
			return new PilotOrder(100);
		}
		else if(orderSize <= 10000)
		{
			return new PilotOrder(orderSize);
		}
		else if(orderSize <= 20000)
		{
			return new SmallOrder(orderSize);
		}
		else if(orderSize <= 40000)
		{
			return new FastOrder(orderSize);
		}
		else if(orderSize <= 50000)
		{
			return new MediumOrder(orderSize);
		}
		else if(orderSize <= 100000)
		{
			return new LargeOrder(orderSize);
		}
		else if(orderSize <= 200000)
		{
			return new HugeOrder(orderSize);
		}
		else
		{
			fos<<"  <>size too large |"<<orderSize<<"| defaulting to HugeOrder of 200000."<<endl;
			orderSize = 200000;
			return new HugeOrder(orderSize);
		}
	}
}

namespace bridge {			// DP 9.

// Seam Point - add another implementation.
//////////////////////////////////////////////////////////////////////////
	class Platform_B_9
	{
	public:
		string sMetal;
		int NumCavity;
		virtual ~Platform_B_9(){fos<<"~Platform_B_9"<<endl;}
		virtual void Mill_Shape(const string &in_finish, const string &sMold){}
		static Platform_B_9*create_Platform(const int in_CavityNum, string &sMetal, string &sFinish);
	};

	class HighCarbon : public Platform_B_9
	{
	public:
		HighCarbon(int in_cavity){sMetal = "aluminum"; NumCavity = in_cavity;}
		virtual ~HighCarbon(){fos<<"~HighCarbon ";}
		void Mill_Shape(const string &in_finish, const string &sMold)
		{
			fos<<"      using HighCarbon tools (drill, cut, and high speed grind) to mill "<<sMetal.c_str()<<" block into "<<NumCavity<<" "<<sMold<<" shapes with "<<in_finish.c_str()<<" finish."<<endl;
		}
	};

	class Carbide : public Platform_B_9
	{
	public:
		Carbide(int in_cavity){sMetal = "steel"; NumCavity = in_cavity;}
		virtual ~Carbide(){fos<<"~Carbide ";}
		void Mill_Shape(const string &in_finish, const string &sMold)
		{
			fos<<"      using Carbide tools (high speed drill, cross cut, and layer grind) to mill "<<sMetal.c_str()<<" block into "<<NumCavity<<" "<<sMold<<" shapes with "<<in_finish.c_str()<<" finish."<<endl;
		}
	};

	class DiamonTipped : public Platform_B_9
	{
	public:
		DiamonTipped(int in_cavity){sMetal = "steel"; NumCavity = in_cavity;}
		virtual ~DiamonTipped(){fos<<"~DiamonTipped ";}
		void Mill_Shape(const string &in_finish, const string &sMold)
		{
			fos<<"      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind) to mill "<<sMetal.c_str()<<" block into "<<NumCavity<<" "<<sMold<<" shapes with "<<in_finish.c_str()<<" finish."<<endl;
		}
	};

	Platform_B_9 *Platform_B_9::create_Platform(const int in_CavityNum, string &sMetal, string &sFinish)
	{
		if(!sMetal.compare("aluminum"))
		{
			return new bridge::HighCarbon(in_CavityNum);
		}
		else if(!sMetal.compare("steel"))
		{
			if(!sFinish.compare("satin"))
			{
				return new bridge::DiamonTipped(in_CavityNum);
			}
			else
			{
				return new bridge::Carbide(in_CavityNum);
			}
		}
		else
		{
			return new bridge::Platform_B_9;
		}
	}

//////////////////////////////////////////////////////////////////////////
// Seam Point - add another abstraction.
//////////////////////////////////////////////////////////////////////////
	class Shape_B_9
	{
	public:
		Platform_B_9 *pTools;
		string sFinish;
		int Volume;
		string sMold;

	public:
		Shape_B_9() : pTools(0),Volume(0){}
		virtual ~Shape_B_9()
		{
			if(pTools) delete pTools;
			fos<<"~Shape_B_9 ";
		}
		virtual void CreateShapewithTools()
		{
			if(pTools)
				pTools->Mill_Shape(sFinish, sMold);
		}
		static Shape_B_9 *create_ShapeObj(string &sMold, string &sFinish);
	};

	class Duck : public Shape_B_9
	{
	public:
		Duck(string &in_Finish)
		{
			sMold = "duck";
			sFinish = in_Finish;
			Volume = 35;
		}
		~Duck(){fos<<"~Duck ";}
	};

	class Car : public Shape_B_9
	{
	public:
		Car(string &in_Finish)
		{
			sMold = "car";
			sFinish = in_Finish;
			Volume = 40;
		}
		~Car(){fos<<"~Car ";}
	};
	class Hero : public Shape_B_9
	{
	public:
		Hero(string &in_Finish)
		{
			sMold = "hero";
			sFinish = in_Finish;
			Volume = 50;
		}
		~Hero(){fos<<"~Hero ";}
	};

	class Dino : public Shape_B_9
	{
	public:
		Dino(string &in_Finish)
		{
			sMold = "dino";
			sFinish = in_Finish;
			Volume = 30;
		}
		~Dino(){fos<<"~Dino ";}
	};

	Shape_B_9 *Shape_B_9::create_ShapeObj(string &sMold, string &sFinish)
	{
		if(!sMold.compare("duck"))
		{
			return new bridge::Duck(sFinish);
		}
		else if(!sMold.compare("car"))
		{
			return new bridge::Car(sFinish);
		}
		else if(!sMold.compare("hero"))
		{
			return new bridge::Hero(sFinish);
		}
		else if(!sMold.compare("dino"))
		{
			return new bridge::Dino(sFinish);
		}
		else
		{
			return new bridge::Duck(sFinish);
		}
	}
}

namespace chain_of_resp {	// DP 8.

// Seam points - add another responder.
	class GetMold_CofR_8
	{
	protected:
		GetMold_CofR_8 *m_pSuccessor;

	public:
		GetMold_CofR_8() : m_pSuccessor(NULL){}
		virtual ~GetMold_CofR_8(){fos<<"~GetMold_CofR_8 ";}
		void setSuccessor(GetMold_CofR_8 *pSuccessor)
		{
			m_pSuccessor = pSuccessor;
		}
		virtual void GetMold(string &sMoldLoc, string &sMold, int CavictyNum)
		{
			fos<<"    <>Can't find place || to get || mold from, defaulting to duck from inventory."<<endl;
			sMoldLoc = "inventory";
		}
	};

	class Inventory : public GetMold_CofR_8
	{
	public:
		~Inventory(){fos<<"~Inventory ";}
		void GetMold(string &sMoldLoc, string &sMold, int CavictyNum)
		{
			if(sMoldLoc.compare("inventory") == 0)
				fos<<"    Pull "<<sMold.c_str()<<" mold from inventory."<<endl;
			else if(m_pSuccessor)
				m_pSuccessor->GetMold(sMoldLoc, sMold, CavictyNum);
			else
				GetMold_CofR_8::GetMold(sMoldLoc, sMold, CavictyNum);
		}
	};
	class SisterCompany : public GetMold_CofR_8
	{
	public:
		~SisterCompany(){fos<<"~SisterCompany ";}
		void GetMold(string &sMoldLoc, string &sMold, int CavictyNum)
		{
			if(sMoldLoc.compare("sisterCompany") == 0)
				fos<<"    Borrow "<<sMold.c_str()<<" mold from sister Company."<<endl;
			else if(m_pSuccessor)
				m_pSuccessor->GetMold(sMoldLoc, sMold, CavictyNum);
			else
				GetMold_CofR_8::GetMold(sMoldLoc, sMold, CavictyNum);
		}
	};
	class Purchase : public GetMold_CofR_8
	{
	public:
		~Purchase(){fos<<"~Purchase ";}
		void GetMold(string &sMoldLoc, string &sMold, int CavictyNum)
		{
			if(sMoldLoc.compare("purchase") == 0)
				fos<<"    Acquire "<<sMold.c_str()<<" mold via purchase."<<endl;
			else if(m_pSuccessor)
				m_pSuccessor->GetMold(sMoldLoc, sMold, CavictyNum);
			else
				GetMold_CofR_8::GetMold(sMoldLoc, sMold, CavictyNum);
		}
	};
	class Mill : public GetMold_CofR_8
	{
	public:
		~Mill(){fos<<"~Mill ";}
		void GetMold(string &sMoldLoc, string &sMold, int CavictyNum)
		{
			if(sMoldLoc.compare("mill") == 0)
			{
				fos<<"    Create "<<sMold.c_str()<<" mold from mill with "<<CavictyNum<<" cavities:"<<endl;
			}
			else
				GetMold_CofR_8::GetMold(sMoldLoc, sMold, CavictyNum);
		}
	};
}

namespace decorator {		// DP 6.
	class Plastic_D_6
	{
	public:
		int totalVol;
	public:
		Plastic_D_6() : totalVol(0){}
		virtual void PrintRecipe(){fos<<"      Recipe: ";}
		virtual int GetVolume(){return 0;}
		//virtual void PrintTotal(){fos<<"Total = "<<totalVol<<"."<<endl;}
		virtual ~Plastic_D_6(){fos<<"~Plastic_D_6"<<endl;}
	};

	class AdditiveDecorator : public Plastic_D_6
	{
	public:
		Plastic_D_6 *pPlasticAdditive;
	public:
		AdditiveDecorator(){}
		AdditiveDecorator(Plastic_D_6 *in_PlasticAdditive) : pPlasticAdditive(in_PlasticAdditive){}
		virtual ~AdditiveDecorator(){fos<<"~AdditiveDecorator ";}
	};
	class AntiBacterial : public AdditiveDecorator
	{
		int volume;
	public:
		AntiBacterial(){}
		AntiBacterial(Plastic_D_6 *in_PlasticAdditive, int in_volume) : volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol+= volume;
		}
		virtual ~AntiBacterial(){fos<<"~AntiBacterial ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"AntiBacterial("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class UVInhibiter : public AdditiveDecorator
	{
		int volume;
	public:
		UVInhibiter(){}
		UVInhibiter(Plastic_D_6 *in_PlasticAdditive, int in_volume) : volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol += volume;
		}
		virtual ~UVInhibiter(){fos<<"~UVInhibiter ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"UVInhibiter("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class MicroFiber : public AdditiveDecorator
	{
		int volume;
	public:
		MicroFiber(){}
		MicroFiber(Plastic_D_6 *in_PlasticAdditive, int in_volume) : volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol+= volume;
		}
		virtual ~MicroFiber(){fos<<"~MicroFiber ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"Microfibers("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class Color : public AdditiveDecorator
	{
		int volume;
		string sColor;
	public:
		Color(){}
		Color(Plastic_D_6 *in_PlasticAdditive, string in_sColor, int PlasticVolume)
			: AdditiveDecorator(in_PlasticAdditive), sColor(in_sColor)
		{
			volume = PlasticVolume/10;
		}
		virtual ~Color(){fos<<"~Color ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<sColor.c_str()<<"("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class ABS : public AdditiveDecorator
	{
		int volume;
	public:
		ABS(){}
		ABS(Plastic_D_6 *in_PlasticAdditive, int in_volume)
			: volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol += volume;
		}
		virtual ~ABS(){fos<<"~ABS ";}

		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"ABS("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class Polypropylene : public AdditiveDecorator
	{
		int volume;
	public:
		Polypropylene(){}
		Polypropylene(Plastic_D_6 *in_PlasticAdditive, int in_volume)
			: volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol += volume;
		}
		virtual ~Polypropylene(){fos<<"~Polypropylene ";}

		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"Polypropylene("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class PET : public AdditiveDecorator
	{
		int volume;
	public:
		PET(){}
		PET(Plastic_D_6 *in_PlasticAdditive, int in_volume)
			: volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol += volume;
		}
		virtual ~PET(){fos<<"~PET ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"PET("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class Polyethelene : public AdditiveDecorator
	{
		int volume;
	public:
		Polyethelene(){}
		Polyethelene(Plastic_D_6 *in_PlasticAdditive, int in_volume)
			: volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol += volume;
		}
		virtual ~Polyethelene(){fos<<"~Polyethelene ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"Polyethelene("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class Styrene : public AdditiveDecorator
	{
		int volume;
	public:
		Styrene(){}
		Styrene(Plastic_D_6 *in_PlasticAdditive, int in_volume)
			: volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol += volume;
		}
		virtual ~Styrene(){fos<<"~Styrene ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"Styrene("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};
	class Nilon66 : public AdditiveDecorator
	{
		int volume;
	public:
		Nilon66(){}
		Nilon66(Plastic_D_6 *in_PlasticAdditive, int in_volume)
			: volume(in_volume), AdditiveDecorator(in_PlasticAdditive)
		{
			//totalVol += volume;
		}
		virtual ~Nilon66(){fos<<"~Nilon66 ";}
		void PrintRecipe()
		{
			pPlasticAdditive->PrintRecipe();
			fos<<"Nylon66("<<volume<<") ";
		}
		int GetVolume()
		{
			return pPlasticAdditive->GetVolume() + volume;
		}
	};

	class Tags_D_6
	{
	public:
		int tagWidth;
		list<Tags_D_6 *> TagDecoratorList;
	public:
		virtual ~Tags_D_6()
		{
			fos<<"~Tags_D_6"<<endl;
			for(std::list<Tags_D_6*>::iterator it = TagDecoratorList.begin(); it != TagDecoratorList.end(); ++it)
			{
				if(*it)
					delete (*it);
			}
			TagDecoratorList.clear();
		}
		virtual void insertTags(){}
		virtual int GetTagWidth(){return 0;}
	};

	class TagDecorator : public Tags_D_6
	{
	public:
		Tags_D_6 *m_pdecorator;
	public:
		TagDecorator(Tags_D_6 * in_tag) : m_pdecorator(in_tag){}
		virtual ~TagDecorator(){fos<<"~TagDecorator ";}
	};
	class Blank : public TagDecorator
	{
	public:
		Blank(Tags_D_6 *in_tag) : TagDecorator(in_tag){}
		~Blank(){fos<<"~Blank ";}
	};
	class ModelNumber : public TagDecorator
	{
		int tagWidth;
	public:
		ModelNumber(Tags_D_6 *in_tag) : TagDecorator(in_tag), tagWidth(2)
		{
		}
		~ModelNumber(){fos<<"~ModelNumber ";}
		void insertTags()
		{
			fos<<"ModelNumber ";
		}
		int GetTagWidth(){return tagWidth;}
	};
	class Country : public TagDecorator
	{
		int tagWidth;
	public:
		Country(Tags_D_6 *in_tag) : TagDecorator(in_tag), tagWidth(2)
		{
		}
		~Country(){fos<<"~Country ";}
		void insertTags()
		{
			fos<<"Country ";
		}
		int GetTagWidth(){return tagWidth;}
	};
	class Date : public TagDecorator
	{
		int tagWidth;
	public:
		Date(Tags_D_6 *in_tag) : TagDecorator(in_tag), tagWidth(2)
		{
		}
		~Date(){fos<<"~Date ";}
		void insertTags()
		{
			fos<<"Date ";
		}
		int GetTagWidth(){return tagWidth;}
	};
	class IncrementCounter : public TagDecorator
	{
		int tagWidth;
	public:
		IncrementCounter(Tags_D_6 *in_tag) : TagDecorator(in_tag), tagWidth(4)
		{
		}
		~IncrementCounter(){fos<<"~IncrementCounter ";}
		void insertTags()
		{
			fos<<"IncCounter ";
		}
		int GetTagWidth(){return tagWidth;}
	};
	class PartNumber : public TagDecorator
	{
		int tagWidth;
	public:
		PartNumber(Tags_D_6 *in_tag) : TagDecorator(in_tag), tagWidth(2)
		{
		}
		~PartNumber(){fos<<"~PartNumber ";}
		void insertTags()
		{
			fos<<"PartNumber ";
		}
		int GetTagWidth(){return tagWidth;}
	};
	class RecycleCode : public TagDecorator
	{
		int tagWidth;
	public:
		RecycleCode(Tags_D_6 *in_tag) : TagDecorator(in_tag), tagWidth(6)
		{
		}
		~RecycleCode(){fos<<"~RecycleCode ";}
		void insertTags()
		{
			fos<<"RecycleCode ";
		}
		int GetTagWidth(){return tagWidth;}
	};
}

namespace factory_method {	// DP 5.
	class observer::Subject_7;

	class Packager_FM_5 : public observer::Observer_7
	{
	public:
		virtual ~Packager_FM_5(){fos<<"~Packager_FM_5 "<<endl;}
		static Packager_FM_5 * createPackager(string &sPackager);

		void update(observer::Subject_7 *pSubject)
		{
			fos<<"        Packager pausing while "<<pSubject->sPackageBinName.c_str()<<" package bin is swapped."<<endl;
		}
	};

	class Bulk : public Packager_FM_5
	{
	public:
		~Bulk(){fos<<"~Bulk ";}
	};

	class ShrinkWrap : public Packager_FM_5
	{
	public:
		~ShrinkWrap(){fos<<"~ShrinkWrap ";}
	};

	class HardPack : public Packager_FM_5
	{
	public:
		~HardPack(){fos<<"~HardPack ";}
	};
	class ZipLock : public Packager_FM_5
	{
	public:
		~ZipLock(){fos<<"~ZipLock ";}
	};

	Packager_FM_5 * Packager_FM_5::createPackager(string &sPackager)
	{
		if(sPackager.compare("Bulk") == 0)
		{
			return new Bulk;
		}
		else if(sPackager.compare("ShrinkWrap") == 0)
		{
			return new ShrinkWrap;
		}
		else if(sPackager.compare("HardPack") == 0)
		{
			return new HardPack;
		}
		else if(sPackager.compare("ZipLock") == 0)
		{
			return new ZipLock;
		}
		else
		{
			sPackager = "Bulk";
			fos<<"  <>Unknown packager || defaulting to Bulk packager."<<endl;
			return new Bulk;
		}
	}
}

namespace template_method {	// DP 4.
// Seam point - add another step.
	class ProcessOrder_TM_4
	{
	protected:
		int CavityNum;
		int OrderSize;

		string sPackager;
		string sPlastic;
		string sMold;
		string sMoldLoc;
		string sFinish;
		string sColor;
		int UvInhibiterSize;
		int AntiBacterialSize;
		string sTags;
		std::vector<string>TagVector;

		string sMetal;
		int PlasticVolume;
		int MicroFibersSize;
		string sAddress;
		string sStuffer;

	public:
		adapter::CleanPlastic_A_2 *pPlastic;
		chain_of_resp::Inventory oInventory;
		chain_of_resp::SisterCompany oSisterCompany;
		chain_of_resp::Purchase oPurchase;
		chain_of_resp::Mill oMill;
		bridge::Shape_B_9 *pShape;
		bridge::Platform_B_9 *pMillTools;
		decorator::Tags_D_6 oTags;
		decorator::Plastic_D_6 oAdditives;
		strategy::Strategy_1 *pInjectProcess;

		abstract_factory::Setup_AF_10 *pOrder;
		factory_method::Packager_FM_5 *pPackager;
		abstract_factory::IJM_AF *pIJM;
		abstract_factory::Mold_AF *pMold;
		abstract_factory::ConveyerBelt_AF *pConveyerBelt;
		abstract_factory::PackageBin_AF *pPackageBin;
		observer::Stuffer *pStuffer;

	private:

		void ParseOrder(std::map<string, string> &order)
		{
			OrderSize = atoi(order["size"].c_str());
			sPackager = order["packager"];
			sPlastic = order["plastic"];
			sMold = order["mold"];
			sMoldLoc = order["moldLoc"];
			sFinish = order["finish"];
			sColor = order["color"];
			UvInhibiterSize = atoi(order["UVInhibiter"].c_str());
			AntiBacterialSize = atoi(order["AntiBacterial"].c_str());
			MicroFibersSize = atoi(order["MicroFibers"].c_str());
			sTags = order["tags"];
			sAddress = order["address"];
			sStuffer = order["stuffer"];

			if(!sTags.empty())
			{
				int pos = 0;
				int TagEndPos = 0;
				do
				{
					TagEndPos = sTags.find(' ', pos);

					string sOneTag = sTags.substr(pos, TagEndPos-pos);
					TagVector.push_back(sOneTag);
					pos = TagEndPos+1;
				}while(TagEndPos !=string::npos);
			}
		}

	public:
		ProcessOrder_TM_4()
			: pPlastic(NULL),  pShape(NULL), pMillTools(NULL), pInjectProcess(NULL),
				pOrder(NULL), pPackager(NULL), pIJM(NULL), pMold(NULL),
				pConveyerBelt(NULL),  pPackageBin(NULL), pStuffer(NULL),
				OrderSize(0), CavityNum(0), PlasticVolume(0)
		{
		}

		virtual ~ProcessOrder_TM_4()
		{
			if(pShape)
				delete pShape;
			if(pInjectProcess)
				delete pInjectProcess;
			if(pPlastic)
				delete pPlastic;
			if(pStuffer)
				delete pStuffer;
			if(pPackageBin)
				delete pPackageBin;
			if(pConveyerBelt)
				delete pConveyerBelt;
			if(pMold)
				delete pMold;
			if(pIJM)
				delete pIJM;
			if(pPackager)
				delete pPackager;
			if(pOrder)
				delete pOrder;
			fos<<"~ProcessOrder_TM_4"<<endl;
		}


		void ProcessOrder(std::map<string, string>	&order)
		{
			ParseOrder(order);

			SetupInjectLine();
			fos<<"  Process order."<<endl;

			GetMold(sMold, sMoldLoc);
			InsertTags();
			LoadBins();
			RunInjectCycle();
			CleanMold();
			ShipToAddress();
		}

	protected:
		virtual void SetupInjectLine()
		{
			if(sPlastic.compare("ABS") && sPlastic.compare("PET") &&
				sPlastic.compare("Polypropylene") && sPlastic.compare("Polyethelene") &&
				sPlastic.compare("Styrene") && sPlastic.compare("Nylon66"))
			{
				fos<<"  <>Unknown plastic || defaulting to ABS."<<endl;
				sPlastic = "ABS";
			}

			pOrder = abstract_factory::Setup_AF_10::createOrder(OrderSize);

			pPackager = factory_method::Packager_FM_5::createPackager(sPackager);

			abstract_factory::IJM_AF *pIJM = pOrder->createIJM();
			abstract_factory::Mold_AF *pMold = pOrder->createMold();
			abstract_factory::ConveyerBelt_AF *pConveyerBelt = pOrder->createConveyerBelt();
			pPackageBin = pOrder->createPackbin();

			observer::Stuffer *pStuffer = observer::Stuffer::create_stuffer(sStuffer);

			sStuffer = pStuffer->sStufferName;
			CavityNum = pIJM->CavityNum;

			fos<<"  Setup injection line for "<<OrderSize/CavityNum<<" run with "<<sPackager.c_str()<<" packager and "<<sStuffer.c_str()<<" stuffing:"<<endl;

			pPackageBin->Attach(pIJM);
			pPackageBin->Attach(pConveyerBelt);
			pPackageBin->Attach(pPackager);
			pPackageBin->Attach(pStuffer);

			sMetal = pMold->sMetal;
			pPlastic = adapter::CleanPlastic_A_2::create_PlasticCleanObj(sPlastic, sMetal);
		}
		virtual void GetMold(string &sMold, string &sMoldLoc)
		{
			oInventory.setSuccessor(&oSisterCompany);
			oSisterCompany.setSuccessor(&oPurchase);
			oPurchase.setSuccessor(&oMill);
			oInventory.GetMold(sMoldLoc, sMold, CavityNum);

			pShape = bridge::Shape_B_9::create_ShapeObj(sMold, sFinish);

			PlasticVolume = pShape->Volume;

			if(!sMoldLoc.compare("mill"))
			{
				pMillTools = bridge::Platform_B_9::create_Platform(CavityNum, sMetal, sFinish);

				pShape->pTools = pMillTools;
				pShape->CreateShapewithTools();
			}
		};

		virtual void InsertTags()
		{
			fos<<"    Insert tags [";
			int TagWidth = 0;
			oTags.TagDecoratorList.push_back(new decorator::Blank(&oTags));

			for(unsigned int i = 0; i<TagVector.size(); ++i)
			{
				string Tag = TagVector[i];
				if(!Tag.compare("ModelNumber"))
				{
					oTags.TagDecoratorList.push_back(new decorator::ModelNumber(&oTags));
					TagWidth += oTags.TagDecoratorList.back()->GetTagWidth();
					oTags.TagDecoratorList.back()->insertTags();
				}
				else if(!Tag.compare("Country"))
				{
					oTags.TagDecoratorList.push_back(new decorator::Country(&oTags));
					TagWidth += oTags.TagDecoratorList.back()->GetTagWidth();
					oTags.TagDecoratorList.back()->insertTags();
				}
				else if(!Tag.compare("Date"))
				{
					oTags.TagDecoratorList.push_back(new decorator::Date(&oTags));
					TagWidth += oTags.TagDecoratorList.back()->GetTagWidth();
					oTags.TagDecoratorList.back()->insertTags();
				}
				else if(!Tag.compare("IncCounter"))
				{
					oTags.TagDecoratorList.push_back(new decorator::IncrementCounter(&oTags));
					TagWidth += oTags.TagDecoratorList.back()->GetTagWidth();
					oTags.TagDecoratorList.back()->insertTags();
				}
				else if(!Tag.compare("PartNumber"))
				{
					oTags.TagDecoratorList.push_back(new decorator::PartNumber(&oTags));
					TagWidth += oTags.TagDecoratorList.back()->GetTagWidth();
					oTags.TagDecoratorList.back()->insertTags();
				}
				else if(!Tag.compare("RecycleCode"))
				{
					oTags.TagDecoratorList.push_back(new decorator::RecycleCode(&oTags));
					TagWidth += oTags.TagDecoratorList.back()->GetTagWidth();
					oTags.TagDecoratorList.back()->insertTags();
				}
			}
			fos<<"] of width "<<TagWidth<<"/20 mm."<<endl;;
		}
		virtual void LoadBins()
		{
			fos<<"    Load plastic, color, and additive bins."<<endl;
			int colorValue = 0;

			if(sColor.empty())
			{
				fos<<"      <>No color specified, defaulting to black."<<endl;
				sColor = "black";
			}

			decorator::Plastic_D_6 *pDecorator = &oAdditives;

			//can change to factory method below
			decorator::ABS *pABS = NULL;
			decorator::PET *pPET = NULL;
			decorator::Polyethelene *pPolyethelene = NULL;
			decorator::Polypropylene *pPolypropylene = NULL;
			decorator::Styrene *pStyrene = NULL;
			decorator::Nilon66 *pNilon66 = NULL;
			if(sPlastic.compare("ABS") == 0)
			{
				pABS = new decorator::ABS(pDecorator, PlasticVolume);
				pDecorator = pABS;
			}
			else if(sPlastic.compare("PET") == 0)
			{
				pPET = new decorator::PET(pDecorator, PlasticVolume);
				pDecorator = pPET;
			}
			else if(sPlastic.compare("Polypropylene") == 0)
			{
				pPolypropylene = new decorator::Polypropylene(pDecorator, PlasticVolume);
				pDecorator = pPolypropylene;
			}
			else if(sPlastic.compare("Styrene") == 0)
			{
				pStyrene = new decorator::Styrene(pDecorator, PlasticVolume);
				pDecorator = pStyrene;
			}
			else if(sPlastic.compare("Nylon66") == 0)
			{
				pNilon66 = new decorator::Nilon66(pDecorator, PlasticVolume);
				pDecorator = pNilon66;
			}
			else if(sPlastic.compare("Polyethelene") == 0)
			{
				pPolyethelene = new decorator::Polyethelene(pDecorator, PlasticVolume);
				pDecorator = pPolyethelene;
			}
			else
			{
				pABS = new decorator::ABS(pDecorator, PlasticVolume);
				pDecorator = pABS;
			}

			decorator::Color *pColorAdditive = new decorator::Color(pDecorator, sColor, PlasticVolume);
			pDecorator = pColorAdditive;

			decorator::UVInhibiter *pUVInhibiter = NULL;
			if (UvInhibiterSize>0)
			{
				pUVInhibiter = new decorator::UVInhibiter(pDecorator, UvInhibiterSize);
				pDecorator = pUVInhibiter;
			}
			decorator::AntiBacterial *pAntiBacterial = NULL;
			if(AntiBacterialSize > 0)
			{
				pAntiBacterial = new decorator::AntiBacterial(pDecorator, AntiBacterialSize);
				pDecorator = pAntiBacterial;
			}
			decorator::MicroFiber *pMicrofiber = NULL;
			if(MicroFibersSize > 0)
			{
				pMicrofiber = new decorator::MicroFiber(pDecorator, MicroFibersSize);
				pDecorator = pMicrofiber;
			}

			pDecorator->PrintRecipe();
			fos<<"Total = "<<pDecorator->GetVolume() * CavityNum<<"."<<endl;

			if(pMicrofiber)
				delete pMicrofiber;
			if(pAntiBacterial)
				delete pAntiBacterial;
			if(pUVInhibiter)
				delete pUVInhibiter;
			if(pColorAdditive)
				delete pColorAdditive;
			if(pABS)
				delete pABS;
			if(pNilon66)
				delete pNilon66;
			if(pStyrene)
				delete pStyrene;
			if(pPET)
				delete pPET;
			if(pPolyethelene)
				delete pPolyethelene;
			if(pPolypropylene)
				delete pPolypropylene;
		}

		virtual void RunInjectCycle()
		{
			string sPlasticName = pPlastic->sPlasticName.c_str();
			fos<<"    Cycle IJM for "<<sPlasticName<<" "<<OrderSize/CavityNum<<" times."<<endl;

			pInjectProcess = strategy::Strategy_1::Create_InjectionObj(sPlasticName);
			pInjectProcess->Inject();

			pPackageBin->notify();
		}

		virtual void CleanMold()
		{
			pPlastic->clean();
		}

		virtual void ShipToAddress()
		{
			fos<<"    Ship to \""<<sAddress.c_str()<<"\""<<endl;
		}
	};
}

void process(map<string, string>& order)
{
	template_method::ProcessOrder_TM_4 *pProcessOrder = new template_method::ProcessOrder_TM_4();

	pProcessOrder->ProcessOrder(order);

	if(pProcessOrder)
		delete pProcessOrder;
}

std::pair<string, string> parse(string line) {
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
		std::cout << line;
		fos<<line;
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

void demo(const string& orderFile)
{
	fos.open("tao.out", ios::out);
	fos << "Hello DP4." << endl<<endl;
	fos << "<<< final solution >>>"<<endl;

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");
	if(!orderFilePtr) return;

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}

	fclose(orderFilePtr);

	fos << "Aloha DP4.\n" << endl;
	fos.close();
}

}

#endif /* DP4_SRC_STUDENTS_TAO_H_ */
