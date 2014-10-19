/*
 * command.h
 *
 * Desc: Defi
 *
 * Category: Behavioral
 *
 *  Created on: Sep 6, 2014
 *      Author: aldgoff
 *
 * URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Command
 * URL: http://www.dofactory.com/net/command-design-pattern
 * URL: http://sourcemaking.com/design_patterns/command
 * URL: http://sourcemaking.com/
 */

#ifndef COMMAND_H_
#define COMMAND_H_

/* Consider the commands necessary to use various lighting technologies. We want the commands and technologies
 * to vary independently, and to instrument by command, or by technology or by both.
 * Instrumentation makes debugging, audit, and undoing easier.
 */

namespace requests {

void demo() {
	cout << "<< Command problem >>\n";

	cout << endl;
}

}

namespace command {

class Light {						// Receivers.
protected:
	const bool debug;
public:
	Light(bool debug=false) : debug(debug) {}
	virtual ~Light() {}
public:
	virtual void turnOn() { cout << "Light is on.\n"; }
	virtual void turnOff() { cout << "Light is off.\n"; }
	virtual void dim() { cout << "Light is dim.\n"; }
};
class Electric : public Light {
public:
	void turnOn() { cout << "Light bulb is on.\n"; }
	void turnOff() { cout << "Light bulb is off.\n"; }
	void dim() { cout << "Light bulb is dim.\n"; }
};
class Gas : public Light {
public:
	void turnOn() { cout << "Gas lamp is burning.\n"; }
	void turnOff() { cout << "Gas lamp is extinguished.\n"; }
	void dim() { cout << "Gas lamp is dim.\n"; }
};
class Flash : public Light {
public:
	Flash() : Light(true) {}
public:
	void turnOn() { cout << "Flashlight is on.\n"; }
	void turnOff() { cout << "Flashlight is off.\n"; }
	void dim() {
		if(debug)	cout << "Flashlight is dim (also send to log file).\n";
		else		cout << "Flashlight is dim.\n";
	}
};

class Command {
protected:
	const bool debug;
public:
	Command(bool debug=false) : debug(debug) {}
	virtual ~Command() {}
public:
	virtual void execute() {}
};
class OnCommand : public Command {
	Light*	light;
public:
	OnCommand(Light* light) : light(light) {}
public:
	void execute() { light->turnOn(); }
};
class OffCommand : public Command {
	Light*	light;
public:
	OffCommand(Light* light, bool debug=false) : Command(true), light(light) {}
public:
	void execute() { light->turnOff(); if(debug) cout << "    It got dark.\n"; }
};
class DimCommand : public Command {
	Light*	light;
public:
	DimCommand(Light* light) : light(light) {}
public:
	void execute() { light->dim(); }
};

class Operate {
	Command*	_on;
	Command*	_off;
	Command* 	_dim;
public:
	Operate(Command* on, Command* off, Command* dim) : _on(on), _off(off), _dim(dim) {}
public:
	void on() { _on->execute(); if(true) cout << "  Also sending to log file.\n"; }
	void off() { _off->execute(); }
	void dim() { _dim->execute(); }
};

void demo() {
	cout << "<< Command solution >>\n";

	Light* lights[] = {	// Receivers.
		new Electric,
		new Gas,
		new Flash,
	};

	for(size_t i=0; i<sizeof(lights)/sizeof(Light*); i++) {	// Client.
		Operate operate(
			new OnCommand(lights[i]),
			new OffCommand(lights[i]),
			new DimCommand(lights[i])
		);
		operate.on();		// Invokers.
		operate.dim();
		operate.off();
		cout << endl;
	}
}

}



#endif /* COMMAND_H_ */
