/*
 * solti.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */
#define DP4_SRC_STUDENTS_SOLTI_H_	// Used unique_ptr.
#ifndef DP4_SRC_STUDENTS_SOLTI_H_
#define DP4_SRC_STUDENTS_SOLTI_H_

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <set>
using namespace std;

namespace final_solti_file {

    const bool on = false;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }
#define INSTRUMENT_DTOR if(on) { cout << "~" << name << endl; }
    class OriginOfEverything {
    public:
        OriginOfEverything(string n) : name(n){};
        virtual ~OriginOfEverything(){}
        string getName() { return name; }
    protected:
        string name;
    };
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

        // Seam point - add another interface.
        class Cleaner : public OriginOfEverything{
        public:
            Cleaner(string n) : OriginOfEverything(n){}
            virtual ~Cleaner(){}
            virtual void clean() = 0;
        };
        class ABSCleaner : public Cleaner{
        public:
            ABSCleaner() : Cleaner("ABSCleaner"){}
            virtual ~ABSCleaner(){ INSTRUMENT_DTOR }
            virtual void clean(){
                abs.clean();
            };
        private:
            legacy_classes::CleanABS abs;
        };
        class PolyCleaner : public Cleaner{
        public:
            PolyCleaner() : Cleaner("PolyCleaner"){}
            virtual ~PolyCleaner(){ INSTRUMENT_DTOR }
            virtual void clean(){
                poly.prepForReuse();
            };
        private:
            legacy_classes::CleanPolys poly;
        };


        class PETSteelCleaner : public Cleaner{
        public:
            PETSteelCleaner() : Cleaner("PETSteelCleaner"){}
            virtual ~PETSteelCleaner(){ INSTRUMENT_DTOR }
            virtual void clean(){
                pet.carbonize();
            };
        private:
            legacy_classes::PETCleanup pet;
        };

        class PETaluminumCleaner : public Cleaner{
        public:
            PETaluminumCleaner() : Cleaner("PETaluminumCleaner"){}
            virtual ~PETaluminumCleaner(){ INSTRUMENT_DTOR }
            virtual void clean(){
                pet.purify();
            };
        private:
            legacy_classes::PETCleanup pet;
        };

        class SynthesisCleaner : public Cleaner{
        public:
            SynthesisCleaner() : Cleaner("SynthesisCleaner"){}
            virtual ~SynthesisCleaner(){ INSTRUMENT_DTOR }
            virtual void clean(){
                cout << "    Clean synthetic mold: ozone wash.\n";
            };
        };
    }

    namespace strategy {		// DP 1.
        // Injection cycle :
        //     ABS - Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject
        //     Poly - Close - heat to 350 - inject at  90 PSI - cool to 290 - separate - smooth eject
        //     PET - Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject

        class InjectionProcess : public OriginOfEverything{
        public:
            InjectionProcess(string n, int run) : OriginOfEverything(n), numRunNeededForTheOrder(run){}
            virtual ~InjectionProcess(){}
            void operate(){
                cout << "    Cycle IJM for " << this->getName() << " "
                    << numRunNeededForTheOrder << " times.\n";
                inject();
            }
        protected:
            virtual void inject() = 0;
            int numRunNeededForTheOrder; // ceil(stoi(order["size"]) / pInjectionLine->pMold->cavity)
        };
        class ABS : public InjectionProcess {
        public:
            ABS(int run) : InjectionProcess("ABS", run){}
            virtual ~ABS(){ INSTRUMENT_DTOR }
        private:
            virtual void inject(){
                cout << "      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject." << endl;
            }
        };
        class Poly : public InjectionProcess {
        public:
            Poly(int run) : InjectionProcess("Poly", run){}
            virtual ~Poly(){ INSTRUMENT_DTOR }
        private:
            virtual void inject(){
                cout << "      Close - heat to 350 - inject at  90 PSI - cool to 290 - separate - smooth eject." << endl;
            }
        };
        class PET : public InjectionProcess {
        public:
            PET(int run) : InjectionProcess("PET", run){}
            virtual ~PET(){ INSTRUMENT_DTOR }
        private:
            virtual void inject(){
                cout << "      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject." << endl;
            }
        };
        // Seam point - add another algorithm.
        class Synthetics : public InjectionProcess {
        public:
            Synthetics(int run) : InjectionProcess("Synthetics", run){}
            virtual ~Synthetics(){ INSTRUMENT_DTOR }
        private:
            virtual void inject(){
                cout << "      Close - heat to 480 - inject at 150 PSI - cool to 390 - separate - shock eject." << endl;
            }
        };
    }

    namespace observer {		// DP 7.
        class Subject;
        class Observer{
        public:
            virtual void update(Subject* pSubject) = 0;
        };
        class Subject{
        public:
            void notify(){
                for (auto s : subscribors){
                    s->update(this);
                }
            };
            void attach(Observer* pNewScribor){
                subscribors.insert(pNewScribor);
            }
            void detach(Observer* pLeavingScribor){
                subscribors.erase(pLeavingScribor);
            }
            virtual string getState() = 0;
        private:
            // using a set to maintain assumes the order of notification is irrelevant
            // otherwise a vector has to be used to maintain an order
            set<Observer*> subscribors;
        };
        // Seam point - add another listener.

    }

    namespace factory_method {	// DP 5.
        // 3. Implement the following three Packagers:
        //   3.1 Bulk (just dump part to output bin)
        //   3.2 ShrinkWrap
        //   3.3 HardPack
        //   3.4 If Packager unknown, default to Bulk
        //     3.4.1 cout << "  <>Unknown packager |<unknown packager>| defaulting to Bulk packager.\n";
        class Bulk; class ShrinkWrap; class HardPack;

        class Packager : public OriginOfEverything, public observer::Observer{
        public:
            Packager(string n) : OriginOfEverything(n){}
            virtual ~Packager(){}
            static Packager* Packager::createPackager(map<string, string>& order);
            virtual void update(observer::Subject* pSubject){
                cout << "        Packager pausing while " << pSubject->getState() << " package bin is swapped." << endl;
            }

        };

        class Bulk : public Packager {
        public:
            Bulk() : Packager("Bulk"){}
            virtual ~Bulk(){ INSTRUMENT_DTOR }
        };
        class ShrinkWrap : public Packager {
        public:
            ShrinkWrap() : Packager("ShrinkWrap"){}
            virtual ~ShrinkWrap(){ INSTRUMENT_DTOR }
        };
        class HardPack : public Packager {
        public:
            HardPack() : Packager("HardPack"){}
            virtual ~HardPack(){ INSTRUMENT_DTOR }
        };
        class ZipLock : public Packager {
        public:
            ZipLock() : Packager("ZipLock"){}
            virtual ~ZipLock(){ INSTRUMENT_DTOR }
        };
        // Seam point - add another class.

        // create packager
        Packager* Packager::createPackager(map<string, string>& order){
            if (order["packager"] == "Bulk"){
                return new Bulk;
            }
            else if (order["packager"] == "ShrinkWrap"){
                return new ShrinkWrap;
            }
            else if (order["packager"] == "HardPack"){
                return new HardPack;
            }
            else if (order["packager"] == "ZipLock"){
                return new ZipLock;
            }
            else{
                cout << "  <>Unknown packager |" << order["packager"] << "| defaulting to Bulk packager.\n";
                return new Bulk;
            }
        }



        class Stuffer : public OriginOfEverything, public observer::Observer{
        public:
            Stuffer(string n) : OriginOfEverything(n){}
            virtual ~Stuffer(){}
            virtual string getStuffing() = 0;
            static Stuffer* createStuffer(map<string, string>& order);
            virtual void update(observer::Subject* pSubject){
                cout << "        Stuffer filling " << pSubject->getState() << " package bin with " << getStuffing() << " stuffing." << endl;
            }
        };
        class Air : public Stuffer {
        public:
            Air() : Stuffer("Air"){}
            virtual ~Air(){ INSTRUMENT_DTOR }
            virtual string getStuffing(){ return "air"; }
        };
        class Popcorn : public Stuffer {
        public:
            Popcorn() : Stuffer("Popcorn"){}
            virtual ~Popcorn(){ INSTRUMENT_DTOR }
            virtual string getStuffing(){ return "styrene popcorn"; }
        };
        class BubbleWrap : public Stuffer {
        public:
            BubbleWrap() : Stuffer("BubbleWrap"){}
            virtual ~BubbleWrap(){ INSTRUMENT_DTOR }
            virtual string getStuffing(){ return "bubble wrap"; }
        };
        class Foam : public Stuffer {
        public:
            Foam() : Stuffer("Foam"){}
            virtual ~Foam(){ INSTRUMENT_DTOR }
            virtual string getStuffing(){ return "expanding foam"; }
        };

        Stuffer* Stuffer::createStuffer(map<string, string>& order){
            if (order["stuffer"] == "Air"){
                return new Air;
            }
            else if (order["stuffer"] == "Popcorn"){
                return new Popcorn;
            }
            else if (order["stuffer"] == "BubbleWrap"){
                return new BubbleWrap;
            }
            else if (order["stuffer"] == "Foam"){
                return new Foam;
            }
            else{
                cout << "  <>Unknown stuffer |" << order["stuffer"] << "| defaulting to Air stuffer.\n";
                return new Air;
            }
        }

    }
    namespace bridge {			// DP 9.
        // Milling Ops:
        //     Aluminum - High carbon  (drill, cut, and high speed grind)
        //     Steel    - Carbide      (high speed drill, cross cut, and layer grind)
        class Tool : public OriginOfEverything {
        public:
            Tool(string n) : OriginOfEverything(n){}
            virtual ~Tool(){};

            virtual string operate() = 0;
        };
        class HighCarbon : public Tool {
        public:
            HighCarbon() : Tool("HighCarbon") {}
            virtual ~HighCarbon(){ INSTRUMENT_DTOR }
            virtual string operate(){
                return "(drill, cut, and high speed grind)";
            };
        };
        class Carbide : public Tool {
        public:
            Carbide() : Tool("Carbide") {}
            virtual ~Carbide(){ INSTRUMENT_DTOR }
            virtual string operate(){
                return "(high speed drill, cross cut, and layer grind)";
            };
        };
        // Seam Point - add another implementation.
        class Diamond_tipped : public Tool {
        public:
            Diamond_tipped() : Tool("Diamond_tipped") {}
            virtual ~Diamond_tipped(){ INSTRUMENT_DTOR }
            virtual string operate(){
                return "(precision drill, oil cooled cut, and cartoid grind)";
            };
        };


        // Shapes:
        //     duck (35 cc)
        //     car (40 cc)
        //     hero (50 cc)
        //     dino (30 cc)  (new)
        class Duck; class Car; class Hero;
        class Shape : public OriginOfEverything {
        public:
            Shape(string n, Tool* t, int v) : OriginOfEverything(n), pTool(t), vol(v){}
            virtual ~Shape(){};

            void millTheShape(string moldBlock, int numCavity, string finish){
                cout << "    using " << this->pTool->getName() << " tools "
                    << this->pTool->operate() << " to mill " << moldBlock
                    << " block into " << numCavity << " " << this->getName() << " shapes with "
                    << finish << " finish." << endl;
            }

            int getVol(){ return vol; }
        protected:
            unique_ptr<Tool> pTool;
            int vol;
        };
        class Duck : public Shape{
        public:
            Duck(Tool* t) : Shape("Duck", t, 35) {}
            virtual ~Duck(){ INSTRUMENT_DTOR }
        };
        class Car : public Shape{
        public:
            Car(Tool* t) : Shape("Car", t, 40) {}
            virtual ~Car(){ INSTRUMENT_DTOR }
        };
        class Hero : public Shape{
        public:
            Hero(Tool* t) : Shape("Hero", t, 50) {}
            virtual ~Hero(){ INSTRUMENT_DTOR }
        };
        // Seam Point - add another abstraction.
        class Dino : public Shape{
        public:
            Dino(Tool* t) : Shape("Dino", t, 30) {}
            virtual ~Dino(){ INSTRUMENT_DTOR }
        };
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

        // IJM:
        //     10,000 - IJM_110
        //     20,000 - IJM_120
        //     50,000 - IJM_210
        //     40, 000 - IJM_140 (new)
        //     100, 000 - IJM_220 (new)
        //     200, 000 - IJM_240 (new)
        class IJM : public OriginOfEverything, public observer::Observer{
        public:
            IJM(string n) : OriginOfEverything(n){}
            virtual ~IJM(){}
            virtual void update(observer::Subject* pSubject){
                cout << "        IJM pausing while " << pSubject->getState() << " package bin is swapped." << endl;
            }
        };
        class IJM_110 : public IJM {
        public:
            IJM_110() : IJM("IJM_110"){}
            virtual ~IJM_110(){ INSTRUMENT_DTOR }
        };
        class IJM_120 : public IJM {
        public:
            IJM_120() : IJM("IJM_120"){}
            virtual ~IJM_120(){ INSTRUMENT_DTOR }
        };
        class IJM_210 : public IJM {
        public:
            IJM_210() : IJM("IJM_210"){}
            virtual ~IJM_210(){ INSTRUMENT_DTOR }
        };

        class IJM_140 : public IJM {
        public:
            IJM_140() : IJM("IJM_140"){}
            virtual ~IJM_140(){ INSTRUMENT_DTOR }
        };
        class IJM_220 : public IJM {
        public:
            IJM_220() : IJM("IJM_220"){}
            virtual ~IJM_220(){ INSTRUMENT_DTOR }
        };
        class IJM_240 : public IJM {
        public:
            IJM_240() : IJM("IJM_240"){}
            virtual ~IJM_240(){ INSTRUMENT_DTOR }
        };

        // Conveyer belts:
        //     10,000 - Linear
        //     20,000 - Y-split
        //     50,000 - Linear
        //     40, 000 - V - level  (new)
        //     100, 000 - Y - split  (new)
        //     200, 000 - V - level  (new)
        class ConveyerBelt : public OriginOfEverything, public observer::Observer{
        public:
            ConveyerBelt(string n) : OriginOfEverything(n){}
            virtual ~ConveyerBelt(){}
            virtual void update(observer::Subject* pSubject){
                cout << "        Conveyer belt pausing while " << pSubject->getState() << " package bin is swapped." << endl;
            }
        };
        class Linear : public ConveyerBelt{
        public:
            Linear() : ConveyerBelt("Linear"){}
            virtual ~Linear(){ INSTRUMENT_DTOR }
        };
        class Y_Split : public ConveyerBelt{
        public:
            Y_Split() : ConveyerBelt("Y-Split"){}
            virtual ~Y_Split(){ INSTRUMENT_DTOR }
        };
        class V_Level : public ConveyerBelt{
        public:
            V_Level() : ConveyerBelt("V-Level"){}
            virtual ~V_Level(){ INSTRUMENT_DTOR }
        };


        // Package bins:
        //     10,000 - Cardboard box
        //     20,000 - Cardboard box
        //     50,000 - Pallot box
        //     40,000 - Pallot box  (new)
        //     100, 000 - Crate  (new)
        //     200, 000 - Crate  (new)
        class PackageBin : public OriginOfEverything, public observer::Subject{
        public:
            PackageBin(string n) : OriginOfEverything(n){}
            virtual ~PackageBin(){}
            virtual string getState(){
                return this->name;
            };

            void notifyFull(){
                cout << "      " << this->name << " package bin full..." << endl;
                this->notify();
            }
        };
        class CardboardBox : public PackageBin{
        public:
            CardboardBox() : PackageBin("CardboardBox"){}
            virtual ~CardboardBox(){ INSTRUMENT_DTOR }
        };
        class PallotBox : public PackageBin{
        public:
            PallotBox() : PackageBin("PallotBox"){}
            virtual ~PallotBox(){ INSTRUMENT_DTOR }
        };
        class Crate : public PackageBin{
        public:
            Crate() : PackageBin("Crate"){}
            virtual ~Crate(){ INSTRUMENT_DTOR }
        };

        // Mold metal & cavites:
        //      10,000 - Aluminum(1)
        //      20,000 - Aluminum(2)
        //      50,000 - Steel(1)
        //      40, 000 - Aluminum(4)  (new)
        //      100, 000 - Steel(2)  (new)
        //      200, 000 - Steel(4)  (new)
        class Mold : public OriginOfEverything{
        public:
            Mold(string n, int c = 1) : OriginOfEverything(n), cavity(c) {}
            virtual ~Mold(){}
            int cavity;
            virtual bridge::Tool* generateTool(string finish = "") = 0;
        };
        class Aluminum : public Mold{
        public:
            Aluminum() : Mold("Aluminum"){}
            Aluminum(int c) : Mold("Aluminum", c){}
            virtual ~Aluminum(){ INSTRUMENT_DTOR }
            virtual bridge::Tool* generateTool(string finish = ""){ return new bridge::HighCarbon; };

        };
        class Steel : public Mold{
        public:
            Steel() : Mold("Steel"){}
            Steel(int c) : Mold("Steel", c){}
            virtual ~Steel(){ INSTRUMENT_DTOR }
            virtual bridge::Tool* generateTool(string finish){
                if (finish == "satin"){
                    return new bridge::Diamond_tipped;
                }
                else{
                    return new bridge::Carbide;
                }
            };
        };



        // Run sizes:
        //     10,000
        //     20,000
        //     50,000
        //     40,000  (new)
        //     100,000  (new)
        //     200,000  (new)
        //     400,000 defaults to 200, 000  (new)
        class AbstractFactory : public OriginOfEverything {
        public:
            AbstractFactory(string n) : OriginOfEverything(n){}
            virtual ~AbstractFactory(){}
            virtual IJM* createIjm() = 0;
            virtual ConveyerBelt* createConveyerBelt() = 0;
            virtual PackageBin* createPackageBin() = 0;
            virtual Mold* createMold() = 0;
        };
        class InjectionLine : public OriginOfEverything {
        public:
            InjectionLine(string n) : OriginOfEverything(n){}
            virtual ~InjectionLine(){}
            unique_ptr<IJM> pIjm;
            unique_ptr<ConveyerBelt> pConveyerBelt;
            unique_ptr<PackageBin> pPackageBin;
            unique_ptr<Mold> pMold;
            unique_ptr<factory_method::Stuffer> pStuffer;
            unique_ptr<factory_method::Packager> pPackager;
            virtual unique_ptr<AbstractFactory> buildFactory() = 0;
            void init(){
                unique_ptr<AbstractFactory> pFactory = buildFactory();
                this->pIjm.reset(pFactory->createIjm());
                this->pConveyerBelt.reset(pFactory->createConveyerBelt());
                this->pPackageBin.reset(pFactory->createPackageBin());
                this->pMold.reset(pFactory->createMold());
            }
            void setPackager(factory_method::Packager* pP){ this->pPackager.reset(pP); }
            void setStuffer(factory_method::Stuffer* pS) { this->pStuffer.reset(pS); }
        };


        // 10,000
        class AF_10000 : public AbstractFactory {
        public:
            AF_10000() : AbstractFactory("AF_10000"){}
            virtual ~AF_10000(){ INSTRUMENT_DTOR }
            virtual IJM* createIjm(){ return new IJM_110; };
            virtual ConveyerBelt* createConveyerBelt(){ return new Linear; };
            virtual PackageBin* createPackageBin(){ return new CardboardBox; };
            virtual Mold* createMold(){ return new Aluminum; };
        };
        class IL_10000 : public InjectionLine {
        public:
            IL_10000() : InjectionLine("IL_10000"){}
            virtual ~IL_10000(){ INSTRUMENT_DTOR }
            virtual unique_ptr<AbstractFactory> buildFactory(){ return unique_ptr<AbstractFactory>(new AF_10000); };
        };

        // 20,000
        class AF_20000 : public AbstractFactory {
        public:
            AF_20000() : AbstractFactory("AF_20000"){}
            virtual ~AF_20000(){ INSTRUMENT_DTOR }
            virtual IJM* createIjm(){ return new IJM_120; };
            virtual ConveyerBelt* createConveyerBelt(){ return new Y_Split; };
            virtual PackageBin* createPackageBin(){ return new CardboardBox; };
            virtual Mold* createMold(){ return new Aluminum(2); };
        };
        class IL_20000 : public InjectionLine {
        public:
            IL_20000() : InjectionLine("IL_20000"){}
            virtual ~IL_20000(){ INSTRUMENT_DTOR }
            virtual unique_ptr<AbstractFactory> buildFactory(){ return unique_ptr<AbstractFactory>(new AF_20000); };
        };

        // 50,000
        class AF_50000 : public AbstractFactory {
        public:
            AF_50000() : AbstractFactory("AF_50000"){}
            virtual ~AF_50000(){ INSTRUMENT_DTOR }
            virtual IJM* createIjm(){ return new IJM_210; };
            virtual ConveyerBelt* createConveyerBelt(){ return new Linear; };
            virtual PackageBin* createPackageBin(){ return new PallotBox; };
            virtual Mold* createMold(){ return new Steel; };
        };
        class IL_50000 : public InjectionLine {
        public:
            IL_50000() : InjectionLine("IL_50000"){}
            virtual ~IL_50000(){ INSTRUMENT_DTOR }
            virtual unique_ptr<AbstractFactory> buildFactory(){ return unique_ptr<AbstractFactory>(new AF_50000); };
        };

        // Seam line - add another family.
        // 40,000
        class AF_40000 : public AbstractFactory {
        public:
            AF_40000() : AbstractFactory("AF_40000"){}
            virtual ~AF_40000(){ INSTRUMENT_DTOR }
            virtual IJM* createIjm(){ return new IJM_140; };
            virtual ConveyerBelt* createConveyerBelt(){ return new V_Level; };
            virtual PackageBin* createPackageBin(){ return new PallotBox; };
            virtual Mold* createMold(){ return new Aluminum(4); };
        };
        class IL_40000 : public InjectionLine {
        public:
            IL_40000() : InjectionLine("IL_40000"){}
            virtual ~IL_40000(){ INSTRUMENT_DTOR }
            virtual unique_ptr<AbstractFactory> buildFactory(){ return unique_ptr<AbstractFactory>(new AF_40000); };
        };

        // 100,000
        class AF_100000 : public AbstractFactory {
        public:
            AF_100000() : AbstractFactory("AF_100000"){}
            virtual ~AF_100000(){ INSTRUMENT_DTOR }
            virtual IJM* createIjm(){ return new IJM_220; };
            virtual ConveyerBelt* createConveyerBelt(){ return new Y_Split; };
            virtual PackageBin* createPackageBin(){ return new Crate; };
            virtual Mold* createMold(){ return new Steel(2); };
        };
        class IL_100000 : public InjectionLine {
        public:
            IL_100000() : InjectionLine("IL_100000"){}
            virtual ~IL_100000(){ INSTRUMENT_DTOR }
            virtual unique_ptr<AbstractFactory> buildFactory(){ return unique_ptr<AbstractFactory>(new AF_100000); };
        };

        // 200,000
        class AF_200000 : public AbstractFactory {
        public:
            AF_200000() : AbstractFactory("AF_200000"){}
            virtual ~AF_200000(){ INSTRUMENT_DTOR }
            virtual IJM* createIjm(){ return new IJM_240; };
            virtual ConveyerBelt* createConveyerBelt(){ return new V_Level; };
            virtual PackageBin* createPackageBin(){ return new Crate; };
            virtual Mold* createMold(){ return new Steel(4); };
        };
        class IL_200000 : public InjectionLine {
        public:
            IL_200000() : InjectionLine("IL_200000"){}
            virtual ~IL_200000(){ INSTRUMENT_DTOR }
            virtual unique_ptr<AbstractFactory> buildFactory(){ return unique_ptr<AbstractFactory>(new AF_200000); };
        };

        // 400,000 - same behavior as 200,000(?)
        //    class AF_400000 : public AbstractFactory {
        //    public:
        //        AF_400000() : AbstractFactory("AF_400000"){}
        //        virtual ~AF_400000(){ INSTRUMENT_DTOR }
        //        virtual IJM* createIjm(){ return new IJM_210; };
        //        virtual ConveyerBelt* createConveyerBelt(){ return new Linear; };
        //        virtual PackageBin* createPackageBin(){ return new PallotBox; };
        //        virtual Mold* createMold(){ return new Steel; };
        //    };
        //    class IL_400000 : public InjectionLine {
        //    public:
        //        IL_400000() : InjectionLine("IL_400000"){}
        //        virtual ~IL_400000(){ INSTRUMENT_DTOR }
        //        virtual unique_ptr<AbstractFactory> buildFactory(){ return unique_ptr<AbstractFactory>(new AF_400000); };
        //    };
    }



    namespace chain_of_resp {	// DP 8.
        // Seam points - add another responder.
        class InjectionLineCreator : public OriginOfEverything {
        public:
            InjectionLineCreator(string n) : OriginOfEverything(n){}
            virtual ~InjectionLineCreator(){}
            virtual abstract_factory_solti::InjectionLine* create(int orderSize){
                if (pNext != NULL){
                    return pNext->create(orderSize);
                }
                else{
                    return NULL;
                }
            }

            void addInjectionLine(InjectionLineCreator* newLine){
                if (pNext != NULL){
                    pNext->addInjectionLine(newLine);
                }
                else{
                    pNext.reset(newLine);
                }
            }
        private:
            unique_ptr<InjectionLineCreator> pNext;
        };
        class ILC_10000 : public InjectionLineCreator {
        public:
            ILC_10000() : InjectionLineCreator("ILC_10000"){}
            virtual ~ILC_10000(){ INSTRUMENT_DTOR }
            virtual abstract_factory_solti::InjectionLine* create(int orderSize){
                if (orderSize <= 10000){
                    return new abstract_factory_solti::IL_10000;
                }
                else{
                    return InjectionLineCreator::create(orderSize);
                }
            }
        };
        class ILC_20000 : public InjectionLineCreator {
        public:
            ILC_20000() : InjectionLineCreator("ILC_20000"){}
            virtual ~ILC_20000(){ INSTRUMENT_DTOR }
            virtual abstract_factory_solti::InjectionLine* create(int orderSize){
                if (orderSize <= 20000){
                    return new abstract_factory_solti::IL_20000;
                }
                else{
                    return InjectionLineCreator::create(orderSize);
                }
            }
        };
        class ILC_50000 : public InjectionLineCreator {
        public:
            ILC_50000() : InjectionLineCreator("ILC_50000"){}
            virtual ~ILC_50000(){ INSTRUMENT_DTOR }
            virtual abstract_factory_solti::InjectionLine* create(int orderSize){
                if (orderSize <= 50000){
                    return new abstract_factory_solti::IL_50000;
                }
                else{
                    return InjectionLineCreator::create(orderSize);
                }
            }
        };
        class ILC_40000 : public InjectionLineCreator {
        public:
            ILC_40000() : InjectionLineCreator("ILC_40000"){}
            virtual ~ILC_40000(){ INSTRUMENT_DTOR }
            virtual abstract_factory_solti::InjectionLine* create(int orderSize){
                if (orderSize <= 40000){
                    return new abstract_factory_solti::IL_40000;
                }
                else{
                    return InjectionLineCreator::create(orderSize);
                }
            }
        };
        class ILC_100000 : public InjectionLineCreator {
        public:
            ILC_100000() : InjectionLineCreator("ILC_100000"){}
            virtual ~ILC_100000(){ INSTRUMENT_DTOR }
            virtual abstract_factory_solti::InjectionLine* create(int orderSize){
                if (orderSize <= 100000){
                    return new abstract_factory_solti::IL_100000;
                }
                else{
                    return InjectionLineCreator::create(orderSize);
                }
            }
        };
        class ILC_200000 : public InjectionLineCreator {
        public:
            ILC_200000() : InjectionLineCreator("ILC_200000"){}
            virtual ~ILC_200000(){ INSTRUMENT_DTOR }
            virtual abstract_factory_solti::InjectionLine* create(int orderSize){
                if (orderSize <= 200000){ // use this to handle all orders larger than 100,000
                    return new abstract_factory_solti::IL_200000;
                }
                else{
                    return InjectionLineCreator::create(orderSize);
                }
            }
        };
    }

    namespace decorator {		// DP 6.
        // Seam point - add another option.
        class Tag : public OriginOfEverything{
        public:
            Tag(string n) : OriginOfEverything(n){}
            virtual ~Tag(){}

            virtual int getTagLength() = 0;
            virtual string getTagContent() = 0;
        };
        class TagCore : public Tag{
        public:
            TagCore() : Tag("TagCore"){}
            virtual ~TagCore(){ INSTRUMENT_DTOR }

            virtual int getTagLength(){
                return 0;
            }
            virtual string getTagContent(){
                return "";
            };
        };
        class TagDecorator : public Tag{
        public:
            TagDecorator(string n, Tag* w) : Tag(n){
                pWrapee.reset(w);
            }
            virtual ~TagDecorator(){}
            unique_ptr<Tag> pWrapee;

        };
        class ModelNumberDecorator : public TagDecorator {
        public:
            ModelNumberDecorator(Tag* w) : TagDecorator("ModelNumberDecorator", w){}
            virtual ~ModelNumberDecorator(){ INSTRUMENT_DTOR }
            virtual int getTagLength(){
                return 2 + this->pWrapee->getTagLength();
            }
            virtual string getTagContent(){
                return this->pWrapee->getTagContent().append("ModelNumber ");
            };
        };
        class CountryDecorator : public TagDecorator {
        public:
            CountryDecorator(Tag* w) : TagDecorator("CountryDecorator", w){}
            virtual ~CountryDecorator(){ INSTRUMENT_DTOR }
            virtual int getTagLength(){
                return 2 + this->pWrapee->getTagLength();
            }
            virtual string getTagContent(){
                return this->pWrapee->getTagContent().append("Country ");
            };
        };
        class DateDecorator : public TagDecorator {
        public:
            DateDecorator(Tag* w) : TagDecorator("DateDecorator", w){}
            virtual ~DateDecorator(){ INSTRUMENT_DTOR }
            virtual int getTagLength(){
                return 2 + this->pWrapee->getTagLength();
            }
            virtual string getTagContent(){
                return this->pWrapee->getTagContent().append("Date ");
            };
        };
        class IncrementCounterDecorator : public TagDecorator {
        public:
            IncrementCounterDecorator(Tag* w) : TagDecorator("IncrementCounterDecorator", w){}
            virtual ~IncrementCounterDecorator(){ INSTRUMENT_DTOR }
            virtual int getTagLength(){
                return 4 + this->pWrapee->getTagLength();
            }
            virtual string getTagContent(){
                return this->pWrapee->getTagContent().append("IncCounter ");
            };
        };
        class PartNumberDecorator : public TagDecorator {
        public:
            PartNumberDecorator(Tag* w) : TagDecorator("PartNumberDecorator", w){}
            virtual ~PartNumberDecorator(){ INSTRUMENT_DTOR }
            virtual int getTagLength(){
                return 2 + this->pWrapee->getTagLength();
            }
            virtual string getTagContent(){
                return this->pWrapee->getTagContent().append("PartNumber ");
            };
        };
        class RecycleCodeDecorator : public TagDecorator {
        public:
            RecycleCodeDecorator(Tag* w) : TagDecorator("RecycleCodeDecorator", w){}
            virtual ~RecycleCodeDecorator(){ INSTRUMENT_DTOR }
            virtual int getTagLength(){
                return 6 + this->pWrapee->getTagLength();
            }
            virtual string getTagContent(){
                return this->pWrapee->getTagContent().append("RecycleCode ");
            };
        };
    }

    namespace template_method {	// DP 4.
        class InjectionMoldingFacility : public OriginOfEverything {
        public:
            InjectionMoldingFacility() : OriginOfEverything("InjectionMoldingFacility"){}
            virtual ~InjectionMoldingFacility(){ INSTRUMENT_DTOR }
            // Setup the injection run:
            //     Setup the injection line
            //         IJM
            //         Mold
            //         Conveyer belt
            //         Packager
            //         Output bin
            //     Get and install the mold
            //     Insert tags into mold
            //     Load additive bins
            //     Run the injection cycle till done
            //     Clean the mold
            void process(map<string, string>& order) {
                // 10. Process order :
                //     10.1 Get mold
                //     10.2 Insert tags into mold
                //     10.3 Load plastic, color die, and additive bins
                //     10.4 Simulate cycling the IJM for the specified plastic <size> times
                //     10.4.1 Just once, specify the injection cycle(depends on plastic type)
                //     10.4.2 Just once, simulate a full parts bin asking upline machines to pause
                //     10.5 Clean the mold(ignore molds that are used up, clean them all)
                SetupTheInjectionLine(order);
                GetAndInstallTheMold(order);
                InsertTagsIntoMold(order);
                LoadAdditiveBins(order);
                RunTheInjectionCycleTillDone(order);
                CleanTheMold(order);
                ShipTheProducts(order);
            }

            virtual void SetupTheInjectionLine(map<string, string>& order){
                // 1. System can handle four types of plastics :
                //     1.1 ABS
                //     1.2 Polypropylene
                //     1.3 Polyethelene
                //     1.4 PET
                //     1.5 If the plastic is unknown, default to ABS
                //         1.5.1 cout << "  <>Unknown plastic |<unknown plastic>| defaulting to ABS.\n";

                if (((order["plastic"] != "Nylon66") && (order["plastic"] != "Styrene") && (order["plastic"] != "ABS") && order["plastic"] != "ABS") && (order["plastic"] != "Polypropylene") && (order["plastic"] != "Polyethelene") && (order["plastic"] != "PET")){
                    cout << "  <>Unknown plastic |" << order["plastic"] << "| defaulting to ABS.\n";
                    order["plastic"] = "ABS";
                }

                if (order.count("size") == 0){
                    cout << "  <>No size specified, defaulting to 100.\n";
                    order["size"] = "100";
                }
                else if (stoi(order["size"]) > 200000){
                    cout << "  <>Size too large |" << order["size"] << "| defaulting to HugeOrder of 200000.\n";
                    order["size"] = "200000";
                }
                int orderSize = stoi(order["size"]);

                // create the IL line
                unique_ptr<chain_of_resp::InjectionLineCreator> pILCHead = unique_ptr<chain_of_resp::InjectionLineCreator>(new chain_of_resp::ILC_10000);
                pILCHead->addInjectionLine(new chain_of_resp::ILC_20000);
                pILCHead->addInjectionLine(new chain_of_resp::ILC_40000);
                pILCHead->addInjectionLine(new chain_of_resp::ILC_50000);
                pILCHead->addInjectionLine(new chain_of_resp::ILC_100000);
                pILCHead->addInjectionLine(new chain_of_resp::ILC_200000);

                pInjectionLine.reset(pILCHead->create(orderSize));
                pInjectionLine->init();

                if (order["plastic"] == "ABS"){
                    pInjectionProcess.reset(new strategy::ABS(ceil(stoi(order["size"]) / pInjectionLine->pMold->cavity)));
                }
                else if (order["plastic"] == "Polypropylene"){
                    pInjectionProcess.reset(new strategy::Poly(ceil(stoi(order["size"]) / pInjectionLine->pMold->cavity)));
                }
                else if (order["plastic"] == "Polyethelene"){
                    pInjectionProcess.reset(new strategy::Poly(ceil(stoi(order["size"]) / pInjectionLine->pMold->cavity)));
                }
                else if ((order["plastic"] == "Styrene") || (order["plastic"] == "Nylon66")){
                    pInjectionProcess.reset(new strategy::Synthetics(ceil(stoi(order["size"]) / pInjectionLine->pMold->cavity)));
                }
                else { // if (order["plastic"] == "PET"){
                    pInjectionProcess.reset(new strategy::PET(ceil(stoi(order["size"]) / pInjectionLine->pMold->cavity)));
                }

                pInjectionLine->setPackager(factory_method::Packager::createPackager(order));
                pInjectionLine->setStuffer(factory_method::Stuffer::createStuffer(order));
                cout << "  " << "Setup injection line for " << orderSize / pInjectionLine->pMold->cavity << " run with "
                    << pInjectionLine->pPackager->getName() << " packager and " << pInjectionLine->pStuffer->getStuffing() << " stuffing:" << endl;

                cout << "    " << pInjectionLine->pIjm->getName()
                    << " - " << pInjectionLine->pMold->getName() << "(" << pInjectionLine->pMold->cavity << ")"
                    << " - " << pInjectionLine->pConveyerBelt->getName() << " conveyer belt"
                    << " - " << pInjectionLine->pPackageBin->getName() << endl;
            };

            virtual void GetAndInstallTheMold(map<string, string>& order){
                // 12. Molds are be pulled fron inventory or milled from bulk metal
                //     12.1 (To keep the final simple, the order will specify the mold location.)
                //         12.1.1 If location and shape unknown, default to duck from inventory
                //         12.1.2 cout << "    <>Can't find place |<loc>| to get |<shape>| mold from, defaulting to duck from inventory.\n";
                //     12.2 Inventory:
                //         12.2.1 cout << "    Pull <shape> mold from inventory.\n";
                //     12.3 Mill:
                //         12.3.1 cout << "    Create <shape> mold from mill with <n> cavities:\n"
                cout << "  Process order." << endl;
                if ((order["moldLoc"] != "inventory") && (order["moldLoc"] != "mill") && (order["moldLoc"] != "sisterCompany") && (order["moldLoc"] != "purchase")){
                    cout << "    <>Can't find place |" << order["moldLoc"] << "| to get |" << order["mold"] << "| mold from, defaulting to duck from inventory.\n";
                    order["moldLoc"] = "inventory";
                }
                if ((order["mold"] != "duck") && (order["mold"] != "car") && (order["mold"] != "hero") && (order["mold"] != "dino")){
                    order["mold"] = "duck";
                }
                if ((order["finish"] != "rippled") && (order["finish"] != "smooth") && (order["finish"] != "dimpled") && (order["finish"] != "sanded") && (order["finish"] != "satin")){
                    order["finish"] = "smooth";
                }

                bridge::Tool* pTool = pInjectionLine->pMold->generateTool(order["finish"]);
                if (order["mold"] == "duck"){
                    pShape.reset(new bridge::Duck(pTool));
                }
                else if (order["mold"] == "car"){
                    pShape.reset(new bridge::Car(pTool));
                }
                else if (order["mold"] == "dino"){
                    pShape.reset(new bridge::Dino(pTool));
                }
                else { // if (shape == "hero"){
                    pShape.reset(new bridge::Hero(pTool));
                }

                if (order["moldLoc"] == "mill"){
                    cout << "    Create " << pShape->getName() << " mold from mill with " << pInjectionLine->pMold->cavity << " cavities:\n";
                    pShape->millTheShape(pInjectionLine->pMold->getName(), pInjectionLine->pMold->cavity, order["finish"]);
                }
                else if (order["moldLoc"] == "sisterCompany"){
                    cout << "    Borrow " << pShape->getName() << " mold from sister company." << endl;
                }
                else if (order["moldLoc"] == "purchase"){
                    cout << "    Acquire " << pShape->getName() << " mold via purchase." << endl;
                }
                else { // if(order["moldLoc"] == "inventory"){
                    cout << "    Pull " << order["mold"] << " mold from inventory.\n";
                }
            }

            virtual void InsertTagsIntoMold(map<string, string>& order){
                // 16. Support three tags, widths in mm(inserted into molds, typically under the support base, think plastic toy) :
                //     16.1 ModelNumber(2 mm)
                //     16.2 Country(2 mm)
                //     16.3 Date(2 mm)
                //     16.4 Total space for tags is 20 mm
                //         16.4.1 cout << "    Insert tags [space separated list of tags ] of width <n>/20 mm.\n";
                //     16.5 Ignore unknown tags
                //         16.5.1 cout << "Ignoring unknown tag <tag>.\n" --> not implemented
                unique_ptr<decorator::Tag> pTag;
                pTag.reset(new decorator::TagCore);

                if (order["tags"].find("IncCounter") != string::npos){
                    pTag.reset(new decorator::IncrementCounterDecorator(pTag.release()));
                }
                if (order["tags"].find("PartNumber") != string::npos){
                    pTag.reset(new decorator::PartNumberDecorator(pTag.release()));
                }
                if (order["tags"].find("RecycleCode") != string::npos){
                    pTag.reset(new decorator::RecycleCodeDecorator(pTag.release()));
                }
                if (order["tags"].find("ModelNumber") != string::npos){
                    pTag.reset(new decorator::ModelNumberDecorator(pTag.release()));
                }
                if (order["tags"].find("Country") != string::npos){
                    pTag.reset(new decorator::CountryDecorator(pTag.release()));
                }
                if (order["tags"].find("Date") != string::npos){
                    pTag.reset(new decorator::DateDecorator(pTag.release()));
                }

                cout << "    Insert tags [" << pTag->getTagContent() << "] of width " << pTag->getTagLength() << "/20 mm.\n";
            }

            virtual void LoadAdditiveBins(map<string, string>& order){
                // 19. Simulate mixing plastic, color, and additives with volume recipe & total(account for multiple cavities) :
                //     19.1 cout << "    Load plastic, color, and additive bins.\n;
                //     19.2 cout << "      Recipe: <plastic>(<vol>) <color>(<vol>) <additive1>(<vol>) <additive2>(<vol>) Total = <vol>.\n";
                cout << "    Load plastic, color, and additive bins.\n";

                // 18. Support six colors(for simplicity, assume volume is 10 % of shape, and die is independent of plastic type) :
                //     18.0 black
                //     18.1 brown
                //     18.2 red
                //     18.3 orange
                //     18.4 yellow
                //     18.5 green
                //     18.6 If no color specified, default to black.
                //         18.6.1 cout << "      <>No color specified, defaulting to black.\n";
                if (order.count("color") == 0){
                    cout << "      <>No color specified, defaulting to black.\n";
                    order["color"] = "black";
                }

                cout << "      Recipe: " << order["plastic"] << "(" << pShape->getVol() << ") " << order["color"]
                    << "(" << (int)(pShape->getVol() * 0.1) << ") ";
                int totalVol = pShape->getVol() * 1.1;
                if (order.count("UVInhibiter") != 0){
                    cout << "UVInhibiter(" << order["UVInhibiter"] << ") ";
                    totalVol += stoi(order["UVInhibiter"]);
                }
                if (order.count("AntiBacterial") != 0){
                    cout << "AntiBacterial(" << order["AntiBacterial"] << ") ";
                    totalVol += stoi(order["AntiBacterial"]);
                }
                if (order.count("MicroFibers") != 0){
                    cout << "MicroFibers(" << order["MicroFibers"] << ") ";
                    totalVol += stoi(order["MicroFibers"]);
                }
                cout << "Total = " << totalVol * pInjectionLine->pMold->cavity << ".\n";
            }

            virtual void RunTheInjectionCycleTillDone(map<string, string>& order){
                // 22. Simulate cycling the IJM for the specified plastic times
                //     22.1 cout << "    Cycle IJM for <plastic> <size> times.\n";
                //     22.2 cout << "      Close - heat to <temp> - inject at <psi> PSI - cool to <temp> - separate - <technique> eject.\n";
                //     22.3 cout << "      <Packager> package bin full...\n";
                //         22.3.1 cout << "        IJM pausing while CardboardBox package bin is swapped.\n";
                //         22.3.2 cout << "        Conveyer belt pausing while CardboardBox package bin is swapped.\n";
                //         22.3.3 cout << "        Packager pausing while CardboardBox package bin is swapped.\n";

                pInjectionProcess->operate();
                pInjectionLine->pPackageBin->attach(pInjectionLine->pIjm.get());
                pInjectionLine->pPackageBin->attach(pInjectionLine->pConveyerBelt.get());
                pInjectionLine->pPackageBin->attach(pInjectionLine->pPackager.get());
                pInjectionLine->pPackageBin->attach(pInjectionLine->pStuffer.get());
                pInjectionLine->pPackageBin->notifyFull();
                pInjectionLine->pPackageBin->detach(pInjectionLine->pIjm.get());
                pInjectionLine->pPackageBin->detach(pInjectionLine->pConveyerBelt.get());
                pInjectionLine->pPackageBin->detach(pInjectionLine->pPackager.get());
                pInjectionLine->pPackageBin->detach(pInjectionLine->pStuffer.get());
            }

            virtual void CleanTheMold(map<string, string>& order){
                // 23. Clean the molds, depends on plastic and metal :
                //     23.1 Use existing cleaning methods(see namespace legacy)
                //     23.2 cout << "    Clean <plastic> <optional metal> mold: <cleaning steps>.\n";
                unique_ptr<adapter::Cleaner> pCleaner;
                if (order["plastic"] == "ABS"){
                    pCleaner.reset(new adapter::ABSCleaner);
                }
                else if (order["plastic"] == "Polypropylene"){
                    pCleaner.reset(new adapter::PolyCleaner);
                }
                else if (order["plastic"] == "Polyethelene"){
                    pCleaner.reset(new adapter::PolyCleaner);
                }
                else if ((order["plastic"] == "Styrene") || (order["plastic"] == "Nylon66")){
                    pCleaner.reset(new adapter::SynthesisCleaner);
                }
                else if (order["plastic"] == "PET"){
                    if (pInjectionLine->pMold->getName() == "Steel"){
                        pCleaner.reset(new adapter::PETSteelCleaner);
                    }
                    else{
                        pCleaner.reset(new adapter::PETaluminumCleaner);
                    }
                }

                pCleaner->clean();
            }

            virtual void ShipTheProducts(map<string, string>& order){
                cout << "    Ship to \"" << order["address"] << "\"" << endl;
            }

            unique_ptr<abstract_factory_solti::InjectionLine> pInjectionLine;
            unique_ptr<bridge::Shape> pShape;
            unique_ptr<strategy::InjectionProcess> pInjectionProcess;
        };
        // Seam point - add another step.

    }

    pair<string, string> parse(string line) {
        char key[83];
        char val[83] = { 0 };

        sscanf(line.c_str(), "%s", key);

        char* equalSign = (char*)strchr(line.c_str(), '=');
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
        unique_ptr<template_method::InjectionMoldingFacility> pIMF;
        pIMF.reset(new template_method::InjectionMoldingFacility);
        for (;;) {	// Get and process each order.
            map<string, string> order = getCompleteOrder(orderFilePtr);
            if (order.size() == 0)
                break;


            pIMF->process(order);
        }
    }

}

#endif /* DP4_SRC_STUDENTS_SOLTI_H_ */
