/*
 * finalOutline.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 *
 *  Intent: Create just the design pattern architecture.
 *  		No derived classes (except for the Observer pattern, where the
 *  		derived classes are themselves base classes for other patterns),
 *  		and the defaults in the specs have not been coded.
 *
 *  Result: The skeleton (outline) of the code, metaphorically, we have first
 *  		framed the house, now can enclose each room. Contrast that with
 *  		the usual approach of building the house room by room, then finding
 *  		it too easy to put the frezzer in the garage instead of the kitchen.
 *
 *  Final LOC: 800.
 */

#ifndef DP4_SRC_OUTLINE_FINAL_H_
#define DP4_SRC_OUTLINE_FINAL_H_

namespace final_outline_file {

const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }

/* Decision logic interfaces (another place to reduce coupling):
 *  1) Strategy			- selectCycleAlgorithm(order)	: "plastic".
 *  2) Adapter			- getCleaningProcess(order)		: "plastic".
 *  3)
 *  4) TemplateMethod	- getOrderProcess(order)		: "plastic".
 *  5) FactoryMethod	- createPackager(order)			: "packager"
 *  6) Decorator		- insertTags(order, cavity)		: "tags".
 *  					  addAddtives(order, color)		: "AdditiveX".
 *  7) ChainOfResp		- getMold(order)				: "moldLoc".
 *  8) Observer			- injection line base class machines inherit.
 *  9) Bridge
 *  	 Abstraction	- getShape(order)				: "mold".
 *  	 Implementation	- getPlatform(order)			: 'metal'.
 * 10) AbstractFactory	- determineInjectionLine(order)	: "size".
 *
 * "key" => present in order file.
 * 'key' => added by code.
 */

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
public:
	static Adapter_2* getCleaningProcess(map<string,string>& order);
};
// Seam point - add another cleaning interface.

Adapter_2* Adapter_2::getCleaningProcess(map<string,string>& order) {
	if(		order["plastic"] == "whatever")	return new Adapter_2;
	else if(order["plastic"] == "whatever")	return new Adapter_2;
	// Seam point - add another cleaning interface.

	else {	// Default.
		return new Adapter_2;
	}
}

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
public:
	static Strategy_1* selectCycleAlgorithm(map<string,string>& order);
};
// Seam point - add another cycle algorithm.

Strategy_1* Strategy_1::selectCycleAlgorithm(map<string,string>& order) {
	if(		order["plastic"] == "whatever")	return new Strategy_1;
	else if(order["plastic"] == "whatever")	return new Strategy_1;
	// Seam point - add another cycle algorithm.

	else {	// Default.
		return new Strategy_1;
	}
}

}

namespace observer {		// DP 7.

/* The output bin is the Subject, it notifies for a pause when full.
 * Earlier injection line machines are the Observers.
 */

class Observer_7;
class Subject_7;

class Subject_7 {
	list<Observer_7*> observers;
public:
	const string name;
public:
	Subject_7(const string& name) : name(name) {}
	~Subject_7();
public:
	void attach(Observer_7* obs) {
		observers.push_back(obs);
	}
	void detach(Observer_7* obs) {
		observers.remove(obs);
	}
	void pause();
};

class Observer_7 {
protected:
	Subject_7* subject;
public:
	Observer_7(Subject_7* subject) : subject(subject) {
		subject->attach(this);
	}
	virtual ~Observer_7() {
		subject->detach(this);
		DTOR("~Observer_7\n");
	}
public:
	virtual void update(Subject_7* subject=0) {
		cout << "        <machine> pausing while";
		cout << subject->name << " output bin is swapped.\n";
	}
};
// No seam point - listeners are the base class machines of the injection line.

Subject_7::~Subject_7() {
	DTOR("~Subject_7 ");
	DTOR("Observers left to process (should be zero) = ");
	char str[80];
	sprintf(str, "%d.\n", observers.size());
	DTOR(str);
}
void Subject_7::pause() {
	cout << "      " << name << " output bin full...\n";
	list<Observer_7*>::iterator it;
	for(it=observers.begin(); it!=observers.end(); it++) {
		(*it)->update(this);
	}
}

}

