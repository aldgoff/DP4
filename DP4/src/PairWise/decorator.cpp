#include "pairWise.h"

namespace pair_wise {

class Client {};

class Decorator : public Client {	// If the options are varying...
protected: Client* decoration;




};

class Option1 : public Decorator {
public:
	Option1(Client* decorator) { cout << "  Option1\n"; }
};
class Option2 : public Decorator {
public:
	Option2(Client* decorator) { cout << "  Option2\n"; }
};
class Option3 : public Decorator {
public:
	Option3(Client* decorator) { cout << "  Option3\n"; }
};









void clientDecorator() {
	Client simpleClient;
	Option1 opt1(&simpleClient);
	Option2 opt2(&opt1);
	Option3 opt3(&opt2);



	cout << endl;
}

}
