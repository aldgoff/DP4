/*
 * pairWise.h
 *
 *  Created on: Feb 13, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_PAIRWISE_PAIRWISE_H_
#define DP4_SRC_PAIRWISE_PAIRWISE_H_

#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace pair_wise {

//void clientDesignPattern();

void clientStrategy();
void clientAdapter();

void clientFacade();
void clientTemplateMethod();

void clientFactoryMethod();
void clientDecorator();

void clientObserver();
void clientChainOfResponsibility();

void clientBridge();
void clientAbstractFactory();

}

#endif /* DP4_SRC_PAIRWISE_PAIRWISE_H_ */
