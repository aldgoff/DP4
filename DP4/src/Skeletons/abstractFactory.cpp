/*
 * abstractFactory.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace skeleton {

class Entity1 {
public: virtual ~Entity1() {}
public:	virtual void id()=0;
};
class Entity1_Able : public Entity1 {
public:	void id() { cout << "  Entity 1 Able.\n"; }
};
class Entity1_Bill : public Entity1 {
public:	void id() { cout << "  Entity 1 Bill.\n"; }
};
class Entity1_Cain : public Entity1 {
public:	void id() { cout << "  Entity 1 Cain.\n"; }
};

class Entity2 {
public: virtual ~Entity2() {}
public:	virtual void id()=0;
};
class Entity2_Able : public Entity2 {
public:	void id() { cout << "  Entity 2 Able.\n"; }
};
class Entity2_Bill : public Entity2 {
public:	void id() { cout << "  Entity 2 Bill.\n"; }
};
class Entity2_Cain : public Entity2 {
public:	void id() { cout << "  Entity 2 Cain.\n"; }
};

class Entity3 {
public: virtual ~Entity3() {}
public:	virtual void id()=0;
};
class Entity3_Able : public Entity3 {
public:	void id() { cout << "  Entity 3 Able.\n"; }
};
class Entity3_Bill : public Entity3 {
public:	void id() { cout << "  Entity 3 Bill.\n"; }
};
class Entity3_Cain : public Entity3 {
public:	void id() { cout << "  Entity 3 Cain.\n"; }
};

class Entity4 {
public: virtual ~Entity4() {}
public:	virtual void id()=0;
};
class Entity4_Able : public Entity4 {
public:	void id() { cout << "  Entity 4 Able.\n"; }
};
class Entity4_Bill : public Entity4 {
public:	void id() { cout << "  Entity 4 Bill.\n"; }
};
class Entity4_Cain : public Entity4 {
public:	void id() { cout << "  Entity 4 Cain.\n"; }
};

class AbstractFactory {	// If groups of objects are varying...
public: virtual ~AbstractFactory() {}
public:
	virtual Entity1* create_entity_1()=0;
	virtual Entity2* create_entity_2()=0;
	virtual Entity3* create_entity_3()=0;
	virtual Entity4* create_entity_4()=0;
};
class Factory_Able : public AbstractFactory {
public:
	Entity1* create_entity_1() { return new Entity1_Able; }
	Entity2* create_entity_2() { return new Entity2_Able; }
	Entity3* create_entity_3() { return new Entity3_Able; }
	Entity4* create_entity_4() { return new Entity4_Able; }
};
class Factory_Bill : public AbstractFactory {
public:
	Entity1* create_entity_1() { return new Entity1_Bill; }
	Entity2* create_entity_2() { return new Entity2_Bill; }
	Entity3* create_entity_3() { return new Entity3_Bill; }
	Entity4* create_entity_4() { return new Entity4_Bill; }
};
class Factory_Cain : public AbstractFactory {
public:
	Entity1* create_entity_1() { return new Entity1_Cain; }
	Entity2* create_entity_2() { return new Entity2_Cain; }
	Entity3* create_entity_3() { return new Entity3_Cain; }
	Entity4* create_entity_4() { return new Entity4_Cain; }
};

void clientAbstractFactory() {
	cout << "Abstract Factory\n";
	AbstractFactory* afs[] = { new Factory_Able, new Factory_Bill, new Factory_Cain};
	for(size_t i=0; i<COUNT(afs); i++) {
		AbstractFactory* af = afs[i];
		Entity1* ents1 = af->create_entity_1();
		Entity2* ents2 = af->create_entity_2();
		Entity3* ents3 = af->create_entity_3();
		Entity4* ents4 = af->create_entity_4();

		ents1->id();
		ents2->id();
		ents3->id();
		ents4->id();

		cout << endl;
	}
}

}
