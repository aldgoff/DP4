/*
 * iterator.h
 *
 * Desc: Access container elements sequentially w/o exposing the containers structure.
 *
 * Category: Behavioral
 *
 *  Created on: Sep 3, 2014
 *      Author: aldgoff
 *
 * URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Iterator
 * URL: http://www.dofactory.com/net/iterator-design-pattern
 * URL: http://sourcemaking.com/design_patterns/iterator
 * URL: http://sourcemaking.com/
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_

namespace traverse {

class Array {
	unsigned items[10];
public:
	Array() {
		for(int i=0; i<10; i++) {
			items[i] = i + 1;
		}
	}
public:
	unsigned min() {
		return 0;
	}
	unsigned max() {
		int x = 0;
		for(int i=0; i<10; i++) {
			if(x < (int)items[i])
				x = items[i];
		}
		return x;
	}
	int findFirstIndex(unsigned x) {
		for(int i=0; i<10; i++) {
			if(x == items[i])
				return i;
		}
		return -1;
	}
};
class List {
public:
	struct node {
		unsigned n;
		node*	 next;
	};
private:
	node items[10];
public:
	List() {
		for(int i=0; i<10; i++) {
			items[i].n = i + 1;
			items[i].next = (i<9)
			? &(items[i+1])
			: 0;
		}
	}
	List::node first() {
		return items[0];
	}
};
class Stack {
	unsigned items[10];
public:
	Stack() {
		for(int i=0; i<10; i++) {
			items[i] = i + 1;
		}
	}
};
// Seam point: Queue;


void demo() {
	cout << "<< Iterator problem >>\n";

	Array	array;
	cout << array.max() << endl;

	List	list;
	Stack	stack;
}

}

namespace iterator_pattern {

// Forward declarations.
class Container;

class Iterator {
protected:
	Container* container;
	int index;
public:
	Iterator(Container* container) : container(container), index(0) {}
	virtual ~Iterator() {}
public:
	virtual void first(){}
	virtual void next(){}
//	virtual bool isDone()=0;
//	virtual int current()=0;
};
class ArrayIter : public Iterator {
public:
	ArrayIter(Container* Array) : Iterator(Array) {}
};
class ListIter : public Iterator {};
class HashIter : public Iterator {};
class StackIter : public Iterator {};

class Container {};
class Array : public Container {
	int	array[10];
public:
	ArrayIter begin() {
		return ArrayIter(this);
	}
};
class List : public Container {};
class Hash : public Container {};
class Stack : public Container {};

class Algorithm {};
class Sort : public Algorithm {};
class Find : public Algorithm {};
class Merge : public Algorithm {};

void demo() {
	cout << "<< Iterator Solution >>\n";

	Array arrayObj;
	Array* arrayPtr = new Array;
	Container* arrayPoly = new Array;

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector<int>::iterator itv = v.begin();
	for(; itv!=v.end(); itv++) {
		cout << *itv << endl;
	}

	ArrayIter ita = arrayObj.begin();
}

}

namespace iterator_pattern2 {

// Forward declarations.
class ArrayIter;

class Container {};
class Array : public Container {
public:
//	ArrayIter* createIterator() const;
};
class List : public Container {};
class Hash : public Container {};
class Stack : public Container {};

class Iterator {
protected:
	Container* container;
	int index;
public:
	Iterator(Container* container) : container(container), index(0) {}
	virtual ~Iterator() {}
public:
	virtual void first()=0;
	virtual void next()=0;
//	virtual bool isDone()=0;
//	virtual int current()=0;
};
class ArrayIter : public Iterator {
public:
	ArrayIter(Array* container) : Iterator(container) {};
public:
	void first() {
		index = 0;
	}
	void next() {
		index++;
	}
};
class ListIter : public Iterator {};
class HashIter : public Iterator {};
class StackIter : public Iterator {};

//ArrayIter* Array::createIterator() {
////	return new ArrayIter(this);
//}

class Algorithm {};
class Sort : public Algorithm {};
class Find : public Algorithm {};
class Merge : public Algorithm {};

void demo() {
	cout << "<< Iterator solution >>\n";

//	Container* array = new Array;
//	Array array;
//	ArrayIter* aItr = array.createIterator();
//	ArrayIter aItr(array);
}

}

#endif /* ITERATOR_H_ */
