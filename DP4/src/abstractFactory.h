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

namespace lecture {

/* Consider the challenge of representing algebras.
 * In this example we will identify 3, these are the families that are varying;
 *   1) Counting algebra
 *   2) Additive algebra
 *   3) Multiplicative algebra
 * Each algebra is a 'Family', and each must implement the following operations;
 *   1) Identity element (0, 1)
 *   2) Scale (post & pre successor elements)
 *   3) Forward operation (such as '+')
 *   4) Reverse operation (such as '/')
 */

namespace abstract_factory_legacy {	// Not used.

void demo() {
	cout << endl;
}

}

namespace abstract_factory_problem {	// Not used.

void demo() {
	cout << endl;
}

}

namespace abstract_factory_solution {

class Identity {	// Identity element (0, 1).
public: virtual ~Identity() { cout << " ~Identity\n"; }
	virtual string value()=0;
};
class Nothing : public Identity {
public: ~Nothing() { cout << "  ~Nothing"; }
public:
	string value() { return "[ ]"; }
};
class Zero : public Identity {
public: ~Zero() { cout << "  ~Zero"; }
public:
	string value() { return "[0]"; }
};
class One : public Identity {
public: ~One() { cout << "  ~One"; }
public:
	string value() { return "[1.0]"; }
};

class Scale {		// Pre and post successors ( 1 2 3 <> 2 1 0).
protected:
	char str[80];
public: virtual ~Scale() { cout << " ~Scale\n"; }
	virtual double inc(double x)=0;
	virtual double dec(double x)=0;
	virtual string convert(double x) { return ""; }
};
class Ticks : public Scale {
public: ~Ticks() { cout << "  ~Ticks"; }
public:
	double inc(double x) { return x + 1; }
	double dec(double x) { return (x>0) ? x - 1 : -1; }
	string convert(double x) {
		string ticks = "";
		if(x == 0)	return "_";
		if(x < 0)	return "<0?!?";
		for(int i=0; i<x; i++)
			ticks += "|";
		return ticks;
	}
};
class Null : public Scale {
public: ~Null() { cout << "  ~Null"; }
public:
	double inc(double x) { return x + 1; }
	double dec(double x) { return x - 1; }
	string convert(double x) {
		sprintf(str, "%.0f", x);
		return str;
	}
};
class Unity : public Scale {
public: ~Unity() { cout << "  ~Unity"; }
public:
	double inc(double x) { return x * 2; }
	double dec(double x) { return x / 2; }
	string convert(double x) {
		sprintf(str, "%.3f", x);
		return str;
	}
};

class ForwardOp {	// Forward op, (count, +, *).
protected:
	char str[80];
public: virtual ~ForwardOp() { cout << " ~ForwardOp\n"; }
	virtual string ops(double a, double b) { return "_"; }
};
class Count : public ForwardOp {
public: ~Count() { cout << "  ~Count"; }
public:
	string ops(double a, double b) {
		string ticks = "";
		if(a + b == 0)	return "_";
		for(int i=0; i<a; i++)
			ticks += "|";
		for(int i=0; i<b; i++)
			ticks += "|";
		return ticks;
	}
};
class Add : public ForwardOp {
public: ~Add() { cout << "  ~Add"; }
public:
	string ops(double a, double b) {
		sprintf(str, "%.0f", a+b);
		return str;
	}
};
class Multiply : public ForwardOp {
public: ~Multiply() { cout << "  ~Multiply"; }
public:
	string ops(double a, double b) {
		sprintf(str, "%.3f", a*b);
		return str;
	}
};

class ReverseOp {	// Reverse op; (take-away, -, /).
protected:
	char str[80];
public: virtual ~ReverseOp() { cout << " ~ReverseOp\n"; }
	virtual string ops(double a, double b) { return "_"; }
};
class TakeAway : public ReverseOp {
public: ~TakeAway() { cout << "  ~TakeAway"; }
public:
	string ops(double a, double b) {
		string ticks = "";
		if(a - b == 0)	return "_";
		if(a - b < 0)	return "<0?!?";
		for(int i=0; i<a-b; i++)
			ticks += "|";
		return ticks;
	}
};
class Subtract : public ReverseOp {
public: ~Subtract() { cout << "  ~Subtract"; }
public:
	string ops(double a, double b) {
		sprintf(str, "%.0f", a-b);
		return str;
	}
};
class Divide : public ReverseOp {
public: ~Divide() { cout << "  ~Divide"; }
public:
	string ops(double a, double b) {
		sprintf(str, "%.3f", a/b);
		return str;
	}
};

class FastHierarchy {	// Abstract Factory - families are varying.
public: virtual ~FastHierarchy() { cout << " ~FastHierarchy\n"; }
public:
	static FastHierarchy* createAlgebra(string id);
public:
	virtual Identity*  createIdentityElement()=0;
	virtual Scale* 	   createScale()=0;
	virtual ForwardOp* createForwardOp()=0;
	virtual ReverseOp* createReverseOp()=0;
};
class Counting : public FastHierarchy {			// Counting - level 0.
public: ~Counting() { cout << " ~Counting"; }
public:
	Identity*	createIdentityElement() {	return new Nothing; }
	Scale*		createScale() {	return new Ticks; }
	ForwardOp*	createForwardOp() {	return new Count; }
	ReverseOp*	createReverseOp() {	return new TakeAway; }
};
class Addition : public FastHierarchy {			// Addition - level 1.
public: ~Addition() { cout << " ~Addition"; }
public:
	Identity*	createIdentityElement() {	return new Zero; }
	Scale*		createScale() {	return new Null; }
	ForwardOp*	createForwardOp() {	return new Add; }
	ReverseOp*	createReverseOp() {	return new Subtract; }
};
class Multiplication : public FastHierarchy {	// Multiplication - level 2.
public: ~Multiplication() { cout << " ~Multiplication"; }
public:
	Identity*	createIdentityElement() {	return new One; }
	Scale*		createScale() {	return new Unity; }
	ForwardOp*	createForwardOp() {	return new Multiply; }
	ReverseOp*	createReverseOp() {	return new Divide; }
};

FastHierarchy* FastHierarchy::createAlgebra(string id) {
	if(id == "Counting")	return new Counting;
	else if(id == "Addition")	return new Addition;
	else if(id == "Multiplication")	return new Multiplication;
	else {
		throw "OOPS!";
	}
}

class ClientCode {
	Identity*	identity;
	Scale*		scale;
	ForwardOp*	forwardOp;
	ReverseOp*	reverseOp;
public:
	ClientCode(FastHierarchy* algebra)
		: identity(algebra->createIdentityElement()),
		  scale(algebra->createScale()),
		  forwardOp(algebra->createForwardOp()),
		  reverseOp(algebra->createReverseOp()) {
	}
	~ClientCode() {
		delete identity;
		delete scale;
		delete forwardOp;
		delete reverseOp;
		cout << "  ~ClientCode\n" << endl;
	}
public:
	void compute() {
		cout << "  The identity element is " << identity->value() << "\n";

		double value = atoi(&(identity->value()[1]));	// Up scale.
		cout << "  ";
		for(int i=0; i<3; i++) {
			value = scale->inc(value);
			cout << scale->convert(value) << "  ";
		}
		value = scale->inc(value);
		cout << scale->convert(value);

		cout << " <> ";									// Down scale.
		for(int i=0; i<5; i++) {
			value = scale->dec(value);
			cout << scale->convert(value) << "  ";
		}
		value = scale->dec(value);
		cout << scale->convert(value) << "\n";

		cout << "  6 fop 2 = " << forwardOp->ops(6, 2) << "\n";	// Forward op.

		cout << "  6 rop 2 = " << reverseOp->ops(6, 2) << "\n";	// Reverse op.
		cout << "  2 rop 6 = " << reverseOp->ops(2, 6) << "\n";
	}
};

void demo() {
	string levels[] = { "Counting", "Addition", "Multiplication" };
	unsigned size = sizeof(levels)/sizeof(*levels);
	FastHierarchy* algebras[size];
	for(size_t i=0; i<size; i++) {
		cout << " " << levels[i] << " Level:\n";
		algebras[i] = FastHierarchy::createAlgebra(levels[i]);
		ClientCode client(algebras[i]);
		client.compute();
		cout << endl;
	}

	for(size_t i=0; i<size; i++) {
		delete algebras[i];
	}

	cout << endl;
}

}

}

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

namespace abstract_factory_legacy {	// Not used.

void demo() {
	cout << endl;
}

}

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

namespace complicated_relationships {	// Not used.

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

namespace abstract_factory_3 {	// Not used.

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
