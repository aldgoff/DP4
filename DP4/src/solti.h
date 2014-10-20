/*
 * solti.h
 *
 *  Created on: Oct 1, 2014
 *      Author: aldgoff
 */

#ifndef SOLTI_H_
#define SOLTI_H_

namespace solti_problem {

void demo() {
	cout << "Solti problem:\n" << endl;
}

}

namespace solti_experimental {

class Hardware {};
class VDBox : public Hardware {};
class VEBox : public Hardware {};
class Render : public Hardware {};
class Blitter : public Hardware {};

class Generation {
	Hardware*	vdbox;
	Hardware*	vebox;
	Hardware*	render;
public:
	Generation() : vdbox(new VDBox), vebox(new VEBox), render(new Render) {}
};
class Gen7 : public Generation {};
class Gen8 : public Gen7 {};
class Gen9 : public Gen8 {
	Hardware*	blitter;
public:
	Gen9() : Gen8(), blitter(new Blitter) {}
};
class Gen10 : public Gen9 {};

void demo() {
	cout << "Solti experimental:\n" << endl;
}

}

namespace solti_solution {

class Generation {};
class Gen7 : public Generation {};
class Gen8 : public Generation {};
class Gen9 : public Generation {};
class Gen10 : public Generation {};

class Hardware {
	Generation*	gen;
public:
	Hardware(Generation* gen=new Gen7) : gen(gen) {}
public:
	virtual ~Hardware() {};
public:
	void task_default() {
		cout << "Hardware default task.\n";
	}
	virtual void task() { task_default(); }
};
class VDBox : public Hardware {};
class VEBox : public Hardware {};
class Render : public Hardware {
public:
	void task() {
		cout << "Render hardware task.\n";
	}
};
class Blitter : public Hardware {};

class Prolog {};
class EpiLog {};

void demo() {
	cout << "Solti solution:\n" << endl;

	Hardware* hardware[] = {
		new VDBox,
		new VEBox,
		new Render,
		new Blitter,
	};

	for(size_t i=0; i<sizeof(hardware)/sizeof(Hardware*); i++) {
		hardware[i]->task();
	}
	cout << endl;
}

}

#endif /* SOLTI_H_ */
