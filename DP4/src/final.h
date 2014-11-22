/*
 * final.h
 *
 *  Created on: May 17, 2014
 *      Author: aldgoff
 */

#ifndef FINAL_H_
#define FINAL_H_

/* Thoughts on the final exam.
 * Basic paradigm, it's a two stage final.
 * Stage 1, refactor code to implement an injection molding shop.
 *   Handout 2nd to last class, give the students one to two weeks to refactor.
 * Stage 2, the spec changes...
 * 	 New colors
 * 	 New plastics (and therefore new sequences, strategy pattern)
 * 	 New objects
 * 	 New packaging
 * 	 New finishes
 * 	 New textures (smooth, pebbled (sand blasted))
 * 	 Add aluminum
 * 	 Model numbers
 * If your refactoring of the existing procedural code into design pattern code in stage 1 is sound,
 * then adding of the specs in stage 2 should take only one hour.
 * That's your feedback, I don't even have to grade the final.
 *
 *  x Flow sequences:	Strategy		- depends on plastic, maybe not on the mold metal, that's just heating and cooling time.
 *  x Tagging:			Decorator		- model number, date, county, run, count
 *    Molds:			Factory Method	- use from inventory, or create new
 *  x Machines:			Abstract Factory- IJM(100, 400), cavities(1, 4), conveyer belt (linear, Y-split)
 *    Bins:				Observer		- plastic bin empty, part bin full
 *    Process:			TemplateMethod	- add packaging prior to dropping part into bin
 *  x Cleaning:			Adapter			- existing classes to clean molds
 *    Milling:			Facade			- only need shape & finish, don't need tips, despurring, sharpening, etc.???
 */
/* Stages
 * Stage 1 (prior to last day of class):
 *   Procedural code with input file of orders and output file of the runs.
 *   Run the procedural code on the orders and confirm you match the output.
 *   Refactor using design patterns and confirm you still match the output.
 * Stage 2 (last day of class):
 *   New specs, new order file, and a new output file.
 *   Running original or refactored code on new order file doesn't crash, but produces an incomplete output file.
 *   Add code until you can process the new order file and match the new output file.
 *   Grade: A <= 1 hr, B <= 2 hrs, C <= 3 hrs, D <= 4 hrs, F > 4 hrs. A D is passing.
 */
/* List of files:
 * Stage 1:
 *   Provided by instructor:
 *     processOrdersAP.cpp	 - Original C++ code, filled with anti-patterns.
 *     orders_1.txt			 - Original order file (input).
 *     runBase_1.txt		 - Baseline run file of original code (output).
 *   Provided by student:
 *     processOrdersDP_1.cpp - Refactored C++ code, uses design patterns.
 *     runComp_1.txt		 - Comparison output file; must match runBase_1.txt.
 * Stage 2:
 *   Provided by instructor:
 *     newSpecs.txt			 - New specs.
 *     orders_2.txt			 - New order file (input).
 *     orders_x.txt			 - Output of original and refactored DP code on new orders file, incomplete.
 *     runBase_2.txt		 - Baseline run file of upgraded C++ code that implements the new specs (output).
 *   Provided by student:
 *     ProcessOrdersDP_2.cpp - Upgraded C++ code that implements the new specs.
 *     runComp_2.txt		 - Comparison output file; must match runBase_2.txt.
 */
/* Specs:
 * 1) Read next order from input file
 * 2) Process
 * 	  2.1) Get mold
 * 	  	   1) Select metal
 * 	  	   	  a) Steel
 * 	  	   	  b) Aluminum
 * 	  	   2) Fetch or make
 * 	  	   	  1) Make: if not in inventory or near end of life
 * 	  	   	  2) Fetch: otherwise
 * 	  2.2) Install mold
 * 	  	   1) Add tag decorators
 * 	  2.3) Setup machine
 * 	  	   1) Load plastic hopper
 * 	  	   2) Load color hoppers
 * 	  	   3) Load additive hoppers
 * 	  2.4) Injection run
 * 	  	   1) Heat plastic
 * 	  	   2) Inject plastic
 * 	  	   3) Cool mold
 * 	  	   4) Separate mold
 * 	  	   5) Eject part
 * 	  	   6) Close mold
 * 	  2.5) Remove mold
 * 	  2.6) Clean mold
 * 	       1) Depends on metal & plastic
 * 	  2.7) Return mold
 * 	       1) To inventory
 * 	       2) Junk if at end of life
 * 3) Write summary of run to output file
 */
