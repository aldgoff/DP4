/*
 * finalOutline.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */

#ifndef DP4_SRC_OUTLINE_FINAL_H_
#define DP4_SRC_OUTLINE_FINAL_H_

namespace final_outline_file {

const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }

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

class Adapter_2 {
public:
	Adapter_2() {}
	virtual ~Adapter_2() { DTOR("~Adapter_2\n"); }
public:
	virtual string steps() { return "cleaning steps"; }
};
// Seam point - add another cleaning interface.

}

namespace strategy {		// DP 1.

class Strategy_1 {
public:
	Strategy_1() {}
	virtual ~Strategy_1() { DTOR("~Strategy_1\n"); }
public:
	virtual void cycle() {
		cout << "      Close - heat to <temp> - inject at <psi> PSI";
		cout << " - cool to <temp> - separate - <technique> eject.\n";
	}
};
// Seam point - add another cycle algorithm.

}

namespace observer {		// DP 7.

// Seam point - add another listener.

}

namespace abstract_factory {// DP 10.

class IJM_AF {
public:
	IJM_AF() {}
	virtual ~IJM_AF() { DTOR("~IJM_AF\n"); }
};
class Mold_AF {
public:
	Mold_AF() {}
	virtual ~Mold_AF() { DTOR("~Mold_AF\n"); }
};
class ConveyerBelt_AF {
public:
	ConveyerBelt_AF() {}
	virtual ~ConveyerBelt_AF() { DTOR("~ConveyerBelt_AF\n"); }
};
class OutputBin_AF {
public:
	OutputBin_AF() {}
	virtual ~OutputBin_AF() { DTOR("~OutputBin_AF\n"); }
};
class AbstractFactory_10 {
public:
	AbstractFactory_10() {}
	virtual ~AbstractFactory_10() { DTOR("~AbstractFactory_10 "); }
public:
	virtual IJM_AF* createIJM() {
		return new IJM_AF;
	}
	virtual Mold_AF* createMold() {
		return new Mold_AF;
	}
	virtual ConveyerBelt_AF* createConveyerBelt() {
		return new ConveyerBelt_AF;
	}
	virtual OutputBin_AF* createOutputBin() {
		return new OutputBin_AF;
	}
};
class InjectionLine_AF {
	AbstractFactory_10* factory;
	IJM_AF*				ijm;
	Mold_AF*			mold;
	ConveyerBelt_AF*	belt;
	OutputBin_AF*		bin;
public:
	InjectionLine_AF() :
		factory(0),
		ijm(0),
		mold(0),
		belt(0),
		bin(0)
	{}
	virtual ~InjectionLine_AF() {
		delete belt;
		delete mold;
		delete ijm;
		delete bin;
		delete factory;
		DTOR("~InjectionLine_AF\n");
	}
public:
	virtual AbstractFactory_10* buildFactory() {
		return new AbstractFactory_10;
	}
public:
	void createLine(map<string,string>& order) {
		factory = buildFactory();

		ijm	 = factory->createIJM();
		mold = factory->createMold();
		belt = factory->createConveyerBelt();
		bin	 = factory->createOutputBin();
	}
public:
	static InjectionLine_AF* determineInjectionLine(map<string,string>& order);
};

// Seam point - add another injection line family.

InjectionLine_AF* InjectionLine_AF::determineInjectionLine(map<string,string>& order) {
	// Seam point - add another injection line family.

	return new InjectionLine_AF;
}

}

namespace bridge {			// DP 9.

// Seam Point - add another implementation.

// Seam Point - add another abstraction.

}

namespace chain_of_resp {	// DP 8.

// Seam points - add another responder.

}

