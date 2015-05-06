/*
 * chao.h
 *
*  Created on: April 29, 2015
*      Author: Chaoshuo Cheng
*
*  Project: Intro to Design Patterns Pilot class.
*/
#define DP4_SRC_STUDENTS_CHAO_H_	// Need shared_ptr.
#ifndef DP4_SRC_STUDENTS_CHAO_H_
#define DP4_SRC_STUDENTS_CHAO_H_

#define _CRT_SECURE_NO_WARNINGS

const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << "~" << x; }

#include <iostream>
#include <map>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <list>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

namespace final_chao_file {

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

	// This can be combined with strtegy pattern
    namespace adapter {			// DP 2.
        class CleanAdapter {
        public:
			virtual ~CleanAdapter() { DTOR("CleanAdapter\n") }
            virtual void clean() = 0;
        };

        class ABS : public CleanAdapter {
        private:
            legacy_classes::CleanABS abs;
        public:
            ABS(){}
			virtual ~ABS() { DTOR("ABS") }
            virtual void clean() {
                abs.clean();
            }
        };
        class Poly : public CleanAdapter {
        private:
            legacy_classes::CleanPolys polys;
        public:
            Poly(){}
            virtual ~Poly() { DTOR("Poly") }
            virtual void clean() {
                polys.prepForReuse();
            }
        };
        class PET : public CleanAdapter {
        protected:
            legacy_classes::PETCleanup pet;
        public:
            PET(){}
            virtual ~PET() { DTOR("PET") }
			virtual void clean() = 0;
        };
		class PET_Aluminum : public PET {
		public:
			PET_Aluminum(){}
			virtual ~PET_Aluminum(){ DTOR("PET_Aluminum") }
			virtual void clean(){ pet.purify(); }
		};
		class PET_Steel : public PET {
		public:
			PET_Steel(){}
			virtual ~PET_Steel(){ DTOR("PET_Steel") }
			virtual void clean(){ pet.carbonize(); }
		};
		class Styrene : public CleanAdapter {
		public:
			Styrene(){}
			virtual ~Styrene(){ DTOR("Styrene") }
			virtual void clean(){ cout << "Clean synthetic mold: ozone wash.\n"; }
		};
		class Nylon66 : public CleanAdapter {
		public:
			Nylon66(){}
			virtual ~Nylon66(){ DTOR("Nylon66") }
			virtual void clean(){ cout << "Clean synthetic mold: ozone wash.\n"; }
		};
        // Seam point - add another interface.

    }

    namespace strategy {		// DP 1.
        class InjectionStrategy;
        class InjectionProcess {
        private:
            shared_ptr<InjectionStrategy> _injectStrategy;
        public:
            InjectionProcess(shared_ptr<InjectionStrategy> injectStrategy) : _injectStrategy(injectStrategy){}
            ~InjectionProcess() { DTOR("InjectionProcess\n") }
            void runInjection();
        };

        class InjectionStrategy {
        public:
			virtual ~InjectionStrategy(){ DTOR("InjectionStrategy") }
            virtual void close()      = 0;
            virtual void heat()       = 0;
            virtual void inject()     = 0;
            virtual void cool()       = 0;
            virtual void separate()   = 0;
            virtual void eject()      = 0;
        };
        class ABSType : public InjectionStrategy {
        public:
			virtual ~ABSType() { DTOR("ABSType") }
            virtual void close()    { cout << "      Close - "; }
            virtual void heat()     { cout << "heat to 440 - "; }
            virtual void inject()   { cout << "inject at 125 PSI - "; }
            virtual void cool()     { cout << "cool to 360 - "; }
            virtual void separate() { cout << "separate - "; }
            virtual void eject()    { cout << "progressive eject.\n"; }
        };
		class PolyType : public InjectionStrategy {
        public:
			virtual ~PolyType() { DTOR("PolyType") }
            virtual void close()    { cout << "      Close - "; }
            virtual void heat()	    { cout << "heat to 350 - "; }
            virtual void inject()   { cout << "inject at 90 PSI - "; }
            virtual void cool()	    { cout << "cool to 290 - "; }
            virtual void separate() { cout << "separate - "; }
            virtual void eject() { cout << "smooth eject.\n"; }
        };
		class PETType : public InjectionStrategy {
        public:
			virtual ~PETType() { DTOR("PETType") }
            virtual void close()    { cout << "      Close - "; }
            virtual void heat()     { cout << "heat to 404 - "; }
            virtual void inject()   { cout << "inject at 110 PSI - "; }
            virtual void cool()     { cout << "cool to 340 - "; }
            virtual void separate() { cout << "separate - "; }
            virtual void eject()    { cout << "smooth eject.\n"; }
        };
		class StyreneType : public InjectionStrategy {
		public:
			virtual ~StyreneType() { DTOR("StyreneType") }
			virtual void close()    { cout << "      Close - "; }
			virtual void heat()     { cout << "heat to 480 - "; }
			virtual void inject()   { cout << "inject at 150 PSI - "; }
			virtual void cool()     { cout << "cool to 390 - "; }
			virtual void separate() { cout << "separate - "; }
			virtual void eject()    { cout << "shock eject.\n"; }
		};
		class Nylon66Type : public InjectionStrategy {
		public:
			virtual ~Nylon66Type() { DTOR("Nylon66Type") }
			virtual void close()    { cout << "      Close - "; }
			virtual void heat()     { cout << "heat to 480 - "; }
			virtual void inject()   { cout << "inject at 150 PSI - "; }
			virtual void cool()     { cout << "cool to 390 - "; }
			virtual void separate() { cout << "separate - "; }
			virtual void eject()    { cout << "shock eject.\n"; }
		};
        void InjectionProcess::runInjection() {
            _injectStrategy->close();
            _injectStrategy->heat();
            _injectStrategy->inject();
            _injectStrategy->cool();
            _injectStrategy->separate();
            _injectStrategy->eject();
        }
        // Seam point - add another algorithm.
    }

	namespace abstract_factory {// DP 10.
		class MachinesFamily {
		public:
			virtual ~MachinesFamily() { DTOR("MachinesFamily\n") }
			virtual string getName() = 0;
			virtual int getCavityNum() = 0;
		};
		class IJM110 : public MachinesFamily {
		private:
			int numOfCavities;
		public:
			IJM110(int cavityNum) : numOfCavities(cavityNum) { cout << "    IJM_110"; }
			virtual ~IJM110() { DTOR("IJM110") }
			string getName() { return "IJM110"; }
			virtual int getCavityNum() { return numOfCavities; }
		};
		class IJM120 : public MachinesFamily {
		private:
			int numOfCavities;
		public:
			IJM120(int cavityNum) : numOfCavities(cavityNum) { cout << "    IJM_120"; }
			virtual ~IJM120() { DTOR("IJM120") }
			string getName() { return "IJM120"; }
			virtual int getCavityNum() { return numOfCavities; }
		};
		class IJM210 : public MachinesFamily {
		private:
			int numOfCavities;
		public:
			IJM210(int cavityNum) : numOfCavities(cavityNum) { cout << "    IJM_210"; }
			virtual ~IJM210() { DTOR("IJM210") }
			string getName() { return "IJM210"; }
			virtual int getCavityNum() { return numOfCavities; }
		};
		class IJM140 : public MachinesFamily {
		private:
			int numOfCavities;
		public:
			IJM140(int cavityNum) : numOfCavities(cavityNum) { cout << "    IJM140"; }
			virtual ~IJM140() { DTOR("IJM140") }
			string getName() { return "IJM140"; }
			virtual int getCavityNum() { return numOfCavities; }
		};
		class IJM220 : public MachinesFamily {
		private:
			int numOfCavities;
		public:
			IJM220(int cavityNum) : numOfCavities(cavityNum) { cout << "    IJM220"; }
			virtual ~IJM220() { DTOR("IJM220") }
			string getName() { return "IJM220"; }
			virtual int getCavityNum() { return numOfCavities; }
		};
		class IJM240 : public MachinesFamily {
		private:
			int numOfCavities;
		public:
			IJM240(int cavityNum) : numOfCavities(cavityNum) { cout << "    IJM240"; }
			virtual ~IJM240() { DTOR("IJM240") }
			string getName() { return "IJM240"; }
			virtual int getCavityNum() { return numOfCavities; }
		};

