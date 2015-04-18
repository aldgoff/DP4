/*
 * finalDtoO.h
 *
 *  Created on: Apr 17, 2015
 *      Author: aldgoff
 *
 *  Project: Intro to Design Patterns Pilot class.
 *  Practice Part I of the final:
 *    replace with finalDesign.h, then hand code upto finalOriginal.h.
 */

#ifndef DP4_SRC_D_TO_O_FINAL_H_
#define DP4_SRC_D_TO_O_FINAL_H_

namespace final_d_to_o_file {

const bool on = true;
#define DTOR(x) if(on) { cout << x; }

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

class ProcessOrder_TM_4 {
public:
	ProcessOrder_TM_4() {}
	virtual ~ProcessOrder_TM_4() { DTOR("~ProcessOrder_TM_4\n"); }
private:
	void setupInjectionLine(map<string, string>& order) {
		cout << "  Setup injection line:\n";
	}
	void getMold(map<string, string>& order) {
		cout << "    Get mold:\n";
	}
	void insertTags(map<string, string>& order) {
		cout << "    Insert tags:\n";
	}
	void loadAdditives(map<string, string>& order) {
		cout << "    Load additives:\n";
	}
protected:
	virtual void injectionCycle(map<string, string>& order) {
		cout << "    Injection cycle - no plastic specified:\n";
	}
private:
	void cleanMold(map<string, string>& order) {
		cout << "    Clean mold:\n";
	}
public:
	void run(map<string, string>& order) {
		setupInjectionLine(order);
		cout << "  Process order.\n";
		getMold(order);
		insertTags(order);
		loadAdditives(order);
		injectionCycle(order);
		cleanMold(order);
	}
};
class ABS : public ProcessOrder_TM_4 {
public:
	ABS() {}
	~ABS() { DTOR("~ABS\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		cout << "    Cycle IJM for ABS <size> times.\n";
	}
};
class Polypropylene : public ProcessOrder_TM_4 {
public:
	Polypropylene() {}
	~Polypropylene() { DTOR("~Polypropylene\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		cout << "    Cycle IJM for Polypropylene <size> times.\n";
	}
};
class Polyethelene : public ProcessOrder_TM_4 {
public:
	Polyethelene() {}
	~Polyethelene() { DTOR("~Polyethelene\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		cout << "    Cycle IJM for Polyethelene <size> times.\n";
	}
};
class PET : public ProcessOrder_TM_4 {
public:
	PET() {}
	~PET() { DTOR("~PET\n"); }
public:
	void injectionCycle(map<string, string>& order) {
		cout << "    Cycle IJM for PET <size> times.\n";
		cout << "      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject.\n";

	}
};
// Seam point - add another plastic.

}

void process(map<string, string> order) {
	using namespace template_method;

	ProcessOrder_TM_4* processOrder = 0;

	if(		order["plastic"] == "ABS")				processOrder = new ABS;
	else if(order["plastic"] == "Polypropylene")	processOrder = new Polypropylene;
	else if(order["plastic"] == "Polyethelene")		processOrder = new Polyethelene;
	else if(order["plastic"] == "PET")				processOrder = new PET;
	// Seam point - add another plastic.

	else {											// Default is ABS.
		cout << "  <>Unknown plastic |" << order["plastic"] << "|";
		cout << " defaulting to ABS.\n";
		order["plastic"] = "ABS";
		processOrder = new ProcessOrder_TM_4;
	}

	processOrder->run(order);

	delete processOrder;
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
	cout << "<<< final design to original >>>\n";

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}
}

}

#endif /* DP4_SRC_D_TO_O_FINAL_H_ */