namespace abstract_factory {// DP 10.

using namespace observer;

class IJM_AF : public Observer_7 {
public:
	IJM_AF(Subject_7* bin) : Observer_7(bin) {}
	virtual ~IJM_AF() { DTOR("~IJM_AF "); }
public:
	void update(Subject_7* bin) {
		cout << "        <ijm> pausing while ";
		cout << bin->name << " output bin is swapped.\n";
	}
};
class Mold_AF {
public:
	Mold_AF() {}
	virtual ~Mold_AF() { DTOR("~Mold_AF\n"); }
};
class ConveyerBelt_AF : public Observer_7 {
public:
	ConveyerBelt_AF(Subject_7* bin) : Observer_7(bin) {}
	virtual ~ConveyerBelt_AF() { DTOR("~ConveyerBelt_AF "); }
public:
	void update(Subject_7* bin) {
		cout << "        <conveyer belt> pausing while ";
		cout << bin->name << " output bin is swapped.\n";
	}
};
class OutputBin_AF : public Subject_7 {
public:
	OutputBin_AF(const string& name) : Subject_7(name) {}
	virtual ~OutputBin_AF() { DTOR("~OutputBin_AF "); }
};
class AbstractFactory_10 {
public:
	AbstractFactory_10() {}
	virtual ~AbstractFactory_10() { DTOR("~AbstractFactory_10 "); }
public:
	virtual IJM_AF* createIJM(OutputBin_AF* bin) {
		return new IJM_AF(bin);
	}
	virtual Mold_AF* createMold() {
		return new Mold_AF;
	}
	virtual ConveyerBelt_AF* createConveyerBelt(OutputBin_AF* bin) {
		return new ConveyerBelt_AF(bin);
	}
	virtual OutputBin_AF* createOutputBin() {
		return new OutputBin_AF("<OutputBin>");
	}
};
class InjectionLine_AF {
	AbstractFactory_10* factory;
	OutputBin_AF*		bin;
	IJM_AF*				ijm;
	Mold_AF*			mold;
	ConveyerBelt_AF*	belt;
public:
	InjectionLine_AF() :
		factory(0),
		bin(0),
		ijm(0),
		mold(0),
		belt(0)
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

		bin	 = factory->createOutputBin();			// Subject_7.

		ijm	 = factory->createIJM(bin);				// Observer_7.
		mold = factory->createMold();
		belt = factory->createConveyerBelt(bin);	// Observer_7.
	}
	OutputBin_AF* getBin() { return bin; };
public:
	static InjectionLine_AF* determineInjectionLine(map<string,string>& order);
};

// Seam point - add another injection line family.

InjectionLine_AF* InjectionLine_AF::determineInjectionLine(map<string,string>& order) {
	unsigned size = atoi(order["size"].c_str());
	if(		size < 10000)	return new InjectionLine_AF;
	else if(size < 20000)	return new InjectionLine_AF;
	// Seam point - add another injection line family.

	else {	// Default.
		return new InjectionLine_AF;
	}
}

}

namespace bridge {			// DP 9.

class Platform_B_9 {
public:
	const string name;
public:
	Platform_B_9(const string name="platform") : name(name) {}
	virtual ~Platform_B_9() { DTOR("~Platform_B_9\n"); }
public:
	virtual string drill() { return "drill"; }
	virtual string cut()   { return "cut"; }
	virtual string grind() { return "grind"; }
public:
	static Platform_B_9* getPlatform(map<string,string>& order);
};
// Seam Point - add another milling platform implementation.

Platform_B_9* Platform_B_9::getPlatform(map<string,string>& order) {
	if(		order["metal"] == "whatever")	return new Platform_B_9;
	else if(order["metal"] == "whatever")	return new Platform_B_9;
	// Seam Point - add another milling platform implementation.

	else {	// Default.
		return new Platform_B_9;
	}
}

class Shape_B_9 {
protected:
	Platform_B_9*	platform;
public:
	const unsigned	volume_cc;
public:
	Shape_B_9(Platform_B_9* platform, unsigned volume_cc=0)
		: platform(platform), volume_cc(volume_cc) {}
	virtual ~Shape_B_9() {
		DTOR("~Shape_B_9 ");
		delete platform;
	}
public:
	virtual void mill(map<string,string>& order) {
		cout << "      using " << platform->name << " tools (";
		cout << platform->drill() << ", ";
		cout << platform->cut() << ", ";
		cout << platform->grind() << ")";
		cout << " to mill " << order["metal"] << " block";
		cout << " into " << order["cavities"] << " <shape> shapes";
		cout << " with " << order["finish"] << " finish.\n";
	}
public:
	static Shape_B_9* getShape(map<string,string>& order);
};
// Seam Point - add another shape abstraction.

Shape_B_9* Shape_B_9::getShape(map<string,string>& order) {
	Platform_B_9* platform = Platform_B_9::getPlatform(order);

	if(		order["mold"] == "whatever")	return new Shape_B_9(platform);
	else if(order["mold"] == "whatever")	return new Shape_B_9(platform);
	// Seam Point - add another shape abstraction.

	else {	// Default.
		return new Shape_B_9(platform);
	}
}

}

namespace chain_of_resp {	// DP 8.

using namespace bridge;

class GetMold_CofR_8 {
protected:
	GetMold_CofR_8* successor;
public:
	GetMold_CofR_8(GetMold_CofR_8* successor=0) : successor(successor) {}
	virtual ~GetMold_CofR_8() { DTOR("~GetMold_CofR_8\n"); }
public:
	virtual Shape_B_9* from(map<string,string>& order) {
		if(order["moldLoc"] == "wherever") {
			cout << "    Get " << order["mold"] << " mold from <somewhere>.\n";
			Shape_B_9* shape = Shape_B_9::getShape(order);
			return shape;
			}
		else if(successor)
			return successor->from(order);
		else {
			return /*GetMold::*/fromDefault(order);
		}
	}
public:
	Shape_B_9* fromDefault(map<string,string>& order) {
		cout << "    Get " << order["mold"] << " mold from <somewhere>.\n";
		return Shape_B_9::getShape(order);
	}
public:
	static GetMold_CofR_8* getMold(map<string,string>& order);
};
// Seam point - add another mold location responder.

GetMold_CofR_8* GetMold_CofR_8::getMold(map<string,string>& order) {
	return
		// new wherever(
		// Seam point - add another mold location responder.
		new GetMold_CofR_8(
	);
}

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
	static Tags_D_6* insertTags(map<string,string>& order, Tags_D_6* cavity);
};
// Seam point - add another tag option.

