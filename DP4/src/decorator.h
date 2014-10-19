/*
 * decorator.h
 *
 * Desc: Dynamically attach additional responsibilities to an object.
 *
 * Category: Structural
 *
 *  Created on: Apr 26, 2014
 *      Author: aldgoff
 *
 *  URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator
 */

#ifndef DECORATOR_H_
#define DECORATOR_H_

class Car {
protected:
	string str;
public:
	Car(string str="Undefined car") : str(str) {}
	virtual string getDesc() { return str; }
	virtual double getCost()=0;
	virtual ~Car() {
		cout << "~Car " << str << "\n";
	}
};

namespace too_many_car_model_options {

/* Consider options for a car.
 * One might subclass a base class, Car, for each set of options,
 * but then the options code gets duplicated leading to scaling problems,
 * and the options are statically linked.
 * For the 4 classes and 9 options implied by the following procedural code,
 * rewrite with the Decorator pattern to eliminate the combinatorial explosion,
 * reduce duplication, improve code locality, and allow for dynamic linking.
 * Pay particular attention to the problem of memory leaks with this pattern.
 */

class RunAbout : public Car {
public:
	RunAbout() : Car("RunAbout") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00
		;
		return cost;
	}
};

class SUV : public Car {
public:
	SUV() : Car("SUV") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 4 doors"
			+ ", AC"
			+ ", automatic transmission"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 3000.00
		;
		return cost;
	}
};

class Status : public Car {
public:
	Status() : Car("Status") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 4 doors"
			+ ", AC"
			+ ", premium sound system"
			+ ", navigation"
			+ ", automatic transmission"
			// Seam: new options scales as the number of car models.
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 1000.00
			+ 2000.00
			+ 3000.00
		;
		return cost;
	}
};

class Performance : public Car {
public:
	Performance() : Car("Performance") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors"
			+ ", AC"
			+ ", premium sound system"
			+ ", navigation"
			+ ", manual transmission"
			+ ", V8"
			+ ", super-charger"
		;
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00
			+ 1500.00
			+ 1000.00
			+ 2000.00
			+ 2500.00
			+ 6000.00
			+ 3000.00
		;
		return cost;
	}
};
// Seam: new car models scale as the number of options.

void demo() {
	cout << "<< Hello Decorator Problem >>\n";

	Car* mine  = new RunAbout;
	Car* yours = new SUV;
	Car* hers  = new Status;
	Car* boss  = new Performance;

	Car* ours[] = {mine, yours, hers, boss};

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
		cout << ours[i]->getDesc() << " costs $" << ours[i]->getCost() << ".\n";
	}
	cout << endl;

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
		delete ours[i];
	}
	cout << endl;
}

}

namespace decorator {

class BaseModel : public Car {
public:
	BaseModel(string name="missing") : Car(name+" with 4 wheels") {}
	string getDesc() {
		string desc = str;
		return desc;
	}
	double getCost() { return 12000.00; }
	~BaseModel() { cout << "~BaseModel: "; }
};

class OptionsDecorator : public Car {
// This is the surprise, options are not cars,
// inheriting from Car violates the "is-a" principle,
// but it is the key to dynamically attaching additional responsibilities.
protected:
	Car* build;
public:
	OptionsDecorator(Car* build, string str="OD") : Car(str), build(build) {}
	string getDesc() { return build->getDesc() + ", " + str; }
	virtual ~OptionsDecorator() {
		cout << "~OptionsDecorator: ";
	}
};

#define OD_Dtor { cout << "~" << str << "\n"; build->~Car(); } // Just to reduce duplication.

class TwoDoors : public OptionsDecorator {
public:
	TwoDoors(Car* build) : OptionsDecorator(build, "2 doors") {}
	double getCost() { return build->getCost() + 2000.00; }
	~TwoDoors() OD_Dtor
};

class FourDoors : public OptionsDecorator {
public:
	FourDoors(Car* build) : OptionsDecorator(build, "4 doors") {}
	double getCost() { return build->getCost() + 4000.00; }
	~FourDoors() OD_Dtor
};

class AC : public OptionsDecorator {
public:
	AC(Car* build) : OptionsDecorator(build, "AC") {}
	double getCost() { return build->getCost() + 1500.00; }
	~AC() OD_Dtor
};

class PremiumSoundSystem : public OptionsDecorator {
public:
	PremiumSoundSystem(Car* build) : OptionsDecorator(build, "premium sound system") {}
	double getCost() { return build->getCost() + 1000.00; }
	~PremiumSoundSystem() OD_Dtor
};

class Navigation : public OptionsDecorator {
public:
	Navigation(Car* build) : OptionsDecorator(build, "navigation") {}
	double getCost() { return build->getCost() + 2000.00; }
	~Navigation() OD_Dtor
};

class ManualTransmission : public OptionsDecorator {
public:
	ManualTransmission(Car* build) : OptionsDecorator(build, "manual transmission") {}
	double getCost() { return build->getCost() + 2500.00; }
	~ManualTransmission() OD_Dtor
};

class AutomaticTransmission : public OptionsDecorator {
public:
	AutomaticTransmission(Car* build) : OptionsDecorator(build, "automatic transmission") {}
	double getCost() { return build->getCost() + 3000.00; }
	~AutomaticTransmission() OD_Dtor
};

class V8 : public OptionsDecorator {
public:
	V8(Car* build) : OptionsDecorator(build, "V8") {}
	double getCost() { return build->getCost() + 6000.00; }
	~V8() OD_Dtor
};

class SuperCharger : public OptionsDecorator {
public:
	SuperCharger(Car* build) : OptionsDecorator(build, "super-charger") {}
	double getCost() { return build->getCost() + 3000.00; }
	~SuperCharger() OD_Dtor
};

void demo() {
	cout << "<< Hello Decorator Solution >>\n";

	Car* mine = new BaseModel("RunAbout");
	mine = new TwoDoors(mine);

	Car* yours = new BaseModel("SUV");
	yours = new FourDoors(yours);
	yours = new AC(yours);
	yours = new AutomaticTransmission(yours);

	Car* hers = new BaseModel("Status");
	hers = new FourDoors(hers);
	hers = new AC(hers);
	hers = new PremiumSoundSystem(hers);
	hers = new Navigation(hers);
	hers = new AutomaticTransmission(hers);

	Car* boss = new BaseModel("Performance");
	boss = new TwoDoors(boss);
	boss = new AC(boss);
	boss = new PremiumSoundSystem(boss);
	boss = new Navigation(boss);
	boss = new ManualTransmission(boss);
	boss = new V8(boss);
	boss = new SuperCharger(boss);

	Car* ours[] = {mine, yours, hers, boss};

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
		cout << ours[i]->getDesc() << " costs $" << ours[i]->getCost() << ".\n";
	}
	cout << endl;

	for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
//		delete ours[i];	cout << endl;
	}
	delete hers; cout << endl; // For demo only, to limit output, loop above is formally correct.
}

}

#endif /* DECORATOR_H_ */