		class MoldMetalFamily {
		public:
			virtual ~MoldMetalFamily() { DTOR("MoldMetalFamily") }
			virtual string getName() = 0;
		};
		class Aluminum : public MoldMetalFamily {
		private:
			int numOfCavities;
		public:
			Aluminum() { cout << "Aluminum"; }
			virtual ~Aluminum() { DTOR("Aluminum") }
			virtual string getName() { return "Aluminum"; }
		};
		class Steel : public MoldMetalFamily {
		public:
			Steel() { cout << "Steel"; }
			virtual ~Steel() { DTOR("Steel") }
			string getName() { return "Steel"; }
		};

		class ConveyerBeltFamily {
		public:
			virtual ~ConveyerBeltFamily() { DTOR("ConveyerBeltFamily") }
			virtual string getName() = 0;
		};
		class LinearBelt : public ConveyerBeltFamily {
		public:
			LinearBelt() { cout << "Linear conveyer belt"; }
			virtual ~LinearBelt() { DTOR("LinearBelt") }
			virtual string getName() { return "LinearBelt"; }
		};
		class YSplitBelt : public ConveyerBeltFamily {
		public:
			YSplitBelt() { cout << "Y-Split conveyer belt"; }
			virtual ~YSplitBelt() { DTOR("YSplitBelt") }
			virtual string getName() { return "YSplitBelt"; }
		};
		class VLevelBelt : public ConveyerBeltFamily {
		public:
			VLevelBelt() { cout << "V-Level conveyer belt"; }
			virtual ~VLevelBelt() { DTOR("VLevelBelt") }
			virtual string getName() { return "VLevelBelt"; }
		};

		class PackageBinFamily {
		public:
			virtual ~PackageBinFamily() { DTOR("PackageBinFamily") }
			virtual string getName() = 0;
		};
		class CardboardBox : public PackageBinFamily {
		public:
			CardboardBox() { cout << "CardboardBox"; }
			virtual ~CardboardBox() { DTOR("CarboardBox") }
			virtual string getName() { return "CardboardBox"; }
		};
		class PallotBox : public PackageBinFamily {
		public:
			PallotBox() { cout << "PallotBox"; }
			virtual ~PallotBox() { DTOR("PallotBox") }
			virtual string getName() { return "PallotBox"; }
		};
		class ZipLock : public PackageBinFamily {
		public:
			ZipLock() { cout << "ZipLock"; }
			virtual ~ZipLock() { DTOR("ZipLock") }
			virtual string getName() { return "ZipLock"; }
		};
		class Crate : public PackageBinFamily {
		public:
			Crate() { cout << "Crate"; }
			virtual ~Crate() { DTOR("Crate") }
			virtual string getName() { return "Crate"; }
		};

		class StufferFamily {
		public:
			virtual ~StufferFamily() { DTOR("StufferFamily") }
			virtual string getName() = 0;
		};
		class Air : public StufferFamily {
		public:
			Air() {}
			virtual ~Air() { DTOR("Air") }
			virtual string getName() { return "Air"; }
		};
		class Popcorn : public StufferFamily {
		public:
			Popcorn() {}
			virtual ~Popcorn() { DTOR("Popcorn") }
			virtual string getName() { return "styrene popcorn"; }
		};
		class BubbleWrap : public StufferFamily {
		public:
			BubbleWrap() {}
			virtual ~BubbleWrap() { DTOR("BubbleWrap") }
			virtual string getName() { return "bubble wrap"; }
		};
		class Foam : public StufferFamily {
		public:
			Foam() {}
			virtual ~Foam() { DTOR("Foam") }
			virtual string getName() { return "expanding foam"; }
		};

		// Seam point - add another family.

