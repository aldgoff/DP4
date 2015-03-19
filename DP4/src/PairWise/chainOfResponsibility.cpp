/*
 * chainOfResponsibility.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

namespace pair_wise {

class Request {
public:
	int	value;
public:
	Request(int value) : value(value) {}
};

class ChainOfResp {		// If handler is varying....
public:
	ChainOfResp*	successor;
public:
	ChainOfResp() : successor(0) {}
	virtual ~ChainOfResp() {}
public:
	virtual void takeCareOfIt(Request* req)=0;
	void oops(Request* req) { cout << "  Nobody handled " <<req->value <<"?\n";}
};
class Handler1 : public ChainOfResp {
public:
	void takeCareOfIt(Request* req) {
		if(req->value < 10)	cout << "  Handler1 handled " <<req->value <<".\n";
		else if(successor)	successor->takeCareOfIt(req);
		else				oops(req);
	}
};
class Handler2 : public ChainOfResp {
public:
	void takeCareOfIt(Request* req) {
		if(req->value < 20)	cout << "  Handler2 handled " <<req->value <<".\n";
		else if(successor)	successor->takeCareOfIt(req);
		else				oops(req);
	}
};
class Handler3 : public ChainOfResp {
public:
	void takeCareOfIt(Request* req) {
		if(req->value < 30)	cout << "  Handler3 handled " <<req->value <<".\n";
		else if(successor)	successor->takeCareOfIt(req);
		else				oops(req);
	}
};

void clientChainOfResponsibility() {
	ChainOfResp*	first  = new Handler1;
	ChainOfResp*	second = new Handler2;	first->successor = second;
	ChainOfResp*	third  = new Handler3;	second->successor = third;

	Request* req[] = { new Request(5),  new Request(15),
					   new Request(25), new Request(55) };
	for(size_t i=0; i<sizeof(req)/sizeof(*req); i++) {
		first->takeCareOfIt(req[i]);
	}
	cout << endl;
}

}
