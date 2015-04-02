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

namespace abstract_factory_solution {

class Herbivore;
class Carnivore;

class Herbivore {
protected:
	string name;
public:
	Herbivore(const string& name) : name(name) {}
	virtual ~Herbivore() { cout << " ~Herbivore"; }
public:
	string Name() { return name; }
public:
	virtual void graze()			{ cout << " Abstract graze().\n"; }
	virtual void mate(Herbivore*)	{ cout << " Abstract mate().\n"; }
	virtual void evade(Carnivore*)	{ cout << " Abstract evade().\n"; }
};
class Bison : public Herbivore {
public:
	Bison() : Herbivore("Bison") {}
	~Bison() { cout << "  ~Bison"; }
public:
	void graze() {
		cout << "  " << name << " eats grass.\n";
	}
	void mate(Herbivore* other) {
		cout << "  Mate with " << other->Name() << " herd.\n";
	}
	void evade(Carnivore* other);
};
class Wildebeest : public Herbivore {
public:
	Wildebeest() : Herbivore("Wildebeest") {}
	~Wildebeest() { cout << "  ~Wildebeest"; }
public:
	void graze() {
		cout << "  " << name << " eats thrash.\n";
	}
	void mate(Herbivore* other) {
		cout << "  Breed with " << other->Name() << ".\n";
	}
	void evade(Carnivore* other);
};
// Seam point - add another Herbivore, follows open/closed principle.

class Carnivore {
protected:
	string name;
public:
	Carnivore(const string& name) : name(name) {}
	virtual ~Carnivore() { cout << " ~Carnivore"; }
public:
	string Name() { return name; }
public:
	virtual void eat(Herbivore*)	{ cout << " Abstract eat().\n"; }
	virtual void mate(Carnivore*)	{ cout << " Abstract mate().\n"; }
	virtual void hunt()				{ cout << " Abstract hunt().\n"; }
};
class Wolf : public Carnivore {
public:
	Wolf() : Carnivore("Wolf") {}
	~Wolf() { cout << "  ~Wolf"; }
public:
	void eat(Herbivore* other) {
		cout << "  " << name << " eats a " << other->Name() << ".\n";
	}
	void mate(Carnivore* other)	{
		cout << "  Mate for life with another " << other->Name() << ".\n";
	}
	void hunt()	{
		cout << "  Hunt in packs.\n";
	}
};
class Lion : public Carnivore {
public:
	Lion() : Carnivore("Lion") {}
	~Lion() { cout << "  ~Lion"; }
public:
	void eat(Herbivore* other) {
		cout << "  " << name << " eats a " << other->Name() << ".\n";
	}
	void mate(Carnivore* other)	{
		cout << "  Mate with another " << other->Name() << ".\n";
	}
	void hunt()	{
		cout << "  Stalk prey.\n";
	}
};
// Seam point - add another Carnivore, follows open/closed principle.

void Bison::evade(Carnivore* other) {
	cout << "  Flee from pack of " << other->Name() << "s.\n";
}
void Wildebeest::evade(Carnivore* other) {
	cout << "  Flee from " << other->Name() << ".\n";
}

class ContinentAbstractFactory {
public:
	virtual ~ContinentAbstractFactory() { cout<<" ~ContinentAbstractFactory\n";}
public:
	static ContinentAbstractFactory* createContinent(string id);
	virtual Herbivore* createHerbivore()=0;
	virtual Carnivore* createCarnivore()=0;
};
class NorthAmerica : public ContinentAbstractFactory {
public: ~NorthAmerica() { cout<<"  ~NorthAmerica";}
	Herbivore* createHerbivore() { return new Bison; }
	Carnivore* createCarnivore() { return new Wolf; }
};
class Africa : public ContinentAbstractFactory {
public: ~Africa() { cout<<"  ~Africa";}
	Herbivore* createHerbivore() { return new Wildebeest; }
	Carnivore* createCarnivore() { return new Lion; }
};
// Seam point - add another continent, follows open/closed principle.

ContinentAbstractFactory* ContinentAbstractFactory::createContinent(string id) {
	if(id == "North America")	return new NorthAmerica;
	else if(id == "Africa")		return new Africa;
	// Seam point - insert another continent, violates open/closed principle.
	else {
		throw "OOPS!";
	}
}

class AnimalWorld {		// Client code - no seam points, closed to modification.
	Herbivore* herbivore;
	Carnivore* carnivore;
public:
	AnimalWorld(ContinentAbstractFactory* continent) {
		herbivore = continent->createHerbivore();
		carnivore = continent->createCarnivore();
	}
	~AnimalWorld() {
		delete herbivore;
		delete carnivore;
		cout << "  ~AnimalWorld\n";
	}
public:
	void runFoodChain() {
		herbivore->graze();
		herbivore->mate(herbivore);
		herbivore->evade(carnivore);
		carnivore->eat(herbivore);
		carnivore->mate(carnivore);
		carnivore->hunt();
	}
};

void demo() {
	string ids[] = { "North America", "Africa" };
	unsigned size = sizeof(ids)/sizeof(*ids);
	ContinentAbstractFactory* continents[size];
	for(size_t i=0; i<size; i++) {
		cout << " " << ids[i] << " Continent:\n";
		continents[i] = ContinentAbstractFactory::createContinent(ids[i]);
		{
		AnimalWorld simulation(continents[i]);
		simulation.runFoodChain();
		}
		cout << endl;
	}

	for(size_t i=0; i<size; i++) {
		delete continents[i];
	}

	cout << endl;
}

}

}

#endif /* ABSTRACTFACTORY_H_ */
