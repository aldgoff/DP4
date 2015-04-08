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
 *   4 - Template Method: order processing
 *   5 - Factory Method: packaging (domain: order)
 *   6 - Decorator: tags, additives
 *   7 - Observer: bins(Subject) (conveyers & IJM pause on full)
 *   8 - ChainOfR: mold location (inventory, mill, borrow, purchase)
 *   9 - Bridge: milling
 *  10 - Abstract Factory: IJM_X, mold(metal, cavities), conveyer belt, bins (domain: size)
 */

namespace final_solution_file {

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
	unsigned cavities() { return m_cavities; }
};
class Aluminum : public Mold_AF {
public:
	Aluminum(unsigned cavities=0) : Mold_AF(cavities) {}
public:
	void id() { cout << "    Aluminum\n"; }
};
class Steel : public Mold_AF {
public:
	Steel(unsigned cavities=0) : Mold_AF(cavities) {}
public:
	void id() { cout << "    Steel\n"; }
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
	virtual ConveyerBelt_AF* createPackager(const map<string, string>& order) {
		cout << "    create Packager base\n";
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
	ConveyerBelt_AF* createPackager(const map<string, string>& order) {
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
	ConveyerBelt_AF* createPackager(const map<string, string>& order) {
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
	ConveyerBelt_AF* createPackager(const map<string, string>& order) {
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
	ConveyerBelt_AF* createPackager(const map<string, string>& order) {
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


class ProcessOrder_TM_4 {
	void getMold() {
		cout << "    Get mold.\n";
	}
	virtual void injectionRun() {
		cout << "    Example injection run - base class.\n";
	}
	void cleanMold() {
		cout << "    Clean mold.\n";
	}
public:
	virtual ~ProcessOrder_TM_4() {}
	void run(map<string, string> order) {
		cout << "-- ProcessEachOrder_TemplateMethod --\n";
		cout << "Setup via Abstract Factory\n";
		getMold();
		injectionRun();
		cleanMold();
	}
};

class GetMold_CofR_8 {};
class Mill_B_9 {};
	class Cavity_Abs_B {};
	class CuttingImp_B {};
class Mill_F_3 {};				// New specs (laser).
class Tags_D_6 {};				// New specs.
class Packaging_FM_5 {};		// New specs.
class Additives_D_6 {};			// New specs.
class PauseOnFull_O_7 {};
class InjectionCycle_S_1 {};	// New specs (plastics).
class Cleaning_A_2 {};			// New specs (plastics).



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
	map<string, string>::iterator it = order.begin();

	Setup_AF_10* injectionLine = Setup_AF_10::createInjectionLine(order);

	IJM_AF*				ijm		= injectionLine->createIJM(order);
	Mold_AF*			mold	= injectionLine->createMold(order);		// CofR.
	ConveyerBelt_AF*	belt	= injectionLine->createPackager(order);	// Factory Method.
	PackageBin_AF*		bin		= injectionLine->createBin(order);

	ijm->id();
	mold->id();
	cout << "    " << mold->cavities() << "\n";
	belt->id();
	bin->id();

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
