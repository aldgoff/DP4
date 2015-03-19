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

namespace lecture {

namespace chain_of_resp_legacy {

class Clerk {
public:
	Clerk() { cout << "  +Clerk ctor.\n"; }
	~Clerk() { cout << "  ~Clerk dtor.\n"; }
public:
	void approves(float amount) {
		cout << "  Clerk approves $" << amount << ".\n";
	}
};

class Owner {
public:
	Owner() { cout << "  +Owner ctor.\n"; }
	~Owner() { cout << "  ~Owner dtor.\n"; }
public:
	void approves(float amount) {
		cout << "  Owner approves $" << amount << ".\n";
	}
};

void clientCode(float amount) {	// Client coupled with lots of classes.
	{
	static Clerk	clerk;
	static Owner	owner;
	// Seam point - insert another approval class.

	if(amount < 20.00)
		clerk.approves(amount);
	else if(amount < 500.00)
		owner.approves(amount);
	// Seam point - insert another approval level.
	else
		cout << "  Denied $" << amount << ", the buck stops here.\n";
	}
}

void demo() {
	cout << "  chain_of_resp_legacy::demo().\n";

	float data[] = { 10.01, 44.77, 111.88, 333.99, 555.22, 999.99, 1010.55 };
	for(size_t i=0; i<sizeof(data)/sizeof(*data); i++) {
		clientCode(data[i]);
	}

	cout << endl;
}

}

namespace chain_of_resp_problem {

class ChainOfResp {
protected:
	ChainOfResp*	successor;
public:
	ChainOfResp() : successor(0) {}
	virtual ~ChainOfResp() { cout << "  ~ChainOfResp\n"; }
public:
	void setSuccessor(ChainOfResp* successor) {
		this->successor = successor;
	}
	virtual void handleRequest(float amount) {
		cout << "  Denied $" << amount << ", the buck stops here.\n";
	}
};
class Clerk : public ChainOfResp {
public:	~Clerk() { cout << "  ~Clerk"; }
	void handleRequest(float amount) {
		if(amount < 20.00)	cout << "  Clerk approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class Supervisor : public ChainOfResp {
public:	~Supervisor() { cout << "  ~Supervisor"; }
	void handleRequest(float amount) {
		if(amount < 100.00)	cout << "  Supervisor approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class Manager : public ChainOfResp {
public:	~Manager() { cout << "  ~Manager"; }
	void handleRequest(float amount) {
		if(amount < 200.00)	cout << "  Manager approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class Director : public ChainOfResp {
public:	~Director() { cout << "  ~Director"; }
	void handleRequest(float amount) {
		if(amount < 400.00)	cout << "  Director approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class VP : public ChainOfResp {
public:	~VP() { cout << "  ~VP"; }
	void handleRequest(float amount) {
		if(amount < 600.00)	cout << "  VP approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class President : public ChainOfResp {
public:	~President() { cout << "  ~President"; }
	void handleRequest(float amount) {
		if(amount < 1000.00) cout << "  President approves $" << amount <<".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};

void clientCode(ChainOfResp* chain, float amount) {
	chain->handleRequest(amount);
}

void demo() {
	cout << "  chain_of_resp_problem::demo().\n";
	{
	Clerk		clerk;
	Supervisor	supervisor;	clerk.setSuccessor(&supervisor);
	Manager		manager;	supervisor.setSuccessor(&manager);
	Director	director;	manager.setSuccessor(&director);
	VP			vp;			director.setSuccessor(&vp);
	President	president;	vp.setSuccessor(&president);

	float data[] = { 10.01, 44.77, 111.88, 333.99, 555.22, 999.99, 1010.55 };
	for(size_t i=0; i<sizeof(data)/sizeof(*data); i++) {
		clientCode(&clerk, data[i]);
	}
	}

	cout << endl;
}

}

namespace chain_of_resp_solution {

class ApprovalStrategy {
public: virtual  ~ApprovalStrategy() { cout << "  ~ApprovalStrategy"; }
	virtual bool operator()(float amount) const { return false; }
};
struct ClerkLogic : public ApprovalStrategy {
	~ClerkLogic() { cout << "  ~ClerkLogic"; }
	bool operator()(float amount) const { return(amount < 20.00); }
};
struct SupervisorLogic : public ApprovalStrategy {
	~SupervisorLogic() { cout << "  ~SupervisorLogic"; }
	bool operator()(float amount) const { return(amount < 100.00); }
};
struct ManagerLogic : public ApprovalStrategy {
	~ManagerLogic() { cout << "  ~ManagerLogic"; }
	bool operator()(float amount) const { return(amount < 200.00); }
};
struct DirectorLogic : public ApprovalStrategy {
	~DirectorLogic() { cout << "  ~DirectorLogic"; }
	bool operator()(float amount) const { return(amount < 400.00); }
};
struct VPLogic : public ApprovalStrategy {
	~VPLogic() { cout << "  ~VPLogic"; }
	bool operator()(float amount) const { return(amount < 600.00); }
};
struct PresidentLogic : public ApprovalStrategy {
	~PresidentLogic() { cout << "  ~PresidentLogic"; }
	bool operator()(float amount) const { return(amount < 1000.00); }
};

class ChainOfResp {
protected:
	ApprovalStrategy*	approval;
	ChainOfResp*		successor;
public:
	ChainOfResp(ApprovalStrategy* approval=0)
		: approval(approval), successor(0) {}
	virtual ~ChainOfResp() {
		delete approval;
		cout << "  ~ChainOfResp\n";
	}
public:
	void setSuccessor(ChainOfResp* successor) {
		this->successor = successor;
	}
	virtual void handleRequest(float amount) {
		cout << "  Denied $" << amount << ", the buck stops here.\n";
	}
};
class Clerk : public ChainOfResp {
	const ApprovalStrategy&	logic;
public:
	Clerk() : ChainOfResp(new ClerkLogic), logic(*approval) {}
	~Clerk() { cout << "  ~Clerk"; }
	void handleRequest(float amount) {
		if(logic(amount))	cout << "  Clerk approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class Supervisor : public ChainOfResp {
	const ApprovalStrategy&	logic;
public:
	Supervisor() : ChainOfResp(new SupervisorLogic), logic(*approval) {}
	~Supervisor() { cout << "  ~Supervisor"; }
	void handleRequest(float amount) {
		if(logic(amount))	cout << "  Supervisor approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class Manager : public ChainOfResp {
	const ApprovalStrategy&	logic;
public:
	Manager() : ChainOfResp(new ManagerLogic), logic(*approval) {}
	~Manager() { cout << "  ~Manager"; }
	void handleRequest(float amount) {
		if(logic(amount))	cout << "  Manager approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class Director : public ChainOfResp {
	const ApprovalStrategy&	logic;
public:
	Director() : ChainOfResp(new DirectorLogic), logic(*approval) {}
	~Director() { cout << "  ~Director"; }
	void handleRequest(float amount) {
		if(amount < 400.00)	cout << "  Director approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class VP : public ChainOfResp {
	const ApprovalStrategy&	logic;
public:
	VP() : ChainOfResp(new VPLogic), logic(*approval) {}
	~VP() { cout << "  ~VP"; }
	void handleRequest(float amount) {
		if(amount < 600.00)	cout << "  VP approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};
class President : public ChainOfResp {
	const ApprovalStrategy&	logic;
public:
	President() : ChainOfResp(new PresidentLogic), logic(*approval) {}
	~President() { cout << "  ~President"; }
	void handleRequest(float amount) {
		if(logic(amount)) cout << "  President approves $" << amount << ".\n";
		else if(successor)	successor->handleRequest(amount);
		else				ChainOfResp::handleRequest(amount);
	}
};

void clientCode(ChainOfResp* chain, float amount) {
	chain->handleRequest(amount);
}

void demo() {
	cout << "  chain_of_resp_solution::demo().\n";
	{
	Clerk		clerk;
	Supervisor	supervisor;	clerk.setSuccessor(&supervisor);
	Manager		manager;	supervisor.setSuccessor(&manager);
	Director	director;	manager.setSuccessor(&director);
	VP			vp;			director.setSuccessor(&vp);
	President	president;	vp.setSuccessor(&president);

	float data[] = { 10.01, 44.77, 111.88, 333.99, 555.22, 999.99, 1010.55 };
	for(size_t i=0; i<sizeof(data)/sizeof(*data); i++) {
		clientCode(&clerk, data[i]);
	}
	}

	cout << endl;
}

}

}

namespace homework {

/* Consider how to model decision making in a military chain of command.
 * Simple decisions get made by the junior officers,
 * harder ones by the senior officers.
 */

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

}

/* Consider how to model decision making in a military chain of command.
 * Simple decisions get made by the junior officers,
 * harder ones by the senior officers.
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
