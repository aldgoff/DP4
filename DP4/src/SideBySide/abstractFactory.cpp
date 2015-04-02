#include "sideBySide.h"

namespace side_by_side {







class Entity1 {			// If the families are varying...
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

class AbstractFactory {	// If the families are varying...
public: virtual ~AbstractFactory() {}
public:
	virtual Entity1* create_entity_1()=0;
	virtual Entity2* create_entity_2()=0;
};
class FactoryAble : public AbstractFactory {
public:
	Entity1* create_entity_1() { return new Entity1_Able; }
	Entity2* create_entity_2() { return new Entity2_Able; }
};
class FactoryBill : public AbstractFactory {
public:
	Entity1* create_entity_1() { return new Entity1_Bill; }
	Entity2* create_entity_2() { return new Entity2_Bill; }
};
class FactoryCain : public AbstractFactory {
public:
	Entity1* create_entity_1() { return new Entity1_Cain; }
	Entity2* create_entity_2() { return new Entity2_Cain; }
};
void clientAbstractFactory() {
	AbstractFactory* afs[] = {new FactoryAble, new FactoryBill, new FactoryCain};
	for(size_t i=0; i<COUNT(afs); i++) {
		AbstractFactory* af = afs[i];
		Entity1* ents1 = af->create_entity_1();
		Entity2* ents2 = af->create_entity_2();
		ents1->id();
		ents2->id();
		cout << endl;
	}
}
}
