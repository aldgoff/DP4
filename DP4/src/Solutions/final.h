/*
 * Solutions/final.h
 *
 *  Created on: Apr 6, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_SOLUTIONS_FINAL_H_
#define DP4_SRC_SOLUTIONS_FINAL_H_

namespace design_patterns_chart {}
/* Design Patterns Chart
 *   1 - Strategy: injection cycle (domain: plastic)
 *   2 - Adapter: cleaning mold (domains: plastic, metal)
 *   3 - Facade: milling mold
 * x 4 - Template Method: order processing
 *   5 - Factory Method: packaging (domain: order)
 *   6 - Decorator: tags, additives
 *   7 - Observer: bins(Subject) (conveyers & IJM pause on full)
 * x 8 - ChainOfR: mold location (inventory, mill, borrow, purchase)
 * x 9 - Bridge: milling
 * x10 - Abstract Factory: IJM_X, mold(metal, cavities), conveyer belt, bins (domain: size)
 */

namespace final_solution_file {

namespace abstract_factory {

class IJM_AF {
public: virtual ~IJM_AF() {}
	virtual void id() { cout << "    IJM_AF base\n"; }
};
class IJM_100 : public IJM_AF {
public:
	void id() { cout << "    IJM_100\n"; }
};
class IJM_200 : public IJM_AF {
public:
	void id() { cout << "    IJM_200\n"; }
};
// Seam point - add another InJection Molding machine.
class IJM_400 : public IJM_AF {
public:
	void id() { cout << "    IJM_400\n"; }
};

class Mold_AF {
	unsigned m_cavities;
public:
	Mold_AF(unsigned cavities=0) : m_cavities(cavities) {}
public: virtual ~Mold_AF() {}
	virtual void id() { cout << "    Mold_AF base\n"; }
	virtual string metal() { return "unobtainium"; }
	unsigned cavities() { return m_cavities; }
};
class Aluminum : public Mold_AF {
public:
	Aluminum(unsigned cavities=0) : Mold_AF(cavities) {}
public:
	void id() { cout << "    Aluminum(" << cavities() << ")\n"; }
	string metal() { return "aluminum"; }
};
class Steel : public Mold_AF {
public:
	Steel(unsigned cavities=0) : Mold_AF(cavities) {}
public:
	void id() { cout << "    Steel(" << cavities() << ")\n"; }
	string metal() { return "steel"; }
};

class ConveyerBelt_AF {
public: virtual ~ConveyerBelt_AF() {}
	virtual void id() { cout << "    ConveyerBelt_AF base\n"; }
};
class LinearBelt : public ConveyerBelt_AF {
public:
	virtual void id() { cout << "    Linear conveyer belt\n"; }
};
class YSplitBelt : public ConveyerBelt_AF {
public:
	virtual void id() { cout << "    Y-Split conveyer belt\n"; }
};
// Seam point - add another conveyer belt.
class VLevelBelt : public ConveyerBelt_AF {
public:
	virtual void id() { cout << "    V-Level conveyer belt\n"; }
};

class PackageBin_AF {
public: virtual ~PackageBin_AF() {}
	virtual void id() { cout << "    PackageBin_AF base\n"; }
};
class CardboardBox : public PackageBin_AF {
public:
	virtual void id() { cout << "    CardboardBox\n"; }
};
class PallotBox : public PackageBin_AF {
public:
	virtual void id() { cout << "    PallotBox\n"; }
};
// Seam point - add another conveyer belt.
class Crate : public PackageBin_AF {
public:
	virtual void id() { cout << "    Crate\n"; }
};

class Setup_AF_10 {	// New specs (size).
public:
	virtual ~Setup_AF_10() {}
	static Setup_AF_10* createInjectionLine(map<string, string> order);
public:
	virtual IJM_AF* createIJM(const map<string, string>& order) {
		cout << "    create IJM base\n";
		return new IJM_AF;
	}
	virtual Mold_AF* createMold(const map<string, string>& order) {
		cout << "    create Mold base\n";
		return new Mold_AF;
	}
	virtual ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		cout << "    create Belt base\n";
		return new ConveyerBelt_AF;
	}
	virtual PackageBin_AF* createBin(const map<string, string>& order) {
		cout << "    create Bin base\n";
		return new PackageBin_AF;
	}
};
class SmallOrder : public Setup_AF_10 {
public:
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_100;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Aluminum(1);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new LinearBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new CardboardBox;
	}
};
class MediumOrder : public Setup_AF_10 {
public:
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_200;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(1);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new LinearBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new PallotBox;
	}
};
// Seam point - add larger orders.
class LargeOrder : public Setup_AF_10 {
public:
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_400;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(2);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new YSplitBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new Crate;
	}
};
class HugeOrder : public Setup_AF_10 {
public:
	IJM_AF* createIJM(const map<string, string>& order) {
		return new IJM_400;
	}
	Mold_AF* createMold(const map<string, string>& order) {
		return new Steel(4);
	}
	ConveyerBelt_AF* createBelt(const map<string, string>& order) {
		return new VLevelBelt;
	}
	PackageBin_AF* createBin(const map<string, string>& order) {
		return new Crate;
	}
};

