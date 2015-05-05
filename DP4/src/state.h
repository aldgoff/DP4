/*
 * state.h
 *
 * Desc: .
 *
 * Category: Behavioral
 *
 *  Created on: May 1, 2015
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#State
 *  	http://www.dofactory.com/net/state-design-pattern
 *  	http://sourcemaking.com/design_patterns/state
 */

#ifndef DP4_SRC_STATE_H_
#define DP4_SRC_STATE_H_

namespace lecture {

namespace state_legacy {

void demo() {
	cout << "<< legacy >>\n";
}

}

namespace state_problem {

void demo() {
	cout << "<< problem >>\n";
}

}

namespace state_solution {

class State;

class Context {
	State* state;
public:
	Context() : state(0) {}
	~Context() { cout << "~Context \n"; }
};

class State {
public:
	State() {}
	virtual ~State() { cout << "~State \n"; }
};
class ThisState : public State {};
class ThatState : public State {};
class YourState : public State {};

void clientCode() {

}

void demo() {
	cout << "<< solution >>\n";

	Context context;

	clientCode();
}

}

}

namespace homework {

namespace state_legacy {

void demo() {
	cout << "<< legacy >>\n";
}

}

namespace state_problem {

void demo() {
	cout << "<< problem >>\n";
}

}

namespace state_solution {

class State;
class Context;

class Context {
public:
	State* state;
public:
	Context(State* state);
	~Context();
public:
	void init();		// This/That/Your => This.
	void progress(Context* context);	// This => That => Your => Your.
	void regress() {	// Your => That => This => This.

	}
};

class State {
public:
	State() {}
	virtual ~State() { cout << "~State\n"; }
public:
	virtual void init() {
		cout << "  State.init()\n";
	}
	virtual void progress(Context* context) {
		cout << "  State.progress()\n";
	}
};
class ThisState : public State {
public:
	~ThisState() { cout << "~ThisState "; }
public:
	void init() {
		cout << "  ThisState.init()\n";
	}
	void progress(Context* context);
};
class ThatState : public State {
public:
	~ThatState() { cout << "~ThatState "; }
public:
	void init() {
		cout << "  ThatState.init()\n";
	}
	void progress(Context* context);
};
class YourState : public State {
public:
	~YourState() { cout << "~YourState "; }
public:
	void init() {
		cout << "  YourState.init()\n";
	}
	void progress(Context* context);
};

void ThisState::progress(Context* context) {
	cout << "  ThisState.progress()\n";
	delete context->state;
	context->state = new ThatState();
}

void YourState::progress(Context* context) {
	cout << "  ThatState.progress()\n";
	delete context->state;
	context->state = new YourState();
}

void ThatState::progress(Context* context) {
	cout << "  ThatState.progress()\n";
	delete context->state;
	context->state = new YourState();
}

Context::Context(State* state) : state(state) {}
Context::~Context() {
	delete state;
	cout << "~Context \n";
}
void Context::init() {		// This/That/Your => This.
	state->init();
}
void Context::progress(Context* context) {	// This => That => Your => Your.
	state->progress(this);
}


void clientCode(Context& context) {
	context.init();
	context.progress(&context);
	context.progress(&context);
}

void demo() {
	cout << "<< solution >>\n";

	Context context(new ThisState());

	clientCode(context);
}

}

}



#endif /* DP4_SRC_STATE_H_ */
