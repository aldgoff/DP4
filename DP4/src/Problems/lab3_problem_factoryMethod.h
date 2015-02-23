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

}

#endif /* FACTORYMETHOD_H_ */
