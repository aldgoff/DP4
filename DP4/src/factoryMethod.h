/*
 * factoryMethod.h
 *
 * Desc: Instantiates a subclass object with the parent class's type.
 *       Let subclasses decide which class to instantiate.
 * 		 A factory method is a static method of a class that
 * 		 returns on object of that class' type, but unlike a
 * 		 ctor, it returns an instance of a subclass.
 *
 * Category: Creational
 *
 *  Created on: July 30, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Factory_Method
 *  	http://www.dofactory.com/net/factory-method-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter23
 *  	http://sourcemaking.com/design_patterns/factory_method
 */

#ifndef FACTORYMETHOD_H_
#define FACTORYMETHOD_H_

#include <vector>
using namespace std;

namespace factory_method_common {

enum Alternatives {
	TYPE1,
	TYPE2,
	TYPE3,
	// Seam point 1 - insert another alternative.
};

}

namespace factory_method_legacy {

using namespace factory_method_common;

class Type1 {
public:
	void run() { cout << "  Type1.run()\n"; }
};
class Type2 {
public:
	void run() { cout << "  Type2.run()\n"; }
};
class Type3 {
public:
	void run() { cout << "  Type3.run()\n"; }
};
// Seam point 2 - add another alternative.

void clientCodeRun(Alternatives alt) {
	switch(alt) {
	case TYPE1:
		Type1 type1;
		type1.run();
		break;
	case TYPE2:
		Type2 type2;
		type2.run();
		break;
	case TYPE3:
		Type3 type3;
		type3.run();
		break;
	// Seam point 3 - insert another alternative.
	default:
	throw "OOPS";		// Requires error handling.
	break;
	}
}

void demo() {
	Alternatives alt[] = { TYPE1, TYPE2, TYPE3 };
	for(size_t i=0; i<sizeof(alt)/sizeof(*alt); i++) {
		clientCodeRun(alt[i]);
	}

	cout << endl;
}
}

namespace factory_method_problem {

using namespace factory_method_common;

class Type1 {
public:
	void run() { cout << "  Type1.run()\n"; }
	void calc() { cout << "   Type1.calc()\n"; }
	void compute() { cout << "    Type1.compute()\n"; }
};
class Type2 {
public:
	void run() { cout << "  Type2.run()\n"; }
	void calc() { cout << "   Type2.calc()\n"; }
	void compute() { cout << "    Type2.compute()\n"; }
};
class Type3 {
public:
	void run() { cout << "  Type3.run()\n"; }
	void calc() { cout << "   Type3.calc()\n"; }
	void compute() { cout << "    Type3.compute()\n"; }
};
// Seam point 2 - add another alternative.

void clientCodeRun(Alternatives alt) {
	switch(alt) {
	case TYPE1:
		Type1 type1;
		type1.run();
		break;
	case TYPE2:
		Type2 type2;
		type2.run();
		break;
	case TYPE3:
		Type3 type3;
		type3.run();
		break;
	// Seam point 3 - insert another alternative.
	default:
	throw "OOPS";		// Requires error handling.
	break;
	}
}

void clientCodeCalc(Alternatives alt) {
	switch(alt) {
	case TYPE1:
		Type1 type1;
		type1.calc();
		break;
	case TYPE2:
		Type2 type2;
		type2.calc();
		break;
	case TYPE3:
		Type3 type3;
		type3.calc();
		break;
	// Seam point 4 - insert another alternative.
	default:
	throw "OOPS";		// Requires error handling.
	break;
	}
}

void clientCodeCompute(Alternatives alt) {
	switch(alt) {
	case TYPE1:
		Type1 type1;
		type1.compute();
		break;
	case TYPE2:
		Type2 type2;
		type2.compute();
		break;
	case TYPE3:
		Type3 type3;
		type3.compute();
		break;
	// Seam point 5 - insert another alternative.
	default:
	throw "OOPS";		// Requires error handling.
	break;
	}
}

void demo() {
	Alternatives alt[] = { TYPE1, TYPE2, TYPE3 };
	for(size_t i=0; i<sizeof(alt)/sizeof(*alt); i++) {
		clientCodeRun(alt[i]);
		clientCodeCalc(alt[i]);
		clientCodeCompute(alt[i]);
	}

	cout << endl;
}

}

