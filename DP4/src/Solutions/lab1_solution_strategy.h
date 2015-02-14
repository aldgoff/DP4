/*
 * lab1_solution_strategy.h
 *
 *  Created on: Feb 13, 2015
 *      Author: aldgoff
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

namespace homework {

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

#endif /* STRATEGY_H_ */