		class OrderFactory {
		private:
			shared_ptr<MachinesFamily>     machine;
			shared_ptr<MoldMetalFamily>    moldMetal;
			shared_ptr<ConveyerBeltFamily> conveyerBelt;
			shared_ptr<PackageBinFamily>   packageBin;
			shared_ptr<StufferFamily>      stuffer;
			shared_ptr<OrderFactory>	   order;
		public:
			OrderFactory(){}
			virtual ~OrderFactory() { DTOR("OrderFactory") }
			void chooseMachineSet(string amount);
			void ProcessOrder();
			shared_ptr<MachinesFamily>				getMachine()		{ return machine; }
			shared_ptr<MoldMetalFamily>			    getMoldMetal()		{ return moldMetal; }
			shared_ptr<ConveyerBeltFamily>			getConveyerBelt()	{ return conveyerBelt; }
			shared_ptr<PackageBinFamily>			getPackageBin()		{ return packageBin; }
			shared_ptr<StufferFamily>		    	getStuffer()		{ return stuffer; }
			virtual shared_ptr<MachinesFamily>		chooseMachine()		{ return nullptr; };
			virtual shared_ptr<MoldMetalFamily>		chooseMoldMetal()	{ return nullptr; }
			virtual shared_ptr<ConveyerBeltFamily>  chooseConveyerBelt(){ return nullptr; }
			virtual shared_ptr<PackageBinFamily>	choosePackageBin()	{ return nullptr; }
			virtual shared_ptr<StufferFamily>    	chooseStuffer()	    { return nullptr; }
			// Seam point - add another type1 member.
			// Seam point - add another type2 member.
			// Seam point - add another type3 member.
			// ...
		};
		class DefaultOrder : public OrderFactory {
		public:
			DefaultOrder(){}
			virtual ~DefaultOrder() { DTOR("DefaultOrder") }
			virtual shared_ptr<MachinesFamily> chooseMachine(){
				return make_shared<IJM110>(1);
			}
			virtual shared_ptr<MoldMetalFamily> chooseMoldMetal(){
				return make_shared<Aluminum>();
			}
			virtual shared_ptr<ConveyerBeltFamily> chooseConveyerBelt(){
				return make_shared<LinearBelt>();
			}
			virtual shared_ptr<PackageBinFamily> choosePackageBin(){
				return make_shared<CardboardBox>();
			}
		};
		class SmallSizeOrder : public OrderFactory {
		public:
			SmallSizeOrder(){}
			virtual ~SmallSizeOrder() { DTOR("SmallSizeOrder") }
			virtual shared_ptr<MachinesFamily> chooseMachine(){
				return make_shared<IJM110>(1);
			}
			virtual shared_ptr<MoldMetalFamily> chooseMoldMetal(){
				return make_shared<Aluminum>();
			}
			virtual shared_ptr<ConveyerBeltFamily> chooseConveyerBelt(){
				return make_shared<LinearBelt>();
			}
			virtual shared_ptr<PackageBinFamily> choosePackageBin(){
				return make_shared<CardboardBox>();
			}
		};
		class MidSizeOrder : public OrderFactory {
		public:
			MidSizeOrder(){}
			virtual ~MidSizeOrder() { DTOR("MidSizeOrder") }
			virtual shared_ptr<MachinesFamily> chooseMachine(){
				return  make_shared<IJM120>(2);
			}
			virtual shared_ptr<MoldMetalFamily> chooseMoldMetal(){
				return make_shared<Aluminum>();
			}
			virtual shared_ptr<ConveyerBeltFamily> chooseConveyerBelt(){
				return make_shared<YSplitBelt>();
			}
			virtual shared_ptr<PackageBinFamily> choosePackageBin(){
				return make_shared<CardboardBox>();
			}
		};
		class RelativeLargeSizeOrder : public OrderFactory {
		public:
			RelativeLargeSizeOrder(){}
			virtual ~RelativeLargeSizeOrder() { DTOR("RelativeLargeSizeOrder") }
			virtual shared_ptr<MachinesFamily> chooseMachine(){
				return  make_shared<IJM210>(1);
			}
			virtual shared_ptr<MoldMetalFamily> chooseMoldMetal(){
				return make_shared<Steel>();
			}
			virtual shared_ptr<ConveyerBeltFamily> chooseConveyerBelt(){
				return make_shared<LinearBelt>();
			}
			virtual shared_ptr<PackageBinFamily> choosePackageBin(){
				return make_shared<PallotBox>();
			}
		};
		class FastOrder : public OrderFactory {
		public:
			FastOrder(){}
			virtual ~FastOrder() { DTOR("FastOrder") }
			virtual shared_ptr<MachinesFamily> chooseMachine(){
				return  make_shared<IJM140>(4);
			}
			virtual shared_ptr<MoldMetalFamily> chooseMoldMetal(){
				return make_shared<Aluminum>();
			}
			virtual shared_ptr<ConveyerBeltFamily> chooseConveyerBelt(){
				return make_shared<VLevelBelt>();
			}
			virtual shared_ptr<PackageBinFamily> choosePackageBin(){
				return make_shared<PallotBox>();
			}
			virtual shared_ptr<StufferFamily> chooseStuffer(){
				return make_shared<Popcorn>();
			}
		};
		class LargeSizeOrder : public OrderFactory {
		public:
			LargeSizeOrder(){}
			virtual ~LargeSizeOrder() { DTOR("LargeSizeOrder") }
			virtual shared_ptr<MachinesFamily> chooseMachine(){
				return  make_shared<IJM220>(2);
			}
			virtual shared_ptr<MoldMetalFamily> chooseMoldMetal(){
				return make_shared<Steel>();
			}
			virtual shared_ptr<ConveyerBeltFamily> chooseConveyerBelt(){
				return make_shared<YSplitBelt>();
			}
			virtual shared_ptr<PackageBinFamily> choosePackageBin(){
				return make_shared<Crate>();
			}
			virtual shared_ptr<StufferFamily> chooseStuffer(){
				return make_shared<Foam>();
			}
		};
		class HugeOrder : public OrderFactory {
		public:
			HugeOrder(){}
			virtual ~HugeOrder() { DTOR("HugeOrder") }
			virtual shared_ptr<MachinesFamily> chooseMachine(){
				return  make_shared<IJM240>(4);
			}
			virtual shared_ptr<MoldMetalFamily> chooseMoldMetal(){
				return make_shared<Steel>();
			}
			virtual shared_ptr<ConveyerBeltFamily> chooseConveyerBelt(){
				return make_shared<VLevelBelt>();
			}
			virtual shared_ptr<PackageBinFamily> choosePackageBin(){
				return make_shared<ZipLock>();
			}
			virtual shared_ptr<StufferFamily> chooseStuffer(){
				return make_shared<BubbleWrap>();
			}
		};

		void OrderFactory::chooseMachineSet(string amount) {
			if (atoi(amount.c_str()) <= atoi("10000"))
				order = make_shared<SmallSizeOrder>();
			else if (atoi(amount.c_str()) <= atoi("20000"))
				order = make_shared<MidSizeOrder>();
			else if (atoi(amount.c_str()) <= atoi("40000"))
				order = make_shared<FastOrder>();
			else if (atoi(amount.c_str()) <= atoi("50000"))
				order = make_shared<RelativeLargeSizeOrder>();
			else if (atoi(amount.c_str()) < atoi("200000"))
				order = make_shared<LargeSizeOrder>();
			else
				order = make_shared<HugeOrder>();

			machine = order->chooseMachine();      cout << " - ";
			moldMetal = order->chooseMoldMetal();    cout << "(" << machine->getCavityNum() << ")" << " - ";
			conveyerBelt = order->chooseConveyerBelt(); cout << " - ";
			packageBin = order->choosePackageBin();   cout << endl;
		}
	}

    namespace observer {		// DP 7.
        class PackageBinObserver;
        class PackageBinSubject {
        private:
			string _name;
            list<PackageBinObserver *> observers;
			void Notify();
        public:
			PackageBinSubject(string name) : _name(name) {}
			virtual ~PackageBinSubject() { DTOR("PackageBinSubject\n") }
            void Attach(PackageBinObserver *pbo) {
                observers.push_back(pbo);
            }
            void Detach(PackageBinObserver *pbo) {
                observers.remove(pbo);
            }
			void isFull() {
				cout << "      " << this->getName() << " package bin full...\n";
				Notify();
			}
			string getName() { return _name; }
        };

        class PackageBinObserver {
        protected:
            PackageBinSubject* packageBin;
        public:
            PackageBinObserver(PackageBinSubject *pbs) : packageBin(pbs) {}
            virtual ~PackageBinObserver() { DTOR("PackageBinObserver") }
            virtual void Update() = 0;
        };
        class Machines : public PackageBinObserver {
        public:
            Machines(PackageBinSubject* s) : PackageBinObserver(s) { packageBin->Attach(this); }
            virtual ~Machines() {
				DTOR("Machines")
				packageBin->Detach(this);
			}
            virtual void Update() {
				cout << "\tIJM pausing while " << packageBin->getName() << " package bin is swapped.\n";
			}
        };
        class ConveyerBelt : public PackageBinObserver {
        public:
            ConveyerBelt(PackageBinSubject* s) : PackageBinObserver(s) {
				packageBin->Attach(this);
			}
            virtual ~ConveyerBelt() {
				DTOR("ConveyerBelt")
				packageBin->Detach(this);
			}
            virtual void Update() {
				cout << "\tConveyer belt pausing while " << packageBin->getName() << " package bin is swapped.\n";
			}
        };
        class Packager : public PackageBinObserver {
        public:
            Packager(PackageBinSubject* s) : PackageBinObserver(s) {
				packageBin->Attach(this);
			}
            virtual ~Packager() {
				DTOR("Packager")
				packageBin->Detach(this);
			}
            virtual void Update() {
				cout << "\tPackager pausing while " << packageBin->getName() << " package bin is swapped.\n";
			}
        };
		class Stuffer : public PackageBinObserver {
		private:
			shared_ptr<abstract_factory::StufferFamily> stufferUsed;
		public:
			Stuffer(PackageBinSubject* s, shared_ptr<abstract_factory::StufferFamily> stuffer) : PackageBinObserver(s), stufferUsed(stuffer){
				packageBin->Attach(this);
			}
			virtual ~Stuffer() {
				DTOR("Stuffer")
					packageBin->Detach(this);
			}
			virtual void Update() {
				cout << "        Stuffer filling " << packageBin->getName() << " package bin with " << stufferUsed->getName() << " stuffing.\n";
			}
		};
        // Seam point - add another listener.

