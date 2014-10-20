/*
 * midterm.h
 *
 *  Created on: Aug 9, 2014
 *      Author: aldgoff
 */

#ifndef MIDTERM_H_
#define MIDTERM_H_

#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

namespace sections_1_2 {

struct Jargon {
	string	designPattern;
	string	category;
	string	description;
};

Jargon jargon[] = {
	{ "Facade",			"Structural", "Define a simpler interface to a set of interfaces making them easier to use." },
	{ "Adapter",		"Structural", "Adapt interfaces so classes can work together polymorphically." },
	{ "Strategy",		"Behavioral", "Define a family of interchangeable algorithms which can vary independently from the clients." },
	{ "Bridge",			"Structural", "Decouples an abstraction from its implementations so they can vary independently." },
	{ "AbstractFactory","Creational", "Provide an interface for creating families of related objects w/o specifying their concrete classes." },
	{ "Decorator",		"Structural", "Dynamically attach additional responsibilities to an object." },
	{ "Observer",		"Behavioral", "Notify observers automatically." },
	{ "TemplateMethod",	"Behavioral", "Define the skeleton of an algorithm." },
	{ "Singleton",		"Creational", "Insure only one instance of an object exists." },
	{ "FactoryMethod",	"Creational", "Instantiates a subclass object with the parent class's type." },
//	{ "Strategy",	"cat,	"" },
//	{ "Strategy",	"cat",	"" },
};

}

namespace section_1_jargon {	// Match the description to the design pattern.

using namespace sections_1_2;

void section1() {
	string section("Match the description to the design pattern.");
	map<string,string>	jars; // Map is being used as a pseudo rng, just mixes up the answers a bit.
	for(size_t i=0; i<sizeof(jargon)/sizeof(*jargon); i++) { // Problem set.
		jars[jargon[i].designPattern] = jargon[i].description;
	}

	cout << "<< Problem Set 1 - Jargon: " << section << " >>\n\n";
	map<string, char> answerKey;
	map<string,string>::iterator it = jars.begin();
	for(int i=0; it!=jars.end(); it++,i++) {
		char number[32];
		sprintf(number, "%2d) _____ ", i+1);
		char dp[30];
		sprintf(dp, "%-20s", jargon[i].designPattern.c_str());
		char letter = 'A' + i;
		cout << number << dp << letter << ") " << it->second << "\n\n";
		answerKey[it->second] = letter;
	}

	cout << "<< Answer Key 1 - Jargon: " << section << " >>\n\n";
	it = jars.begin();
	for(int i=0; it!=jars.end(); it++,i++) {
		char number[9];
		sprintf(number, "%2d) ", i+1);
		char letter = answerKey[jars[jargon[i].designPattern]];
		char dp[30];
		sprintf(dp, "%-20s", jargon[i].designPattern.c_str());
		cout << number << "__" << letter << "__ " << dp << "\n\n";
	}
	cout << endl;
}

}

namespace section_2_taxonomy {	// What category (Structural, Behavioral, Creational) are these design patterns?

using namespace sections_1_2;

void section2() {
	string section("What category (Structural, Behavioral, Creational) are these design patterns?");
	map<string,string>	jars;
	for(size_t i=0; i<sizeof(jargon)/sizeof(*jargon); i++) { // Problem set.
		jars[jargon[i].designPattern] = jargon[i].category;
	}

	cout << "<< Problem Set 2 - Taxonomy: " << section << " >>\n\n";
	map<string,string>::iterator it = jars.begin();
	for(int i=1; i<=9; it++,i++) {
		char number[32];
		sprintf(number, "%2d) ______________  ", i);
		char dp[30];
		sprintf(dp, "%-20s", jargon[i].designPattern.c_str());
		cout << number << dp << "\n\n";
	}

	cout << "<< Answer Key 2 - Taxonomy: " << section << " >>\n\n";
	it = jars.begin();
	for(int i=1; i<=9; it++,i++) {
		char number[19];
		sprintf(number, "%2d) __%-10s__  ", i, jargon[i].category.c_str());
		char dp[30];
		sprintf(dp, "%-20s", jargon[i].designPattern.c_str());
		cout << number << dp << "\n\n";
	}
}

}

