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
 * URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Template_Method
 */

#ifndef TEMPLATEMETHOD_H_
#define TEMPLATEMETHOD_H_

typedef unsigned int uint;

/* Consider a company that has written a number of games, and plans more.
 * All of their games involve players taking turns.
 * Below is troubled code that 'represents' the historical development of their products.
 * Rewrite it using the Template Method design pattern to eliminate duplication.
 * Removing the structural duplication will facilitate faster development of new games.
 * Part of the challenge of design patterns is spotting when one is applicable.
 * This exercise has been deliberately designed to muddy the waters.
 * It is therefore more like what you will find in the wild versus the classroom.
 * Hint #1: you may want to review Stepanov's concept of uplift.
 * Hint #2: refactoring is your friend.
 */

namespace duplicated_skelaton {

void playGo() {
	cout << "  Setup Go board, 9-stone handicap.\n";
	cout << "     Black  White\n";

	short int turns = 0;
	unsigned short count = 0;
	while(count < 4) {
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
	while(n < 4) {
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

#define PLAYERS 2

void playCheckers() {
	cout << "  Setup Checker board.\n";
	cout << "     Red   Black\n";

	uint side = 0;
	uint moves = 0;
	while(moves < 4) {
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
	while(move < 9) {
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

void demo() {
	cout << "<< Template Method problem >>\n";

	playGo();
	playChess();
	playCheckers();
	playQuantumTicTacToe();
}

}

namespace templateMethod {

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
	cout << "<< Template Method solution >>\n";

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

#endif /* TEMPLATEMETHOD_H_ */