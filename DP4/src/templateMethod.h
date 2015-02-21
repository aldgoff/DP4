/*
 * templateMethod.h
 *
 * Desc: Define the skeleton of an algorithm.
 *
 * Category: Behavioral
 *
 *  Created on: May 10, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Template_Method
 *  	http://www.dofactory.com/net/template-method-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter19
 *  	http://sourcemaking.com/design_patterns/template_method
 */

#ifndef TEMPLATEMETHOD_H_
#define TEMPLATEMETHOD_H_

typedef unsigned int uint;

namespace lecture {

namespace template_method_common {

enum Alternatives {
	THIS,
	THAT,
	YOUR,
	// Seam point 1 - insert another alternative.
};

void sameStep1() { cout << "  Same step 1.\n"; }
void sameStep2() { cout << "   Same step 2.\n"; }
void thisStep3() { cout << "    Diff step 3 this way.\n"; }
void thatStep3() { cout << "    Diff step 3 that way.\n"; }
void yourStep3() { cout << "    Diff step 3 your way.\n"; }
// Seam point 2 - add another alternative.
void sameStep4() { cout << "     Same step 4.\n"; }

}

namespace template_method_legacy {

using namespace template_method_common;

void clientCode(Alternatives alt) {
	switch(alt) {
	case 0:
		sameStep1();	// Lots of duplication, but flow is clear.
		sameStep2();
		thisStep3();
		sameStep4();
		break;
	case 1:
		sameStep1();	// Process specified in multiple places.
		sameStep2();
		thatStep3();
		sameStep4();
		break;
	case 2:
		sameStep1();
		sameStep2();
		yourStep3();
		sameStep4();
		break;
						// Seam point 3 - insert another alternative.
	default:
	throw "OOPS";		// Requires error handling.
	break;
	}
}

void demo() {
	Alternatives alt[] = { THIS, THAT, YOUR };
	for(size_t i=0; i<sizeof(alt)/sizeof(*alt); i++) {
		clientCode(alt[i]);
	}

	cout << endl;
}

}

namespace template_method_problem {

using namespace template_method_common;

void clientCode(Alternatives alt) {
	sameStep1();
	sameStep2();
	switch(alt) {		// Avoids duplication, but flow is obscured.
	case 0:
		thisStep3();
		break;
	case 1:
		thatStep3();
		break;
	case 2:
		yourStep3();
		break;
						// Seam point 3 - add another alternative.
	default:
	throw "OOPS";		// Still requires error handling.
	break;
	}
	sameStep4();
}

void demo() {
	Alternatives alt[] = { THIS, THAT, YOUR };
	for(size_t i=0; i<sizeof(alt)/sizeof(*alt); i++) {
		clientCode(alt[i]);
	}

	cout << endl;
}

}

namespace template_method_solution {

class TemplateMethod {
public: virtual ~TemplateMethod() {}
public:
	void run() {		// Process specified in only one place.
		sameStep1();
		sameStep2();
		diffStep3();
		sameStep4();
	}
protected:
			void sameStep1() { cout << "  Same step 1.\n"; }
			void sameStep2() { cout << "   Same step 2.\n"; }
	virtual void diffStep3() { cout << "    Diff step 3.\n"; }
			void sameStep4() { cout << "     Same step 4.\n"; }
};
class Step3_ThisWay : public TemplateMethod {
public:
	void diffStep3() { cout << "    Diff step 3 this way.\n"; }
};
class Step3_ThatWay : public TemplateMethod {
public:
	void diffStep3() { cout << "    Diff step 3 that way.\n"; }
};
class Step3_YourWay : public TemplateMethod {
public:
	void diffStep3() { cout << "    Diff step 3 your way.\n"; }
};
// Seam point (only 1) - add another alternative.

void demo() {
	TemplateMethod* steps[] = {
		new Step3_ThisWay, new Step3_ThatWay, new Step3_YourWay
	};
	for(size_t i=0; i<sizeof(steps)/sizeof(*steps); i++) {
		steps[i]->run();
	}

	cout << endl;
}

}

}

