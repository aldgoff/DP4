/*
 * sideBySide.h
 *
 *  Created on: Sep 16, 2014
 *      Author: aldgoff
 */

#ifndef SIDEBYSIDE_H_
#define SIDEBYSIDE_H_

#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace side_by_side {

void clientDesignPattern();

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

void clientCommand();

}

#endif /* SIDEBYSIDE_H_ */
