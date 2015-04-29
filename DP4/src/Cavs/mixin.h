/*
 * mixin.h
 *
 *  Created on: Apr 28, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_CAVS_MIXIN_H_
#define DP4_SRC_CAVS_MIXIN_H_


namespace mixin {

class Super {
public: virtual ~Super() {}
	virtual void samiam() {}
};

template<size_t N>
class Terived : public Super {
public:
	enum { size = N };
public:
	virtual void samiam() {
		cout << "  samiam(" << size << ") doing something interesting...\n";
	}
};

void demo() {
	cout << "<< mixin >>\n";

	Super* item = new Terived<5>;

	item->samiam();
}

}


#endif /* DP4_SRC_CAVS_MIXIN_H_ */