namespace decorator {		// DP 6.

class Tags_D_6 {
public:
	Tags_D_6() {}
	virtual ~Tags_D_6() { cout << "~Tags_D_6\n"; }
public:
	virtual unsigned width() {
		return 0;
	}
	virtual string list() {
		return "";
	}
public:	// Cavity only.
	virtual void setBlankWidth(unsigned tagsWdith_mm) {}
	virtual unsigned getBlankWidth() { return 0; }
};
class Cavity : public Tags_D_6 {
public:
	const unsigned totalWidth_mm;
	unsigned blankWidth_mm;
public:
	Cavity()
	  : totalWidth_mm(20), blankWidth_mm(0)
	{}
	virtual ~Cavity() { cout << "~Cavity "; }
public:
	virtual unsigned width() {
		return 0;
	}
	virtual string list() {
		return "";
	}
	virtual void setBlankWidth(unsigned tagsWdith_mm) {
		blankWidth_mm = totalWidth_mm - tagsWdith_mm;
	}
	virtual unsigned getBlankWidth() {
		return blankWidth_mm;
	}
};
class Tag : public Tags_D_6 {
protected:
	Tags_D_6* option;
public:
	Tag(Tags_D_6* option) : option(option) {}
	virtual ~Tag() { cout << "~Tag\n"; delete option; }
public:
	virtual unsigned width() {
		return option->width() + 0;	// 2 mm.
	}
	virtual string list() {
		return option->list() + "";	// ModelNumber.
	}
public:
	static Tags_D_6* insertTags(const string& list, Tags_D_6* cavity);
};
// Seam point - add another tag option.

Tags_D_6* Tag::insertTags(const string& list, Tags_D_6* cavity) {
	char tag[80] = "";
	const char* remainingTokens = list.c_str();

	for(;;) {
		if(!sscanf(remainingTokens, "%s", tag))
			break;

//		if(		!strcmp(tag,  "<tag1>"))		cavity = new <Tag1>;
//		else if(!strcmp(tag,  "<tag2>"))		cavity = new <Tag2>;
		// Seam point - add another tag option.

		else {
			cout << "Ignoring unknown tag " << tag << ".\n";
		}

		remainingTokens = strchr(remainingTokens+1, ' ');
	}

	return cavity;
}

class Plastic_D_6 {
protected:
	unsigned volume_cc;
public:
	Plastic_D_6(unsigned volume_cc=0) : volume_cc(volume_cc) {}
	virtual ~Plastic_D_6() { DTOR("~Plastic_D_6\n"); }
public:
	virtual unsigned volume() {
		return 0;
	}
	virtual string nameAndVol() {
		return "";
	}
public:	// Color class only.
	void setVolume(unsigned volume_cc) {
		this->volume_cc = volume_cc;
	}
};
class Color : public Plastic_D_6 {
	const string color;
public:
	Color(const string& color) : color(color) {}
	virtual ~Color() { DTOR("~Color "); }
public:
	virtual unsigned volume() {
		return volume_cc;
	}
	virtual string nameAndVol() {
		char str[80];
		sprintf(str, "(%d) ", volume_cc);
		return(color + str);
	}
};
class Additive : public Plastic_D_6 {
protected:
	Plastic_D_6* option;
public:
	Additive(Plastic_D_6* option, unsigned volume_cc=0)
		: Plastic_D_6(volume_cc), option(option) {}
	virtual ~Additive() { cout << "~Additive\n"; delete option; }
public:
	virtual unsigned volume() {
		return option->volume() + volume_cc;
	}
	virtual string nameAndVol() {
		char str[80];
		sprintf(str, "(%d) ", volume_cc);
		return(option->nameAndVol() + str);
	}
public:
	static Plastic_D_6*	addAdditives(map<string,string>& order, Plastic_D_6* color);
};
// Seam point - add another additive option.

Plastic_D_6* Additive::addAdditives(map<string,string>& order, Plastic_D_6* color) {
	if(order.find("Additive") != order.end()) {
		color = new Additive(color, atoi(order["Additive"].c_str()));
	}
	// Seam point - add another additive option.

	return color;
}

}

namespace factory_method {	// DP 5.

class Packager_FM_5 {
public:
	Packager_FM_5() {}
	virtual ~Packager_FM_5() { DTOR("~Packager_FM_5\n"); }
public:
	static Packager_FM_5* createPackager(map<string, string>& order);
};
// Seam point - add another Packager class.

Packager_FM_5* Packager_FM_5::createPackager(map<string, string>& order) {
	// Seam point - add another Packager class.

	return new Packager_FM_5;
}

}

