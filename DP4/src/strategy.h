/*
 * strategy.h
 *
 * Desc: Define a family of interchangeable algorithms which can vary independently from the clients.
 *
 * Category: Behavioral
 *
 *  Created on: Mar 29, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Strategy
 *  	http://www.dofactory.com/net/strategy-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter9
 *  	http://sourcemaking.com/design_patterns/strategy
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

namespace homework {

/* Consider a sales order processing system.
 * It must compute tax amounts that depend on country.
 * The legacy code below is typical of how such a system may initially evolve.
 * However, it won't scale well.
 * Consider what's required to maintain these switch statements under new specs.
 * New specs:
 *   Add new tax rules for Canada
 *     Different rate for election years 7.5%
 *   Add Germany
 *     new tax rules luxury tax
 * This is shown in the code section under the strategy_problem namespace.
 * Refactor the legacy code using the strategy pattern.
 *   1) Implement the new specs
 *   2) Avoid code duplication
 *   3) Avoid need for exceptions
 *   4) Avoid having to change existing code as much as possible
 *   	a) New tax specs
 *   	c) New country
 *   5) Make sure you get the same results as from the problem namespace code
 */

namespace strategy_common {

enum Alternative {	// Domain (x).
	USA,
	CANADA,
	// Seam point 1 - insert new country code (violates open/closed principle).
	GERMANY,
};

const char* CountryName[] = {
	"USA",
	"Canada",
	// Seam point 2 - insert new country name (violates open/closed principle).
	"Germany",
};

struct SalesOrder {
	int			amount;
	double		price;
	Alternative	country;
};

double byState() { return 0.060; }	// Simple model for academic purposes.
bool electionYear() { return true; }
bool luxurious(double amount) { return amount > 10000.00; }

}

namespace strategy_legacy {

using namespace strategy_common;

// In tax file...
double taxAmount(int amount, double price, Alternative alt=USA) {
	switch(alt) {
	case USA:
		return byState()*amount*price;
		break;
	case CANADA:
		if(electionYear())
			return 0.075*amount*price;
		else
			return 0.065*amount*price;
		break;
	// Seam point 3 - insert new country (violates open/closed principle).
	default: throw "OOPS"; break;	// Error handling.
	}
}

void clientCode(SalesOrder& order) {
	char str[20];
	double tax = taxAmount(order.amount, order.price, order.country);
	sprintf(str, "$%.2f for %s order.", tax, CountryName[order.country]);
	cout << str << "\n";
}

void demo() {
	SalesOrder orders[] = {
		{ 5, 10.00, USA },
		{ 1, 20.00, CANADA },
	};
	for(size_t i=0; i<sizeof(orders)/sizeof(*orders); i++) {
		cout << "  " << i+1 << ") ";
		clientCode(orders[i]);
	}

	cout << endl;
}

}

namespace strategy_problem {

using namespace strategy_common;

// In tax file...
double taxAmount(int amount, double price, Alternative alt=USA) {
	switch(alt) {
	case USA:
		return byState()*amount*price;
		break;
	case CANADA:
		if(electionYear())	return 0.075*amount*price;
		else				return 0.065*amount*price;
		break;
	// Seam point 3 - insert new country (violates open/closed principle).
	case GERMANY:
		if(luxurious(amount))	return 0.088*amount*price;
		else					return 0.077*amount*price;
		break;
	default: throw "OOPS"; break;	// Error handling.
	}
}

void clientCode(SalesOrder& order) {
	char str[20];
	double tax = taxAmount(order.amount, order.price, order.country);
	sprintf(str, "$%.2f for %s order.", tax, CountryName[order.country]);
	cout << str << "\n";
}

void demo() {
	SalesOrder orders[] = {
		{ 5, 10.00, USA },
		{ 1, 20.00, CANADA },
		{ 2, 99.99, GERMANY },
	};
	for(size_t i=0; i<sizeof(orders)/sizeof(*orders); i++) {
		cout << "  " << i+1 << ") ";
		clientCode(orders[i]);
	}

	cout << endl;
}

}

