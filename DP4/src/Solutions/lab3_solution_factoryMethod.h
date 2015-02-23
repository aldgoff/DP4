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
 *  Created on: Feb 23 2015
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

#endif /* FACTORYMETHOD_H_ */
