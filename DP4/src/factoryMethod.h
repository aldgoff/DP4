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

#include <string>
#include <vector>
using namespace std;

namespace lecture {

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

}

namespace homework {

/* Problem: sending encrypted video streams.
 * What varies
 *   1) Display Types (DisplayPort, HDMI, MIPI, Widi) (HEVC)
 *   2) Crypto Protocols (PVP, ID1, RSE) (RDX)
 *   3) Resolutions ([640,480], [1920,1080]) ([3840,2160])
 *   4) Framerates (48, 50, 60) (75, 120)
 * Model as
 *   1) Classes
 *   2) Classes
 *   3) Pair of integers
 *   4) Integer
 * Use factory method to reduce coupling & avoid combinatorial explosion.
 */

namespace factory_method_common {	// Deprecated.

char str[80];

class Framerate {
	int	framesPerSec;
public:
	Framerate(int framesPerSec) : framesPerSec(framesPerSec) {}
	string operator()() {
		sprintf(str, "%d", framesPerSec);
		return str;
	}
};

class Resolution {
	int	h;
	int	v;
public:
	Resolution(int h, int v) : h(h), v(v) {}
	string operator()() {
		sprintf(str, "[%d, %d]", h, v);
		return str;
	}
};

}

namespace factory_method_legacy {	// Deprecated.

using namespace factory_method_common;

class Crypto {
	string name;
public:
	Crypto(const string& name) : name(name) {}
	string operator()() { return name; }
};

class DisplayPort {
	string		name;
	Resolution	res;
	Crypto		protocol;
	Framerate	framerate;
public:
	DisplayPort(
		const string&	name,
		Resolution		res,
		Crypto			protocol,
		Framerate		framerate)
	: name(name), res(res), protocol(protocol), framerate(framerate) {}
	string operator()() {
		sprintf(str, "  %s%s via %s at %s fps.\n", name.c_str(),
			res().c_str(), protocol().c_str(), framerate().c_str());
		return str;
	}
};

void demo() {
	Framerate	framerate(60);
	Resolution	res(1920,1080);
	Crypto		protocol("PVP");
	DisplayPort	dp("DisplayPort", res, protocol, framerate);
	cout << dp();

	cout << endl;
}

}

namespace factory_method_problem {

enum Crypto {
	PVP,
	ID1,
	RSA,
	// Seam point 1 - insert another crypto protocol.
};
const char* crypto_names[] = {
	"PVP",
	"ID1",
	"RSA",
	// Seam point 2 - insert another crypto protocol.
};

enum Display {
	DISPLAY_PORT,
	HDMI,
	MIPI,
	WIDI,
	// Seam point A - insert another display type.
};
const char* display_names[] = {
	"DisplayPort",
	"HDMI",
	"MIPI",
	"Widi",
	// Seam point B - insert another display type.
};

class Pvp {
public:
	const char* encrypt_video() { return "PVP"; }
};
class Id1 {
public:
	const char* encrypt_video() { return "ID1"; }
};
class Rsa {
public:
	const char* encrypt_video() { return "RSA"; }
};
// Seam point 3 - add another crypto protocol - SOLID.

// Imagine that these are all in separate files. Do you even know all the
// display types that will have to change when a new crypto procotol is added?
class DisplayPort {
public:
	string send_video(int* res, Crypto crypto, int framerate) {
		string protocol;
		switch(crypto) {
		case PVP:	protocol = Pvp().encrypt_video();	break;
		case ID1:	protocol = Id1().encrypt_video();	break;
		case RSA:	protocol = Rsa().encrypt_video();	break;
		// Seam point i - insert another crypto protocol.
		default: throw "OOPS"; break;
		}
		char str[80];
		sprintf(str, "  Send DisplayPort[%d,%d] via %s at %d fps.",
			res[0], res[1], protocol.c_str(), framerate);
		return str;
	}
};
class Hdmi {
public:
	string send_video(int* res, Crypto crypto, int framerate) {
		string protocol;
		switch(crypto) {
		case PVP:	protocol = Pvp().encrypt_video();	break;
		case ID1:	protocol = Id1().encrypt_video();	break;
		case RSA:	protocol = Rsa().encrypt_video();	break;
		// Seam point j - insert another crypto protocol.
		default: throw "OOPS"; break;
		}
		char str[80];
		sprintf(str, "  Send HDMI[%d,%d] via %s at %d fps.",
			res[0], res[1], protocol.c_str(), framerate);
		return str;
	}
};
class Mipi {
public:
	string send_video(int* res, Crypto crypto, int framerate) {
		string protocol;
		switch(crypto) {
		case PVP:	protocol = Pvp().encrypt_video();	break;
		case ID1:	protocol = Id1().encrypt_video();	break;
		case RSA:	protocol = Rsa().encrypt_video();	break;
		// Seam point k - insert another crypto protocol.
		default: throw "OOPS"; break;
		}
		char str[80];
		sprintf(str, "  Send MIPI[%d,%d] via %s at %d fps.",
			res[0], res[1], protocol.c_str(), framerate);
		return str;
	}
};
class Widi {
public:
	string send_video(int* res, Crypto crypto, int framerate) {
		string protocol;
		switch(crypto) {
		case PVP:	protocol = Pvp().encrypt_video();	break;
		case ID1:	protocol = Id1().encrypt_video();	break;
		case RSA:	protocol = Rsa().encrypt_video();	break;
		// Seam point l - insert another crypto protocol.
		default: throw "OOPS"; break;
		}
		char str[80];
		sprintf(str, "  Send Widi[%d,%d] via %s at %d fps.",
			res[0], res[1], protocol.c_str(), framerate);
		return str;
	}
};
// Seam point C - add another display type - SOLID.

// Client code, also in a separate file.
void send_video(Display display, int* res, Crypto crypto, int framerate) {
	switch(display) {
	case DISPLAY_PORT:
		cout << DisplayPort().send_video(res, crypto, framerate) << "\n";
		break;
	case HDMI:
		cout << Hdmi().send_video(res, crypto, framerate) << "\n";
		break;
	case MIPI:
		cout << Mipi().send_video(res, crypto, framerate) << "\n";
		break;
	case WIDI:
		cout << Widi().send_video(res, crypto, framerate) << "\n";
		break;
	// Seam point D - insert another display type.
	default:
	throw "OOPS";
	break;
	}
}

void demo() {
	int res[] = {1920, 1080};
	int framerate = 60;
	Display displays[] = {DISPLAY_PORT, HDMI, MIPI, WIDI};
	Crypto cryptos[] = {PVP, ID1, RSA};

	for(size_t i=0; i<sizeof(displays)/sizeof(*displays); i++) {
		for(size_t j=0; j<sizeof(cryptos)/sizeof(*cryptos); j++) {
			send_video(displays[i], res, cryptos[j], framerate);
		}
		cout << endl;
	}
}

}

namespace factory_method_solution {

class Crypto {
public: virtual ~Crypto() {}
public:
	static Crypto* makeObject(const string& type);
	virtual const char* encrypt_video()=0;
};
class PVP : public Crypto {
public:
	const char* encrypt_video() { return "PVP"; }
};
class ID1 : public Crypto {
public:
	const char* encrypt_video() { return "ID1"; }
};
class RSA : public Crypto {
public:
	const char* encrypt_video() { return "RSA"; }
};
// Seam point 1 - add another crypto protocol - SOLID.
Crypto* Crypto::makeObject(const string& type) {
	if(     type == "PVP")	return new PVP;
	else if(type == "ID1")	return new ID1;
	else if(type == "RSA")	return new RSA;
	// Seam point 3 - insert another crypto protocol.
	else {
		throw "OOPS";
	}
}

class Display {
protected:
	char str[80];
public: virtual ~Display() {}
public:
	static Display* makeObject(const string& type);
	virtual void send_video(int* res, Crypto* crypto, int framerate)=0;
};
class DisplayPort : public Display {
public:
	void send_video(int* res, Crypto* crypto, int framerate) {
		sprintf(str, "DisplayPort[%d,%d] via %s at %d fps.",
			res[0], res[1], crypto->encrypt_video(), framerate);
		cout << "  Send " << str << "\n";
	}
};
class HDMI : public Display {
public:
	void send_video(int* res, Crypto* crypto, int framerate) {
		sprintf(str, "HDMI[%d,%d] via %s at %d fps.",
			res[0], res[1], crypto->encrypt_video(), framerate);
		cout << "  Send " << str << "\n";
	}
};
class MIPI : public Display {
public:
	void send_video(int* res, Crypto* crypto, int framerate) {
		sprintf(str, "MIPI[%d,%d] via %s at %d fps.",
			res[0], res[1], crypto->encrypt_video(), framerate);
		cout << "  Send " << str << "\n";
	}
};
class Widi : public Display {
public:
	void send_video(int* res, Crypto* crypto, int framerate) {
		sprintf(str, "Widi[%d,%d] via %s at %d fps.",
			res[0], res[1], crypto->encrypt_video(), framerate);
		cout << "  Send " << str << "\n";
	}
};
// Seam point 2 - add another display type - SOLID.
Display* Display::makeObject(const string& type) {
	if(type == "DisplayPort")	return new DisplayPort;
	else if(type == "HDMI")		return new HDMI;
	else if(type == "MIPI")		return new MIPI;
	else if(type == "Widi")		return new Widi;
	// Seam point 4 - insert another display type.
	else {
		throw "OOPS";
	}
}

void send_video(Display* display, int* res, Crypto* crypto, int framerate) {
	display->send_video(res, crypto, framerate);
}

void demo() {
	int res[] = {1920, 1080};
	int framerate = 60;
	string displays[] = { "DisplayPort", "HDMI", "MIPI", "Widi"};
	string cryptos[] = { "PVP", "ID1", "RSA"};

	for(size_t i=0; i<sizeof(displays)/sizeof(*displays); i++) {
		for(size_t j=0; j<sizeof(cryptos)/sizeof(*cryptos); j++) {
			Display* display = Display::makeObject(displays[i]);
			Crypto* crypto = Crypto::makeObject(cryptos[j]);
			send_video(display, res, crypto, framerate);
		}
		cout << endl;
	}
}

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

namespace factory_method_common {

char str[80];

class Framerate {
	int	framesPerSec;
public:
	Framerate(int framesPerSec) : framesPerSec(framesPerSec) {}
	string operator()() {
		sprintf(str, "at %d fps.\n", framesPerSec);
		return str;
	}
};

class Resolution {
	int	h;
	int	v;
public:
	Resolution(int h, int v) : h(h), v(v) {}
	string operator()() {
		sprintf(str, "[%d, %d] ", h, v);
		return str;
	}
};

class Display {
	string name;
public:
	Display(const string& name) : name(name) {}
	string operator()() {
		sprintf(str, "  %s", name.c_str());
		return str; }
};

class Crypto {
	string name;
public:
	Crypto(const string& name) : name(name) {}
	string operator()() {
		sprintf(str, "via %s ", name.c_str());
		return str;
	}
};

}

namespace factory_method_legacy {

using namespace factory_method_common;

void demo() {
	Display		display("DisplayPort");
	Crypto		crypto("PVP");
	Resolution	res(1920,1080);
	Framerate	framerate = 60;
	switch(1) {
	case 1:	cout << display() << res() << crypto() << framerate(); break;
	}

	cout << endl;
}

}

namespace factory_method_problem {

//void send_video(int* res, int frameRate, int display, int protocol);

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

namespace factory_method_solution {	// Each class hierarchy is an example of the Factory Method design pattern.

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