Setup_AF_10* Setup_AF_10::createInjectionLine(map<string, string> order) {
	unsigned size = atoi(order["size"].c_str());

	if(size <= 10000)	return new SmallOrder;
	else if(size <= 50000)	return new MediumOrder;
	// Seam point - add larger orders.
	else if(size <= 100000)	return new LargeOrder;
	else if(size <= 200000)	return new HugeOrder;

	return new Setup_AF_10;
}

}

namespace bridge {	// Done - depends on shape and metal.

class Platform {
public:
	static Platform* getPlatform(map<string,string> order);
public: virtual ~Platform() {}
	virtual string name() { return "base"; }
	virtual string drill()=0;
	virtual string cut()=0;
	virtual string grind()=0;
};
class HighCarbon : public Platform {	// Aluminum.
public:
	string name() { return "HighCarbon"; }
	string drill() { return "drill"; }
	string cut() { return "cut"; }
	string grind() { return "high speed grind"; }
};
class DiamondTipped : public Platform {	// Steel.
public:
	string name() { return "DiamondTipped"; }
	string drill() { return "precision drill"; }
	string cut() { return "oil cooled cut"; }
	string grind() { return "cartoid grind"; }
};
// Seam Point - add another platform.
class Carbide : public Platform {		// Brass.
public:
	string name() { return "Carbide"; }
	string drill() { return "high speed drill"; }
	string cut() { return "cross cut"; }
	string grind() { return "layer grind"; }
};

Platform* Platform::getPlatform(map<string,string> order) {
	string metal = order["metal"];
	if(metal == "aluminum")		return new HighCarbon;
	else if(metal == "steel")	return new DiamondTipped;
	// Seam Point - add another platform.
	else if(metal == "brass")	return new Carbide;

	return new HighCarbon;	// Default.
}

class Shape {
protected:
	Platform* platform;
public:
	Shape(Platform* platform) : platform(platform) {}
	virtual ~Shape() {}
public:
	static Shape* getShape(map<string,string> order);
public:
	virtual void mill(map<string,string>& order) {
		cout << "    Unknown shape " << order["mold"] << ".\n";
	}
};
class Duck : public Shape {
	string	name;
public:
	Duck(Platform* platform) : Shape(platform), name("duck") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "    Using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};
class Car : public Shape {
	string	name;
public:
	Car(Platform* platform) : Shape(platform), name("car") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "    Using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};
class Hero : public Shape {
	string	name;
public:
	Hero(Platform* platform) : Shape(platform), name("hero") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "    Using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};
// Seam Point - add another shape.
class Dino : public Shape {
	string	name;
public:
	Dino(Platform* platform) : Shape(platform), name("dino") {};
	void mill(map<string,string>& order) {	// Simulated specific steps to mill shape.
		cout << "    Using " << platform->name() << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", and ";
		cout << platform->grind() << ") ";
		cout << "to mill " << order["metal"] << " block into ";
		cout << order["cavities"] << " " << name << " shapes ";
		cout << "with " << order["finish"] << " finish.\n";
	}
};

Shape* Shape::getShape(map<string,string> order) {
	Platform* platform = Platform::getPlatform(order);
	string mold = order["mold"];

	if(mold == "duck")		return new Duck(platform);
	else if(mold == "car")	return new Car(platform);
	else if(mold == "hero")	return new Hero(platform);
	// Seam Point - add another shape.
	else if(mold == "dino")	return new Dino(platform);

	return new Shape(platform);	// Reports shape unknown.
}

}

namespace chain_of_resp {	// Done - depends on mold location.

class GetMold {
protected:
	GetMold* successor;
public:
	GetMold(GetMold* successor=0) : successor(successor) {};
	virtual ~GetMold() {}
public:
	virtual void from(map<string, string>& order) {
		string place = order["moldLoc"];
		string mold = order["mold"];
		cout << "  Can't find place " << place;
		cout << " to get " << mold << " mold from.\n";
	}
};
class Inventory : public GetMold {
public:
	Inventory(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "inventory")
			cout << "    Pull " << order["mold"] << " mold from inventory.\n";
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};
class Mill : public GetMold {
public:
	Mill(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		using namespace bridge;
		string place = order["moldLoc"];
		if(place == "mill") {
			cout << "    Create " << order["mold"] << " mold from mill ";
			cout << "with " << order["cavities"] << " cavities.\n";
			Shape* shape = Shape::getShape(order);
			shape->mill(order);
			}
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};
// Seam points - add another mold source.
class SisterCompany : public GetMold {
public:
	SisterCompany(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "sisterCompany")
			cout << "    Borrow " << order["mold"] << " mold from sister company.\n";
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};
class Purchase : public GetMold {
public:
	Purchase(GetMold* successor=0) : GetMold(successor) {};
public:
	void from(map<string, string>& order) {
		string place = order["moldLoc"];
		if(place == "purchase")
			cout << "    Acquire " << order["mold"] << " mold via purchase.\n";
		else if(successor != 0)
			successor->from(order);
		else
			GetMold::from(order);	// Oops.
	}
};

}

namespace template_method {

class ProcessOrder_TM_4 {
	void setupLine(map<string, string>& order) {
		cout << "  Setup injection line via Abstract Factory\n";
		using namespace abstract_factory;
		Setup_AF_10* injectionLine = Setup_AF_10::createInjectionLine(order);

		IJM_AF*				ijm		= injectionLine->createIJM(order);
		Mold_AF*			mold	= injectionLine->createMold(order);		// CofR.
		ConveyerBelt_AF*	belt	= injectionLine->createBelt(order);	// Factory Method.
		PackageBin_AF*		bin		= injectionLine->createBin(order);

		ijm->id();
		mold->id();
		order["metal"] = mold->metal();
		char str[80];
		sprintf(str, "%d", mold->cavities());
		order["cavities"] = str;

		belt->id();
		bin->id();
	}
	void getMold(map<string, string>& order) {
		using namespace chain_of_resp;
		GetMold* getMold =
			new Inventory(
			new Mill(
			new Purchase(
			new SisterCompany(
			new GetMold(
		)))));
		getMold->from(order);
	}
	void insertTags() {
		cout << "    Insert tags via decorator pattern.\n";
	}
	void loadAdditiveBins() {
		cout << "    Load additive bins via decorator pattern.\n";
	}
	virtual void injectionRun() {
		cout << "    Example injection run - base class.\n";
	}
	void cleanMold() {
		cout << "    Clean mold.\n";
	}
public:
	virtual ~ProcessOrder_TM_4() {}
	void run(map<string, string>& order) {
		setupLine(order);
		cout << "  Run order via TemplateMethod\n";
		getMold(order);
		insertTags();
		loadAdditiveBins();
		injectionRun();
		cleanMold();
	}
};
class ABS : public ProcessOrder_TM_4 {
public:
	void injectionRun() {
		cout << "    Example ABS injection run.\n";
	}
};
class Polypropylene : public ProcessOrder_TM_4 {
public:
	void injectionRun() {
		cout << "    Example Polypropylene injection run.\n";
	}
};
class Polyethelene : public ProcessOrder_TM_4 {
public:
	void injectionRun() {
		cout << "    Example Polyethelene injection run.\n";
	}
};
class PET : public ProcessOrder_TM_4 {
public:
	void injectionRun() {
		cout << "    Example PET injection run.\n";
	}
};

}

namespace patterns_todo {

class Mill_F_3 {};				// New specs (laser).
class Tags_D_6 {};				// New specs.
class Packaging_FM_5 {};		// New specs.
class Additives_D_6 {};			// New specs.
class PauseOnFull_O_7 {};
class InjectionCycle_S_1 {};	// New specs (plastics).
class Cleaning_A_2 {};			// New specs (plastics).

}

using namespace abstract_factory;
using namespace chain_of_resp;
using namespace template_method;

pair<string, string> parse(string line) {
	char key[83];
	char val[83];

	sscanf(line.c_str(), "%s", key);
	char* equalSign = strchr(line.c_str(), '=');
	if(equalSign) {
		sscanf(++equalSign, "%s", val);
	}

	return make_pair(key, val);
}

void process(map<string, string> order) {
	ProcessOrder_TM_4* processOrder = 0;

	if(order["plastic"] == "ABS")	processOrder = new ABS;
	else if(order["plastic"] == "Polypropylene")	processOrder = new Polypropylene;
	else if(order["plastic"] == "Polyethelene")	processOrder = new Polyethelene;
	else if(order["plastic"] == "PET")	processOrder = new PET;
	else {
		processOrder = new ProcessOrder_TM_4;	// Default process
	}

	processOrder->run(order);

//	cout << "  If order <= 10,000, IJM_100, use aluminum, single cavity, linear belt.\n";
//	cout << "  If order <= 50,000, IJM_200, use steel, single cavity, linear belt.\n";
//	cout << "  If order <= 100,000, IJM_400, use steel, 2-cavity, y-split belt.\n";
//	cout << "  If order <= 200,000, IJM_400, use steel, 4-cavity, y-split belt.\n";
}

void reveal(map<string, string> order) {
	map<string, string>::iterator it = order.begin();
	for(; it!=order.end(); it++) {
		cout << "[" << it->first << "] = " << it->second << "\n";
	}
	cout << "order[orderNum] = " << order["orderNum"] << "\n";
	cout << "order[mold] = " << order["mold"] << "\n";
	cout << "order[moldLoc] = " << order["moldLoc"] << "\n";
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


#endif /* DP4_SRC_SOLUTIONS_FINAL_H_ */