namespace home_work {

/* Consider a 6 step process as implied by the legacy namespace below.
 * Optimization is the only difference between the processes.
 * Consider new specs (ala problem namespace below):
 * 	 Two more processes with different optimizations, critical and npc.
 *   For both of these the cleanup step must be better and different.
 * Refactor using the Template Method design pattern.
 */

namespace template_method_common {

bool morning() { return true; }

void fast() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  Fast optimized\n";
	cout << "  usual cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

void economic() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  Economic optimized\n";
	cout << "  usual cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

}

namespace template_method_new_specs {

using namespace template_method_common;

void critical() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  Critical optimized\n";
	cout << "  meticulous cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

void npc() {
	cout << "  setup\n";
	cout << "  schedule\n";
	if(morning())
		cout << "  highHeat\n";
	else
		cout << "  lowHeat\n";
	cout << "  NPC optimized\n";
	cout << "  meticulous cleanup\n";
	cout << "  putaway\n";
	cout << endl;
}

}

namespace template_method_legacy {

using namespace template_method_common;

void demo() {
	fast();
	economic();
}

}

namespace template_method_problem {

using namespace template_method_common;
using namespace template_method_new_specs;

void demo() {
	fast();
	economic();
	critical();
	npc();
}

}

namespace template_method_solution {

class TemplateMethod {
	bool morning() { return true; }
public: virtual ~TemplateMethod() {}
public:
	void run() {	// A 6 step process.
		setup();		// Most steps the same.
		schedule();
		if(morning())
			highHeat();
		else
			lowHeat();
		optimize();		// Must differ.
		cleanup();		// May differ.
		putaway();
		cout << endl;
	}
private:
	void setup()    { cout << "  setup\n"; }	// Same steps.
	void schedule() { cout << "  schedule\n"; }
	void highHeat() { cout << "  highHeat\n"; }
	void lowHeat()  { cout << "  lowHeat\n"; }
protected:
	virtual void optimize()=0;	// Subclasses must supply.
	virtual void cleanup() { cout << "  usual cleanup\n"; }	// Default behavior.
private:
	void putaway() { cout << "  putaway\n"; }	// Same steps.
};
class Fast : public TemplateMethod {
public:
	void optimize() { cout << "  Fast optimized\n"; }
};
class Economic : public TemplateMethod {
public:
	void optimize() { cout << "  Economic optimized\n"; }
};
class Critical : public TemplateMethod {
public:
	void optimize() { cout << "  Critical optimized\n"; }
	void cleanup()  { cout << "  detailed cleanup\n"; }
};
class NPC : public TemplateMethod {
public:
	void optimize() { cout << "  NPC optimized\n"; }
	void cleanup()  { cout << "  meticulous cleanup\n"; }
};

void demo() {
	TemplateMethod* process[] = {new Fast, new Economic, new Critical, new NPC};
	for(size_t i=0; i<sizeof(process)/sizeof(*process); i++) {
		process[i]->run();
	}
}

}

}