        void PackageBinSubject::Notify() {
            for (list<PackageBinObserver *>::iterator iter = observers.begin(); iter != observers.end(); iter++)
            {
                (*iter)->Update();
            }
        }
    }


    namespace bridge {			// DP 9.
        class Finishes {
        public:
			Finishes() {}
			virtual ~Finishes() { DTOR("Finishes\n") }
            virtual string getFinishStyle() = 0;
        };
        class SmoothFinish : public Finishes {
        public:
			SmoothFinish() {}
			virtual ~SmoothFinish() { DTOR("SmoothFinish") }
			virtual string getFinishStyle() { return "smooth"; }
        };
        class RippleFinish : public Finishes {
        public:
			RippleFinish() {}
			virtual ~RippleFinish() { DTOR("RippleFinish") }
			virtual string getFinishStyle() { return "rippled"; }
        };
		class DimpledFinish : public Finishes {
		public:
			DimpledFinish() {}
			virtual ~DimpledFinish() { DTOR("DimpledFinish") }
			virtual string getFinishStyle() { return "dimpled"; }
		};
		class SandedFinish : public Finishes {
		public:
			SandedFinish() {}
			virtual ~SandedFinish() { DTOR("SandedFinish") }
			virtual string getFinishStyle() { return "sanded"; }
		};
		class SatinFinish : public Finishes {
		public:
			SatinFinish() {}
			virtual ~SatinFinish() { DTOR("SatinFinish") }
			virtual string getFinishStyle() { return "satin"; }
		};
        // Seam Point - add another implementation.

        class MillTools {
        public:
			MillTools() {}
			virtual ~MillTools() { DTOR("MillTool") }
			virtual void mill(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) = 0;
        };
		class DefaultMillTool : public MillTools {
		public:
			DefaultMillTool() {}
			virtual ~DefaultMillTool() { DTOR("DefaultMillTool") }
			virtual void mill(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {}
		};
        class CarbonTools : public MillTools {
        public:
			CarbonTools() {}
			virtual ~CarbonTools() { DTOR("CarbonTools") }
			virtual void mill(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {
				cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill aluminum block into " << numToMill << " " << shapeToMill << " shapes with " << finishStyle->getFinishStyle() << " finish.\n";
			}
        };
        class CarbideTools : public MillTools {
        public:
			CarbideTools() {}
			virtual ~CarbideTools() { DTOR("CarbideTools") }
			virtual void mill(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {
				cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill steel block into " << numToMill << " " << shapeToMill << " shapes with " << finishStyle->getFinishStyle() << " finish.\n";
			}
        };
		class DiamondTippedTools : public MillTools {
		public:
			DiamondTippedTools() {}
			virtual ~DiamondTippedTools() { DTOR("DiamondTippedTools") }
			virtual void mill(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {
				cout << "      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind) to mill steel block into " << numToMill << " " << shapeToMill << " shapes with " << finishStyle->getFinishStyle() << " finish.\n";
			}
		};
        // Seam Point - add another implementation.

        class CavityShape {
        protected:
            shared_ptr<MillTools> millTool;
        public:
            CavityShape(shared_ptr<MillTools> tool) : millTool(tool) {}
			virtual ~CavityShape() { DTOR("Cavity") }
			virtual void makeCavityShape(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) = 0;
			virtual int plasticRequired() = 0;
			virtual string getName() = 0;
        };
        class DuckShape : public CavityShape {
        public:
			DuckShape(shared_ptr<MillTools> tool) : CavityShape(tool) {}
			virtual ~DuckShape() { DTOR("DuckShape") }
			virtual void makeCavityShape(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {
				millTool->mill(numToMill, shapeToMill, finishStyle);
			}
			virtual int plasticRequired() { return 35; }
			virtual string getName() { return "duck"; }
        };
        class CarShape : public CavityShape {
        public:
			CarShape(shared_ptr<MillTools> tool) : CavityShape(tool) {}
			virtual ~CarShape() { DTOR("CarShape") }
			virtual void makeCavityShape(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {
				millTool->mill(numToMill, shapeToMill, finishStyle);
			}
			virtual int plasticRequired() { return 40; }
			virtual string getName() { return "car"; }
        };
        class HeroShape : public CavityShape {
        public:
			HeroShape(shared_ptr<MillTools> tool) : CavityShape(tool) {}
			virtual ~HeroShape() { DTOR("HeroShape")}
			virtual void makeCavityShape(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {
				millTool->mill(numToMill, shapeToMill, finishStyle);
			}
			virtual int plasticRequired() { return 50; }
			virtual string getName() { return "hero"; }
        };
		class DinoShape : public CavityShape {
		public:
			DinoShape(shared_ptr<MillTools> tool) : CavityShape(tool) {}
			virtual ~DinoShape() { DTOR("DinoShape") }
			virtual void makeCavityShape(int numToMill, string shapeToMill, shared_ptr<Finishes> finishStyle) {
				millTool->mill(numToMill, shapeToMill, finishStyle);
			}
			virtual int plasticRequired() { return 30; }
			virtual string getName() { return "dino"; }
		};
        // Seam Point - add another abstraction.

    }

    namespace chain_of_resp {	// DP 8.
        class MoldLoc{
        private:
            MoldLoc* successor;
        public:
            MoldLoc() {}
			virtual ~MoldLoc() { DTOR("MoldLoc\n") }
            virtual void setChainOfResp(MoldLoc* nextLoc) {
                successor = nextLoc;
            }
            virtual void pullMold(string mold, string requestedLoc, int cavityNum) {
                if (successor)
                    successor->pullMold(mold, requestedLoc, cavityNum);
            }
        };
		class DefaultMoldLoc : public MoldLoc {
		public:
			DefaultMoldLoc() {}
			virtual ~DefaultMoldLoc() { DTOR("DefaultMoldLoc") }
			virtual void pullMold(string mold, string requestedLoc, int cavityNum){
				if (requestedLoc == "")
					cout << "  <>Can't find place |" << requestedLoc << "| to get |" << mold << "| mold from, defaulting to duck from inventory.\n";
				else
					MoldLoc::pullMold(mold, requestedLoc, cavityNum);
			}
		};
        class Inventory : public MoldLoc {
        public:
            Inventory() {}
			virtual ~Inventory() { DTOR("Inventory") }
			virtual void pullMold(string mold, string requestedLoc, int cavityNum){
                if (requestedLoc == "inventory")
                    cout << "Pull " << mold.c_str() << " mold from inventory.\n";
                else
                    MoldLoc::pullMold(mold, requestedLoc, cavityNum);
            }
        };
        class Mill : public MoldLoc {
        public:
            Mill() {}
			virtual ~Mill() { DTOR("Mill") }
			virtual void pullMold(string mold, string requestedLoc, int cavityNum){
                if (requestedLoc == "mill")
                    cout << "  Create " << mold.c_str() << " mold from mill with " << cavityNum << " cavities:\n";
                else
					MoldLoc::pullMold(mold, requestedLoc, cavityNum);
            }
        };
		class sisterCompany : public MoldLoc {
		public:
			sisterCompany() {}
			virtual ~sisterCompany() { DTOR("sisterCompany") }
			virtual void pullMold(string mold, string requestedLoc, int cavityNum){
				if (requestedLoc == "sisterCompany")
					cout << "  Borrow " << mold.c_str() << " mold from sister company.\n";
				else
					MoldLoc::pullMold(mold, requestedLoc, cavityNum);
			}
		};
		class Purchase : public MoldLoc {
		public:
			Purchase() {}
			virtual ~Purchase() { DTOR("Purchase") }
			virtual void pullMold(string mold, string requestedLoc, int cavityNum){
				if (requestedLoc == "purchase")
					cout << "  Acquire " << mold.c_str() << " mold via purchase.\n";
				else
					MoldLoc::pullMold(mold, requestedLoc, cavityNum);
			}
		};
        // Seam points - add another responder.

    }

