#include "sideBySide.h"

namespace side_by_side {







class DesignPattern {	// If an element is varying, use a Design Pattern.
public:
	void doSomething() { cout << "  Design Pattern\n"; }







};





class Element1 : public DesignPattern {






};
class Element2 : public DesignPattern {






};
class Element3 : public DesignPattern {






};









void clientDesignPattern() {
	DesignPattern* dp[] = { new Element1, new Element2, new Element3};
	for(size_t i=0; i<COUNT(dp); i++) {
		dp[i]->doSomething();



	}
	cout << endl;
}

}