namespace strategy_solution {

using namespace strategy_common;

class TaxStrategy {	// Range (y).
public: virtual ~TaxStrategy() { cout << "    TaxStrategy dtor\n"; }
public:
	virtual double rate(double amount=0) const =0;
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
// Seam point 1 - add another tax strategy (follows open/closed principle).

class Country {		// Domain (x).
public:
	const string name;
	TaxStrategy* taxStrategy;
public:
	Country(const string& name, TaxStrategy* taxStrategy)
	: name(name), taxStrategy(taxStrategy) {}
	~Country() { delete taxStrategy; }
};

struct Sales {
	int				amount;
	double			price;
	const Country&	country;
};

void clientCode(const Sales& order) {
	char str[20];
	double rate = order.country.taxStrategy->rate(order.amount);
	double tax = rate*order.amount*order.price;
	sprintf(str, "$%.2f for ", tax);
	cout << str << order.country.name << " order.\n";
}

void demo() {
	{
	Country usa = Country("USA",	 new ByState());
	Country can = Country("Canada",	 new ByElectionYear());
	Country ger = Country("Germany", new ByLuxuriousness());
	Sales orders[] = {
		{ 5, 10.00, usa },
		{ 1, 20.00, can },
		{ 2, 99.99, ger },
	};
	for(size_t i=0; i<sizeof(orders)/sizeof(*orders); i++) {
		cout << "  " << i+1 << ") ";
		clientCode(orders[i]);
	}
	}

	cout << endl;
}

}

}

/* Consider a sales order processing system.
 * It must compute tax amounts that depend on country.
 * The legacy code below is typical of how such a system may initially evolve.
 * However, it won't scale well.
 * The multiple switch statements are an Anti-Pattern.
 * Consider what's required to maintain these switch statements under new specs.
 * New specs:
 *   Add new tax rules for Canada
 *     Different rate for election years 6.9%
 *   Add new currency symbol for Quebec orders '#'
 *   Add Germany
 *     new tax rules 10.5%
 *     new currency symbol 'e'
 *   Add date format
 *     USA & Canada - MMDDYY
 *     Germany - DDMMCCYY
 * This is shown in the code section under the strategy_problem namespace.
 * Refactor the legacy code using the strategy pattern.
 *   1) Implement the new specs
 *   2) Avoid code duplication
 *   3) Avoid need for exceptions
 *   4) Avoid having to change existing code as much as possible
 *   	a) New tax specs
 *   	b) New currency symbol
 *   	c) New country
 *   5) Adding the date format spec will require changing existing code even with DP
 *   6) Make sure you get the same results as from the problem namespace code
 */

/* PS  I'm not entirely happy with this example,
 * it is simultaneously too complicated and too simplistic,
 * but it follows the development of chapter 9 in DPE.
 * As formulated, the strategy pattern is needed only for the tax calculation.
 * ... it's an academic exercise... :(
 */

namespace strategy_legacy {

enum CountryCode {
	USA,
	Canada,
};

const char* CountryName[] = {
	"USA",
	"Canada",
};

// In tax file...
double taxAmount(int num, double price, CountryCode cc=USA) {
	double tax = 0;

	switch(cc) {
	case USA:
		tax = 0.075*num*price;
		break;
	case Canada:
		tax = 0.065*num*price;
		break;
	default:
	throw "OOPS";
	break;
	}

	return tax;
}

// In currency file...
char currencySymbol(CountryCode cc=USA) {
	char symbol = ' ';

	switch(cc) {
	case USA:
		symbol = '$';
		break;
	case Canada:
		symbol = '$';
		break;
	default:
	throw "OOPS";
	break;
	}

	return symbol;
}

class SalesOrder {
public:
	int	 number;
	double	price;
	CountryCode countryCode;
public:
	void process() {
		char str[20];
		char   sym = currencySymbol(countryCode);
		double tax = taxAmount(number, price, countryCode);
		sprintf(str, "%c%.2f for %s order.", sym, tax, CountryName[countryCode]);
		cout << str << "\n";
	}
};

void demo() {
	SalesOrder orders[] = {
		{5, 10.00, USA},
		{1, 20.00, Canada},
	};

	for(size_t i=0; i<sizeof(orders)/sizeof(SalesOrder); i++) {
		cout << "  " << i+1 << ") ";
		orders[i].process();
	}

	cout << endl;
}

}