namespace experimental {

namespace template_method_common {

void client1() {
	cout << "   Same step 1.\n";
	cout << "   Usual step 2.\n";
	cout << "   Occasional step 3.\n";
	cout << "   Client 1 diff step 4.\n";
	cout << "   Step 5a.\n";
	cout << "   Step 5b.\n";
	cout << "   Same step 6.\n";
	cout << endl;
}
void client2() {
	cout << "   Same step 1.\n";
	cout << "   Usual step 2.\n";
	cout << "   Client 2 diff step 3.\n";
	cout << "   Client 2 diff step 4.\n";
	cout << "   Step 5a.\n";
	cout << "   Step 5b.\n";
	cout << "   Same step 6.\n";
	cout << endl;
}

}

namespace template_method_new_specs {

void client3() {
	cout << "   Same step 1.\n";
	cout << "   Unusual step 2.\n";
	cout << "   Client 3 diff step 3.\n";
	cout << "   Client 3 diff step 4.\n";
	cout << "   Option 2 step 5.\n";
	cout << "   Step 5b.\n";
	cout << "   Step 5a.\n";
	cout << "   Same step 6.\n";
	cout << endl;
}
void client4() {
	cout << "   Same step 1.\n";
	cout << "   Usual step 2.\n";
	cout << "   Client 4 diff step 3.\n";
	cout << "   Client 4 diff step 4.\n";
	cout << "   Step 5b.\n";
	cout << "   Step 5a.\n";
	cout << "   Same step 6.\n";
	cout << endl;
}

}

namespace template_method_legacy {

using namespace template_method_common;

void demo() {
	client1();
	client2();
}

}

namespace template_method_problem {

using namespace template_method_common;
using namespace template_method_new_specs;

void demo() {
	client1();
	client2();
	client3();
	client4();
}

}

namespace template_method_solution {

using namespace template_method_common;
using namespace template_method_new_specs;

class TemplateMethod {
public: virtual ~TemplateMethod() { cout << "  ** TM dtor.\n"; }
public:
	void run() {
		alwaysSameStep1();
		usuallySameStep2();
		occasionalSameStep3();
		alwaysDifferentStep4();
		twoOptionsStep5();
		alwaysSameStep6();
		cout << endl;
	}
private:
	void alwaysSameStep1() {				cout << "   Same step 1.\n";}
protected:
	virtual void usuallySameStep2() {		cout << "   Usual step 2.\n";}
	virtual void occasionalSameStep3() {	cout << "   Occasional step 3.\n";}
	virtual void alwaysDifferentStep4()=0;
	virtual void twoOptionsStep5() { order1Step5(); }
protected:
	void order1Step5 () { cout << "   Step 5a.\n   Step 5b.\n"; }
	void order2Step5 () { cout << "   Step 5b.\n   Step 5a.\n"; }
private:
	void alwaysSameStep6() {				cout << "   Same step 6.\n";	}
};

class Client1 : public TemplateMethod {
public:
	void alwaysDifferentStep4() { cout << "   Client 1 diff step 4.\n"; }
	void twoOptionsStep5() { order1Step5(); }
};
class Client2 : public TemplateMethod {
public:
	void occasionalSameStep3()	{ cout << "   Client 2 diff step 3.\n";}
	void alwaysDifferentStep4() { cout << "   Client 2 diff step 4.\n"; }
	void twoOptionsStep5() { order1Step5(); }
};
class Client3 : public TemplateMethod {
public:
	void usuallySameStep2() 	{ cout << "   Unusual step 2.\n";}
	void occasionalSameStep3()	{ cout << "   Client 3 diff step 3.\n";}
	void alwaysDifferentStep4() { cout << "   Client 3 diff step 4.\n"; }
	void twoOptionsStep5() { order2Step5(); }
};
class Client4 : public TemplateMethod {
public:
	void occasionalSameStep3()	{ cout << "   Client 4 diff step 3.\n";}
	void alwaysDifferentStep4() { cout << "   Client 4 diff step 4.\n"; }
	void twoOptionsStep5() { order2Step5(); }
};

void demo() {
	TemplateMethod* clients[] =  {
		new Client1(), new Client2(), new Client3(), new Client4()
	};
	for(size_t i=0; i<sizeof(clients)/sizeof(*clients); i++) {
		cout << "  Client " << i+1 << "\n";
		clients[i]->run();
	}

	for(size_t i=0; i<sizeof(clients)/sizeof(*clients); i++) {
		delete clients[i];
	}
	cout << endl;
}

}

}

