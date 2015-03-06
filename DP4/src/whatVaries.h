/*
 * whatVaries.h
 *
 *  Created on: Feb 7, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_WHATVARIES_H_
#define DP4_SRC_WHATVARIES_H_

using namespace std;

/* Summary DP1 (Intro):
 * Single inheritance trees:
 *   1) If the algorithms are varying, use the Strategy pattern.
 *   2) If the interfaces are varying, use the Adapter pattern.
 *   3) If the API's are varying, use the Facade pattern.
 *   4) If the steps are varying, use the Template Method pattern.
 *   5) If the classes are varying, use the Factory Method pattern.
 *   6) If the options are varying, use the Decorator pattern.
 *   7) If the listeners are varying, use the Observer pattern.
 *   8) If the responders are varying, use the Chain of Responsibility pattern.
 * Multiple inheritance trees:
 *   9) If the abstractions & implementations are varying, use bridge pattern.
 *   A) If the families are varying, use the Abstract Factory pattern.
*/

char str[20];	// Used to improve formatting of tax amounts.

namespace if_data_varying {	// Obsolete concept.
								  // <rates>
double tax_WA(double amount) { return 0.066*amount; }
double tax_OR(double amount) { return 0.077*amount; }
double tax_CA(double amount) { return 0.088*amount; }
//...
double tax_HI(double amount) { return 0.099*amount; }
// Seam point - add Puerto Rico.

void demo() {
	cout << "  if_data_varying::demo().\n";
	double data[] = { 0.066, 0.077, 0.088, 0.099 };
	for(size_t i=0; i<sizeof(data)/sizeof(*data); i++) {
		cout << data[i];
	}
	cout << endl;
}

}

namespace grid {	// Text font set to 8 points.

/*  0
 *  1
 *  2
 *  3
 *  4
 *  5
 *  6
 *  7
 *  8
 *  9
 * 10
 * 11
 * 12
 * 13
 * 14
 * 15
 * 16
 * 17
 * 18
 * 19
 * 20
 * 21
 * 22
 * 23
 * 24
 * 25
 * 26
 * 27
 * 28
 * 29
 * 30
 * 31
 * 32
 * 33
 * 34
 * 35
 * 36
 * 37
 * 38
 * 39
 * 40
 * 41
 * 42
 * 43
 */
}