namespace section_3_principles {	// Which of the SWE principles below apply specifically to design patterns?

struct Principles {
	string	answer;
	string	concept;
};

Principles principles[] = { // For randomization to work, requires 13 entries.
	{ "true",	"The form of each part derives from its context in the larger whole" },
	{ "true",	"Work from the outermost context" },
	{ "true",	"Design from context" },
	{ "true",	"Open-closed principle" },
	{ "true",	"Dependency inversion principle" },
	{ "true",	"Encapsulate what varies" },
//	{ "true",	"Abstract classes versus interfaces" },
	{ "true",	"Commonality and variability analysis" },
	{ "true",	"A named approach for solving a design problem" },
	{ "false",	"Test driven development" },
	{ "false",	"Coding standards" },
	{ "false",	"Refactoring" },
	{ "false",	"Coupling and cohesion" },
	{ "false",	"YAGNI (you ain't gonna need it)" },
//	{ "false",	"DRY" },
};

void section3() {
	string section("Which of the SWE principles below apply specifically to design patterns?");
	char line[80+1];
	char answer[80+1];
	long s = 0;			// Randomization, think successor, requires 13 entries in principles.

	cout << "<< Problem Set 3 - Principles: " << section << " >>\n\n";
	for(size_t i=0; i<sizeof(principles)/sizeof(Principles); i++) {
		s = (((((((((s*s)%13)*s)%13)*s)%13)*s)%13) + 3)%13;	// Single pure attractor.
		sprintf(line, " %2d) %2ld) _________  %s\n", i+1, s+1,
				principles[s].concept.c_str()
		);
		cout << line << endl;
	}

	cout << "<< Answer Key 3 - Principles: " << section << " >>\n\n";
	for(size_t i=0; i<sizeof(principles)/sizeof(Principles); i++) {
		s = (((((((((s*s)%13)*s)%13)*s)%13)*s)%13) + 3)%13;	// Single pure attractor.
		sprintf(answer, "__%s%s", principles[s].answer.c_str(), "_________");
		sprintf(line, " %2d) %2ld) %-9.9s  %s\n", i+1, s+1,
				answer,
				principles[s].concept.c_str()
		);
		cout << line << endl;
	}
}

}

namespace section_4_recognize_design_patterns {	// Identify the design pattern in each code example.

struct Recognition {
	string	subSection;
	string	designPattern;
	string	headClass;
};

Recognition recognition[] = {
	{ "4.1", "Adapter",        "DomainSpecificName"},
	{ "4.2", "TemplateMethod", "DrSeuss"},
	{ "4.3", "Strategy",       "DeadlySins"},
};

namespace section_4_1 {

class DomainSpecificName {
public:
	virtual void draw() {}
	virtual void calc() {}
	// ...
	virtual void diff() {}
public:
	virtual ~DomainSpecificName() {}
};
class SomethingElse {
public:
	virtual void display() {}
	virtual void compute() {}
	// ...
	virtual void subtract() {}
public:
	virtual ~SomethingElse() {}
};
class Section_4_1 : public DomainSpecificName {
	SomethingElse dsn;
public:
	void draw() { dsn.display(); }
	void calc() { dsn.compute(); }
	// ...
	void diff() { dsn.subtract(); }
};

string clientCode(DomainSpecificName* object) {
	object->draw();
	object->calc();
	// ...
	object->diff();
	return "DomainSpecificName";
}

}

namespace section_4_2 {

class DrSeuss {
public:
	virtual ~DrSeuss() {}
protected:
	virtual void sam() {}
	virtual void iam() {}
	virtual void dont() {}
	virtual void like() {}
	virtual void ham() {}
public:
	void run() {
		sam();
		iam();
		dont();
		like();
		ham();
	}
};
class OneFish : public DrSeuss {
public:
	void iam() {}
};
class TwoFish : public DrSeuss {
public:
	void sam() {}
	void ham() {}
};
class RedFish : public DrSeuss {
public:
	void dont() {}
	void like() {}
};
class BlueFish : public DrSeuss {
public:
	void ham() {}
	void dont() {}
	void sam() {}
};

string clientCode(DrSeuss* wonderful) {
	wonderful->run();
	return "DrSeuss";
}

}

namespace section_4_3 {

class DeadlySins {
public:
	virtual ~DeadlySins() {}
public:
	virtual void cleverCompute() {}
};
class waste : public DeadlySins {
public:
	void cleverCompute() {}
};
class haste : public DeadlySins {
public:
	void cleverCompute() {}
};
class sloth : public DeadlySins {
public:
	void cleverCompute() {}
};
class lust : public DeadlySins {
public:
	void cleverCompute() {}
};

string clientCode(DeadlySins* greed) {
	greed->cleverCompute();
	return "DeadlySins";
}

}

void section4() {
	string section("Identify the design pattern in each code example.");
	char line[80+1];
	char answer[80+1];

	vector<string> runs;	// Be sure the examples run.
	runs.push_back(section_4_1::clientCode(new section_4_1::Section_4_1));
	runs.push_back(section_4_2::clientCode(new section_4_2::DrSeuss));
	runs.push_back(section_4_3::clientCode(new section_4_3::DeadlySins));

	cout << "<< Problem Set 4 - Recognition: " << section << " >>\n\n";
	for(size_t i=0; i<sizeof(recognition)/sizeof(Recognition); i++) {
		sprintf(line, " %3s) ________________  %s\n",
				recognition[i].subSection.c_str(),
				runs[i].c_str()
		);
		cout << line << endl;
	}

	cout << "<< Answer Key 4 - Recognition: " << section << " >>\n\n";
	for(size_t i=0; i<sizeof(recognition)/sizeof(Recognition); i++) {
		sprintf(answer, "_%s%s", recognition[i].designPattern.c_str(), "________________");
		sprintf(line, " %3s) %-16.16s  %s\n",
				recognition[i].subSection.c_str(),
				answer,
				recognition[i].headClass.c_str()
		);
		cout << line << endl;
	}

	cout << "*** COPY OVER CODE ***\n" << endl;
}

namespace answer_key {
	// 4_1: Adapter (DomainSpecificName)
	// 4_2: TemplateMethod (DrSeuss)
	// 4_3: Strategy (DeadlySins)
}

}

