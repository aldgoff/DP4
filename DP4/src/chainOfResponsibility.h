/*
 * chainOfResponsibility.h
 *
 * Desc: Pass a request down a chain of objects until one handles it.
 *
 * Category: Behavioral
 *
 *  Created on: Sep 2, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Chain_of_Responsibility
 *  	http://www.dofactory.com/net/chain-of-responsibility-design-pattern
 *
 *  	http://sourcemaking.com/design_patterns/chain_of_responsibility
 */

#ifndef CHAINOFRESPONSIBILITY_H_
#define CHAINOFRESPONSIBILITY_H_

namespace chain_of_resp_legacy {

void demo() {
	cout << "  chain_of_resp_legacy::demo().\n";
}

}

namespace chain_of_resp_problem {

void demo() {
	cout << "  chain_of_resp_problem::demo().\n";
}

}

namespace chain_of_resp_solution {

void demo() {
	cout << "  chain_of_resp_solution::demo().\n";
}

}

/* Consider how to model decision making in a military chain of command.
 * Simple decisions get made by the junior officers, harder ones by the senior officers.
 */

namespace decisions  {

class Lieutenant {
public:
	bool handleRequest(unsigned request) {
		if(request<10) {
			cout << "Lieutenant - I've got this one(" << request << ").\n";
			return true;
			}
		else {
			return false;
		}
	}
};

class Captain {
public:
	bool handleRequest(unsigned request) {
		if(request<20) {
			cout << "Captain - I've got this one(" << request << ").\n";
			return true;
			}
		else {
			return false;
		}
	}
};

class Major {
public:
	bool handleRequest(unsigned request) {
		if(request<30) {
			cout << "Major - I've got this one(" << request << ").\n";
			return true;
			}
		else {
			return false;
		}
	}
};

// Seam point: Lieutenant Colonel.

class Colonel {
public:
	bool handleRequest(unsigned request) {
		if(request<50) {
			cout << "Colonel - I've got this one(" << request << ").\n";
			return true;
			}
		else {
			return false;
		}
	}
};

class General {
public:
	bool handleRequest(unsigned request) {
		if(request<60) {
			cout << "General - I've got this one(" << request << ").\n";
			return true;
			}
		else {
			return false;
		}
	}
};

class CommanderInChief {
public:
	bool handleRequest(unsigned request) {
		if(60<=request) {
			cout << "CommanderInChief - I've got this one(" << request << ").\n";
			return true;
			}
		else {
			return false;
		}
	}
};

void demo() {
	cout << "<< Chain of Responsibility problem >>\n";

	Lieutenant	lieutenant;
	Captain		captain;
	Major		major;
	// Seam point: Lieutenant Colonel.
	Colonel		colonel;
	General		general;
	CommanderInChief pres;

	unsigned requests[] = {1, 15, 25, 55, 99};

	for(size_t i=0; i<sizeof(requests)/sizeof(*requests); i++) {
		unsigned request = requests[i];
		if(lieutenant.handleRequest(request))
			;
		else if(captain.handleRequest(request))
			;
		else if(major.handleRequest(request))
			;
		// Seam point: Lieutenant Colonel.
		else if(colonel.handleRequest(request))
			;
		else if(general.handleRequest(request))
			;
		else if(pres.handleRequest(request))
			;
		else {
			cout << "Request not handled(" << request << ").\n";
		}
	}

	cout << endl;
}

}

namespace chainOfResponsibility {

/* The code below is not simpler, in fact a little more complicated.
 * Also, it has the same number of seam points, and client code isn't closed to modification.
 * It's benefit however, is better flexibility for dynamic situations,
 * stuff only known at runtime.
 * Say the captain gets killed in action, it is trivial to close the chain,
 * not so in the static code above.
 */

class Officer {
protected:
	Officer* successor;
public:
	Officer() : successor(0) {};
	virtual ~Officer() {};
public:
	void setSuccessor(Officer* successor) {
		this->successor = successor;
	}
	virtual void handleRequest(unsigned request)=0;
};
class Lieutenant : public Officer {
public:
	void handleRequest(unsigned request) {
		if(request<10)
			cout << "Lieutenant - I've got this one(" << request << ").\n";
		else if(successor != 0)
			successor->handleRequest(request);
		else
			cout << "Request not handled.\n";
	}
};
class Captain : public Officer {
public:
	void handleRequest(unsigned request) {
		if(request<20)
			cout << "Captain - I've got this one(" << request << ").\n";
		else if(successor != 0)
			successor->handleRequest(request);
		else
			cout << "Request not handled.\n";
	}
};
class Major : public Officer {
public:
	void handleRequest(unsigned request) {
		if(request<30)
			cout << "Major - I've got this one(" << request << ").\n";
		else if(successor != 0)
			successor->handleRequest(request);
		else
			cout << "Request not handled.\n";
	}
};
// Seam point: Lieutenant Colonel.
class Colonel : public Officer {
public:
	void handleRequest(unsigned request) {
		if(request<50)
			cout << "Colonel - I've got this one(" << request << ").\n";
		else if(successor != 0)
			successor->handleRequest(request);
		else
			cout << "Request not handled.\n";
	}
};
class General : public Officer {
public:
	void handleRequest(unsigned request) {
		if(request<60)
			cout << "General - I've got this one(" << request << ").\n";
		else if(successor != 0)
			successor->handleRequest(request);
		else
			cout << "Request not handled.\n";
	}
};
class CommanderInChief : public Officer {
public:
	void handleRequest(unsigned request) {
		if(60<=request)
			cout << "CommanderInChief - The buck stops here(" << request << ").\n";
		else if(successor != 0)
			successor->handleRequest(request);
		else
			cout << "Request not handled.\n";
	}
};

void demo() {
	cout << "<< Chain of Responsibility solution >>\n";

	Officer* lieutenant = new Lieutenant;
	Officer* captain	= new Captain;
	Officer* major		= new Major;
	// Seam point: Lieutenant Colonel.
	Officer* colonel	= new Colonel;
	Officer* general	= new General;
	Officer* pres		= new CommanderInChief;

	lieutenant->setSuccessor(captain);
	captain->setSuccessor(major);
	major->setSuccessor(colonel);
	// Seam point: Lieutenant Colonel.
	colonel->setSuccessor(general);
	general->setSuccessor(pres);

	lieutenant->setSuccessor(major);	// Captain KIA, only known at run time.

	unsigned requests[] = {1, 15, 25, 55, 99};

	for(size_t i=0; i<sizeof(requests)/sizeof(*requests); i++) {
		lieutenant->handleRequest(requests[i]);
	}

	cout << endl;
}

}

#endif /* CHAINOFRESPONSIBILITY_H_ */