Tags_D_6* Tag::insertTags(map<string,string>& order, Tags_D_6* cavity) {
	if(order.find("tags") == order.end())
		return cavity;

	char tag[80] = "";
	const char* remainingTokens = order["tags"].c_str();

	while(remainingTokens) {
		if(!sscanf(remainingTokens, "%s", tag))
			break;

		if(		!strcmp(tag,  "whatever"))		cavity = new Tag(cavity);
		else if(!strcmp(tag,  "whatever"))		cavity = new Tag(cavity);
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
	unsigned vol_cc = 0;

	if(order.find("Additive1") != order.end()) {
		vol_cc = atoi(order["Additive1"].c_str());
		color = new Additive(color, vol_cc);
	}
	if(order.find("Additive2") != order.end()) {
		vol_cc = atoi(order["Additive2"].c_str());
		color = new Additive(color, vol_cc);
	}
	// Seam point - add another additive option.

	return color;
}

}

namespace factory_method {	// DP 5.

using namespace observer;

class Packager_FM_5 : public Observer_7 {
public:
	Packager_FM_5(Subject_7* bin) : Observer_7(bin) {}
	virtual ~Packager_FM_5() { DTOR("~Packager_FM_5 "); }
public:
	void update(Subject_7* bin) {
		cout << "        <packager> pausing while ";
		cout << bin->name << " output bin is swapped.\n";
	}
public:
	static Packager_FM_5* createPackager(map<string, string>& order, Subject_7* bin);
};
// Seam point - add another Packager class.

Packager_FM_5* Packager_FM_5::createPackager(map<string, string>& order, Subject_7* bin) {
	if(		order["packager"] == "whatever")	return new Packager_FM_5(bin);
	else if(order["packager"] == "whatever")	return new Packager_FM_5(bin);
	// Seam point - add another Packager class.

	else {	// Default.
		return new Packager_FM_5(bin);
	}
}

}

namespace template_method {	// DP 4.

using namespace abstract_factory;
using namespace factory_method;
using namespace strategy;
using namespace adapter;
using namespace decorator;
using namespace chain_of_resp;
using namespace bridge;

class ProcessOrder_TM_4 {
	InjectionLine_AF*	injectionLine;
	Packager_FM_5*		packager;
	GetMold_CofR_8*		mold;
	Shape_B_9*			shape;
	Tags_D_6*			cavity;
	Plastic_D_6*		color;
	Strategy_1*			algorithm;
	Adapter_2*			cleaning;
public:
	ProcessOrder_TM_4() :
		injectionLine(0),
		packager(0),
		mold(0),
		shape(0),
		cavity(0),
		color(0),
		algorithm(0),
		cleaning(0)
	{}
	virtual ~ProcessOrder_TM_4() {	// Reverse order from initialization.
		delete cleaning;
		delete algorithm;
		delete color;
		delete cavity;
		delete shape;
		delete mold;
		delete packager;
		delete injectionLine;
		DTOR("~ProcessOrder_TM_4\n");
	}
private:
	void setupInjectionLine(map<string, string>& order) {
		injectionLine = InjectionLine_AF::determineInjectionLine(order);
		injectionLine->createLine(order);

		OutputBin_AF* bin = injectionLine->getBin();
		packager = Packager_FM_5::createPackager(order, bin);

		cout << "  Setup <DerivedOrder> injection line";
		cout << " for <size> run with <Packager> packager:\n";

		cout << "    <IJM> - <Metal>(<cavities>)";
		cout << " - <Type> conveyer belt - <OutputBin>\n";
	}
	void getMold(map<string, string>& order) {
		mold = GetMold_CofR_8::getMold(order);

		shape = mold->from(order);
	};
	void insertTags(map<string, string>& order) {
		cavity = new Cavity;

		cavity = Tag::insertTags(order, cavity);

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
		injectionLine->getBin()->pause();
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
public:
	static ProcessOrder_TM_4* getOrderProcess(map<string,string>& order);
};
// Seam point - add another polymorphic step.

ProcessOrder_TM_4* ProcessOrder_TM_4::getOrderProcess(map<string,string>& order) {
	if(		order["plastic"] == "whatever")		return new ProcessOrder_TM_4;
	else if(order["plastic"] == "whatever")		return new ProcessOrder_TM_4;
	// Seam point - add another plastic.

	else {	// Default.
		return new ProcessOrder_TM_4;
	}
}

}

void process(map<string, string>& order) {
	using namespace template_method;

	ProcessOrder_TM_4* processOrder = ProcessOrder_TM_4::getOrderProcess(order);

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
	cout << "<<< final outline >>>\n";

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