/* Variations:
 * Mold   RunSize   Plastic        Color   Additives      Metal     Cavities  Finish   Tags           Bins       Sequences  Packaging   Cleaning   GetMold       Milling    InjectionMachine
 * Class  Variable  Class          Enum    Decorator      Class     Variable  Enum     Decorator      Observer   Strategy   Factory     Adapter    ChainOfR      Facade     AbstractFactory
 * -----  --------  -------------  ------  -------------  --------  --------  -------  -------------  ---------  ---------  ----------  ---------  ------------  ---------  ----------------
 * Duck   10,000    ABS            Black   UVInhibitor    Steel     1         Smooth   Null           Plastic    PreHeat    Bulk        Carbonize  Fetch         Raster     IJM_100
 * Car    20,000    Polypropylene  Red                              2         Rippled  Tag            Color      PSI        ShrinkWrap  SoapWater  Mill          Vector     IJM_400
 * Hero   150,000   Polyethelene   Green                            4                  ModelNumber    Additives  CoolDown   HardPack    Acetone
 *        50,000    PET            Blue                                                CountryMadeIn  IJM        Eject
 *                                 White                                               DateMade       Packager
 * --------- Seams -------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Dino   500       Styrene        Brown   AntiBacterial  Aluminum  8         Dimpled  IncCounter     Additives  PlasticT   ZipLock     Alcohol    Purchase      LaserEtch  IJM_800
 *        2,000     Nylon66        Orange  MicroFibers                        Sanded                  Conveyer   MoldTemp                          ~Mill(steel)
 *                                 Yellow
 *                                 Violet
 *                                 Gray
 */
/* Dependencies:
 * Sequences depend on Metal & Plastic
 * Cleaning depends on Metal & Plastic - use Adapter pattern.
 * Plastic depends on Metal
 * Steel molds have a 50,000 run lifetime
 * Aluminum molds have a 10,000 run lifetime
 */
/* List of classes used in final <not yet>.
 * Strategy
 * Adapter
 * Facade
 * Template Method
 * Factory Method
 * Decorator
 * Chain of Responsibility
 * <Abstract Factory>
 * Observer
<<<<<<< HEAD
<<<<<<< HEAD
=======
 */
/* Implementation:
 * To keep things simple for a classroom setting, imagine that the larger system
 * prepares the order file (input) with both the customers' orders and persistent data
 * from the injection molding shop such as mold location, run count, etc.
>>>>>>> refs/heads/final
=======
 */
/* Implementation:
 * To keep things simple for a classroom setting, imagine that the larger system
 * prepares the order file (input) with both the customers' orders and persistent data
 * from the injection molding shop such as mold location, run count, etc.
>>>>>>> refs/heads/final
 */

#include "map"
#include "vector"
#include "string"
#include "cassert"
using namespace std;