namespace factory_method_solution {

using namespace factory_method_common;

class FactoryMethod {	// If the classes are varying...
public:	virtual ~FactoryMethod() {}
public:
	virtual void run() {}
	virtual void calc() {}
	virtual void compute() {}
public:
	static FactoryMethod* makeObject(Alternatives type);
};
class Type1 : public FactoryMethod {
public:
	void run() { cout << "  Type1.run()\n"; }
	void calc() { cout << "   Type1.calc()\n"; }
	void compute() { cout << "    Type1.compute()\n"; }
};
class Type2 : public FactoryMethod {
public:
	void run() { cout << "  Type2.run()\n"; }
	void calc() { cout << "   Type2.calc()\n"; }
	void compute() { cout << "    Type2.compute()\n"; }
};
class Type3 : public FactoryMethod {
public:
	void run() { cout << "  Type3.run()\n"; }
	void calc() { cout << "   Type3.calc()\n"; }
	void compute() { cout << "    Type3.compute()\n"; }
};
// Seam point 2 - add another alternative.

FactoryMethod* FactoryMethod::makeObject(Alternatives type) {
	switch(type) {
	case TYPE1:	return new Type1;
	case TYPE2:	return new Type2;
	case TYPE3:	return new Type3;
	// Seam point 1 - insert another alternative.
	default: return new FactoryMethod;
	}
}

void clientCodeRun(FactoryMethod* obj) {
	obj->run();
}
void clientCodeCalc(FactoryMethod* obj) {
	obj->calc();
}
void clientCodeCompute(FactoryMethod* obj) {
	obj->compute();
}

void demo() {
	FactoryMethod* classes[] = {
		FactoryMethod::makeObject(TYPE1),
		FactoryMethod::makeObject(TYPE2),
		FactoryMethod::makeObject(TYPE3)};
	for(size_t i=0; i<sizeof(classes)/sizeof(*classes); i++) {
		clientCodeRun(classes[i]);
		clientCodeCalc(classes[i]);
		clientCodeCompute(classes[i]);
	}

	cout << endl;
}

}


/* Consider the problem of sending encrypted video streams to
 * a variety of display types under different crypto protocols
 * with different resolutions and at different frame rates.
 * Resolutions are easily modeled as a 2D array of integers
 * as are frame rates as a singular integer. However, we
 * want to avoid coupling the user class with all the various
 * display types and cryptographic protocols, and as usual,
 * we want to avoid any combinatorial explosions.
 */

namespace factory_method_problem2 {

void send_video(int* res, int frameRate, int display, int protocol);

class DisplayPort {
public:
	void send_video(int* res, int frameRate, int protocol) {
		char stream[64];
		sprintf(stream, "  DisplayPort[%d, %d]", res[0], res[1]);
		switch(protocol) {
		case 1:	cout << stream << " via PVP at " << frameRate << " fps.\n";	break;
		case 2:	cout << stream << " via ID1 at " << frameRate << " fps.\n";	break;
		case 3:	cout << stream << " via RSA at " << frameRate << " fps.\n";	break;
		// Seam point - new protocol.
		default: cout << "  OOPs!\n" << endl;
		break;
		}
	}
};
class HDMI {
public:
	void send_video(int* res, int frameRate, int protocol) {
		char stream[64];
		sprintf(stream, "  HDMI[%d, %d]", res[0], res[1]);
		switch(protocol) {
		case 1:	cout << stream << " via PVP at " << frameRate << " fps.\n";	break;
		case 2:	cout << stream << " via ID1 at " << frameRate << " fps.\n";	break;
		case 3:	cout << stream << " via RSA at " << frameRate << " fps.\n";	break;
		// Seam point - new protocol.
		default: cout << "  OOPs!\n" << endl;
		break;
		}
	}
};
class MIPI {
public:
	void send_video(int* res, int frameRate, int protocol) {
		char stream[64];
		sprintf(stream, "  MIPI[%d, %d]", res[0], res[1]);
		switch(protocol) {
		case 1:	cout << stream << " via PVP at " << frameRate << " fps.\n";	break;
		case 2:	cout << stream << " via ID1 at " << frameRate << " fps.\n";	break;
		case 3:	cout << stream << " via RSA at " << frameRate << " fps.\n";	break;
		// Seam point - new protocol.
		default: cout << "  OOPs!\n" << endl;
		break;
		}
	}
};
class Widi {
public:
	void send_video(int* res, int frameRate, int protocol) {
		char stream[64];
		sprintf(stream, "  Widi[%d, %d]", res[0], res[1]);
		switch(protocol) {
		case 1:	cout << stream << " via PVP at " << frameRate << " fps.\n";	break;
		case 2:	cout << stream << " via ID1 at " << frameRate << " fps.\n";	break;
		case 3:	cout << stream << " via RSA at " << frameRate << " fps.\n";	break;
		// Seam point - new protocol.
		default: cout << "  OOPs!\n" << endl;
		break;
		}
	}
};
// Seam point - new display technology (HEVC).

void send_video(int* res, int frameRate, int display, int protocol)
{
	switch(display) {
	case 1:	DisplayPort().send_video(res, frameRate, protocol);	break;
	case 2:	HDMI().send_video(res, frameRate, protocol);	break;
	case 3:	MIPI().send_video(res, frameRate, protocol);	break;
	case 4:	Widi().send_video(res, frameRate, protocol);	break;
	// Seam point - new display technology (HEVC).
	default:
	break;
	}
}

void demo() {
	cout << "<< Factory Method problem >>\n";

	int	res[] = {1920, 1080};
	int	frameRate = 60;

	for(int display=1; display<=4; display++) {
		for(int protocol=1; protocol<=3; protocol++) {
			send_video(res, frameRate, display, protocol);
		}
		cout << endl;
	}
}

}

