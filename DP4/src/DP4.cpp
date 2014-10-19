//============================================================================
// Name        : DP4.cpp
// Author      : Allan Goff
// Version     :
// Copyright   : Novatia Labs 2014
// Description : Examples for a Design Patterns class.
//============================================================================

#ifdef runConfigs
facade
adapter
strategy
bridge
#endif

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#include "facade.h"
#include "adapter.h"

#include "strategy.h"
#include "bridge.h"

/*====================================================================================================================*/

void runFacade() {
	facade::Facade house;
	house.goToWork(); cout << endl;
	house.comeHome(); cout << endl;
}

void runAdapter() {
	adapter_problem::demo();
	adapter_solution::demo();
}

void runStrategy() {
//	wikibooks_cpp_pcdp::demo_strategy(); cout << endl;

	multipleCaseStatements::demo();	cout << endl;

//	strategy1::demo1();	cout << endl;
//	strategy1::demo2();	cout << endl;
	strategy2::demo0();	cout << endl;
	strategy3::demo();	cout << endl;
}

void runBridge() {
	wikibooks_cpp_pcdp::demo_bridge();

	bridge::demo();
}

/*====================================================================================================================*/

int main(int argc, char* args[]) {
	cout << "Hello DP4.\n" << endl;

	if(argc == 1)
		cout << "  No args.\n" << endl;

	for(int i=0; i<argc; i++) {
		if(!strcmp(args[i], "facade"))		runFacade();
		if(!strcmp(args[i], "adapter"))		runAdapter();
		if(!strcmp(args[i], "strategy"))	runStrategy();
		if(!strcmp(args[i], "bridge"))		runBridge();
	}

	cout << "Aloha DP4.\n";
	return 0;
}
