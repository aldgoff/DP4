/*
 * adapter.h
 *
 * Desc: Adapt interfaces so classes can work together polymorphically.
 *
 * Category: Structural
 *
 *  Created on: Mar 8, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Adapter
 *  	http://www.dofactory.com/net/adapter-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter7
 *  	http://sourcemaking.com/design_patterns/adapter
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

namespace adapter_solution {

using namespace home_grown;

class Polygon : public ShapeInterfaceDraw {	// New code.
	commercial::Polygon poly;
public:
	void draw() { poly.display(); }
};
class Torus : public ShapeInterfaceDraw {
	commercial::Torus torus;
public:
	void draw() { torus.display(); }
};
class Bezel : public ShapeInterfaceDraw {
	commercial::Bezel bezel;
public:
	void draw() { bezel.display(); }
};

void demo() {
	vector<ShapeInterfaceDraw*> shapes;	// Old client code stays the same.
	shapes.push_back(new Point);
	shapes.push_back(new Line);
	shapes.push_back(new Rect);
	shapes.push_back(new Polygon);		// Just add new code.
	shapes.push_back(new Torus);
	shapes.push_back(new Bezel);

	for(size_t i=0; i<shapes.size(); i++) {	// Client code stays simple because
		shapes[i]->draw();					// API's have been converged.
	}

	for(size_t i=0; i<shapes.size(); i++) {	// Release allocated memory.
		delete shapes[i];
	}

	cout << endl;
}

}

#endif /* ADAPTER_H_ */