namespace section_5_apply_design_patterns {	// Which design pattern should be applied to correct each problematic code example below?

struct Application {
	string	subSection;
	string	designPattern;
	string	headClass;
};

Application application[] = {
	{ "5.1", "AbstractFactory", "Cool Hand Luke"},
	{ "5.2", "Facade", "Homeowner painting"},
	{ "5.3", "Bridge?", "tbd"},
};

namespace section_5_1 {

enum Sym {
	orbit,
	gum,
	rubber
};

class Cool;
class Hand;
class Luke;

class Cool {
public:
	void comm(Hand* hand) {}
	void escape() { cout << "  Luke escapes.\n"; }
};
class Hand {
public:
	void talk(Luke* luke) {}
	void chase(Luke* luke) {}
	void problem(Luke* luke, Cool* cool) {}
};
class Luke {
public:
	void listen(Cool* cool, Hand* hand) {}
};

class One;
class Two;
class Ten;

class One {
public:
	void comm(Two* two) {}
	void escape() { cout << "  One escapes.\n"; }
};
class Two {
public:
	void talk(Ten* ten) {}
	void chase(Ten* ten) {}
	void problem(Ten* ten, One* one) {}
};
class Ten {
public:
	void listen(One* one, Two* two) {}
};

class Alpha;
class Beta;
class Gamma;

class Alpha {
public:
	void comm(Beta* beta) {}
	void escape() { cout << "  Alpha escapes.\n"; }
};
class Beta  {
public:
	void talk(Gamma* gamma) {}
	void chase(Gamma* gamma) {}
	void problem(Gamma* gamma, Alpha* alpha) {}
};
class Gamma {
public:
	void listen(Alpha* alpha, Beta* beta) {}
};

string clientCode(Sym sym) {
	Cool* cool = 0;
	Hand* hand = 0;
	Luke* luke = 0;

	One* one = 0;
	Two* two = 0;
	Ten* ten = 0;

	Alpha* alpha = 0;
	Beta*  beta  = 0;
	Gamma* gamma = 0;

	switch(sym) {
	case orbit:
		cool = new Cool;
		hand = new Hand;
		luke = new Luke;
		cool->comm(hand);
		hand->talk(luke);
		luke->listen(cool, hand);
		hand->problem(luke, cool);
		cool->escape();
		hand->chase(luke);
		break;
	case gum:
		one = new One;
		two = new Two;
		ten = new Ten;
		one->comm(two);
		two->talk(ten);
		ten->listen(one, two);
		two->problem(ten, one);
		one->escape();
		two->chase(ten);
		break;
	case rubber:
		alpha = new Alpha;
		beta  = new Beta;
		gamma = new Gamma;
		alpha->comm(beta);
		beta->talk(gamma);
		gamma->listen(alpha, beta);
		beta->problem(gamma, alpha);
		alpha->escape();
		beta->chase(gamma);
		break;
	}

	return "clientCode";
}

}

namespace section_5_2 { // Contractor wants a uniform look in his subdivision, but needs to offer buyers some choice.

namespace problem { // "Paint" package.

enum Color { black, brown, read, orange, yellow, green, blue, violet, gray, white };
enum Shine { flat, satin, semiGloss, gloss };
enum Chemisty { stain, paint, powderCoating };
enum Pallet { pastel, vibrant };

class House {
public:
	void base(Color, Shine, Chemisty) {};
	void trim(Color, Shine, Chemisty) {};
};
class Deck {
public:
	void base(Color, Shine, Chemisty) {};
	void rails(Color, Shine, Chemisty) {};
	void posts(Color, Shine, Chemisty) {};
};
class Gate {
public:
	void powderCoat(Color) {};
	void whiteWash() {};
};
class Fence {
public:
	void whiteWash() {};
};

void validate(House house, Deck deck, Gate gate, Fence fence) {
	if(false) {
		throw "Invalid combination of options.";
	}
}

void orderPrep(int type) {
	House	house;
	Deck	deck;
	Gate	gate;
	Fence	fence;

	switch (type) {
	case 1:
	case 2:
	case 3:
		cout << "Not used by contractor.\n";
		break;
	case 4:
		house.base(white, satin, paint);
		house.trim(blue, semiGloss, paint);
		deck.base(gray, flat, stain);
		deck.rails(blue, semiGloss, stain);
		deck.posts(white, gloss, stain);
		gate.powderCoat(white);
		fence.whiteWash();
		cout << "Customer type 4 - valid options.\n";
		break;
	case 9:
		cout << "Customer type 9 - valid options.\n";
		break;
	case 13:
		cout << "Customer type 13 - invalid options.\n";
		break;
	default:
		cout << "Unsupported customer type: " << type << endl;
		break;
	}

	try {
		validate(house, deck, gate, fence);
	}
	catch (string& error) {
		cout << error << "\n";
	}
}

void clientCode() {
	for(int i=1; i<=16; i++) {
		orderPrep(i);
	}
//	orderPrep(4);
//	orderPrep(9);
//	orderPrep(13);
}

};

namespace solution {

class Facade {
public:
	enum ColorPallet {
		pastel,
		vibrant,
	};
	enum Shine {
		summer,
		winter,
	};
private:
	ColorPallet	cp;
	Shine		shine;
public:
	Facade(ColorPallet cp=pastel, Shine shine=winter) : cp(cp), shine(shine) {}
public:
	void paintHouse(ColorPallet cp=pastel) { cout << "House:" << endl; };
	void stainDeck(Shine shine=summer) { cout << "Deck:" << endl; };
	void coatGate() { cout << "Gate:" << endl; };
	void whiteWashFence() { cout << "Fence:" << endl; };
//public:
//	void audit(int type) {
//		cout << "Customer type " << type << "\n";
//	}
};

void clientCode(int type) {
	Facade::ColorPallet pallet;
	Facade::Shine		shine;

	switch (type) {
	case 1:
		pallet = Facade::pastel;
		shine  = Facade::summer;
		break;
	case 2:
		pallet = Facade::pastel;
		shine  = Facade::winter;
		break;
	case 3:
		pallet = Facade::vibrant;
		shine  = Facade::summer;
		break;
	case 4:
		pallet = Facade::vibrant;
		shine  = Facade::winter;
		break;
	default:
	break;
	}

	Facade scheme(pallet, shine);
	scheme.paintHouse();
	scheme.stainDeck();
	scheme.coatGate();
	scheme.whiteWashFence();
	cout << endl;
}

void demo() {
	for(int i=1; i<=4; i++) {
		clientCode(i);
	}
//
//	Facade customer1(Facade::pastel, Facade::summer);
//	customer1.paintHouse();
//	customer1.stainDeck();
//	customer1.audit(4);
//
//	Facade customer2(Facade::vibrant, Facade::winter);
//	customer2.paintHouse();
//	customer2.stainDeck();
//	customer2.audit(9);
};

}

}

void section5() {
	string section("Which design pattern should be applied to correct each problematic code example below?");
	char line[80+1];
	char answer[80+1];

	cout << "<< Problem Set 5 - Application: " << section << " >>\n\n";
	for(size_t i=0; i<sizeof(application)/sizeof(Application); i++) {
		sprintf(line, " %3s) _________________  %s\n",
				application[i].subSection.c_str(),
				application[i].headClass.c_str()
		);
		cout << line << endl;
	}

	cout << "<< Answer Key 5 - Application: " << section << " >>\n\n";
	for(size_t i=0; i<sizeof(application)/sizeof(Application); i++) {
		sprintf(answer, "_%s%s", application[i].designPattern.c_str(), "_________________");
		sprintf(line, " %3s) %-17.17s  %s\n",
				application[i].subSection.c_str(),
				answer,
				application[i].headClass.c_str()
		);
		cout << line << endl;
	}

	// Be sure the examples run.
	section_5_1::clientCode(section_5_1::orbit);
	section_5_1::clientCode(section_5_1::gum);
	section_5_1::clientCode(section_5_1::rubber);
	cout << endl;

	section_5_2::problem::clientCode();
	cout << endl;

	section_5_2::solution::demo();
	cout << endl;

	cout << "*** COPY OVER CODE ***\n" << endl;
}

namespace answer_key {
	// 5_1: AbstractFactory
	// 5_2: Bridge?
}

}