    namespace decorator {		// DP 6.
        class Additives {
        public:
			virtual ~Additives() { DTOR("Additives\n") }
			virtual void addAdditive() = 0;
        };
		class DefaultAdditive : public Additives {
		public:
			DefaultAdditive(){}
			virtual ~DefaultAdditive() { DTOR("DefaultAdditive") }
			virtual void addAdditive() {}
		};
        class AdditivesDecorator : public Additives{
        protected:
			int        _amount;
            shared_ptr<Additives> additiveDecorator;
        public:
            AdditivesDecorator(shared_ptr<Additives> additive, int amount) : additiveDecorator(additive), _amount(amount) {}
			virtual ~AdditivesDecorator() { DTOR("AdditivesDecorator") }
        };
        class UVInhibiter : public AdditivesDecorator {
        public:
            UVInhibiter(shared_ptr<Additives> product, int amount) : AdditivesDecorator(product, amount) {}
			virtual ~UVInhibiter() { DTOR("UVInhibiter") }
            virtual void addAdditive(){
                additiveDecorator->addAdditive();
				cout << "UVInhibiter(" << _amount << ") ";
            }
        };
        class Antibacterial : public AdditivesDecorator {
        public:
			Antibacterial(shared_ptr<Additives> product, int amount) : AdditivesDecorator(product, amount) {}
			virtual ~Antibacterial() { DTOR("Antibacterial") }
            virtual void addAdditive(){
                additiveDecorator->addAdditive();
				cout << "AntiBacterial(" << _amount << ") ";
            }
        };
		class MicroFibers : public AdditivesDecorator {
		public:
			MicroFibers(shared_ptr<Additives> product, int amount) : AdditivesDecorator(product, amount) {}
			virtual ~MicroFibers() { DTOR("MicroFibers") }
			virtual void addAdditive(){
				additiveDecorator->addAdditive();
				cout << "MicroFibers(" << _amount << ") ";
			}
		};
        // Seam point - add another option.


        class Tags {
        public:
            Tags() {}
			virtual ~Tags() { DTOR("Tags\n") }
			virtual void addTag() = 0;
			virtual int getTagWidth() = 0;
        };
		class BlankTag : public Tags {
		public:
			BlankTag() {}
			virtual ~BlankTag() { DTOR("BlankTag") }
			virtual int getTagWidth() { return 0; }
			void addTag(){}
		};
		class TagsDecorator : public Tags {
        protected:
			string _name;
            shared_ptr<Tags> tagDecorator;
        public:
			TagsDecorator(shared_ptr<Tags> tag, string name) : tagDecorator(tag), _name(name) {}
			virtual ~TagsDecorator(){ DTOR("TagsDecorator") }
        };
        class ModelTag : public TagsDecorator {
        public:
			ModelTag(shared_ptr<Tags> tag, string name) : TagsDecorator(tag, name) {}
			virtual ~ModelTag() { DTOR("ModelTag") }
			virtual int getTagWidth() { return 2; }
            void addTag(){
                tagDecorator->addTag();
                cout << _name.c_str() << " ";
            }
        };
        class CountryTag : public TagsDecorator {
        public:
			CountryTag(shared_ptr<Tags> tag, string name) : TagsDecorator(tag, name) {}
			virtual ~CountryTag() { DTOR("CountryTag") }
			virtual int getTagWidth() { return 2; }
            void addTag(){
                tagDecorator->addTag();
				cout << _name.c_str() << " ";
            }
        };
        class DateTag : public TagsDecorator {
        public:
			DateTag(shared_ptr<Tags> tag, string name) : TagsDecorator(tag, name) {}
			virtual ~DateTag() { DTOR("DateTag") }
			virtual int getTagWidth() { return 2; }
            void addTag(){
                tagDecorator->addTag();
				cout << _name.c_str() << " ";
            }
        };
		class IncCounter : public TagsDecorator {
		public:
			IncCounter(shared_ptr<Tags> tag, string name) : TagsDecorator(tag, name) {}
			virtual ~IncCounter() { DTOR("IncCounter") }
			virtual int getTagWidth() { return 4; }
			void addTag(){
				tagDecorator->addTag();
				cout << _name.c_str() << " ";
			}
		};
		class PartNumber : public TagsDecorator {
		public:
			PartNumber(shared_ptr<Tags> tag, string name) : TagsDecorator(tag, name) {}
			virtual ~PartNumber() { DTOR("PartNumber") }
			virtual int getTagWidth() { return 2; }
			void addTag(){
				tagDecorator->addTag();
				cout << _name.c_str() << " ";
			}
		};
		class RecycleCode : public TagsDecorator {
		public:
			RecycleCode(shared_ptr<Tags> tag, string name) : TagsDecorator(tag, name) {}
			virtual ~RecycleCode() { DTOR("RecycleCode") }
			virtual int getTagWidth() { return 6; }
			void addTag(){
				tagDecorator->addTag();
				cout << _name.c_str() << " ";
			}
		};
		// Seam point - add another option.