namespace final {

namespace order { // The fundamental entity is the Order.

class Metal {};
enum Finish {
	smooth,
	rippled,
	// Seam.
	dimpled,
	sanded
};
class Mold {
	string		 name;		// "duck", "car", "hero" -- "dino".
	Metal*		 metal;		// Steel -- Aluminum.
	const int	 cavities;	// 1, 2, 4 -- 8
	const Finish finish;	//
	int			 runCount;	//
public:
	Mold(string name) : name(name), metal(new Metal), cavities(1), finish(smooth), runCount(0) {}
};

class GetMold {};	// Chain of Responsibility pattern - get from inventory, mill shop, or purchase.
class FromInventory	: public GetMold{};
class MillIt		: public GetMold{};
// Seam.
class PurchaseIt	: public GetMold{};
// Mill down for steel.

class Tags {};		// Decorator pattern - one, many, or all.
class NullTag		: public Tags {};
class ModelNumber	: public Tags {};
class CountryMadeIn	: public Tags {};
class DateMade		: public Tags {};
// Seam.
class IncCounter	: public Tags {};

class Additives {};	// Decorator pattern - the optional additives.
class UVInhibitor	: public Additives {};
// Seam.
class AntiBacterial	: public Additives {};
class MicroFibers	: public Additives {};

class Flow {};		// Strategy pattern - cycling the IJM for each injection run.
class ABSFlow	  : public Flow {};
class PolyFlow	  : public Flow {};
class PETFlow	  : public Flow {};
// Seam.
class StyreneFlow : public Flow {};
class Nylon66Flow : public Flow {};

class Packaging {	// Factory Method pattern - need classes to handle packaging the units.
public:
	static Packaging* makeObject(int selection);
	virtual void action() { cout << "Not a valid selection.\n"; }
public:
	virtual ~Packaging() {}
};
class Bulk : public Packaging {
public:
	void action() {
		cout << "Collect in large cardboard bin.\n";
	}
};
class ShrinkWrap : public Packaging {
public:
	void action() {
		cout << "  Pull printed cardboard backing onto frame.\n";
		cout << "  Place piece on backing.\n";
		cout << "  Cover with plastic sheet.\n";
		cout << "  Apply heat.\n";
	}
};
class HardPack : public Packaging {
public:
	void action() {
		cout << "  Stuff plastic shell into void.\n";
		cout << "  Drop piece onto shell.\n";
		cout << "  Cover with cardboard backing.\n";
		cout << "  Staple.\n";
	}
};
// Seam.
class ZipLock : public Packaging {
public:
	void action() {
		cout << "  Blow bag open.\n";
		cout << "  Drop piece into bag.\n";
		cout << "  Zip closed.\n";
	}
};
Packaging* Packaging::makeObject(int selection) {
	switch(selection) {
	case 1:	return new Bulk;
	case 2:	return new ShrinkWrap;
	case 3:	return new HardPack;
	// seam.
	case 4: return new ZipLock;
	default:
		cout << " OOPs, " << selection << " not a valid selection.\n" << endl;
		return new Packaging;
	}
}

class Bins {};		// Observer pattern - when order is done, cleanup and put away.
class PlasticBin	   : public Bins {};
class ColorBin		   : public Bins {};
class UVInhibitorBin   : public Bins {};
class IJM			   : public Bins {};
class Packager		   : public Bins {};
// Seam.
class AntiBacterialBin : public Bins {};
class MicroFibersBin   : public Bins {};
class Conveyer		   : public Bins {};

class CleanABS {};	// Adapter pattern - existing interfaces.
class CleanPolys {};
class PETCleanup {};
class Cleaning {};	// Adapter class - clean the mold, depends on metal & plastic.
class ABSCleaning :			  public Cleaning {};
class PolypropyleneCleaning : public Cleaning {};
class PolyetheleneCleaning :  public Cleaning {};
class PETCleaning :			  public Cleaning {};
// Seam.
class StyreneCleaning		: public Cleaning {};
class Nylon66Cleaning		: public Cleaning {};

class Order {		// Template Method pattern - each injection run.
	int			number;		// Variable
	int			runSize;	// Variable
	Mold*		mold;		// Class
	GetMold*	getMold;	// Chain of Responsibility (inventory, mill -- purchase)
	Tags*		tags;		// Decorator (nullTag, modelNumber, countryMadeIn, dateMade -- incCounter)
	Additives*	additives;	// Decorator (UVInhibitor -- antiBacterial, microFibers)
	Flow*		flow;		// Strategy (depend on metal & plastic)
	Bins*		bins;		// Observer (plastic, color, UVInhibitor, IJM, packager -- antiBacterial, microFibers, conveyer)
	Packaging*	packaging;	// Factory Method (bulk, shrinkWrap, hardPack -- zipLock)
	Cleaning*	cleaning;	// Adapter (ABS, poly, PET -- styrene, nylon)
};

struct RasterMilling {	// Facade pattern - existing interface.
	void raster1() {}
	void raster2() {}
	void raster3() {}
	void raster4() {}
	void raster5() {}
	void finish1() {}
	void finish2() {}
	void finish3() {}
};
struct VectorMilling {
	void vector1() {}
	void vector2() {}
	void vector3() {}
	void vector4() {}
	void finish1() {}
	void finish2() {}
};
// Seam.
struct LaserEtchMilling {
	void etch1() {}
	void etch2() {}
	void etch3() {}
};
class Mill {		// Facade pattern.
public:
	virtual ~Mill() {}
public:
	virtual void shape() {}
	virtual void finish() {}
};
class RasterMill	: public Mill {
	RasterMilling mill;
public:
	void shape() {
		mill.raster2();
		mill.raster4();
		mill.raster1();
	}
	void finish() {
		mill.finish3();
	}
};
class VectorMill	: public Mill {
	VectorMilling mill;
public:
	void shape() {
		mill.vector1();
		mill.vector4();
	}
	void finish() {
		mill.finish1();
	}
};
// Seam.
class LaserEtchMill	: public Mill {
	LaserEtchMilling mill;
public:
	void shape() {
		mill.etch1();
		mill.etch3();
	}
	void finish() {}
};

// Abstract factory is about the IJM machine, outside Order class.

}

namespace strategy { // The flow sequence.

class FlowStrategy {
public:
	virtual ~FlowStrategy() {}
public:
	virtual void run()=0;
};
class ABS			: public FlowStrategy {
	void run() {
		cout << "  Injection mold one part out of ABS.\n";
	}
};
class Polypropylene	: public FlowStrategy {};
class Polyethylene	: public FlowStrategy {};
class PET			: public FlowStrategy {};
// Spec add.
class Styrene		: public FlowStrategy {};
class Nylon66		: public FlowStrategy {};

}

namespace adapter { // The mold cleaning technique. DONE.

class Mold {
	string		name;
	string		metal;
	int			cavities;
	string		finish;
	const int	lifetime;
	int			runCount;
public:
	Mold(string name) :
		name(name), metal("steel"), cavities(1), finish("smooth"), lifetime(50000), runCount(0) {}
public:
	string type() {
		return "steel";
	}
};

// Existing classes with cleaning technique.
class CleanABS {
public:
	void clean(Mold* mold) {
		cout << "Soak in alcohol, rinse with water, dry.\n";
	}
};

class CleanPolys {
public:
	void prepForReuse(Mold* mold) {
		cout << "Rinse with acetone, dry.\n";
	}
};

class PETCleanup {
public:
	void carbonize(Mold* mold) { // Use only on stainless steel.
		cout << "Heat to 895 C.\n";
	}
	void purify(Mold* mold) {	// Use only on aluminum.
		cout << "Rinse with soap and water, dry.\n";
	}
};

// Adapter pattern.
class CleanPlastic {
public:
	virtual void clean(Mold* mold) {}
	virtual ~CleanPlastic() {}
};
class ABS			: public CleanPlastic {
	CleanABS	poly;
public:
	void clean(Mold* mold) {
		poly.clean(mold);
	}
};
class Polypropylene	: public CleanPlastic {
	CleanPolys	poly;
public:
	void clean(Mold* mold) {
		poly.prepForReuse(mold);
	}
};
class Polyethylene	: public CleanPlastic {
	CleanPolys	poly;
public:
	void clean(Mold* mold) {
		poly.prepForReuse(mold);
	}
};
class PET			: public CleanPlastic {
	PETCleanup	poly;
public:
	void clean(Mold* mold) {
		if(mold->type() == "steel")
			poly.carbonize(mold);
		else {
			poly.purify(mold);
		}
	}
};
// Spec add.
class Styrene		: public CleanPlastic {
public:
	void clean(Mold* mold) {
		cout << "Soak in alcohol, rinse with water, dry.\n";
	}
};
class Nylon66		: public CleanPlastic {
public:
	void clean(Mold* mold) {
		cout << "Heat to 550 C.\n";
	}
};

}

namespace facade { // Milling machine control, very complicated, only need two methods say.
}

namespace chain_of_responsibility {

class GetMold {
protected:
	GetMold* successor;
public:
	GetMold(GetMold* successor=0) : successor(successor) {};
	virtual ~GetMold() {}
public:
	virtual void from(const string& place) {
		cout << "  Can't find place " << place << " to get mold from.\n";
	}
};
class Inventory : public GetMold {
public:
	Inventory(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(const string& place) {
		if(place == "inventory")
			cout << "  Pull mold from inventory.\n";
		else if(successor != 0)
			successor->from(place);
		else
			GetMold::from(place);	// Oops.
	}
};
class Mill : public GetMold {
public:
	Mill(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(const string& place) {
		if(place == "mill")
			cout << "  Create mold from mill.\n";
		else if(successor != 0)
			successor->from(place);
		else
			GetMold::from(place);	// Oops.
	}
};
class Purchase : public GetMold {
public:
	Purchase(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(const string& place) {
		if(place == "purchase")
			cout << "  Acquire mold via purchase.\n";
		else if(successor != 0)
			successor->from(place);
		else
			GetMold::from(place);	// Oops.
	}
};

}

namespace template_method { // Order processing.

class PartBin {
public:
	bool full() {
		return false;
	}
	void advanceBin() {}
};

class Stock {
public:
	bool empty() {
		return false;
	}
	void refill() {}
};
class Plastic : public Stock {};
class Color : public Stock {};
// Spec add.
class UVInhibitor : public Stock {};

class Order {
protected:
	adapter::Mold*			mold;
	strategy::FlowStrategy*	flow;
	vector<Stock>	stockBin;
	PartBin			partBin;
public:
	Order(
		adapter::Mold*			mold,
		strategy::FlowStrategy*	flow)
		: mold(), flow(flow) {}
	virtual ~Order() {}
public:
	void getMold_FactoryMethod() {
		cout << "getMold_FactoryMethod\n";
	}
	void installMold() {
		cout << "installMold\n";
		cout << "  CofR to fetch from inventory, mill, or purchase.\n";
		cout << "  hookupConnections\n";

		chain_of_responsibility::GetMold* getMold =
			new chain_of_responsibility::Inventory(
			new chain_of_responsibility::Mill(
			new chain_of_responsibility::Purchase(
			new chain_of_responsibility::GetMold(
		))));
		getMold->from("inventory");	// Replace with source from order.

		//	addTaggingDecorators();
	}
	void machineSetup() {	// Setup the Stock bins.
		cout << "machineSetup\n";
		stockBin.push_back(Plastic());
		stockBin.push_back(Color());
		// Spec add.
		stockBin.push_back(UVInhibitor());
	}
	virtual void injectionRun()=0;
	void removeMold() {
		cout << "removeMold\n";
	}
	void cleanMold_Adapter() {
		cout << "cleanMold_Adapter\n";
	}
	void returnMoldToInventory() {
		cout << "returnMoldToInventory\n";
	}
public:
	void run() {
		cout << "-- ProcessEachOrder_TemplateMethod --\n";
		getMold_FactoryMethod();
		installMold();
		machineSetup();
		injectionRun();
		removeMold();
		cleanMold_Adapter();
		returnMoldToInventory();
	}
};
class SingleColor	: public Order {	// Just one color.
public:
	SingleColor(strategy::FlowStrategy* flow) : Order(new adapter::Mold("car"), flow) {}
public:
	void injectionRun() {
		cout << "injectionRun\n";
		for(int i=1; i<32; i*=2) {
			flow->run();
			if(partBin.full()) {
				partBin.advanceBin();
			}
			vector<Stock>::iterator it = stockBin.begin();	// For each stock bin, replace if empty.
			for(; it!=stockBin.end(); it++) {
				if(it->empty()) {
					it->refill();
				}
			}
		}
	}
};
class MultiColor	: public Order {	// Different colors in different bins.
public:
	MultiColor(strategy::FlowStrategy* flow) : Order(new adapter::Mold("car"), flow) {}
public:
	void injectionRun() {}
};
class MixedColor	: public Order {	// Mixed colors in same bins.
public:
	MixedColor(strategy::FlowStrategy* flow) : Order(new adapter::Mold("car"), flow) {}
public:
	void injectionRun() {
	}
};

}

namespace factory_method { // Creating or fetching the mold.

class Mold {};
class DuckMold : public Mold {};
class CarMold  : public Mold {};
class HeroMold : public Mold {};
// Spec add:
class DinoMold : public Mold {};

class CreateMold {};
class CreateDuckMold : public CreateMold {};
class CreateCarMold  : public CreateMold {};
class CreateHeroMold : public CreateMold {};
// Spec add:
class CreateDinoMold : public CreateMold {};

}

namespace decorators { // Tags and packaging.

class Tag {};
class NullTag	   : public Tag {};
class TagDecorator : public Tag {};
class ModelNumber	: public TagDecorator {};
class CountryMadeIn : public TagDecorator {};
class DateMade		: public TagDecorator {};
// Spec add.
class IncrementCounter : public TagDecorator {};

class Packaging {};
class Bulk				 : public Packaging {};
class PackagingDecorator : public Packaging {};
class ShrinkWrap : public PackagingDecorator {};
class HardPack	 : public PackagingDecorator {};
// Spec add.
class ZipLock	 : public PackagingDecorator {};
}

namespace observer { // When the order processing decides on a color change, the part & color bins have to be notified.
}

namespace bridge { // Milling machines used to create the molds: Raster versus Vector, shape primitives.
}

namespace abstract_factory { // The specific injection molding machine.

/* IJM_Machine_100
 * 	 Requires 1 cavity molds
 * 	 Requires linear conveyer belt
 * IJM_Machine_400
 * 	 Requires 2 or 4 cavity molds
 * 	 Requires Y-split conveyer belt
 */

class IJM {};
class Machine_100 : public IJM {};
// Spec add.
class Machine_400 : public IJM {};

class InjectionMold {};
class Cavity_1 : public InjectionMold {};
// Spec add.
class Cavity_4 : public InjectionMold {};

class Conveyer {};
class LinearBelt : public Conveyer {};
// Spec add.
class YSplitBelt : public Conveyer {};

// Spec add is the IJM_Machine_400, a 4 cavity capable IJMM, with a Y-split conveyer belt.

}

// Specs are encoded as key/value pairs to allow additions that won't break developing code.
struct Specs {
	const char*	key;
	const char*	val;
};

struct Order {
	enum { MaxSpecs = 10 };
	uint	orderNumber;
	Specs	spec[MaxSpecs];	// To allow initialization by struct rather than ctor.
	map<const char*, string> specs;
};

void readOrders(vector<Order>& orders) {
	int i = 0;
	Order order[] = { // First spec must be num, end of specs indicated by two blank strings {"",""}, or {"end",""}.
		{++i, {{"orderNum",""},
				{"mold", "duck"},
				{"moldLoc", "inventory"},
				{"metal", "steel"},
				{"size", "50"},
				{"",""} }},
		{++i, {{"orderNum",""},
				{"mold", "car"},
				{"moldLoc", "mill"},
				{"metal", "steel"},
				{"size","100"},
				{"plastic","ABS"},
				{"",""} }},
		{++i, {{"orderNum",""},
				{"mold", "hero"},
				{"moldLoc", "purchase"},
				{"metal", "steel"},
				{"size","500"},
				{"end",""} }},
	};

	const char* key = 0;
	const char* val = 0;
	char		value[10+1] = "";
	for(size_t i=0; i<sizeof(order)/sizeof(Order); i++) {	// For every order...
		for(int j=0; j<Order::MaxSpecs; j++) {					// Retrieve every spec...
			key = order[i].spec[j].key;
			if(strlen(key) == 0 || !strcmp(key, "end"))				// No more specs.
				break;
			if(j > 0)
				val = order[i].spec[j].val;
			else {													// Treat 1st spec (must be order number) specially.
				sprintf(value, "%03d", i+1);
				val = value;
			}
			order[i].specs[key] = val;								// Store specs in map.
		}
		orders.push_back(order[i]);								// Accumulate orders.
	}
}

void printOrderElement(vector<Order>::iterator it, const char* str) {
	char padding[80+1];
	int size = 10 - strlen(str);
	sprintf(padding, "%*c", size, ' ');
	cout << "   " << str << padding << " = " << it->specs[str] << "\n";
	//   mold       = hero
}

void demo() {
	cout << "<< final solution >>\n";

	vector<Order> orders;
	readOrders(orders);

	vector<Order>::iterator it = orders.begin();
	const char* indent = "   ";
	for(; it!=orders.end(); it++) {
		cout << it->orderNumber << ":\n";
		printOrderElement(it, "orderNum");
		printOrderElement(it, "mold");
		printOrderElement(it, "moldLoc");
		printOrderElement(it, "metal");
		printOrderElement(it, "size");
		printOrderElement(it, "plastic");
		printOrderElement(it, "seam");

		cout << indent << "----------\n";
		string plastic = it->specs["plastic"].size() ? it->specs["plastic"] : "poly";
		cout << indent << "plastic  = " << plastic << "\n";
		cout << endl;
	}

	template_method::Order* order = new template_method::SingleColor(new strategy::ABS);
	order->run();

}

}

#endif /* FINAL_H_ */