#ifdef Output

Hello dpsg.

<< Problem Set 1: Match the description to the design pattern. >>

 1) ____ Facade              A) Provide an interface for creating families of related objects w/o specifying their concrete classes.

 2) ____ Adapter             B) Adapt interfaces so classes can work together polymorphically.

 3) ____ Strategy            C) Decouples an abstraction from its implementations so they can vary independently.

 4) ____ Bridge              D) Dynamically attach additional responsibilities to an object.

 5) ____ AbstractFactory     E) Define a simpler interface to a set of interfaces making them easier to use.

 6) ____ Decorator           F) Instantiates a subclass object with the parent class type.

 7) ____ Observer            G) Notify observers automatically.

 8) ____ TemplateMethod      H) Insure only one instance of an object exists.

 9) ____ Singleton           I) Define a family of interchangeable algorithms which can vary independently from the clients.

10) ____ FactoryMethod       J) Define the skeleton of an algorithm.

<< Answer Key 1: Match the description to the design pattern. >>

 1) __E__ Facade

 2) __B__ Adapter

 3) __I__ Strategy

 4) __C__ Bridge

 5) __A__ AbstractFactory

 6) __D__ Decorator

 7) __G__ Observer

 8) __J__ TemplateMethod

 9) __H__ Singleton

10) __F__ FactoryMethod


<< Problem Set 2: What category (Structural, Behavioral, Creational) are these design patterns? >>

 1) ______________  Adapter

 2) ______________  Strategy

 3) ______________  Bridge

 4) ______________  AbstractFactory

 5) ______________  Decorator

 6) ______________  Observer

 7) ______________  TemplateMethod

 8) ______________  Singleton

 9) ______________  FactoryMethod

<< Answer Key 2: What category (Structural, Behavioral, Creational) are these design patterns? >>

 1) __Structural__  Adapter

 2) __Behavioral__  Strategy

 3) __Structural__  Bridge

 4) __Creational__  AbstractFactory

 5) __Structural__  Decorator

 6) __Behavioral__  Observer

 7) __Behavioral__  TemplateMethod

 8) __Creational__  Singleton

 9) __Creational__  FactoryMethod


section_3_principles

section_4_recognize_design_patterns
  Running DSN.
  Running Dr. Seuss.
  Running deadly sins.


section_5_apply_design_patterns
  Luke escapes.
  One escapes.
  Alpha escapes.

Aloha dpsg.


#endif

#endif /* MIDTERM_H_ */
