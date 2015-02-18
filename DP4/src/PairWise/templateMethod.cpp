#include "pairWise.h"

namespace pair_wise {







class TemplateMethod {	// If the steps are varying...
public:	virtual ~TemplateMethod() {};
public:
	void sameStep1() { cout << "  sameStep1\n"; };
	void sameStep2() { cout << "  sameStep2\n"; };
	virtual void diffStep3() { cout << "  diffStep3 - "; };
	void sameStep4() { cout << "  sameStep4\n"; };
	void run() {
		sameStep1();
		sameStep2();
		diffStep3();
		sameStep4();
	}
};

class Step3_thisWay : public TemplateMethod {
public:
	void diffStep3() {
		TemplateMethod::diffStep3();
		cout << "thisWay\n";
	}
};
class Step3_thatWay : public TemplateMethod {
public:
	void diffStep3() {
		TemplateMethod::diffStep3();
		cout << "thatWay\n";
	}
};
class Step3_yourWay : public TemplateMethod {
public:
	void diffStep3() {
		TemplateMethod::diffStep3();
		cout << "yourWay\n";
	}
};

void clientTemplateMethod() {
	TemplateMethod* steps[] = { new Step3_thisWay, new Step3_thatWay, new Step3_yourWay };
	for(size_t i=0; i<COUNT(steps); i++) {
		steps[i]->run();
	}
	cout << endl;
}

}