namespace strategy {

namespace antiPattern_ifelse {	// If tax rates are varying, model as doubles.

struct Data {
	double		amount;
	const char*	state;
};
Data data[] = {
	{ 10.00, "WA" },
	{ 20.00, "OR" },
	{ 30.00, "CA" },
	{ 40.00, "HI" },
};

double tax(double amount, const char* state) {	// Maintenance headache. Client
	double rate = 0.00;						// code not closed to modification.

	if(		!strcmp(state, "WA"))
		rate = 0.066;
	else if(!strcmp(state, "OR"))
		rate = 0.077;
	else if(!strcmp(state, "CA"))
		rate = 0.088;
	else if(!strcmp(state, "HI"))
		rate = 0.099;
	// Seam point: insert another state & rate (violates open/closed principle).
	else {
		throw "OOPS";	// Exception handling, complicates logic of client code.
	}

	return rate*amount;
}

void demo() {
	cout << "antiPattern_ifelse::demo().\n";
	for(size_t i=0; i<sizeof(data)/sizeof(Data); i++) {
		sprintf(str, "$%.2f", tax(data[i].amount, data[i].state));
		cout << "  " << i+1 << ") tax = " << str << ".\n";
	}
	cout << endl;
}

}

namespace abstract_over_doubles {	// Variables: variation over built-in type.
















struct Data {
	double amount;
	double rate;
};
Data data[] = {		// But how to get correct tax rate into the data?
	{ 10.00, 0.066 },
	{ 20.00, 0.077 },
	{ 30.00, 0.088 },
	{ 40.00, 0.099 },
};

double tax(double amount, double rate) {  // Client code closed to modification.
	return rate*amount;
}

void demo() {
	cout << "abstract_over_doubles::demo().\n";
	for(size_t i=0; i<sizeof(data)/sizeof(Data); i++) {
		sprintf(str, "$%.2f", tax(data[i].amount, data[i].rate));
		cout << "  " << i+1 << ") tax = " << str << ".\n";
	}
	cout << endl;
}

}

namespace vary_tax_rate_by_state {	// Map state to tax rate.

enum State {
	WA,
	OR,
	CA,
	HI,
	// Seam point - add a state.
};
double rates[] = {
	0.066,
	0.077,
	0.088,
	0.099,
	// Seam point - add a rate.
};

struct Data {
	double	amount;
	State	state;
};
Data data[] = {		// Map states to tax rates with enums and arrays.
	{ 10.00, WA },
	{ 20.00, OR },
	{ 30.00, CA },
	{ 40.00, HI },
};

double tax(double amount, double rate) {  // Client code closed to modification.
	return rate*amount;
}

void demo() {
	cout << "vary_tax_rate_by_state::demo().\n";
	for(size_t i=0; i<sizeof(data)/sizeof(Data); i++) {
		sprintf(str, "$%.2f", tax(data[i].amount, rates[data[i].state]));
		cout << "  " << i+1 << ") tax = " << str << ".\n";
	}
	cout << endl;
}

}

namespace contingency_forces {

double byState() { return 0.060; }	// Simple model for academic purposes.
bool electionYear() { return true; }
bool luxurious(double amount) { return amount > 10000.00; }
double teired(double amount) {
	if(		amount < 100.00)	return 0.050;
	else if(amount < 1000.00)	return 0.065;
	else if(amount < 10000.00)	return 0.075;
	else					 	return 0.085;
}
// ... additional special cases.

}

namespace antiPattern_switch {	// If tax algorithms vary, model as TaxStrategy.

using namespace contingency_forces;

enum CountryCode {
	USA,
	Canada,
	Germany,
	Russia,
};
struct Data {
	double	 	amount;
	CountryCode country;
};
Data data[] = {
	{ 10.00, USA },
	{ 20.00, Canada },
	{ 30.00, Germany },
	{ 40.00, Russia },
};

double tax(double amount, CountryCode country) { // Maintenance headache. Client
	switch(country) {						 // code not closed to modification.
	case USA:					return byState()*amount;		break;
	case Canada:
		if(electionYear())		return 0.075*amount;
		else					return 0.065*amount;			break;
	case Germany:
		if(luxurious(amount))	return 0.088*amount;
		else					return 0.077*amount;			break;
	case Russia:				return teired(amount)*amount;	break;
	// Seam point: insert another country (violates open/closed principle).
	default:
	throw "OOPS";	// Exception handling, complicates logic of client code.
	break;
	}
}

void demo() {
	cout << "antiPattern_algorithms::demo().\n";
	for(size_t i=0; i<sizeof(data)/sizeof(Data); i++) {
		sprintf(str, "$%.2f", tax(data[i].amount, data[i].country));
		cout << "  " << i+1 << ") tax = " << str << ".\n";
	}
	cout << endl;
}
}

namespace abstract_over_TaxStrategy {	// Polymorphism: variation over a class.

using namespace contingency_forces;

class TaxStrategy {
public: virtual ~TaxStrategy() {}
public:
	virtual double rate(double amount=0) const { return 0.00; }
};
class ByState : public TaxStrategy {
public:
	double rate(double amount=0) const {
		return byState();
	}
};
class ByElectionYear : public TaxStrategy {
public:
	double rate(double amount=0) const {
		if(electionYear())
			return 0.075;
		else
			return 0.065;
	}
};
class ByLuxuriousness : public TaxStrategy {
public:
	double rate(double amount=0) const {
		if(luxurious(amount))
			return 0.088;
		else
			return 0.077;
	}
};
class ByTier : public TaxStrategy {
public:
	double rate(double amount=0) const {
		return teired(amount);
	}
};
// Seam point - add a tax strategy (follows open/closed principle).








struct Data {
	double	 	 amount;
	TaxStrategy* taxStrategy;
};
Data data[] = {			   // But how to get correct tax strategy into the data?
	{ 10.00, new ByState },
	{ 20.00, new ByElectionYear },
	{ 30.00, new ByLuxuriousness },
	{ 40.00, new ByTier },
};

double tax(double amount, const TaxStrategy* tax) {	// Client code closed
	return tax->rate()*amount;						// to modifications.
}

void demo() {
	cout << "abstract_over_TaxStrategy::demo().\n";
	for(size_t i=0; i<sizeof(data)/sizeof(Data); i++) {
		sprintf(str, "$%.2f", tax(data[i].amount, data[i].taxStrategy));
		cout << "  " << i+1 << ") tax = " << str << ".\n";
	}
	cout << endl;
}

}

namespace vary_tax_strategy_by_country {	// Map country to tax strategy.

using namespace contingency_forces;

class TaxStrategy {
public: virtual ~TaxStrategy() {}
public:
	virtual double rate(double amount=0) const { return 0.00; }
};
class ByState : public TaxStrategy {
public:
	double rate(double amount=0) const {
		return byState();
	}
};
class ByElectionYear : public TaxStrategy {
public:
	double rate(double amount=0) const {
		if(electionYear())
			return 0.075;
		else
			return 0.065;
	}
};
class ByLuxuriousness : public TaxStrategy {
public:
	double rate(double amount=0) const {
		if(luxurious(amount))
			return 0.088;
		else
			return 0.077;
	}
};
class ByTier : public TaxStrategy {
public:
	double rate(double amount=0) const {
		return teired(amount);
	}
};
// Seam point: add a tax strategy (follows open/closed principle).

class Country {
public:
	const TaxStrategy*	tax;
public:
	Country(const TaxStrategy* tax) : tax(tax) {}
};
class USA : public Country {
public:
	USA(const TaxStrategy* tax) : Country(tax) {}
};
class Canada : public Country {
public:
	Canada(const TaxStrategy* tax) : Country(tax) {}
};
class Germany : public Country {
public:
	Germany(const TaxStrategy* tax) : Country(tax) {}
};
class Russia : public Country {
public:
	Russia(const TaxStrategy* tax) : Country(tax) {}
};
// Seam point - add a country (follows open/closed principle).

struct Data {
	double	 amount;
	Country* country;
};
Data data[] = {	// Map countries to tax strategies by composition.
	{ 10.00, new USA(new ByState) },
	{ 20.00, new Canada(new ByElectionYear) },
	{ 30.00, new Germany(new ByLuxuriousness) },
	{ 40.00, new Russia(new ByTier) },
};

double tax(double amount, const TaxStrategy* tax) {	// Client code closed
	return tax->rate()*amount;						// to modifications.
}

void demo() {
	cout << "vary_tax_strategy_by_country::demo().\n";
	for(size_t i=0; i<sizeof(data)/sizeof(Data); i++) {
		sprintf(str, "$%.2f", tax(data[i].amount, data[i].country->tax));
		cout << "  " << i+1 << ") tax = " << str << ".\n";
	}
	cout << endl;
}

}

}