namespace strategy_problem {

enum CountryCode {
	USA,
	Canada,
	Germany,
	// Country seam point.
};

const char* CountryName[] = {
	"USA",
	"Canada",
	"Germany",
	// Country seam point.
};

// Run time requirements.
bool electionYear() { return true; }
bool Quebec() { return true; }

// In tax file...
double taxAmount(int num, double price, CountryCode cc=USA) {
	double tax = 0;

	switch(cc) {
	case USA:
		tax = 0.075*num*price;
		break;
	case Canada:
		if(electionYear())
			tax = 0.069*num*price;
		else
			tax = 0.065*num*price;
		break;
	case Germany:
		tax = 0.105*num*price;
		break;
	// Country seam point.
	default:
	throw "OOPS";
	break;
	}

	return tax;
}

// In currency file...
char currencySymbol(CountryCode cc=USA) {
	char symbol = ' ';

	switch(cc) {
	case USA:
		symbol = '$';
		break;
	case Canada:
		if(Quebec())
			symbol = '#';
		else
			symbol = '$';
		break;
	case Germany:
		symbol = 'e';
		break;
	// Country seam point.
	default:
	throw "OOPS";
	break;
	}

	return symbol;
}

// In new date format file...
string dateFormat(CountryCode cc=USA) {
	string fmt = "";

	switch(cc) {
	case USA:
	case Canada:
		fmt = "MMDDYY";
		break;
	case Germany:
		fmt = "DDMMCCYY";
		break;
	// Country seam point (this makes 5).
	default:
	throw "OOPS";
	break;
	}

	return fmt;
}

class SalesOrder {
public:
	int	 number;
	double	price;
	CountryCode countryCode;
public:
	void process() {
		char str[20];
		char   sym = currencySymbol(countryCode);
		double tax = taxAmount(number, price, countryCode);
		string fmt = dateFormat(countryCode);
		sprintf(str, "%c%.2f for %s order on %s.",
			sym, tax, CountryName[countryCode], fmt.c_str());
		cout << str << "\n";
	}
};

void demo() {
	SalesOrder orders[] = {
		{5, 10.00, USA},
		{1, 20.00, Canada},
		{9, 99.99, Germany},
	};

	for(size_t i=0; i<sizeof(orders)/sizeof(SalesOrder); i++) {
		cout << "  " << i+1 << ") ";
		orders[i].process();
	}

	cout << endl;
}

}

namespace strategy_solution {

// Run time requirements.
bool electionYear() { return true; }
bool Quebec() { return true; }

class Tax {
protected:
	double	rate;
public:
	Tax(double rate) : rate(rate) {}
	virtual ~Tax() {}
public:
	virtual double amount(int num, double price) {
		return rate*num*price;
	}
};
class FixedRate : public Tax {
public:
	FixedRate(double rate=0.000) : Tax(rate) {}
};
class ContingentRate : public Tax {
public:
	ContingentRate(double rate=0.000) : Tax(rate) {}
	double amount(int num, double price) {
		double cRate = electionYear() ? 0.069 : rate;
		return cRate*num*price;
	}
};

class Currency {
public: virtual ~Currency() {}
public:
	virtual char currencySymbol() { return ' '; }
};
class Dollar : public Currency {
public:
	char currencySymbol() { return '$'; }
};
class Pound : public Currency {
public:
	char currencySymbol() { return '#'; }
};
class Euro : public Currency {
public:
	char currencySymbol() { return 'e'; }
};

class DateFormat {
public: virtual ~DateFormat() {}
public:
	virtual string str() { return ""; }
};
class MMDDYY : public DateFormat {
public:
	string str() { return "MMDDYY"; }
};
class DDMMCCYY : public DateFormat {
public:
	string str() { return "DDMMCCYY"; }
};

class Country {
public:
	string		name;
	Tax*		tax;		// Realistically requires the strategy pattern.
	Currency*	currency;	// Probably can make do with a built in type.
	DateFormat*	fmt;		// Ditto, but implemented as strategy as academic exercise.
public:
	Country(string name, Tax* tax=new Tax(0.00),
			Currency* currency=new Currency, DateFormat* fmt=new DateFormat)
	: name(name), tax(tax), currency(currency), fmt(fmt) {}
};

class SalesOrder {
public:
	Country*	country;
	int	 number;
	double	price;
public:
	SalesOrder(int number, double price, Country* country)
	: country(country), number(number), price(price) {}
public:
	void process() {
		char str[20];
		char   sym = country->currency->currencySymbol();
		double tax = country->tax->amount(number, price);
		string fmt = country->fmt->str();
		sprintf(str, "%c%.2f for %s order on %s.",
			sym, tax, country->name.c_str(), fmt.c_str());
		cout << str << "\n";
	}
};

void demo() {
	Country
		usa = Country("USA", new FixedRate(0.075), new Dollar, new MMDDYY),
		can = Country("Canada", new ContingentRate, new Pound, new MMDDYY),
		ger = Country("Germany", new FixedRate(0.105), new Euro, new DDMMCCYY);
	SalesOrder* orders[] = {
		new SalesOrder(5, 10.00, &usa),
		new SalesOrder(1, 20.00, &can),
		new SalesOrder(9, 99.99, &ger),
	};

	for(size_t i=0; i<sizeof(orders)/sizeof(SalesOrder*); i++) {
		cout << "  " << i+1 << ") ";
		orders[i]->process();
	}

	cout << endl;
}

}


