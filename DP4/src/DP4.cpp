//============================================================================
// Name        : DP4.cpp
// Author      : Allan Goff
// Version     :
// Copyright   : Novatia Labs 2014
// Description : Examples for a Design Patterns class.
//============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#include "Lectures/lectures.h"

#include "facade.h"
#include "adapter.h"
#include "strategy.h"
#include "bridge.h"
#include "abstractFactory.h"
#include "decorator.h"

#include "observer.h"
#include "templateMethod.h"

#include "singleton.h"
#include "factoryMethod.h"

#include "midterm.h"

#include "composite.h"
#include "chainOfResponsibility.h"

#include "iterator.h"
#include "visitor.h"

#include "command.h"
// Seam point half avoided by auto generation.

#include "forest.h"
#include "final.h"
#include "principles.h"
#include "varies.h"

#include "solti.h"

#include "SideBySide/sideBySide.h"
#include "PairWise/pairWise.h"
#include "Skeletons/skeletons.h"

#include "meta.h"
#include "whatVaries.h"

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

void runAbstractFactory() {
//	problem_scenario::demo();
//	abstract_factory::demo();

//	problem_scenario_2::demo();
//	abstract_factory_2::demo();

	complicated_relationships::demo();
	abstract_factory_3::demo();
}

void runDecorator() {
	too_many_car_model_options::demo();
	decorator::demo();
}

void runObserver() {
	ripples::demo();
//	observer::demo_deprecated();
	observer::demo();
}

void runTemplateMethod() {
	duplicated_skelaton::demo();
	templateMethod::demo();
}

void runSingleton() {
	too_many::demo();
	singleton::demo();
//	double_checked_locking_pattern::demo();
//	polyton::demo();
}

void runFactoryMethod() {
	factory_method_problem2::demo();
	factory_method::demo();
}


void runMidterm() {
	section_1_jargon::section1();
	section_2_taxonomy::section2();
	cout << endl;

	section_3_principles::section3();
	cout << endl;

	section_4_recognize_design_patterns::section4();
	cout << endl;

	section_5_apply_design_patterns::section5();
	cout << endl;

	cout << endl;
}


void runComposite() {
	leaf_versus_list::demo();
	composite::demo();
}

void runChainOfResponsibility() {
	decisions::demo();
	chainOfResponsibility::demo();
}

void runIterator() {
	traverse::demo();
	iterator_pattern::demo();
}

void runVisitor() {
	call_back::demo();
	visitor::demo();
}

void runCommand() {
	requests::demo();
	command::demo();
}

// Seam point; can be eliminated by use of design patterns.

void runFinal() {
	final_problem::demo();
	final_solution::demo();
}

void runPrinciples() {
	principles::demo();
}

void runVaries() {
//	problem::demo();
//	solution::demo();
}

void runSolti() {
	solti_problem::demo();
	solti_experimental::demo();
	solti_solution::demo();
}

void runPairWise() {
	pair_wise::clientStrategy();
	pair_wise::clientAdapter();
}

void runSideBySide() {
	side_by_side::clientDesignPattern();
	side_by_side::clientStrategy();
	side_by_side::clientAdapter();
	side_by_side::clientFacade();
	side_by_side::clientTemplateMethod();
	side_by_side::clientFactoryMethod();
	side_by_side::clientDecorator();
	side_by_side::clientObserver();
	side_by_side::clientCommand();
}

void runSkeletons() {
	skeleton::clientStrategy();
	skeleton::clientAdapter();
	skeleton::clientFacade();
	skeleton::clientTemplateMethod();
	skeleton::clientFactoryMethod();
	skeleton::clientDecorator();
	skeleton::clientObserver();
	skeleton::clientChainOfResponsibility();
	skeleton::clientBridge();
	skeleton::clientAbstractFactory();
}

void runWhatVaries() {
//	abstractByComposition::demo();
	{
	using namespace strategy;

	antiPattern_ifelse::demo();
	abstract_over_doubles::demo();
	vary_tax_rate_by_state::demo();
	cout << endl;

	antiPattern_switch::demo();
	abstract_over_TaxStrategy::demo();
	vary_tax_strategy_by_country::demo();
	}
}

void runVirtualDtorBug() {
//	virtual_dtor_bug::demo();
//	const_ref_ptr_bug::demo();
//	ref_study::demo();
}

/*====================================================================================================================*/

int main(int argc, char* args[]) {
	cout << "Hello DP4.\n" << endl;

	if(argc == 1) {	// Give user better feedback.
		cout << "  No args - use these (one per line).\n";
		cout << "  Header files to include in DP4.cpp also listed.\n";
		cout << endl;
		meta("");
	}

	for(int i=1; i<argc; i++)
		meta(string(args[i]));

	for(int i=0; i<argc; i++) {
//		if(!strcmp(args[i], "facade"))		runFacade();
//		if(!strcmp(args[i], "adapter"))		runAdapter();
//		if(!strcmp(args[i], "strategy"))	runStrategy();
//		if(!strcmp(args[i], "bridge"))		runBridge();
//
//		if(!strcmp(args[i], "abstractFactory"))	runAbstractFactory();
//		if(!strcmp(args[i], "decorator"))		runDecorator();
//		if(!strcmp(args[i], "observer"))		runObserver();
//		if(!strcmp(args[i], "templateMethod"))	runTemplateMethod();
//
//		if(!strcmp(args[i], "singleton"))		runSingleton();
//		if(!strcmp(args[i], "factoryMethod"))	runFactoryMethod();
//
//		if(!strcmp(args[i], "midterm"))			runMidterm();
//
//		if(!strcmp(args[i], "composite"))				runComposite();
//		if(!strcmp(args[i], "chainOfResponsibility"))	runChainOfResponsibility();
//
//		if(!strcmp(args[i], "iterator"))		runIterator();
//		if(!strcmp(args[i], "visitor"))			runVisitor();
//
//		if(!strcmp(args[i], "command"))			runCommand();
//
//		if(!strcmp(args[i], "final"))			runFinal();
//		if(!strcmp(args[i], "principles"))		principles::demo();
//		if(!strcmp(args[i], "varies"))			runVaries();
//
//		if(!strcmp(args[i], "solti"))			runSolti();
//
//		if(!strcmp(args[i], "sideBySide"))		runSideBySide();
//
		if(!strcmp(args[i], "skeletons"))		runSkeletons();
		if(!strcmp(args[i], "sideBySide"))		runSideBySide();
		if(!strcmp(args[i], "pairWise"))		runPairWise();
		if(!strcmp(args[i], "whatVaries"))		runWhatVaries();
		if(!strcmp(args[i], "virtualDtorBug"))	runVirtualDtorBug();
//
//		// Seam point; can be eliminated by use of design patterns.
	}
//
//	for(int i=1; i<argc; i++)
//		meta(string(args[i]));

	cout << "Aloha DP4.\n";
	return 0;
}
