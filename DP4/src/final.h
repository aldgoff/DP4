/*
 * final.h
 *
 *  Created on: May 17, 2014
 *      Author: aldgoff
 */

#ifndef FINAL_H_
#define FINAL_H_

/* Thoughts on the final exam.
 * Basic paradigm, it's a two week final.
 * Week 1, refactor code to implement an injection molding shop.
 * Week 2, the spec changes...
 * 	 New colors
 * 	 New plastics (and therefore new sequences, strategy pattern)
 * 	 New objects
 * 	 New packaging
 * 	 New finishes
 * 	 New textures (smooth, pebbled (sand blasted))
 * 	 Add aluminum
 * 	 Model numbers
 * If your refactoring of the existing procedural code into design pattern code in week 1 is sound,
 * the adding of the specs in week 2 should take only one hour.
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
 *
 * Week 1:
 *   Procedural code with input file of orders and output file of the runs.
 *   Run the procedural code on the orders and confirm you match the output.
 *   Refactor using design patterns and confirm you still match the output.
 * Week 2:
 *   New specs, new order file, and a new output file.
 *   Add code until you can process the new order file and match the new output file.
 *   Grade: A <= 1 hr, B <= 2 hrs, C <= 3 hrs, D <= 4 hrs, F > 4 hrs. A D is passing.
 */

#include "map"
#include "vector"
#include "string"
using namespace std;

namespace final {

namespace observer { // When the order processing decides on a color change, the part & color bins have to be notified.
}

namespace bridge { // Milling machines used to create the molds: Raster versus Vector, shape primitives.
}

namespace facade { // Milling machine control, very complicated, only need two methods say.
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

namespace adapter { // The mold cleaning technique.

class Mold {};

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

class PetCleanup {
public:
	void carbonize(Mold* mold) { // Use only on stainless steel.
		cout << "Heat to 695 C.\n";
	}
	void purify(Mold* mold) {	// Use only on aluminum.
		cout << "Rinse with soap and water.\n";
		cout << "Dry.\n";
	}
};

class CleanPlastic {
public:
	virtual void clean(int moldType) {}
	virtual ~CleanPlastic() {}
};
class ABS			: public CleanPlastic {};
class Polypropylene	: public CleanPlastic {};
class Polyethylene	: public CleanPlastic {};
class PET			: public CleanPlastic {};
// Spec add.
class Styrene		: public CleanPlastic {};
class Nylon66		: public CleanPlastic {};

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

namespace abstract_factory { // The specific injection molding machine.

/* IJM_Machine_100
 * 	 Requires 1 cavity molds
 * 	 Requires linear conveyer belt
 * IJM_Machine_400
 * 	 Requires 4 cavity molds
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
	strategy::FlowStrategy*	flow;
	vector<Stock>	stockBin;
	PartBin			partBin;
public:
	Order(strategy::FlowStrategy*flow) : flow(flow) {}
	virtual ~Order() {}
public:
	void getMold_FactoryMethod() {
		cout << "getMold_FactoryMethod\n";
	}
	void installMold() {
		cout << "installMold\n";
		//	hookupConnections();
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
	SingleColor(strategy::FlowStrategy* flow) : Order(flow) {}
public:
	void injectionRun() {
		for(int i=0; i<5; i++) {
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
	MultiColor(strategy::FlowStrategy* flow) : Order(flow) {}
public:
	void injectionRun() {}
};
class MixedColor	: public Order {	// Mixed colors in same bins.
public:
	MixedColor(strategy::FlowStrategy* flow) : Order(flow) {}
public:
	void injectionRun() {
	}
};

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
		{++i, {{"num",""}, {"size", "50"}, {"",""} }},
		{++i, {{"num",""}, {"size","100"}, {"plastic","ABS"}, {"",""} }},
		{++i, {{"num",""}, {"size","500"}, {"end",""} }},
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

void demo() {
	cout << "<< final solution >>\n";

	vector<Order> orders;
	readOrders(orders);

	vector<Order>::iterator it = orders.begin();
	const char* indent = "   ";
	for(; it!=orders.end(); it++) {
		cout << it->orderNumber << ":\n";
		cout << indent << "orderNum = " << it->specs["num"] 	<< "\n";
		cout << indent << "size     = " << it->specs["size"]    << "\n";
		cout << indent << "plastic  = " << it->specs["plastic"] << "\n";
		cout << indent << "seam     = " << it->specs["seam"]    << "\n";
		cout << indent << "----------\n";
		cout << indent << "Car mold\n";
		string plastic = it->specs["plastic"].size() ? it->specs["plastic"] : "poly";
		cout << indent << "plastic  = " << plastic << "\n";
		cout << indent << "Steel\n";
		cout << endl;
	}

	template_method::Order* order = new template_method::SingleColor(new strategy::ABS);
	order->run();

}

}

#endif /* FINAL_H_ */