namespace wikibooks_cpp_pcdp {

class StrategyInterface {
public:
	virtual void execute() const=0;
	virtual ~StrategyInterface() {}
};

class ConcreteStrategyA : public StrategyInterface {
public:
	virtual void execute() const {
		cout << "Execute concrete strategy A." << endl;
	}
};

class ConcreteStrategyB : public StrategyInterface {
public:
	virtual void execute() const {
		cout << "Execute concrete strategy B." << endl;
	}
};

class ConcreteStrategyC : public StrategyInterface {
public:
	virtual void execute() const {
		cout << "Execute concrete strategy C." << endl;
	}
};

class Context {
private:
	StrategyInterface* currentStrategy;
public:
	explicit Context(StrategyInterface* strategy) : currentStrategy(strategy) {}
	void setStrategy(StrategyInterface* strategy) {
		currentStrategy = strategy;
	}
	void execute() const {
		currentStrategy->execute();
	}
};

void demo_strategy() {
	cout << "*** wikibooks_cpp_pcdp demo_strategy ***" << endl;

	ConcreteStrategyA	concreteStrategyA;
	ConcreteStrategyB	concreteStrategyB;
	ConcreteStrategyC	concreteStrategyC;

	Context contextA(&concreteStrategyA);
	Context contextB(&concreteStrategyB);
	Context contextC(&concreteStrategyC);

	contextA.execute();
	contextB.execute();
	contextC.execute();
	cout << endl;

	contextA.setStrategy(&concreteStrategyB);
	contextA.execute();
	contextA.setStrategy(&concreteStrategyC);
	contextA.execute();
}

}

namespace multipleCaseStatements {

// Problem scenario: an order processing system.
// A number of actions are required, such as computing taxes or using a particular
// currency, that are typically different between countries, but can be the same.
// Also, each action may have variations that depend upon run time parameters.
// The specs grew to include 3 countries and 3 actions with 1 to 3 implementations.
// Show a redesign using the strategy pattern that will require only a linear amount
// of code to be added or changed, such changes being well localized, and handling
// any addition of country, action, implementation, or run time dependency.
// Below is the existing code (a bit stylized and abstracted for academic purposes).

enum CountryCode {
	USA,
	Canada,
	Germany
};

const char* CountryName[] = {
	"USA",
	"Canada",
	"Germany"
};

bool electionYear = true;

// In some file.
void taxes(CountryCode country, bool electionYear=true) {
	switch(country) {
	case USA:		cout << "Compute complex taxes for " << CountryName[country] << "." << endl;	break;
	case Canada:
		if(electionYear) {
			cout << "Compute election taxes for ";
		} else {
			cout << "Compute complex taxes for ";
		}
		cout << CountryName[country] << "." << endl;	break;
	case Germany:	cout << "Compute complex taxes for " << CountryName[country] << "." << endl;	break;
	}
}

// In some other file.
void currency(CountryCode country) {
	switch(country) {
	case USA:		cout << "Use currency in dollars for " << CountryName[country] << "." << endl;	break;
	case Canada:	cout << "Use currency in dollars for " << CountryName[country] << "." << endl;	break;
	case Germany:	cout << "Use currency in euros for " << CountryName[country] << "." << endl;	break;
	}
}

// In yet another file...
void dateFormat(CountryCode country) {
	switch(country) {
	case USA:		cout << "Use MMDDYY date format for " << CountryName[country] << "." << endl;	break;
	case Canada:	cout << "Use MMDDCCYY date format for " << CountryName[country] << "." << endl;	break;
	case Germany:	cout << "Use CCYYMMDD date format for " << CountryName[country] << "." << endl;	break;
	}
}

void demo(bool electionYear=true) {
	cout << "*** multipleCaseStatements demo ***" << endl;

	CountryCode countries[] = { USA, Canada, Germany };
	for(size_t i=0; i<sizeof(countries)/sizeof(CountryCode); i++) {
		taxes(countries[i], electionYear);
		currency(countries[i]);
		dateFormat(countries[i]);
	}
}

// Spec change 1: add another country (India).
// Spec change 2: add another implementation (simple taxes).
// Spec change 3: add another action (shipping).

}

