/*
 * abstractFactory.h
 *
 * Desc: Provide an interface for creating families of related objects w/o specifying their concrete classes.
 *
 * Category: Creational
 *
 *  Created on: Apr 12, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Abstract_Factory
 *  	http://www.dofactory.com/net/abstract-factory-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter11
 *  	http://sourcemaking.com/design_patterns/abstract_factory
 */

#ifndef ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_H_

#include <stdlib.h>
#include <string>

namespace homework {

/* Consider a wild life simulation with different animals and continents.
 * The major complexity is the relationships between the animals.
 * Animals are grouped according to their continent, so the simulation
 * runs on a continent by continent basis.
 * With a procedural approach, scaling is quadratic.
 * The effort to add a relationship scales as the number of continents.
 * The effort add a continent scales as the number of relationships.
 * Use the Abstract Factory design pattern to reduce coupling,
 * enhance cohesion, and avoid quadratic scaling.
 */

namespace abstract_factory_problem {

enum Continent {
	NorthAmerica,
	Africa,
	// Seam point - insert another continent, violates open/closed principle.
};
string ids[] = {
	"North America",
	"Africa",
	// Seam point - insert another continent, violates open/closed principle.
};

// North American animals.
class Bison;
class Wolf;

class Bison {
	string 	name;
public:
	Bison() : name("Bison") {}
	~Bison() { cout << "  ~Bison"; }
public:
	string Name() { return name; };
	void graze() {
		cout << "  " << name << " eats grass.\n";
	}
	void mate(Bison* bison) {
		cout << "  Mate with " << bison->Name() << " herd.\n";
	}
	void evade(Wolf* wolf);
};

class Wolf {
	string 	name;
public:
	Wolf() : name("Wolf") {}
	~Wolf() { cout << " ~Wolf"; }
public:
	string Name() { return name; };
	void eat(Bison* bison) {
		cout << "  " << name << " eats a " << bison->Name() << ".\n";
	}
	void mate(Wolf* wolf) {
		cout << "  Mate for life with another " << wolf->Name() << ".\n";
	}
	void hunt() {
		cout << "  Hunt in packs.\n";
	}
};

void Bison::evade(Wolf* wolf) {
	cout << "  Flee from pack of " << wolf->Name() << "s.\n";
}

// African animals.
class Wildebeest;
class Lion;

class Wildebeest {
	string 	name;
public:
	Wildebeest() : name("Wildebeest") {}
	~Wildebeest() { cout << " ~Wildebeest"; }
public:
	string Name() { return name; };
	void graze() {
		cout << "  " << name << " eats thrash.\n";
	}
	void mate(Wildebeest* wildebeest) {
		cout << "  Breed with " << wildebeest->Name() << ".\n";
	}
	void evade(Lion* lion);
};

class Lion {
	string 	name;
public:
	Lion() : name("Lion") {}
	~Lion() { cout << " ~Lion"; }
public:
	string Name() { return name; };
	void eat(Wildebeest* wildebeest) {
		cout << "  " << name << " eats a " << wildebeest->Name() << ".\n";
	}
	void mate(Lion* lion) {
		cout << "  Mate with another " << lion->Name() << ".\n";
	}
	void hunt() {
		cout << "  Stalk prey.\n";
	}
};

void Wildebeest::evade(Lion* lion) {
	cout << "  Flee from " << lion->Name() << ".\n";
}

// Seam point - add animals for another continent, follows open/closed principle.

class AnimalWorld {
	Bison*		bison;		// North America animals.
	Wolf*		wolf;
	Wildebeest*	wildebeest;	// Africa animals.
	Lion*		lion;
	// Seam point - insert another continent, violates open/closed principle.
public:
	AnimalWorld()
	  : bison(new Bison), wolf(new Wolf),
		wildebeest(new Wildebeest), lion(new Lion)
	// Seam point - insert another continent, violates open/closed principle.
	{}
	~AnimalWorld() {
		delete bison;
		delete wolf;
		delete wildebeest;
		delete lion;
		// Seam point - insert another continent, violates open/closed principle.
		cout << " ~AnimalWorld\n" << endl; }
public:
	void runFoodChain(Continent continent) {
		cout << " " << ids[continent] << " Continent:\n";
		switch(continent) {
		case NorthAmerica:
			bison->graze();
			bison->mate(bison);
			bison->evade(wolf);
			wolf->eat(bison);
			wolf->mate(wolf);
			wolf->hunt();
			break;
		case Africa:
			wildebeest->graze();
			wildebeest->mate(wildebeest);
			wildebeest->evade(lion);
			lion->eat(wildebeest);
			lion->mate(lion);
			lion->hunt();
			break;
		// Seam point - insert another continent, violates open/closed principle.
		default:
			throw "OOPS!";
		}
	}
};

void demo() {
	AnimalWorld simulation;
	Continent continents[] = { NorthAmerica, Africa };
	unsigned size = sizeof(continents)/sizeof(*continents);
	for(size_t i=0; i<size; i++) {
		simulation.runFoodChain(continents[i]);
		cout << endl;
	}
}

}

}

#endif /* ABSTRACTFACTORY_H_ */
