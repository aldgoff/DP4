/*
 * lab1_problem_strategy.h
 *
 *  Created on: Feb 13, 2015
 *      Author: aldgoff
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

}

#endif /* STRATEGY_H_ */