namespace homework {

/* Consider a company that has written a number of games, and plans more.
 * All of their games involve players taking turns.
 * Below is troubled code that represents the historical development of their products.
 * Rewrite it using the Template Method design pattern to eliminate duplication.
 * Removing the structural duplication will facilitate faster development of new games.
 * Part of the challenge of design patterns is spotting when one is applicable.
 * This exercise has been deliberately designed to muddy the waters.
 * It is therefore more like what you will find in the wild versus the classroom.
 * Hint #1: you may want to review Stepanov's concept of uplift.
 * Hint #2: refactoring is your friend.
 * Hint #3: what is common (conceptually) between the games?
 */

namespace template_method_common {

void playGo() {
	cout << "  Setup Go board, 9-stone handicap.\n";
	cout << "     Black  White\n";

	short int turns = 0;
	unsigned short count = 0;
	while(count < 4) {	// For academic exercise, game over on move 4.
		if(turns == 0) ++count;
		turns = (turns+1) % 2;
		if(turns%2 == 1) {
			cout << "  " << count << ": place";
		}
		else {
			cout << "  place\n";
		}
	}

	cout << "\n  Black won.\n";
	cout << endl;
}

#define TWO 2

void playChess() {
	cout << "  Setup Chess board.\n";
	cout << "    White   Black\n";

	int play = 0;
	int n = 0;
	while(n < 4) {	// For academic exercise, game over on move 4.
		if(play == 0) ++n;
		play = (play+1) % TWO;
		if(play%TWO == 1)
			cout << "  " << n << ": move";
		else {
			cout << "  capture\n";
		}
	}

	cout << "\n  White won.\n";
	cout << endl;
}

}

namespace template_method_new_specs {

#define PLAYERS 2

void playCheckers() {
	cout << "  Setup Checker board.\n";
	cout << "     Red   Black\n";

	uint side = 0;
	uint moves = 0;
	while(moves < 4) {	// For academic exercise, game over on move 4.
		if(side == 0) ++moves;
		side = (side+1) % PLAYERS;
		if(side%PLAYERS == 1) {
			cout << "  " << moves << ": move";
			}
		else
			cout << "  jump\n";
	}

	cout << "\n  Red won.\n";
	cout << endl;
}

void playQuantumTicTacToe() {
	cout << "  Clear Quantum Tic-Tac-Toe board.\n";
	cout << "      X        O\n";

	short move = 0;
	while(move < 9) {	// For academic exercise, game over on move 9.
		++move;
		cout << "  " << move << ": " << move << "-" << (move)%9 + 1;
		if(move%2 == 0)
			cout << "\n";
		else
			cout << "  ";
	}

	cout << "\n  X won.\n";
	cout << endl;
}

}

namespace template_method_legacy {

using namespace template_method_common;

void demo() {
	playGo();
	playChess();
}

}

namespace template_method_problem {

using namespace template_method_common;
using namespace template_method_new_specs;

void demo() {
	playGo();
	playChess();
	playCheckers();
	playQuantumTicTacToe();
}

}

namespace template_method_solution {

/* What do all four games have in common?
 * 1) There is intialization.
 * 2) A loop that makes moves and tests for game over.
 * 3) A way to count moves.
 * 4) A way to determine which player moves next.
 * 5) Reporting the score.
 */

using namespace template_method_common;
using namespace template_method_new_specs;

class Game {
protected:
	uint movesCount;
public:
	Game() : movesCount(0) {}
	virtual ~Game() {}
protected:
	virtual void initializeGame()=0;
	virtual void move(uint move, uint turn)=0;
	virtual uint playsPerMove() { return 2; }
	virtual bool endOfGame()=0;
	virtual void printScore()=0;
public:
	void play() { // Template method.
		initializeGame();
		uint turn = 0;
		while(!endOfGame()) {
			if(turn == 0) ++movesCount;
			turn = (turn+1) % playsPerMove();
			move(movesCount, turn);
		}
		printScore();
	}
};
class Go : public Game {
public:
	Go() {}
	virtual ~Go() { cout << "  ~Go\n"; }
public:
	void initializeGame() {
		cout << "  Setup Go board, 9-stone handicap.\n";
		cout << "     Black  White\n";
	}
	void move(uint move, uint turn) {
		if(turn%2 == 1)	cout << "  " << movesCount << ": place";
		else			cout << "  place\n";
	}
	bool endOfGame() {
		return(movesCount==4);
	}
	void printScore() {
		cout << "\n  Black won.\n";
	}
};
class Chess : public Game {
public:
	Chess() {}
	virtual ~Chess() { cout << "  ~Chess\n"; }
public:
	void initializeGame() {
		cout << "  Setup Chess board.\n";
		cout << "    White   Black\n";
	}
	void move(uint move, uint turn) {
		if(turn%2 == 1)	cout << "  " << movesCount << ": move";
		else			cout << "  capture\n";
	}
	bool endOfGame() {
		return(movesCount==4);
	}
	void printScore() {
		cout << "\n  White won.\n";
	}
};
class Checkers : public Game {
public:
	Checkers() {}
	virtual ~Checkers() { cout << "  ~Checkers\n"; }
public:
	void initializeGame() {
		cout << "  Setup Checker board.\n";
		cout << "     Red   Black\n";
	}
	void move(uint move, uint turn) {
		if(turn%2 == 1)	cout << "  " << movesCount << ": move";
		else			cout << "  jump\n";
	}
	bool endOfGame() {
		return(movesCount==4);
	}
	void printScore() {
		cout << "\n  Red won.\n";
	}
};
class QuantumTicTacToe : public Game {
public:
	QuantumTicTacToe() {}
	virtual ~QuantumTicTacToe() { cout << "  ~QuantumTicTacToe\n"; }
public:
	void initializeGame() {
		cout << "  Clear Quantum Tic-Tac-Toe board.\n";
		cout << "      X        O\n";
	}
	void move(uint move, uint turn) {
		cout << "  " << move << ": " << move << "-" << (move)%9 + 1;
		if(move%2 == 0)	cout << "\n";
		else			cout << "  ";
	}
	uint playsPerMove() {
		return 1;
	}
	bool endOfGame() {
		return(movesCount==9);
	}
	void printScore() {
		cout << "\n  X won.\n";
	}
};

void demo() {
	Game* games[] = { new Go, new Chess, new Checkers, new QuantumTicTacToe };

	for(size_t i=0; i<sizeof(games)/sizeof(Game*); i++) {
		cout << endl;
		games[i]->play();
	}

	cout << endl;
	for(size_t i=0; i<sizeof(games)/sizeof(Game*); i++) {
		delete games[i];
	}
}

}

}

#endif /* TEMPLATEMETHOD_H_ */