namespace strategy1 {

class Country {
protected:
	const char*	name;
public:
	explicit Country(const char* name) : name(name) {}
	virtual ~Country() {}
public:
	virtual void taxes() 	  { cout << "Compute taxes for " << name << "." << endl;	}
	virtual void currency()   { cout << "Use currency for " << name << "." << endl;		}
	virtual void dateFormat() {	cout << "Use date format for " << name << "." << endl;	}
	// Seam point: add another function.
};

class USA : public Country{
public:
	USA() : Country("USA") {}
};
class Canada : public Country{
public:
	Canada() : Country("Canada") {}
};
class Germany : public Country{
public:
	Germany() : Country("Germany") {}
};
// Seam point: add another Country.

// All in different files, never need to touch again.
void taxes(Country& country) {
	country.taxes();
}
void currency(Country& country) {
	country.currency();
}
void dateFormat(Country& country) {
	country.dateFormat();
}

void demo1() {
	cout << "*** strategy1 demo1 ***" << endl;
	taxes(multipleCaseStatements::USA);
	currency(multipleCaseStatements::Canada);
	dateFormat(multipleCaseStatements::Germany);
}

void demo2() {
	cout << "*** strategy1 demo2 ***" << endl;
	Country* countries[] = { new USA(), new Canada(), new Germany() };

	for(size_t i=0; i<sizeof(countries)/sizeof(Country*); i++) {
		countries[i]->taxes();
		countries[i]->currency();
		countries[i]->dateFormat();
	}
}

}

namespace strategy2 {

class Taxes {public: virtual void use() {cout << "  Taxes: ";} virtual ~Taxes() {}};
class Currency {public: virtual void use() {cout << "  Currency: ";} virtual ~Currency() {}};
class DateFormat {public: virtual void use() {cout << "  DateFormat: ";} virtual ~DateFormat() {}};
// Seam point: add another action.

// Action implementations.
class Complex : public Taxes {public: void use() { Taxes::use(); cout << "complex." << endl;}};
class Election : public Taxes {public: void use() { Taxes::use(); cout << "election." << endl;}};
// Seam point: add another tax.

class Dollars : public Currency {public: void use() { Currency::use(); cout << "dollars." << endl;}};
class Euros   : public Currency {public: void use() { Currency::use(); cout << "euros." << endl;}};
// Seam point: add another Currency.

class MMDDYY  : public DateFormat {public: void use() { DateFormat::use(); cout << "MMDDYY." << endl;}};
class MMDDCCYY : public DateFormat {public: void use() { DateFormat::use(); cout << "MMDDCCYY." << endl;}};
class CCYYMMDD  : public DateFormat {public: void use() { DateFormat::use(); cout << "CCYYMMDD." << endl;}};
// Seam point: add another DateFormat.

class Country {
public:
	const char* name;
	Taxes*		taxes;		// Actions.
	Currency*	currency;
	DateFormat*	dateFormat;
public:
	Country(const char* name, Taxes* taxes=0, Currency* currency=0, DateFormat* dateFormat=0)
	: name(name), taxes(taxes), currency(currency), dateFormat(dateFormat) {}
	void changeTaxes(Taxes* newTaxes) { taxes = newTaxes; }
	void changeCurrency(Currency* newCurrency) { currency = newCurrency; }
	void changeDateFormat(DateFormat* newDateFormat) { dateFormat = newDateFormat; }
};
// Seam point: add another action.

class USA : public Country { public:
	USA() : Country("USA", new Complex, new Dollars, new MMDDYY) {}
};
class Canada : public Country { public:
	Canada() : Country("Canada", new Complex, new Dollars, new MMDDCCYY) {}
};
class Germany : public Country { public:
	Germany() : Country("Germany", new Complex, new Euros, new CCYYMMDD) {}
};
// Seam point: add another Country.

void demo0(bool electionYear=true) {
	cout << "*** strategy2 demo0 ***" << endl;

	Country* countries[] = { new USA, new Canada, new Germany }; // Seam point: add another country.
	if(electionYear) countries[1]->changeTaxes(new Election);	//Special case.

	for(size_t i=0; i<sizeof(countries)/sizeof(Country*); i++) {
		cout << countries[i]->name << ": " << endl;
		countries[i]->taxes->use();
		countries[i]->currency->use();
		countries[i]->dateFormat->use();
		// Seam point: add another action.
	}
}

}