namespace factory_method {	// Each class hierarchy is an example of the Factory Method design pattern.

class Crypto {
public:
	static Crypto* makeObject(int selection);
	virtual const char* action() { return "Not a valid selection.\n"; }
	enum { count = 3 };
public:
	virtual ~Crypto() {}
};
class PVP : public Crypto {
public:
	const char* action() { return "PVP"; }
};
class ID1 : public Crypto {
public:
	const char* action() { return "ID1"; }
};
class RSA : public Crypto {
public:
	const char* action() { return "RSA"; }
};
// Seam point - new crypto technology (IDX).

Crypto* Crypto::makeObject(int selection) {
	switch(selection) {
	case 1:	return new PVP;
	case 2:	return new ID1;
	case 3:	return new RSA;
	default:
		cout << " OOPs, " << selection << " not a valid selection.\n" << endl;
		return new Crypto;
	}
}

class Display {
public:
	static Display* makeObject(int selection);
	virtual const char* action() { return "Not a valid selection.\n"; }
	enum { count = 4 };
public:
	virtual ~Display() {}
};
class DisplayPort : public Display {
public:
	const char* action() { return "DisplayPort"; }
};
class HDMI : public Display {
public:
	const char* action() { return "HDMI"; }
};
class MIPI : public Display {
public:
	const char* action() { return "MIPI"; }
};
class Widi : public Display {
public:
	const char* action() { return "Widi"; }
};
// Seam point - new display technology (HEVC).

Display* Display::makeObject(int selection) {
	switch(selection) {
	case 1:	return new DisplayPort;
	case 2:	return new HDMI;
	case 3:	return new MIPI;
	case 4:	return new Widi;
	default:
		cout << " OOPs, " << selection << " not a valid selection.\n" << endl;
		return new Display;
	}
}

void demo() {
	cout << "<< Factory Method solution >>\n";

	int	res[] = {1920, 1080};
	int	frameRate = 60;

	vector<Display*>	displays;
	vector<Crypto*>		protocols;

	for(size_t i=1; i<=Display::count; i++)
		displays.push_back(Display::makeObject(i));
	for(size_t j=1; j<=Crypto::count; j++)
		protocols.push_back(Crypto::makeObject(j));

	for(size_t i=0; i<Display::count; i++) {
		char stream[64];
		sprintf(stream, "  %s[%d, %d]", displays[i]->action(), res[0],res[1]);
		for(size_t j=0; j<Crypto::count; j++) {
			cout << stream << " via " << protocols[j]->action();
			cout << " at " << frameRate << " fps.\n";
		}
		cout << endl;
	}

	for(size_t i=0; i<Display::count; i++)
		delete displays[i];
	for(size_t j=0; j<Crypto::count; j++)
		delete protocols[j];

}

}

namespace obsolete {

class Factory {
public:
	static Factory* makeObject(int selection);
	virtual void action() {}
public:
	virtual ~Factory() {}
};
class Sub1 : public Factory {
public:
	void action() {	cout << "  Sub1\n"; }
};
class Sub2 : public Factory {
public:
	void action() {	cout << "  Sub2\n"; }
};
class Sub3 : public Factory {
public:
	void action() {	cout << "  Sub3\n"; }
};

Factory* Factory::makeObject(int selection) {
	switch(selection) {
	case 1:	return new Sub1;
	case 2:	return new Sub2;
	case 3:	return new Sub3;
	default:
		cout << " OOPs, " << selection << " not a valid selection.\n" << endl;
		return new Factory;
	}
}

void demo() {
	vector<Factory*>	objects;

	for(size_t i=1; i<=3; i++)
		objects.push_back(Factory::makeObject(i));

	for(size_t i=0; i<objects.size(); i++)
		objects[i]->action();

	for(size_t i=0; i<objects.size(); i++)
		delete objects[i];

	Factory* first = Factory::makeObject(1);
	first->action();
}

}

#endif /* FACTORYMETHOD_H_ */