		class Color {
		protected:
			int _addedColorAmount;
		public:
			Color() {}
			virtual ~Color() { DTOR("Color\n") }
			virtual void addColor(int plasticAmount) { _addedColorAmount = plasticAmount / 10; }
			virtual int getAddedColorAmount() = 0;
		};
		class DefaultColor : public Color {
		public:
			DefaultColor() {}
			virtual ~DefaultColor() { DTOR("DefaultColor") }
			virtual void addColor(int plasticAmount) {}
			virtual int getAddedColorAmount() { return 0; }
		};
		class ColorDecorator : public Color {
		private:
			shared_ptr<Color> colorDecorator;
		public:
			ColorDecorator(shared_ptr<Color> color) : colorDecorator(color) {}
			virtual ~ColorDecorator() { DTOR("ColorDecorator") }
		};
		class Black : public ColorDecorator {
		public:
			Black(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Black() { DTOR("Black") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "black(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Brown : public ColorDecorator {
		public:
			Brown(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Brown() { DTOR("Brown") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "brown(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Red : public ColorDecorator {
		public:
			Red(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Red() { DTOR("Red") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "red(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Orange : public ColorDecorator {
		public:
			Orange(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Orange() { DTOR("Orange") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "orange(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Yellow : public ColorDecorator {
		public:
			Yellow(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Yellow() { DTOR("Yellow") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "yellow(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Green : public ColorDecorator {
		public:
			Green(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Green() { DTOR("Green") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "green(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Blue : public ColorDecorator {
		public:
			Blue(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Blue() { DTOR("Blue") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "blue(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Violet : public ColorDecorator {
		public:
			Violet(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Violet() { DTOR("Violet") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "violet(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class Gray : public ColorDecorator {
		public:
			Gray(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~Gray() { DTOR("Gray") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "gray(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
		class White : public ColorDecorator {
		public:
			White(shared_ptr<Color> color) : ColorDecorator(color){}
			virtual ~White() { DTOR("White") }
			virtual void addColor(int plasticAmount) {
				Color::addColor(plasticAmount);
				cout << "white(" << _addedColorAmount << ") ";
			}
			virtual int getAddedColorAmount() { return _addedColorAmount; }
		};
        // Seam point - add another option.

    }

    namespace factory_method {	// DP 5.
        class PackagerFactory {
        public:
			virtual ~PackagerFactory() { DTOR("PackagerFactory\n") }
			static shared_ptr<PackagerFactory> makePackager(string packagerType);
			virtual string getName() = 0;
        };
        class Bulk : public PackagerFactory {
        public:
            Bulk(){}
			virtual ~Bulk() { DTOR("Bulk") }
			virtual string getName() { return "Bulk"; }
        };
        class ShrinkWrap : public PackagerFactory {
        public:
            ShrinkWrap() {}
			virtual ~ShrinkWrap() { DTOR("ShrinkWrap") }
			virtual string getName() { return "ShrinkWrap"; }
        };
        class HardPack : public PackagerFactory {
        public:
            HardPack() {}
			virtual ~HardPack() { DTOR("HardPack") }
			virtual string getName() { return "HardPack"; }
        };
		class ZipLock : public PackagerFactory {
		public:
			ZipLock() {}
			virtual ~ZipLock() { DTOR("ZipLock") }
			virtual string getName() { return "ZipLock"; }
		};
        // Seam point - add another class.

		shared_ptr<PackagerFactory> PackagerFactory::makePackager(string packagerType) {
			if (packagerType == "Bulk")
			{
				return make_shared<Bulk>();
			}
			else if (packagerType == "ShrinkWrap")
			{
				return make_shared<ShrinkWrap>();
			}
			else if (packagerType == "HardPack")
			{
				return make_shared<HardPack>();
			}
			else if (packagerType == "ZipLock")
			{
				return make_shared<ZipLock>();
			}
			else
			{
                cout << "  <>Unknown packager |<unknown packager>| defaulting to Bulk packager.\n";
				return make_shared<Bulk>();
            }
        }

		class PlasticFactory {
		public:
			virtual ~PlasticFactory() { DTOR("PlasticFactory\n") }
			static shared_ptr<PlasticFactory> makePlastic(string plasticType);
			virtual string getPlasticCategory() = 0;
		};
		class ABS : public PlasticFactory {
		public:
			ABS() { cout << "ABS"; }
			virtual ~ABS() { DTOR("ABS") }
			virtual string getPlasticCategory() { return "ABS"; }
		};
		class Polypropylene : public PlasticFactory {
		public:
			Polypropylene() { cout << "Polypropylene"; }
			virtual ~Polypropylene() { DTOR("Polypropylene") }
			virtual string getPlasticCategory() { return "Poly"; }
		};
		class Polyethelene : public PlasticFactory {
		public:
			Polyethelene() { cout << "Polyethelene"; }
			virtual ~Polyethelene() { DTOR("Polyethelene") }
			virtual string getPlasticCategory() { return "Poly"; }
		};
		class PET : public PlasticFactory {
		public:
			PET() { cout << "PET"; }
			virtual ~PET() { DTOR("PET") }
			virtual string getPlasticCategory() { return "PET"; }
		};
		class Styrene : public PlasticFactory {
		public:
			Styrene() { cout << "Styrene"; }
			virtual ~Styrene() { DTOR("Styrene") }
			virtual string getPlasticCategory() { return "Synthetics"; }
		};
		class Nylon66 : public PlasticFactory {
		public:
			Nylon66() { cout << "Nylon66"; }
			virtual ~Nylon66() { DTOR("Nylon66") }
			virtual string getPlasticCategory() { return "Synthetics"; }
		};
		shared_ptr<PlasticFactory> PlasticFactory::makePlastic(string plasticType)
		{
			if (plasticType == "ABS")
			{
				return make_shared<ABS>();
			}
			else if (plasticType == "Polypropylene")
			{
				return make_shared<Polypropylene>();
			}
			else if (plasticType == "Polyethelene")
			{
				return make_shared<Polyethelene>();
			}
			else if (plasticType == "PET")
			{
				return make_shared<PET>();
			}
			else if (plasticType == "Styrene")
			{
				return make_shared<Styrene>();
			}
			else if (plasticType == "Nylon66")
			{
				return make_shared<Nylon66>();
			}
			else {
				cout << "  <>Unknown plastic |<unknown plastic>| defaulting to ABS.\n";
				return make_shared<ABS>();
			}
		}
		// Seam point - add another class.
    }

    namespace template_method {	// DP 4.
        class InjectionRunTemplateMethod {
        public:
            virtual ~InjectionRunTemplateMethod() { cout << "InjectionRunTemplateMethod"; }
            void runInjection() {
                setupInjectionLine();
                getAndInstallMold();
                insertTagsIntoMold();
                loadAdditiveBins();
                runInjectionCycle();
                cleanMold();
            }
        protected:
            virtual void setupInjectionLine() = 0;
            virtual void getAndInstallMold() = 0;
            virtual void insertTagsIntoMold() = 0;
            virtual void loadAdditiveBins() = 0;
            virtual void runInjectionCycle() = 0;
            virtual void cleanMold() = 0;
        };
        class InjectionRunMethod_A : public InjectionRunTemplateMethod {
        public:
            virtual ~InjectionRunMethod_A() { cout << "InjectionRunMethod_A"; }
            virtual void setupInjectionLine() {/*TO BE IMPLEMENTED*/}
            virtual void getAndInstallMold() {/*TO BE IMPLEMENTED*/}
            virtual void insertTagsIntoMold() {/*TO BE IMPLEMENTED*/}
            virtual void loadAdditiveBins() {/*TO BE IMPLEMENTED*/}
            virtual void runInjectionCycle() {/*TO BE IMPLEMENTED*/}
            virtual void cleanMold() {/*TO BE IMPLEMENTED*/}
        };
        class InjectionRunMethod_B : public InjectionRunTemplateMethod {
        public:
            virtual ~InjectionRunMethod_B() { cout << "InjectionRunMethod_B"; }
            virtual void setupInjectionLine() {/*TO BE IMPLEMENTED*/ }
            virtual void getAndInstallMold() {/*TO BE IMPLEMENTED*/ }
            virtual void insertTagsIntoMold() {/*TO BE IMPLEMENTED*/ }
            virtual void loadAdditiveBins() {/*TO BE IMPLEMENTED*/ }
            virtual void runInjectionCycle() {/*TO BE IMPLEMENTED*/ }
            virtual void cleanMold() {/*TO BE IMPLEMENTED*/ }
        };
        // Seam point - add another step.

    }

    void process(map<string, string> order) {
		string size;
		if (order.find("size") == order.end())
		{
			cout << "  <>No size specified, defaulting to 100.\n";
			size = "100";
		}
		else
			size = order.find("size")->second;

		string plastic;
		if (order.find("plastic") == order.end())
		{
			cout << "  <>Unknown plastic |<unknown plastic>| defaulting to ABS.\n";
			plastic = "ABS";
		}
		else
			plastic = order.find("plastic")->second;

		string packager;
		if (order.find("packager") == order.end())
		{
			cout << "  <>Unknown packager |<unknown packager>| defaulting to Bulk packager.\n";
			packager = "Bulk";
		}
		else
			packager = order.find("packager")->second;

		string mold;
		if (order.find("mold") == order.end())
			mold = "";
		else
			mold = order.find("mold")->second;

		string moldLoc;
		if (order.find("moldLoc") == order.end())
			moldLoc = "";
		else
			moldLoc = order.find("moldLoc")->second;

		string finish;
		if (order.find("finish") == order.end())
			finish = "";
		else
			finish = order.find("finish")->second;

		string tags;
		if (order.find("tags") == order.end())
			tags = "";
		else
			tags = order.find("tags")->second;

		string color;
		if (order.find("color") == order.end())
			color = "";
		else
			color = order.find("color")->second;

		string uvInhibiter;
		if (order.find("UVInhibiter") == order.end())
			uvInhibiter = "";
		else
			uvInhibiter = order.find("UVInhibiter")->second;

		string antibacterial;
		if (order.find("AntiBacterial") == order.end())
			antibacterial = "";
		else
			antibacterial = order.find("AntiBacterial")->second;

		string microFibers;
		if (order.find("MicroFibers") == order.end())
			microFibers = "";
		else
			microFibers = order.find("MicroFibers")->second;

		string stuffer;
		if (order.find("stuffer") == order.end())
			stuffer = "";
		else
			stuffer = order.find("stuffer")->second;

		string address;
		if (order.find("address") == order.end())
			address = "";
		else
			address = order.find("address")->second;

		shared_ptr<factory_method::PackagerFactory> requestedPackageBin = factory_method::PackagerFactory::makePackager(packager);
		cout << "\n  Setup injection line for " << size << " run with " << requestedPackageBin->getName() << " packager:\n  ";
        shared_ptr<abstract_factory::OrderFactory> anOrder = make_shared<abstract_factory::OrderFactory>();
        anOrder->chooseMachineSet(size);

		cout << "  Process order.\n  ";
		shared_ptr<chain_of_resp::DefaultMoldLoc> defaultMoldLoc = make_shared<chain_of_resp::DefaultMoldLoc>();
        shared_ptr<chain_of_resp::Inventory>           inventory = make_shared<chain_of_resp::Inventory>();
        shared_ptr<chain_of_resp::Mill>                     mill = make_shared<chain_of_resp::Mill>();
		shared_ptr<chain_of_resp::sisterCompany>   sisterCompany = make_shared<chain_of_resp::sisterCompany>();
		shared_ptr<chain_of_resp::Purchase>             purchase = make_shared<chain_of_resp::Purchase>();
		defaultMoldLoc->setChainOfResp(inventory.get());
		inventory->setChainOfResp(sisterCompany.get());
		sisterCompany->setChainOfResp(purchase.get());
		purchase->setChainOfResp(mill.get());
		defaultMoldLoc->pullMold(mold, moldLoc, anOrder->getMachine()->getCavityNum());

		shared_ptr<bridge::Finishes> finishStyle;
		if (finish == "smooth")
			finishStyle = make_shared<bridge::SmoothFinish>();
		else if (finish == "rippled")
			finishStyle = make_shared<bridge::RippleFinish>();
		else if (finish == "dimpled")
			finishStyle = make_shared<bridge::DimpledFinish>();
		else if (finish == "satin")
			finishStyle = make_shared<bridge::SatinFinish>();
		else
			finishStyle = make_shared<bridge::SmoothFinish>();

		shared_ptr<bridge::MillTools> millTool;
		if (moldLoc == "" || moldLoc == "inventory")
			millTool = make_shared<bridge::DefaultMillTool>();
		else if (finishStyle->getFinishStyle() == "satin")
			millTool = make_shared<bridge::DiamondTippedTools>();
		else if (anOrder->getMoldMetal()->getName() == "Aluminum")
			millTool = make_shared<bridge::CarbonTools>();
		else if (anOrder->getMoldMetal()->getName() == "Steel")
			millTool = make_shared<bridge::CarbideTools>();
		else
			millTool = make_shared<bridge::DefaultMillTool>();

		shared_ptr<bridge::CavityShape> cavityShape;
		if (mold == "duck")
			cavityShape = make_shared<bridge::DuckShape>(millTool);
		else if (mold == "car")
			cavityShape = make_shared<bridge::CarShape>(millTool);
		else if (mold == "hero")
			cavityShape = make_shared<bridge::HeroShape>(millTool);
		else if (mold == "dino")
			cavityShape = make_shared<bridge::DinoShape>(millTool);
		else
			cavityShape = make_shared<bridge::DuckShape>(millTool);

		cavityShape->makeCavityShape(anOrder->getMachine()->getCavityNum(), cavityShape->getName(), finishStyle);

        // Extract tags from order
		cout << "    Insert tags [";
		int totalTagWidth = 0;
		istringstream tags_ss(tags);
		vector<string> tagVec;
		copy(istream_iterator<string>(tags_ss), istream_iterator<string>(), back_inserter(tagVec));

		shared_ptr<decorator::Tags> basicTag = make_shared<decorator::BlankTag>();
		for (vector<string>::iterator iter = tagVec.begin(); iter != tagVec.end(); iter++)
		{
			if (*iter == "ModelNumber")
				basicTag = make_shared<decorator::ModelTag>(basicTag, *iter);
			if (*iter == "Country")
				basicTag = make_shared<decorator::CountryTag>(basicTag, *iter);
			if (*iter == "Date")
				basicTag = make_shared<decorator::DateTag>(basicTag, *iter);
			if (*iter == "IncCounter")
				basicTag = make_shared<decorator::IncCounter>(basicTag, *iter);
			if (*iter == "PartNumber")
				basicTag = make_shared<decorator::PartNumber>(basicTag, *iter);
			if (*iter == "RecycleCode")
				basicTag = make_shared<decorator::RecycleCode>(basicTag, *iter);

			totalTagWidth += basicTag->getTagWidth();
		}
		basicTag->addTag();
		cout << "] of width " << totalTagWidth << "/20 mm.\n";

		cout << "    Load plastic, color, and additive bins.\n";

		int colorAmount = 0;
		shared_ptr<decorator::Color> requestedColor = make_shared<decorator::DefaultColor>();
		if (color == "brown")
		{
			requestedColor = make_shared<decorator::Brown>(requestedColor);
		}
		else if (color == "red")
		{
			requestedColor = make_shared<decorator::Red>(requestedColor);
		}
		else if (color == "orange")
		{
			requestedColor = make_shared<decorator::Orange>(requestedColor);
		}
		else if (color == "yellow")
		{
			requestedColor = make_shared<decorator::Yellow>(requestedColor);
		}
		else if (color == "green")
		{
			requestedColor = make_shared<decorator::Green>(requestedColor);
		}
		else if (color == "blue")
		{
			requestedColor = make_shared<decorator::Blue>(requestedColor);
		}
		else if (color == "violet")
		{
			requestedColor = make_shared<decorator::Violet>(requestedColor);
		}
		else if (color == "gray")
		{
			requestedColor = make_shared<decorator::Gray>(requestedColor);
		}
		else if (color == "white")
		{
			requestedColor = make_shared<decorator::White>(requestedColor);
		}
		else {
			cout << "      <>No color specified, defaulting to black.\n";
			requestedColor = make_shared<decorator::Black>(requestedColor);
		}

		cout << "      Recipe: ";
		shared_ptr<factory_method::PlasticFactory> plasticUsed = factory_method::PlasticFactory::makePlastic(plastic);
		cout << "(" << cavityShape->plasticRequired() << ") ";

		requestedColor->addColor(cavityShape->plasticRequired());
		colorAmount = requestedColor->getAddedColorAmount();

		int uvInhibiterAmount = 0;
		shared_ptr<decorator::Additives> additive = make_shared<decorator::DefaultAdditive>();
		if (uvInhibiter != "")
		{
			uvInhibiterAmount = atoi(uvInhibiter.c_str());
			additive = make_shared<decorator::UVInhibiter>(additive, uvInhibiterAmount);
		}
		int antibacterialAmount = 0;
		if (antibacterial != "")
		{
			antibacterialAmount = atoi(antibacterial.c_str());
			additive = make_shared<decorator::Antibacterial>(additive, antibacterialAmount);
		}
		int microFiberAmount = 0;
		if (microFibers != "")
		{
			microFiberAmount = atoi(microFibers.c_str());
			additive = make_shared<decorator::MicroFibers>(additive, microFiberAmount);
		}
		additive->addAdditive();

		int totalAmount = anOrder->getMachine()->getCavityNum() *
			(cavityShape->plasticRequired() + colorAmount + uvInhibiterAmount + antibacterialAmount + microFiberAmount);
		cout << "Total = " << totalAmount << ".\n";


		// Run injection process
		cout << "    Cycle IJM for " << plasticUsed->getPlasticCategory() << " " << size << " times.\n";

		shared_ptr<strategy::InjectionProcess> injectProcess;
		if (plasticUsed->getPlasticCategory() == "ABS")
			injectProcess = make_shared<strategy::InjectionProcess>(make_shared<strategy::ABSType>());
		else if (plasticUsed->getPlasticCategory() == "Poly")
			injectProcess = make_shared<strategy::InjectionProcess>(make_shared<strategy::PolyType>());
		else if (plasticUsed->getPlasticCategory() == "PET")
			injectProcess = make_shared<strategy::InjectionProcess>(make_shared<strategy::PETType>());
		else if (plasticUsed->getPlasticCategory() == "Synthetics" && plastic == "Styrene")
			injectProcess = make_shared<strategy::InjectionProcess>(make_shared<strategy::StyreneType>());
		else if (plasticUsed->getPlasticCategory() == "Synthetics" && plastic == "Nylon66")
			injectProcess = make_shared<strategy::InjectionProcess>(make_shared<strategy::Nylon66Type>());
		else
			injectProcess = make_shared<strategy::InjectionProcess>(make_shared<strategy::ABSType>());

		shared_ptr<adapter::CleanAdapter> cleanAdapter;
		if (plasticUsed->getPlasticCategory() == "ABS")
		{
			cleanAdapter = make_shared<adapter::ABS>();
		}
		else if (plasticUsed->getPlasticCategory() == "Poly")
		{
			cleanAdapter = make_shared<adapter::Poly>();
		}
		else if (plasticUsed->getPlasticCategory() == "PET")
		{
			if (anOrder->getMoldMetal()->getName() == "Aluminum")
				cleanAdapter = make_shared<adapter::PET_Aluminum>();
			else if (anOrder->getMoldMetal()->getName() == "Steel")
				cleanAdapter = make_shared<adapter::PET_Steel>();
			else
				cleanAdapter = make_shared<adapter::PET_Aluminum>();
		}
		else if (plasticUsed->getPlasticCategory() == "Synthetics" && plastic == "Styrene")
		{
			cleanAdapter = make_shared<adapter::Styrene>();
		}
		else if (plasticUsed->getPlasticCategory() == "Synthetics" && plastic == "Nylon66")
		{
			cleanAdapter = make_shared<adapter::Nylon66>();
		}
		else
		{
			cleanAdapter = make_shared<adapter::ABS>();
		}

		injectProcess->runInjection();

		shared_ptr<observer::PackageBinSubject> packageBin = make_shared<observer::PackageBinSubject>(anOrder->getPackageBin()->getName());
		shared_ptr<abstract_factory::StufferFamily> stufferRequested;
		if (stuffer == "Air")
		{
			stufferRequested = make_shared<abstract_factory::Air>();
		}
		else if (stuffer == "Popcorn")
		{
			stufferRequested = make_shared<abstract_factory::Popcorn>();
		}
		else if (stuffer == "BubbleWrap")
		{
			stufferRequested = make_shared<abstract_factory::BubbleWrap>();
		}
		else if (stuffer == "Foam")
		{
			stufferRequested = make_shared<abstract_factory::Foam>();
		}
		else{
			stufferRequested = make_shared<abstract_factory::Air>();
		}

        shared_ptr<observer::PackageBinObserver> observers[] =
        {
            make_shared<observer::Machines>(packageBin.get()),
            make_shared<observer::ConveyerBelt>(packageBin.get()),
            make_shared<observer::Packager>(packageBin.get()),
			make_shared<observer::Stuffer>(packageBin.get(), stufferRequested),
        };
        packageBin->isFull();

        cleanAdapter->clean();
    }

    pair<string, string> parse(string line) {
        char key[83];
        char val[83] = { 0 };

        sscanf(line.c_str(), "%s", key);

        char* equalSign = const_cast<char *>(strchr(line.c_str(), '='));
        string value = "";
        if (equalSign) {	// tags = sam i am
            char*	nextToken = equalSign += 2;
            while (nextToken) {
                sscanf(nextToken, "%s", val);
                value += val;
                nextToken = strchr(nextToken + 1, ' ');
                value += " ";
            }
            value.erase(value.length() - 1, 1);
        }

        return make_pair(key, value);
    }

    map<string, string> getCompleteOrder(FILE* orderFilePtr) {
        map<string, string> order;
        char line[80 + 3];
        pair<string, string>	keyValue;

        while (fgets(line, 80, orderFilePtr)) {
            cout << line;
            if (strstr(line, "endOfOrder")) {
                return(order);
            }
            else {
                keyValue = parse(line);
                string key = keyValue.first;
                if (strchr(key.c_str(), ':'))	// Skip left justified order number.
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

        for (;;) {	// Get and process each order.
            map<string, string> order = getCompleteOrder(orderFilePtr);
            if (order.size() == 0)
                break;
            process(order);
        }
    }

}

#endif /* DP4_SRC_STUDENTS_CHAO_H_ */
