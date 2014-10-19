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
 * URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Abstract_Factory
 */

#ifndef ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_H_

namespace complicated_relationships {

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

enum Continents {
	NorthAmerica,
	Africa,
};

// North American animals.
class Bison;
class Wolf;

class Bison {
	string name;
public:
	Bison() : name("Bison") {}
	string getName() { return name; }
	void mate(Bison* other) { cout << "More " << name << "\n"; }
	void graze() { cout << "Bigger " << name << "\n"; }
	void evade(Wolf* wolf);
};
class Wolf {
	string name;
public:
	Wolf() : name("Wolf") {}
	string getName() { return name; }
	void mate(Wolf* other) { cout << "More " << name << "\n"; }
	void hunt() { cout << "Smaller " << name << "\n"; }
	void eat(Bison* bison);
};

void Bison::evade(Wolf* wolf) { cout << name << " evades " << wolf->getName() << "\n"; }
void Wolf::eat(Bison* bison) { cout << name << " eats " << bison->getName() << "\n"; }

// African animals.
class Wildebeest;
class Lion;

class Wildebeest {
	string name;
public:
	Wildebeest() : name("Wildebeest") {}
	string getName() { return name; }
	void mate(Wildebeest* other) { cout << "More " << name << "\n"; }
	void graze() { cout << "Bigger " << name << "\n"; }
	void evade(Lion* lion);
};
class Lion {
	string name;
public:
	Lion() : name("Lion") {}
	string getName() { return name; }
	void mate(Lion* other) { cout << "More " << name << "\n"; }
	void hunt() { cout << "Smaller " << name << "\n"; }
	void eat(Wildebeest* wildebeest);
};

void Wildebeest::evade(Lion* lion) { cout << name << " evades " << lion->getName() << "\n"; }
void Lion::eat(Wildebeest* wildebeest) { cout << name << " eats " << wildebeest->getName() << "\n"; }

void runFoodChain(Continents continent) {
	Wolf*	wolf = 0;
	Bison*	bison = 0;
	Lion*		lion = 0;
	Wildebeest*	wildebeest = 0;

	switch(continent) {
	case NorthAmerica:
		wolf = new Wolf;
		bison = new Bison;
		bison->graze();
		bison->mate(bison);
		bison->evade(wolf);
		wolf->eat(bison);
		wolf->mate(wolf);
		wolf->hunt();
		break;
	case Africa:
		lion = new Lion;
		wildebeest = new Wildebeest;
		wildebeest->graze();
		wildebeest->mate(wildebeest);
		wildebeest->evade(lion);
		lion->eat(wildebeest);
		lion->mate(lion);
		lion->hunt();
		// Seam - new relationship, scales as number of continents.
		break;
	// Seam - new continent, scales as number of relationships.
	}
}

void demo() {
	cout << "<< Hello Abstract Factory Problem >>\n";

	runFoodChain(NorthAmerica);	cout << endl;
	runFoodChain(Africa);		cout << endl;
}

}

namespace abstract_factory_3 {

class Herbivore;
class Carnivore;

class Herbivore {
	string name;
public:
	Herbivore(string name) : name(name) {}
	virtual ~Herbivore() {}
	string getName() { return name; }
	void mate(Herbivore* other) { cout << "More " << name << "\n"; }
	void graze() { cout << "Bigger " << name << "\n"; }
	void evade(Carnivore* carnivore);
};
class Bison : public Herbivore {
public:
	Bison() : Herbivore("Bison") {}
};
class Wildebeest : public Herbivore {
public:
	Wildebeest() : Herbivore("Wildebeest") {}
};

class Carnivore {
	string name;
public:
	Carnivore(string name) : name(name) {}
	virtual ~Carnivore() {}
	string getName() { return name; }
	void mate(Carnivore* other) { cout << "More " << name << "\n"; }
	void hunt() { cout << "Smaller " << name << "\n"; }
	void eat(Herbivore* herbivore);
};
class Wolf : public Carnivore {
public:
	Wolf() : Carnivore("Wolf") {}
};
class Lion : public Carnivore {
public:
	Lion() : Carnivore("Lion") {}
};

void Herbivore::evade(Carnivore* carnivore) { cout << name << " evades " << carnivore->getName() << "\n"; }
void Carnivore::eat(Herbivore* herbivore) { cout << name << " eats " << herbivore->getName() << "\n"; }

class ContinentFactory {
public:
	enum Continents {
		NorthAmericaID,
		AfricaID,
	};
public:
	static ContinentFactory* newContinent(Continents continentID);
	virtual ~ContinentFactory() {}
	virtual Herbivore* createHerbivore()=0;
	virtual Carnivore* createCarnivore()=0;
};
class NorthAmerica : public ContinentFactory {
public:
	Herbivore* createHerbivore() { return new Bison; }
	Carnivore* createCarnivore() { return new Wolf; }
};
class Africa : public ContinentFactory {
public:
	Herbivore* createHerbivore() { return new Wildebeest; }
	Carnivore* createCarnivore() { return new Lion; }
};

ContinentFactory* ContinentFactory::newContinent(Continents continentID) {
	switch(continentID) {
	case NorthAmericaID: return new NorthAmerica;
	case AfricaID:		 return new Africa;
	};
	throw "oops";
}

class AnimalWorld {
	Herbivore* herbivore;
	Carnivore* carnivore;
public:
	AnimalWorld(ContinentFactory::Continents continentID) {
		ContinentFactory* continent = ContinentFactory::newContinent(continentID);
		herbivore = continent->createHerbivore();
		carnivore = continent->createCarnivore();
	}
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
	cout << "<< Hello Abstract Factory Solution >>\n";

	AnimalWorld(ContinentFactory::NorthAmericaID).runFoodChain();	cout << endl;
	AnimalWorld(ContinentFactory::AfricaID).runFoodChain();			cout << endl;
}

}

#endif /* ABSTRACTFACTORY_H_ */
