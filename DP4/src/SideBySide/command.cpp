#include "sideBySide.h"

namespace side_by_side {

class ReceiverA { public: void comply() { cout << "receiver A\n"; } };
class ReceiverB { public: void comply() { cout << "receiver B\n"; } };
class ReceiverC { public: void comply() { cout << "receiver C\n"; } };



class Command {			// If the requests are varying...


public: virtual ~Command() {}
public:
	virtual void execute() {}




};





class Request1 : public Command {
	ReceiverA*	rec;
public:
	void execute() { cout << "  Request action 1 on ";
	rec->comply(); }
public:
	Request1(ReceiverA* rec) : rec(rec) {}
};
class Request2 : public Command {
	ReceiverB*	rec;
public:
	void execute() { cout << "  Request action 2 on ";
	rec->comply(); }
public:
	Request2(ReceiverB* rec) : rec(rec) {}
};
class Request3 : public Command {
	ReceiverC*	rec;
public:
	void execute() { cout << "  Request action 3 on ";
	rec->comply(); }
public:
	Request3(ReceiverC* rec) : rec(rec) {}
};









void clientCommand() {
	Command* commands[] = { new Request1(new ReceiverA), new Request2(new ReceiverB), new Request3(new ReceiverC)};
	for(size_t i=0; i<COUNT(commands); i++) {
		commands[i]->execute();



	}
	cout << endl;
}

}
