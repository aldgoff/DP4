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
 *  URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Strategy
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

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
