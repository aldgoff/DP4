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
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator
 *  	http://www.dofactory.com/net/decorator-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter17
 *  	http://sourcemaking.com/design_patterns/decorator
 */

#ifndef DECORATOR_H_
#define DECORATOR_H_

#include <string>
using namespace std;

namespace homework {

/* Consider options for a car.
 * One might subclass a base class, Car, for each set of options,
 * but then the options code gets duplicated leading to scaling problems,
 * and the options are statically linked.
 * For the 4 classes and 9 options implied by the following procedural code,
 * rewrite with the Decorator pattern to eliminate the combinatorial explosion,
 * reduce duplication, improve code locality, and allow for dynamic linking.
 * Pay particular attention to the problem of memory leaks with this pattern.
 */

namespace decorator_common {

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

}

namespace decorator_legacy {

using namespace decorator_common;

class RunAbout : public Car {
public:
	RunAbout() : Car("RunAbout") {}
	string getDesc() {
		string desc = str + " with 4 wheels"
			+ ", 2 doors";
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 2000.00;
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
			+ ", automatic transmission";
		return desc;
	}
	double getCost() {
		double cost = 12000.00
			+ 4000.00
			+ 1500.00
			+ 3000.00;
		return cost;
	}
};

void demo() {
	Car* cars[] = { new RunAbout, new SUV};

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		cout << cars[i]->getDesc() << " costs $" << cars[i]->getCost() << ".\n";
	cout << endl;

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		delete cars[i];
	cout << endl;
}

}

namespace decorator_problem {

using namespace decorator_common;

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
	Car* mine  = new RunAbout;
	Car* yours = new SUV;
	Car* hers  = new Status;
	Car* boss  = new Performance;

	Car* cars[] = {mine, yours, hers, boss};

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		cout << cars[i]->getDesc() << " costs $" << cars[i]->getCost() << ".\n";
	cout << endl;

	for(size_t i=0; i<sizeof(cars)/sizeof(Car*); i++)
		delete cars[i];
	cout << endl;
}

}

}

#endif /* DECORATOR_H_ */