namespace adapter {

namespace antiPattern_ {}
namespace abstract_ {}
namespace vary_ {}

}


#ifdef experimental
// Probably need to add... using namespace strategy;

namespace experiment_polymorphic_refs_dtor {

namespace abstractOverTaxStrategy {	// Polymorphism - allow variation over a class.

class TaxStrategy {
//public: virtual ~TaxStrategy() {}
public:
	virtual double rate(double amount=0) const { return 0.00; }			// Alternative
	virtual double operator()(double amount=0) const { return 1.23; }	// implementations.
};

double taxRate(double amount, TaxStrategy* tax) {	// Client code closed to modifications.
	return tax->rate()*amount;
}
double tax(double amount, TaxStrategy* tax) {	// Client code closed to modifications.
	return (*tax)()*amount;
}

class ByState : public TaxStrategy {
public:
	double operator()(double amount=0) const {
		return antiPattern_switch::byState();
	}
};
class ByElectionYear : public TaxStrategy {
public:
	double operator()(double amount=0) const {
		if(antiPattern_switch::electionYear())
			return 0.075;
		else
			return 0.065;
	}
};
class ByLuxuriousness : public TaxStrategy {
public:
	double operator()(double amount=0) const {
		if(antiPattern_switch::luxurious(amount))
			return 0.088;
		else
			return 0.077;
	}
};
class ByTier : public TaxStrategy {
public:
	double operator()(double amount=0) const {
		return antiPattern_switch::teired(amount);
	}
};

}

namespace abstractOverTaxRef {

class TaxRef {
public: virtual ~TaxRef() {}
public:
	virtual double operator()(double amount=0) { return 0.00; }
};

}

namespace abstractByComposition {

using namespace abstractOverTaxStrategy;

class Country {
public:
	const TaxStrategy&	tax;
	const TaxStrategy*	pTax;
public:
	Country(const TaxStrategy& tax, const TaxStrategy* pTax=new TaxStrategy) : tax(tax), pTax(pTax) {}
};

double tax(double amount, const TaxStrategy& tax) {
	return tax()*amount;
}

class USA : public Country {
public:
	USA(const TaxStrategy& tax) : Country(tax) {}
};
class Canada : public Country {
public:
	Canada(const TaxStrategy& tax, const TaxStrategy* pTax=new TaxStrategy) : Country(tax, pTax) {}
};
class Germany : public Country {
public:
	Germany(const TaxStrategy& tax) : Country(tax) {}
};
class Russia : public Country {
public:
	Russia(const TaxStrategy& tax) : Country(tax) {}
};

struct Data {
	double	 amount;
	Country* country;
};

class Base {
public: virtual ~Base() {}
public:
	virtual void run()		  const { cout << "  Base run().\n"; }
	virtual void operator()() const { cout << "  Base op().\n"; }
};
class D1 : public Base {
//public: virtual ~D1() {}
public:
	void run()		  const { cout << "  D1 run().\n"; }
	void operator()() const { cout << "  D1 op().\n"; }
};

class B {
public:
	const Base&	base;
public:
	B(const Base& base) : base(base) {}
};
class C : public B {
public:
	C(const Base& base) : B(base) {}
};

void demo() {
	cout << "whatVaries.h namespace abstractByComposition.\n";
	Country* ss = new Canada(ByElectionYear());
	cout << ss->tax() << endl;
	Data data[] = {
			{ 10.00, new USA(ByState()) },
			{ 20.00, new Canada(ByElectionYear(), new ByElectionYear) },
			{ 30.00, new Germany(ByLuxuriousness()) },
			{ 40.00, new Russia(ByTier()) },
	};

	for(size_t i=0; i<sizeof(data)/sizeof(Data); i++) {
		cout << "  " << i+1 << ") ";
		double amount = data[i].amount;
		cout << "amount = " << amount;
		Country* country = data[i].country;
		cout << " tax rates = " << country->tax() << ", " << (*(country->pTax))();
//		const TaxStrategy& tax = country->tax;
//		tax();
//		cout << tax(amount, country->tax);
//		const TaxStrategy& tax = data[i].country->tax;
		cout << "\n";
	}

	const Base& obj = D1();
	obj.run();
	obj();
	B* b = new C(obj);
	b->base.run();
	b->base();
	B* cc = new C(D1());
	cc->base.run();
	cc->base();

//	const TaxStrategy& strat = dynamic_cast<const TaxStrategy&>(ByElectionYear());
//	const TaxStrategy& strat = (const ByElectionYear&)ByElectionYear();
	const TaxStrategy& strat = ByElectionYear();
	cout << strat() << endl;
	Country* mine = new Canada(strat);
	cout << mine->tax() << endl;

	Country* yours = new Canada((const ByElectionYear&)ByElectionYear());
	cout << yours->tax() << endl;
}

}

namespace abstractOverCountries {	// Polymorphism - allow variation over a class.

class Country {
public: virtual ~Country() {}
public:
	virtual double rate(double amount=0) { return 0.00; }
};

double tax(double amount, Country* country) {	// Client code closed to modifications.
	return country->rate()*amount;
}

class USA : public Country {
public:
	double rate() {
		return antiPattern_switch::byState();
	}
};
class Canada : public Country {
public:
	double rate() {
		if(antiPattern_switch::electionYear())
			return 0.075;
		else
			return 0.065;
	}
};
class Germany : public Country {
public:
	double rate(double amount) {
		if(antiPattern_switch::luxurious(amount))
			return 0.088;
		else
			return 0.077;
	}
};
class Russia : public Country {
public:
	double rate(double amount) {
		return antiPattern_switch::teired(amount);
	}
};

}

namespace virtual_dtor_bug {	// Compiler bug: polymorphic refs with virtual dtor.

class StrategyBase_VirtualDtor {
public:
	virtual ~StrategyBase_VirtualDtor() {};
public:
	virtual void run() 		  const { cout << "  StrategyBase_VirtualDtor run().\n"; }
	virtual void operator()() const { cout << "  StrategyBase_VirtualDtor Op().\n"; }
};
class StrategyD1_VirtualDtor : public StrategyBase_VirtualDtor {
public:
	void run()		  const { cout << "  StrategyD1_VirtualDtor run().\n"; }
	void operator()() const { cout << "  StrategyD1_VirtualDtor Op().\n"; }
};

class StrategyBase_RegularDtor {
public:
//	virtual ~StrategyBase_RegularDtor() {};	// Really?!?
	~StrategyBase_RegularDtor() {};
public:
	virtual void run() 		  const { cout << "  StrategyBase_RegularDtor run().\n"; }
	virtual void operator()() const { cout << "  StrategyBase_RegularDtor Op().\n"; }
};
class StrategyD1_RegularDtor : public StrategyBase_RegularDtor {
public:
	void run()		  const { cout << "  StrategyD1_RegularDtor run().\n"; }
	void operator()() const { cout << "  StrategyD1_RegularDtor Op().\n"; }
};

class ClientBase {
public:
		StrategyBase_VirtualDtor* vdBasePtr;
  const StrategyBase_VirtualDtor& vdBaseRef;
		StrategyBase_RegularDtor* rdBasePtr;
  const StrategyBase_RegularDtor& rdBaseRef;
public:
	virtual ~ClientBase() {}
	ClientBase(
			StrategyBase_VirtualDtor* vdBasePtr,
	  const	StrategyBase_VirtualDtor& vdBaseRef,
			StrategyBase_RegularDtor* rdBasePtr,
	  const	StrategyBase_RegularDtor& rdBaseRef)
			: vdBasePtr(vdBasePtr), vdBaseRef(vdBaseRef),
			  rdBasePtr(rdBasePtr), rdBaseRef(rdBaseRef)
	  {}
};
class ClientD1 : public ClientBase {
public:
	ClientD1(
			StrategyBase_VirtualDtor* vdBasePtr,
	  const	StrategyBase_VirtualDtor& vdBaseRef,
	  	  	StrategyBase_RegularDtor* rdBasePtr,
	  const	StrategyBase_RegularDtor& rdBaseRef)
			: ClientBase(vdBasePtr, vdBaseRef, rdBasePtr, rdBaseRef) {}
};

void demo() {

	cout << "virtual_dtor_bug::demo()\n";
	cout << "  ** 24 element phase space, 4 Dimensions (2x2x3x2)...\n";
	cout << "     1) Pointers/references\n";
	cout << "     2) Method/Op()\n";
	cout << "     3) Virtual/regular/default dtor\n";
	cout << "     4) Explicit/implicit construction\n";
	cout << endl;

	ClientBase* clientD1 = new ClientD1(
							new StrategyD1_VirtualDtor,
							StrategyD1_VirtualDtor(),
							new StrategyD1_RegularDtor,
							StrategyD1_RegularDtor());

	cout << "  Works with pointers/method & op()/virtual dtor.\n";
	cout << "    "; clientD1->vdBasePtr->run();
	cout << "    "; (*clientD1->vdBasePtr)();
	cout << endl;

	cout << "  Fails with references/method & op()/virtual dtor.\n";
	cout << "    "; clientD1->vdBaseRef.run();
	cout << "    "; clientD1->vdBaseRef();
	cout << endl;

	cout << "  Works with pointers/method & op()/regular&default dtor.\n";
	cout << "    "; clientD1->rdBasePtr->run();
	cout << "    "; (*clientD1->rdBasePtr)();
	cout << endl;

	cout << "  Works with references/method & op()/default dtor, but fails w/ regular dtor.\n";
	cout << "    "; clientD1->rdBaseRef.run();
	cout << "    "; clientD1->rdBaseRef();
	cout << endl;

	const StrategyD1_VirtualDtor& sd1vd = StrategyD1_VirtualDtor();
	const StrategyD1_RegularDtor& sd1rd = StrategyD1_RegularDtor();
	ClientBase* clientD1_1 = new ClientD1(
							new StrategyD1_VirtualDtor,
							sd1vd,
							new StrategyD1_RegularDtor,
							sd1rd);

	cout << "  Works with pointers & refs/method & op()/virtual & default dtor w/ explicit construction.\n";
	cout << "    "; clientD1_1->vdBasePtr->run();
	cout << "    "; (*clientD1_1->vdBasePtr)();
	cout << "    "; clientD1_1->rdBaseRef.run();
	cout << "    "; clientD1_1->rdBaseRef();
	cout << endl;

	cout << "  Analysis: fails for refs with non default dtors w/ implicit construction.\n";
	cout << "  However, refs were all const, pointers weren't; need one more test.\n";
	cout << "  Are you kidding me?!?\n" << endl;
}

}

namespace const_ref_ptr_bug {	// Polymorphism broken for refs (arg ctor, non defalt dtor).

class Strategy {
public: virtual ~Strategy() {}
public:
	virtual void run()		  const { cout << "  Strategy run().\n"; }
	virtual void operator()() const { cout << "  Strategy op().\n"; }
};
class Algorithm1 : public Strategy {
public:
	void run()		  const { cout << "  Algorithm1 run().\n"; }
	void operator()() const { cout << "  Algorithm1 op().\n"; }
};

class ClientBase {
protected:
	Strategy*	ptr;
	const Strategy&	ref;
public:
	ClientBase(Strategy* ptr, const Strategy& ref) : ptr(ptr), ref(ref) {}
	void run() {
		ptr->run();
		(*ptr)();
		ref.run();
		ref();
	}
};
class ClientD1 : public ClientBase {
public:
	ClientD1(Strategy* ptr, const Strategy& ref) : ClientBase(ptr, ref) {}
};

void demo() {
	cout << "  const_ref_ptr_bug::demo().\n";
	cout << endl;

	Strategy* algorPtr1 = new Algorithm1;	// Works.
	algorPtr1->run();
	(*algorPtr1)();
	cout << endl;

	const Strategy& algorRef1 = Algorithm1();	// Works.
	algorRef1.run();
	algorRef1();
	cout << endl;

	ClientBase* client = new ClientD1(algorPtr1, algorRef1);	// Works.
	client->run();
	cout << endl;

	client = new ClientD1(new Algorithm1(), Algorithm1());	// Fails for
	client->run();											// virtual & regular dtor,
	cout << endl;											// works for default dtor.
}

}

namespace ref_study {

class Base {
public:
	Base() { cout << "  ** Base ctor.\n"; }
	virtual ~Base() { cout << "  -- Base dtor.\n"; }
public:
	virtual void run() { cout << "  base.run().\n"; }
	virtual void ran() const { cout << "  base.ran().\n"; }
};
class Dev : public Base {
public:
	Dev() { cout << "  ** Dev ctor.\n"; }
	~Dev() { cout << "  -- Dev dtor.\n"; }
public:
	void run() { cout << "  dev.run().\n"; }
	void ran() const { cout << "  dev.ran().\n"; }
};

void func(Base& ref) {
	ref.run();
}
void fanc(const Base& ref) {
	ref.ran();
}

void demo() {
	cout << "  ref_study::demo().\n";
	int m = 13;
	int n = 14;
	float sam = 1.0;
	string iam = "Sam I am.";
	int& r = n;
	r = m;
	cout << "  " << r << "\n";
	r = sam;
	cout << "  " << r << "\n";
//	r = iam;	// Cannot convert string to int.
	cout << endl;

	if(true) { cout << "  Free floating Base() & Dev().\n";	// OK.
		Base();
		Dev();
	}
	cout << endl;

	if(true) {	cout << "  Assign and ref constructed Base().\n";	// OK.
		Base b = Base();
		func(b);
		cout << "  Ref constructed Base().\n";
		Base&	rb = b;
		func(rb);
	}
	cout << endl;

	if(true) {	cout << "  Assign constructed Dev() to Dev.\n";	// OK.
		Dev d = Dev();
		d.run();
		func(d);
		fanc(d);
	}
	cout << endl;

	if(true) {	cout << "  Assign new Dev to Base*.\n";	// OK.
		Base* dp = new Dev;
		dp->run();
		func(*dp);
		fanc(*dp);
		delete dp;
	}
	cout << endl;

	if(true) {	cout << "  Init new Dev to Base*.\n";	// OK.
		Base* dp(new Dev);
		dp->run();
		func(*dp);
		fanc(*dp);
		delete dp;
	}
	cout << endl;

	if(true) {	cout << "  Construct Base() to Base, w/ cctor & assignment op.\n";	// OK.
		int x(1);
		cout << "  " << x << ".\n";
		Base b = Base();
		b.ran();
		Base c(b);	// Cctor.
		c.ran();
		Base a = b;	// Assignment operator.
		a.ran();
	}
	cout << endl;

	if(true) { cout << "  Assign constructed Dev() to Base.\n";	// Unexpected behavior.
//		int sam[] = { 1,2,3,4,5 };	// Mash stack.
		Base d = Dev();
		d.run();
		func(d);
	}
	cout << endl;

	if(true) { cout << "  Inits of built-in types.\n";	// .
	int x = 1;
	int y(2);
	int z(int(3));
	cout << "  " << int(0) << x << y << z << endl;
	Dev().ran();
	Dev e = Dev();
	const Dev one = Dev();
	Dev f(one);
	Dev g(Dev());
	cout << endl;

	Dev& d(Dev());
	Dev c = Dev();
	c.run();
//	d.ran();
	}
	cout << endl;

	if(true) { cout << "  Assign constructed Dev() to const Base&.\n";	// OK.
//		Base& rd = Dev();
//		rd.run();
//		func(rd);
		const Base& rd = Dev();
		rd.ran();
		fanc(rd);
		const Base& id(Dev());
//		id.ran();
//		fanc(id);
	}
	cout << endl;

	cout << "  Ref constructed dev.\n";
//	Base&	rd = e;
//	func(rd);
	cout << endl;

//	Base& a = Dev();	// Invalid init of non-const ref.
//	const Base& a = Dev();
////	a.run();	// Passing const ref as 'this' arg discards qualifiers.
//	a.ran();
//	fanc(a);
	fanc(Dev());
	cout << endl;

}

}

}

#endif

#endif /* DP4_SRC_WHATVARIES_H_ */
