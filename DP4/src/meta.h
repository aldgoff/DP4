/*
 * meta.h
 *
 *  Created on: Oct 18, 2014
 *      Author: aldgoff
 *
 * Desc: Apply principles of DP's to the class code.
 * 		 In particular, shouldn't have to add code in 5 places
 * 		 for each new design pattern - really? I'm teaching this stuff?!?
 */

#ifndef META_H_
#define META_H_

#define COUNT(x) (sizeof(x)/sizeof(*x))

class DesignPattern {
public:
	virtual ~DesignPattern() {}
public:
	virtual void problem() {
		cout << "<< desPat problem >>";
	}
	virtual void solution() {
		cout << "<< desPat solution >>";
	}
};
class Strategy : public DesignPattern {
public:
	virtual void problem() {
		cout << "<< Strategy problem >>";
	}
	virtual void solution() {
		cout << "<< Strategy solution >>";
	}
};
class Adapter : public DesignPattern {
public:
	virtual void problem() {
		cout << "<< Adapter problem >>";
	}
	virtual void solution() {
		cout << "<< Adapter solution >>";
	}
};
class Facade : public DesignPattern {
public:
	virtual void problem() {
		cout << "<< Facade problem >>";
	}
	virtual void solution() {
		cout << "<< Facade solution >>";
	}
};

void meta() {
	DesignPattern* desPats[] = {
		new Strategy,
		new Adapter,
		new Facade,
	};

	for(size_t i=0; i<COUNT(desPats); i++) {
		cout << i+1 << ") ";
		desPats[i]->problem();		cout << "\n";
		cout << i+1 << ") ";
		desPats[i]->solution();		cout << "\n";
		cout << "\n";
	}
}


#endif /* META_H_ */
