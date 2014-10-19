//============================================================================
// Name        : DP4.cpp
// Author      : Allan Goff
// Version     :
// Copyright   : Novatia Labs 2014
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#include "facade.h"


/*====================================================================================================================*/

void runFacade() {
	facade::Facade house;
	house.goToWork(); cout << endl;
	house.comeHome(); cout << endl;
}

/*====================================================================================================================*/

int main(int argc, char* args[]) {
	cout << "Hello DP4.\n" << endl;

	if(argc == 1)
		cout << "  No args.\n" << endl;

	for(int i=0; i<argc; i++) {
		if(!strcmp(args[i], "facade"))		runFacade();
	}

	cout << "Aloha DP4.\n";
	return 0;
}