namespace strategy3 {

// Actions (with implementations).
class Taxes {
	public: virtual void use() {cout << "  Taxes: ";} virtual ~Taxes() {}
};
class Complex : public Taxes {
	public: void use() { Taxes::use(); cout << "complex." << endl;}
};
class Election : public Taxes {
	public: void use() { Taxes::use(); cout << "election." << endl;}
};
// Seam point: add another tax.
class Simple : public Taxes {
	public: void use() { Taxes::use(); cout << "simple." << endl;}
};

class Currency {
	public: virtual void use() {cout << "  Currency: ";} virtual ~Currency() {}
};
class Dollars : public Currency {
	public: void use() { Currency::use(); cout << "dollars." << endl;}
};
class Euros   : public Currency {
	public: void use() { Currency::use(); cout << "euros." << endl;}
};
// Seam point: add another Currency.

class DateFormat {
	public: virtual void use() {cout << "  DateFormat: ";} virtual ~DateFormat() {}
};
class MMDDYY  : public DateFormat {
	public: void use() { DateFormat::use(); cout << "MMDDYY." << endl;}
};
class MMDDCCYY : public DateFormat {
	public: void use() { DateFormat::use(); cout << "MMDDCCYY." << endl;}
};
class CCYYMMDD  : public DateFormat {
	public: void use() { DateFormat::use(); cout << "CCYYMMDD." << endl;}
};
// Seam point: add another DateFormat.

// Seam point: add another action (with at least one implementation).
class Shipping {
	public: virtual void use() {cout << "  Shipping: default" << endl;} virtual ~Shipping() {}
};
class UPS : public Shipping {
	public: void use() { cout << "  Shipping: UPS." << endl;}
};

// Countries, base class with derived classes.
class Country {
public:
	const char* name;
	Taxes*		taxes;		// Actions.
	Currency*	currency;
	DateFormat*	dateFormat;
	// Seam point: add another action.
	Shipping*	shipping;
public:
	Country(const char* name, Taxes* taxes, Currency* currency, DateFormat* dateFormat, /*Seam*/ Shipping* shipping=new Shipping)
	: name(name), taxes(taxes), currency(currency), dateFormat(dateFormat), /*Seam*/ shipping(shipping) {}
	void changeTaxes(Taxes* newTaxes) { taxes = newTaxes; }
	void changeCurrency(Currency* newCurrency) { currency = newCurrency; }
	void changeDateFormat(DateFormat* newDateFormat) { dateFormat = newDateFormat; }
	// Seam point: add another action.
	void changeShipping(Shipping* newShipping) { shipping = newShipping; }
};

class USA : public Country { public:
	USA() : Country("USA", new Complex, new Dollars, new MMDDYY) {}
};
class Canada : public Country { public:
	Canada() : Country("Canada", new Complex, new Dollars, new MMDDCCYY) {}
};
class Germany : public Country { public:
	Germany() : Country("Germany", new Complex, new Euros, new CCYYMMDD) {}
};
// Seam point: add another Country.
class India : public Country { public:
	India() : Country("India", new Simple, new Euros, new CCYYMMDD, /*Seam*/ new UPS) {}
};

void demo(bool electionYear=true) {
	cout << "*** strategy3 demo ***" << endl;

	Country* countries[] = { new USA, new Canada, new Germany, /*Seam*/ new India }; // Seam point: add another country.
	if(electionYear) countries[1]->changeTaxes(new Election);	//Special case.

	for(size_t i=0; i<sizeof(countries)/sizeof(Country*); i++) {
		Country* country = countries[i];
		cout << country->name << ": " << endl;
		country->taxes->use();
		country->currency->use();
		country->dateFormat->use();
		// Seam point: add another action.
		country->shipping->use();
	}
}

}

#endif /* STRATEGY_H_ */