namespace template_method {	// DP 4.

using namespace abstract_factory;
using namespace factory_method;
using namespace strategy;
using namespace adapter;
using namespace decorator;

class ProcessOrder_TM_4 {
	InjectionLine_AF*	injectionLine;
	Packager_FM_5*		packager;
	Strategy_1*			algorithm;
	Adapter_2*			cleaning;
	Tags_D_6*			cavity;
	Plastic_D_6*		color;
public:
	ProcessOrder_TM_4() :
		injectionLine(0),
		packager(0),
		algorithm(0),
		cleaning(0),
		cavity(0),
		color(0)
	{}
	virtual ~ProcessOrder_TM_4() {	// Reverse order from initialization.
		delete color;
		delete cavity;
		delete cleaning;
		delete algorithm;
		delete packager;
		delete injectionLine;
		DTOR("~ProcessOrder_TM_4\n");
	}
private:
	void setupInjectionLine(map<string, string>& order) {
		injectionLine = InjectionLine_AF::determineInjectionLine(order);
		injectionLine->createLine(order);

		packager = Packager_FM_5::createPackager(order);

		cout << "  Setup <DerivedOrder> injection line";
		cout << " for <size> run with <Packager> packager:\n";

		cout << "    <IJM> - <Metal>(<cavities>)";
		cout << " - <Type> conveyer belt - <OutputBin>\n";
	}
	void getMold(map<string, string>& order) {
		cout << "    Get <shape> mold from <somewhere>.\n";
	};
	void insertTags(map<string, string>& order) {
		cavity = new Cavity;

		string list = "";
		if(order.find("list") != order.end()) {
			list = order["list"];
			cavity = Tag::insertTags(list, cavity);
		}

		unsigned tagsWidth_mm = cavity->width();
		cavity->setBlankWidth(tagsWidth_mm);

		cout << "    Insert tags [" << cavity->list() << "]";
		cout << " of width " << tagsWidth_mm << "/";
		cout << cavity->getBlankWidth() << " mm.\n";

	};
	void loadAdditivies(map<string, string>& order) {
		color = new Color(order["color"]);

		color = Additive::addAdditives(order, color);
		unsigned shapeVol_cc = 10;	// Get actual volume from shape.
		color->setVolume(0.1*shapeVol_cc);

		unsigned total_cc = shapeVol_cc + color->volume();
		string list = color->nameAndVol();

		unsigned cavities = 2;	// Get cavities from mold.

		cout << "    Load plastic, color, and additive bins.\n";
		cout << "      Recipe: " << order["plastic"] << "(" << shapeVol_cc << ") ";
		cout << list;	// " <Additive1>(<vol>) <Additive2>(<vol>)";
		cout << "Total = " << cavities*total_cc << ".\n";
	};
protected:
	virtual void injectionCycle(map<string, string>& order) {
		cout << "    Cycle <IJM>:";
		cout << " for " << order["plastic"];
		cout << " " << order["size"] << " times.\n";
		algorithm = new Strategy_1;
		algorithm->cycle();
	};
private:
	void cleanMold(map<string, string>& order) {
		cleaning = new Adapter_2;
		cout << "    Clean <plastic> <optional metal> mold:";
		cout << " <cleaning steps>.\n";
		cleaning->steps();
	};
public:
	void run(map<string, string>& order) {
		setupInjectionLine(order);
		cout << "  Process order:\n";
		getMold(order);
		insertTags(order);
		loadAdditivies(order);
		injectionCycle(order);	// Polymorphic step.
		cleanMold(order);
		// Seam point - add another step.
	}
};
// Seam point - add another polymorphic step.

}

void process(map<string, string>& order) {
	using namespace template_method;

	ProcessOrder_TM_4* processOrder = new ProcessOrder_TM_4;

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

#endif /* DP4_SRC_OUTLINE_FINAL_H_ */
